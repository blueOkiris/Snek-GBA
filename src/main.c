#include <gba.h>
#include <sprites.h>
#include <game.h>

#define CLOCKS_PER_SEC  262144

int main(void) {
    load_sprites();
    set_palletes();
    reset();
    
    // Set up a timer to be 1:1 with clock
    volatile uint16_t *tmr1_ctrl = (volatile uint16_t *) 0x04000102;
    volatile uint16_t *tmr1_data = (volatile uint16_t *) 0x04000100;
    *tmr1_ctrl = 0x0081; // b8 - en, b6 - intrp, b2 - cascade, b1-0 - freq
    *tmr1_data = 0;
    double delta_ms = 0.1667;
    while(1) {
        // Skip past vblanks and vdraws
        while(REG_DISPLAY_VCONT >= 160);
        while(REG_DISPLAY_VCONT < 160);
        
        g_state.keys = ~REG_KEY_INPUT & KEY_ANY;
        if(g_state.keys & KEY_UP) {
            g_state.plyr_dir = UP;
        } else if(g_state.keys & KEY_DOWN) {
            g_state.plyr_dir = DOWN;
        } else if(g_state.keys & KEY_LEFT) {
            g_state.plyr_dir = LEFT;
        } else if(g_state.keys & KEY_RIGHT) {
            g_state.plyr_dir = RIGHT;
        }
        
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
        set_obj_pos(
            g_state.plyr_head_obj,
            (int) g_state.plyr_head_x, (int) g_state.plyr_head_y
        );
        g_state.plyr_head_obj->attr2 = g_state.plyr_dir + 1;
        
        delta_ms = *tmr1_data / (float) CLOCKS_PER_SEC;
        *tmr1_ctrl = 0;
        *tmr1_data = 0x0000;
        *tmr1_ctrl = 0x0081;
    }
    
    return 0;
}