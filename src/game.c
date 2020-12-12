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
    g_state.plyr_head_obj->attr2 = SNAKE_HEAD_RIGHT;
    set_obj_pos(
        g_state.plyr_head_obj,
        (int) g_state.plyr_head_x, (int) g_state.plyr_head_y
    );
    g_state.plyr_tile_x = ((int) g_state.plyr_head_x / 8) * 8;
    g_state.plyr_tile_y = ((int) g_state.plyr_head_y / 8) * 8;
    
    g_state.num_bodies = 1;
    g_state.max_bodies = 100;
    
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
    
    REG_DISPLAY = 0x1000 | 0x0040; // set display parameters to enable objects
    g_state.keys = 0;
}
