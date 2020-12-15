#include <stdlib.h>
#include <gba.h>
#include <graphics.h>
#include <game.h>

game_state_t g_state;

void reset(void) {
    g_state.plyr_width = 8;
    g_state.plyr_height = 8;
    g_state.plyr_spd = 64;
    g_state.plyr_dir = RIGHT;
    
    g_state.plyr_head_x = 112;
    g_state.plyr_head_y = 72;
    g_state.plyr_head_obj = &OAM[0];
    g_state.plyr_head_obj->attr0 = 0; // 4bpp, square
    g_state.plyr_head_obj->attr1 = 0; // 8x8 size when square
    g_state.plyr_head_obj->attr2 = SNAKE_HEAD_RIGHT;
    set_obj_pos(
        g_state.plyr_head_obj,
        (int) g_state.plyr_head_x, (int) g_state.plyr_head_y
    );
    g_state.plyr_tile_x = ((int) g_state.plyr_head_x / 8) * 8;
    g_state.plyr_tile_y = ((int) g_state.plyr_head_y / 8) * 8;
    
    g_state.num_bodies = 2;
    g_state.max_bodies = 63;
    
    g_state.plyr_bodies[0] = &OAM[1];
    g_state.plyr_bodies[0]->attr0 = 0;
    g_state.plyr_bodies[0]->attr1 = 0;
    g_state.plyr_bodies[0]->attr2 = BLANK;
    g_state.plyr_bodies_x[0] = 0;
    g_state.plyr_bodies_y[0] = 0;
    set_obj_pos(g_state.plyr_bodies[0], 0, 0);
    for(int i = 1; i < g_state.num_bodies + 1; i++) {
        g_state.plyr_bodies[i] = &OAM[i + 1];
        g_state.plyr_bodies[i]->attr0 = 0; // 4bpp, square
        g_state.plyr_bodies[i]->attr1 = 0; // 8x8 size when square
        g_state.plyr_bodies[i]->attr2 = SNAKE_BODY;
        
        g_state.plyr_bodies_x[i] = g_state.plyr_tile_x - 8 * i;
        g_state.plyr_bodies_y[i] = g_state.plyr_tile_y;
        
        set_obj_pos(
            g_state.plyr_bodies[i],
            (int) g_state.plyr_bodies_x[i], (int) g_state.plyr_bodies_y[i]
        );
    }
    for(int i = g_state.num_bodies + 1; i < g_state.max_bodies + 1; i++) {
        g_state.plyr_bodies[i] = &OAM[i + 1];
        g_state.plyr_bodies[i]->attr0 = 0;
        g_state.plyr_bodies[i]->attr1 = 0;
        g_state.plyr_bodies[i]->attr2 = BLANK;
        
        g_state.plyr_bodies_x[i] = 0;
        g_state.plyr_bodies_y[i] = 0;
        
        set_obj_pos(g_state.plyr_bodies[i], 0, 0);
    }
    
    g_state.frog = &OAM[g_state.max_bodies + 2];
    g_state.frog->attr0 = 0;
    g_state.frog->attr1 = 0;
    g_state.frog->attr2 = FROG;
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
    
    g_state.score = 0;
    for(int i = 0; i < 10; i++) {
        g_state.score_display[i] = &OAM[g_state.max_bodies + 3 + i];
        g_state.score_display[i]->attr0 = 0;
        g_state.score_display[i]->attr1 = 0;
        g_state.score_display[i]->attr2 = DIGIT_OFFSET;
        set_obj_pos(g_state.score_display[i], 80 - 8 * i, 0);
    }
    display_score();
    
    // Set display parameters
    REG_DISPLAY = VIDEO_MODE0 | OBJ_ENABLE | MAP_MODE_1D | BG0_EN | BG1_EN;
    g_state.keys = 0;
}

void display_score() {
    int score = g_state.score;
    for(int i = 0; i < 10; i++) {
        int digit = score % 10;
        score /= 10;
        g_state.score_display[i]->attr2 = DIGIT_OFFSET + digit;
    }
}
