#include <gba.h>
#include <game.h>

int main(void) {
    set_sprites();
    set_palletes();
    reset();
    
    while(1) {
        // Skip past vblanks and vdraws
        while(REG_DISPLAY_VCONT >= 160);
        while(REG_DISPLAY_VCONT < 160);
        
        g_state.keys = ~REG_KEY_INPUT & KEY_ANY;
        
        // TODO: Separate physics from framerate
        int player_max_clamp_y = SCREEN_HEIGHT - g_state.player_height;
        if(g_state.keys & KEY_UP) {
            g_state.player_y = clamp(
                g_state.player_y - g_state.player_vel, 0, player_max_clamp_y
            );
            set_obj_pos(g_state.player_obj, g_state.player_x, g_state.player_y);
        } else if(g_state.keys & KEY_DOWN) {
            g_state.player_y = clamp(
                g_state.player_y + g_state.player_vel, 0, player_max_clamp_y
            );
            set_obj_pos(g_state.player_obj, g_state.player_x, g_state.player_y);
        }
    }
    
    return 0;
}