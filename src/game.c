#include <gba.h>
#include <sprites.h>
#include <game.h>

game_state_t g_state;

void set_palletes(void) {
    OBJ_PALLETE0[1] = color(0x00, 0x00, 0x00); // black
    OBJ_PALLETE0[2] = color(0x1F, 0x1F, 0x1F); // white
    OBJ_PALLETE0[3] = color(0x11, 0x08, 0x00); // orange-brown
    OBJ_PALLETE0[4] = color(0x1F, 0x14, 0x00); // gold
    OBJ_PALLETE0[5] = color(0x11, 0x00, 0x00); // maroon
}

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
    g_state.plyr_head_obj->attr2 = 1; // 1st tile in block four with pallete 0
    set_obj_pos(
        g_state.plyr_head_obj,
        (int) g_state.plyr_head_x, (int) g_state.plyr_head_y
    );
    
    REG_DISPLAY = 0x1000 | 0x0040; // set display parameters to enable objects
    g_state.keys = 0;
}
