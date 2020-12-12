#include <stdlib.h>
#include <gba.h>
#include <graphics.h>
#include <game.h>

#define CLOCKS_PER_SEC  262144

int main(void) {
    // Set up a timer to be 1:1 with clock
    volatile uint16_t *tmr0_ctrl = (volatile uint16_t *) 0x04000102;
    volatile uint16_t *tmr0_data = (volatile uint16_t *) 0x04000100;
    volatile uint16_t *tmr1_ctrl = (volatile uint16_t *) 0x04000106;
    volatile uint16_t *tmr1_data = (volatile uint16_t *) 0x04000104;
    
    load_background();
    load_sprites();
    set_palletes();
    
    reset();
    
    *tmr0_ctrl = 0;
    *tmr0_data = 0;
    *tmr0_ctrl = 0x0081; // b8 - en, b6 - intrp, b2 - cascade, b1-0 - freq
    
    int room = TITLE;
    char seeded = 0;
    *tmr1_data = 0;
    *tmr1_ctrl = 0x0083;
    
    double delta_ms = 0.1667;
    while(1) {
        /* vsync stopped working here for some reason??? */
        // Skip past vblanks and vdraws
        //while(REG_DISPLAY_VCONT >= 160);
        //while(REG_DISPLAY_VCONT < 160);
        
        g_state.keys = ~REG_KEY_INPUT & KEY_ANY;
        
        if(room == TITLE) {
            REG_BG1_CONTROL = 0x0200; // Place title in front
            
            g_state.plyr_head_obj->attr2 = BLANK;
            for(int i = 0; i < g_state.max_bodies + 1; i++) {
                g_state.plyr_bodies[i]->attr2 = BLANK;
            }
            g_state.frog->attr2 = BLANK;
            
            if(g_state.keys & KEY_START) {
                while(g_state.keys & KEY_START) {
                    g_state.keys = ~REG_KEY_INPUT & KEY_ANY;
                }
                REG_BG1_CONTROL = 0x0202; // Place title behind
                
                if(!seeded) {
                    srand(*tmr1_data);
                    
                    *tmr1_ctrl = 0;
                    seeded = 1;
                }
                
                room = GAME;
                reset();
            }
        } else if(room == GAME) {
            if(g_state.keys & KEY_START) {
                while(g_state.keys & KEY_START) {
                    g_state.keys = ~REG_KEY_INPUT & KEY_ANY;
                }
                room = PAUSED;
            }
            if(g_state.keys & KEY_SELECT) {
                room = TITLE;
            }
            
            // Update direction            
            if(g_state.keys & KEY_UP && g_state.plyr_dir != DOWN) {
                g_state.plyr_dir = UP;
            } else if(g_state.keys & KEY_DOWN && g_state.plyr_dir != UP) {
                g_state.plyr_dir = DOWN;
            } else if(g_state.keys & KEY_LEFT && g_state.plyr_dir != RIGHT) {
                g_state.plyr_dir = LEFT;
            } else if(g_state.keys & KEY_RIGHT && g_state.plyr_dir != LEFT) {
                g_state.plyr_dir = RIGHT;
            }
            
            // Move
            switch(g_state.plyr_dir) {
                case UP:
                    g_state.plyr_head_y = clamp(
                        g_state.plyr_head_y - delta_ms * g_state.plyr_spd,
                        0, SCREEN_HEIGHT - 8
                    );
                    break;
                case DOWN:
                    g_state.plyr_head_y = clamp(
                        g_state.plyr_head_y + delta_ms * g_state.plyr_spd,
                        0, SCREEN_HEIGHT - 8
                    );
                    break;
                case LEFT:
                    g_state.plyr_head_x = clamp(
                        g_state.plyr_head_x - delta_ms * g_state.plyr_spd,
                        0, SCREEN_WIDTH - 8
                    );
                    break;
                case RIGHT:
                    g_state.plyr_head_x = clamp(
                        g_state.plyr_head_x + delta_ms * g_state.plyr_spd,
                        0, SCREEN_WIDTH - 8
                    );
                    break;
            }
            
            int new_tile_x = ((int) g_state.plyr_head_x / 8) * 8;
            int new_tile_y = ((int) g_state.plyr_head_y / 8) * 8;
            
            // When reaching a new tile
            if(g_state.plyr_tile_x != new_tile_x
                    || g_state.plyr_tile_y != new_tile_y) {
                // Update all positions
                g_state.plyr_bodies_x[0] = g_state.plyr_tile_x;
                g_state.plyr_bodies_y[0] = g_state.plyr_tile_y;
                set_obj_pos(
                    g_state.plyr_bodies[0],
                    g_state.plyr_bodies_x[0] - 8, g_state.plyr_bodies_y[0] - 8
                );
                
                for(int i = g_state.max_bodies; i >= 1; i--) {
                    g_state.plyr_bodies_x[i] = g_state.plyr_bodies_x[i - 1];
                    g_state.plyr_bodies_y[i] = g_state.plyr_bodies_y[i - 1];
                    set_obj_pos(
                        g_state.plyr_bodies[i],
                        g_state.plyr_bodies_x[i], g_state.plyr_bodies_y[i]
                    );
                }
                
                g_state.plyr_tile_x = new_tile_x;
                g_state.plyr_tile_y = new_tile_y;
                set_obj_pos(
                    g_state.plyr_head_obj,
                    g_state.plyr_tile_x, g_state.plyr_tile_y
                );
            }
            
            g_state.plyr_head_obj->attr2 = g_state.plyr_dir + 1;
            
            // Eat frog
            if(g_state.frog_x == g_state.plyr_tile_x
                    && g_state.frog_y == g_state.plyr_tile_y) {
                // Move frog
                g_state.frog_x = (rand() % (240 / 8 - 2) + 1) * 8;
                for(int i = 1; i < g_state.num_bodies + 1; i++) {
                    if(g_state.frog_x == g_state.plyr_bodies_x[i]
                            || g_state.frog_x == g_state.plyr_head_x) {
                        g_state.frog_x = (rand() % (240 / 8 - 2) + 1) * 8;
                        i = 1;
                    }
                }
                g_state.frog_y = (rand() % (160 / 8 - 2) + 1) * 8;
                for(int i = 1; i < g_state.num_bodies + 1; i++) {
                    if(g_state.frog_y == g_state.plyr_bodies_x[i]
                            || g_state.frog_y == g_state.plyr_head_y) {
                        g_state.frog_y = (rand() % (160 / 8 - 2) + 1) * 8;
                        i = 1;
                    }
                }
                set_obj_pos(g_state.frog, g_state.frog_x, g_state.frog_y);
                
                // Score
                g_state.num_bodies++;
                if(g_state.num_bodies >= g_state.max_bodies + 1) {
                    // Reset at max bodies and get a bonus
                    g_state.num_bodies = 2;
                    for(int i = g_state.num_bodies + 1;
                            i < g_state.max_bodies + 1; i++) {
                        g_state.plyr_bodies[i]->attr2 = BLANK;
                    }
                    g_state.score += 500;
                }
                g_state.plyr_bodies[g_state.num_bodies]->attr2 = SNAKE_BODY;
                g_state.score += 1;
                display_score();
            }
            
            // Die
            if(g_state.plyr_tile_x == 0
                    || g_state.plyr_tile_x == SCREEN_WIDTH - 8
                    || g_state.plyr_tile_y == 0
                    || g_state.plyr_tile_y == SCREEN_HEIGHT - 8) {
                room = DEATH;
            }
            for(int i = 1; i < g_state.num_bodies + 1; i++) {
                if(g_state.plyr_bodies_x[i] == g_state.plyr_tile_x
                        && g_state.plyr_bodies_y[i] == g_state.plyr_tile_y) {
                    room = DEATH;
                }
            }
        } else if(room == PAUSED) {
            if(g_state.keys & KEY_START) {
                while(g_state.keys & KEY_START) {
                    g_state.keys = ~REG_KEY_INPUT & KEY_ANY;
                }
                room = GAME;
            }
            if(g_state.keys & KEY_SELECT) {
                room = TITLE;
            }
        } else if(room == DEATH) {
            REG_BG1_CONTROL = 0x0301; // Place dead in front
            
            g_state.plyr_head_obj->attr2 = BLANK;
            for(int i = 0; i < g_state.max_bodies + 1; i++) {
                g_state.plyr_bodies[i]->attr2 = BLANK;
            }
            g_state.frog->attr2 = BLANK;
            
            if(g_state.keys & KEY_START) {
                while(g_state.keys & KEY_START) {
                    g_state.keys = ~REG_KEY_INPUT & KEY_ANY;
                }
                room = TITLE;
            }
        }
        
        delta_ms = *tmr0_data / (float) CLOCKS_PER_SEC;
        *tmr0_ctrl = 0;
        *tmr0_data = 0x0000;
        *tmr0_ctrl = 0x0081;
    }
    
    return 0;
}