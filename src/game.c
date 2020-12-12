#include <gba.h>
#include <game.h>

game_state_t g_state;

void set_sprites(void) {
    // 8x32 paddle sprite and 8x8 ball sprite
    volatile uint16_t *paddle_tile_mem = (uint16_t *) TILE_MEM[4][1];
    volatile uint16_t *ball_tile_mem = (uint16_t *) TILE_MEM[4][5];
    
    // Give them palletes
    for(int i = 0; i < 4 * (sizeof(tile_4bpp_t) / 2); ++i) {
        paddle_tile_mem[i] = 0x1111; // 0x0001_0001_0001_0001 - 4 bits 1st color
    }
    for(int i = 0; i < (sizeof(tile_4bpp_t) / 2); ++i) {
        ball_tile_mem[i] = 0x2222; // 4 bits of pallete 2nd color
    }
    
    // Copy to oam
    g_state.player_obj = &OAM[0];
    g_state.player_obj->attr0 = 0x8000; // 4bpp, tall shape
    g_state.player_obj->attr1 = 0x4000; // 8x32 size when tall shape
    g_state.player_obj->attr2 = 1; // Start 1st tile in block 4 w pallete 0
    
    g_state.ball_obj = &OAM[1];
    g_state.ball_obj->attr0 = 0; // 4bpp, square
    g_state.ball_obj->attr1 = 0; // 8x8 size when square
    g_state.ball_obj->attr2 = 5; // 5th tile in block four with pallete 0
}

void set_palletes(void) {
    OBJ_PALLETE0[1] = color(0x1F, 0x1F, 0x1F); // white
    OBJ_PALLETE0[2] = color(0x1F, 0x00, 0x1F); // magenta
}

void reset(void) {
    g_state.player_width = 8;
    g_state.player_height = 32;
    g_state.ball_width = 8;
    g_state.ball_height = 8;
    
    g_state.player_vel = 2;
    g_state.ball_vel_x = 2;
    g_state.ball_vel_y = 2;
    
    g_state.player_x = 5;
    g_state.player_y = 96;
    g_state.ball_x = 22;
    g_state.ball_y = 96;
    
    set_obj_pos(g_state.player_obj, g_state.player_x, g_state.player_y);
    set_obj_pos(g_state.ball_obj, g_state.ball_x, g_state.ball_y);
    
    REG_DISPLAY = 0x1000 | 0x0040; // set display parameters to enable objects
    g_state.keys = 0;
}
