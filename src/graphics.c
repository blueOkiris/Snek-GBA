#include <gba.h>
#include <graphics.h>

/*
 * Pallete 0 colors will be:
 * 1 - black
 * 2 - white
 * 3 - brownish orange
 * 4 - golden-rod
 * 5 - red
 */
uint16_t spr_snake_head_up[sizeof(tile_4bpp_t) / 2] = {
    0x0003, 0x3000,
    0x0033, 0x3300,
    0x0313, 0x3130,
    0x0334, 0x3330,
    0x4523, 0x3253,
    0x3523, 0x4253,
    0x3333, 0x3343,
    0x0343, 0x3330
};
uint16_t spr_snake_head_down[sizeof(tile_4bpp_t) / 2] = {
    0x0333, 0x3430,
    0x3433, 0x3333,
    0x3524, 0x3253,
    0x3523, 0x3254,
    0x0333, 0x4330,
    0x0313, 0x3130,
    0x0033, 0x3300,
    0x0003, 0x3000
};
uint16_t spr_snake_head_left[sizeof(tile_4bpp_t) / 2] = {
    0x0334, 0x0000,
    0x3355, 0x3300,
    0x4322, 0x3130,
    0x3333, 0x4333,
    0x3343, 0x3333,
    0x3322, 0x3130,
    0x3455, 0x3300,
    0x0333, 0x0000
};
uint16_t spr_snake_head_right[sizeof(tile_4bpp_t) / 2] = {
    0x0000, 0x3330,
    0x0033, 0x5543,
    0x0313, 0x2233,
    0x3333, 0x3433,
    0x3334, 0x3333,
    0x0313, 0x2235,
    0x0033, 0x5533,
    0x0000, 0x4330,
};
uint16_t spr_snake_body[sizeof(tile_4bpp_t) / 2] = {
    0x0011, 0x4300,
    0x0433, 0x2230,
    0x3533, 0x3223,
    0x3533, 0x3313,
    0x3553, 0x3331,
    0x3555, 0x3351,
    0x0355, 0x5530,
    0x0034, 0x3300
};

uint16_t spr_blank[sizeof(tile_4bpp_t) / 2] = {
    0x0000, 0x0000,
    0x0000, 0x0000,
    0x0000, 0x0000,
    0x0000, 0x0000,
    0x0000, 0x0000,
    0x0000, 0x0000,
    0x0000, 0x0000,
    0x0000, 0x0000
};

uint16_t spr_frog[sizeof(tile_4bpp_t) / 2] = {
    0x0710, 0x0170,
    0x7677, 0x7767,
    0x7277, 0x7727,
    0x0799, 0x9970,
    0x0177, 0x7710,
    0x1877, 0x7781,
    0x1878, 0x8781,
    0x8871, 0x1788
};

void load_sprites(void) {
    volatile uint16_t *snake_head_up_tile =
        (uint16_t *) TILE_MEM[4][SNAKE_HEAD_UP];
    volatile uint16_t *snake_head_down_tile =
        (uint16_t *) TILE_MEM[4][SNAKE_HEAD_DOWN];
    volatile uint16_t *snake_head_left_tile =
        (uint16_t *) TILE_MEM[4][SNAKE_HEAD_LEFT];
    volatile uint16_t *snake_head_right_tile =
        (uint16_t *) TILE_MEM[4][SNAKE_HEAD_RIGHT];
    volatile uint16_t *snake_body_tile = (uint16_t *) TILE_MEM[4][SNAKE_BODY];
    volatile uint16_t *blank_tile = (uint16_t *) TILE_MEM[4][BLANK];
    volatile uint16_t *frog = (uint16_t *) TILE_MEM[4][FROG];
    for(int i = 0; i < sizeof(tile_4bpp_t) / 2; i += 2) {
        snake_head_up_tile[i] = spr_snake_head_up[i + 1];
        snake_head_up_tile[i + 1] = spr_snake_head_up[i];
        snake_head_down_tile[i] = spr_snake_head_down[i + 1];
        snake_head_down_tile[i + 1] = spr_snake_head_down[i];
        snake_head_left_tile[i] = spr_snake_head_left[i + 1];
        snake_head_left_tile[i + 1] = spr_snake_head_left[i];
        snake_head_right_tile[i] = spr_snake_head_right[i + 1];
        snake_head_right_tile[i + 1] = spr_snake_head_right[i];
        
        snake_body_tile[i] = spr_snake_body[i + 1];
        snake_body_tile[i + 1] = spr_snake_body[i];
        
        blank_tile[i] = spr_blank[i + 1];
        blank_tile[i + 1] = spr_blank[i];
        
        frog[i] = spr_frog[i + 1];
        frog[i + 1] = spr_frog[i];
    }
}

uint16_t tile_checkered[sizeof(tile_4bpp_t) / 2] = {
    0x1111, 0x6666,
    0x1111, 0x6666,
    0x1111, 0x6666,
    0x1111, 0x6666,
    0x6666, 0x1111,
    0x6666, 0x1111,
    0x6666, 0x1111,
    0x6666, 0x1111
};
uint16_t tile_grass[sizeof(tile_4bpp_t) / 2] = {
    0x2345, 0x3452,
    0x4523, 0x5234,
    0x2453, 0x4532,
    0x5324, 0x3245,
    0x3452, 0x4523,
    0x4532, 0x5324,
    0x4523, 0x4523,
    0x2345, 0x5324
};
uint16_t tile_wall[sizeof(tile_4bpp_t) / 2] = {
    0x8688, 0x8688,
    0x7677, 0x7677,
    0x7677, 0x7677,
    0x6666, 0x6666,
    0x6886, 0x8886,
    0x6776, 0x7776,
    0x6776, 0x7776,
    0x6666, 0x6666
};

uint16_t tile_snek_s[sizeof(tile_4bpp_t) / 2] = {
    0x0011, 0x1100,
    0x0100, 0x0010,
    0x0000, 0x0100,
    0x0001, 0x1000,
    0x0010, 0x0000,
    0x0100, 0x0000,
    0x0100, 0x0010,
    0x0011, 0x1100
};

uint16_t tile_snek_n[sizeof(tile_4bpp_t) / 2] = {
    0x1000, 0x0001,
    0x1000, 0x0011,
    0x1000, 0x0101,
    0x1000, 0x1001,
    0x1001, 0x0001,
    0x1010, 0x0001,
    0x1100, 0x0001,
    0x1000, 0x0001
};

uint16_t tile_snek_e[sizeof(tile_4bpp_t) / 2] = {
    0x0111, 0x1111,
    0x0000, 0x0001,
    0x0000, 0x0001,
    0x0000, 0x0001,
    0x0001, 0x1111,
    0x0000, 0x0001,
    0x0000, 0x0001,
    0x0111, 0x1111
};

uint16_t tile_snek_k[sizeof(tile_4bpp_t) / 2] = {
    0x0010, 0x0001,
    0x0010, 0x0001,
    0x0001, 0x0001,
    0x0001, 0x0001,
    0x0000, 0x1111,
    0x0001, 0x0001,
    0x0010, 0x0001,
    0x0010, 0x0001
};

void load_background(void) {
    // Load bg into character memory
    volatile uint16_t *checker = (uint16_t *) TILE_MEM[0][1];
    volatile uint16_t *grass = (uint16_t *) TILE_MEM[0][2];
    volatile uint16_t *wall = (uint16_t *) TILE_MEM[0][3];
    volatile uint16_t *snek_s = (uint16_t *) TILE_MEM[0][4];
    volatile uint16_t *snek_n = (uint16_t *) TILE_MEM[0][5];
    volatile uint16_t *snek_e = (uint16_t *) TILE_MEM[0][6];
    volatile uint16_t *snek_k = (uint16_t *) TILE_MEM[0][7];
    for(int i = 0; i < sizeof(tile_4bpp_t) / 2; i += 2) {
        checker[i] = tile_checkered[i + 1];
        checker[i + 1] = tile_checkered[i];
        grass[i] = tile_grass[i + 1];
        grass[i + 1] = tile_grass[i];
        wall[i] = tile_wall[i + 1];
        wall[i + 1] = tile_wall[i];
        snek_s[i] = tile_snek_s[i + 1];
        snek_s[i + 1] = tile_snek_s[i];
        snek_n[i] = tile_snek_n[i + 1];
        snek_n[i + 1] = tile_snek_n[i];
        snek_e[i] = tile_snek_e[i + 1];
        snek_e[i + 1] = tile_snek_e[i];
        snek_k[i] = tile_snek_k[i + 1];
        snek_k[i + 1] = tile_snek_k[i];
    }
    
    // Load tile map into screenblock 8
    volatile uint16_t *map0 = (uint16_t *) SCREEN_BLOCK_MEM[1];
    volatile uint16_t *map1 = (uint16_t *) SCREEN_BLOCK_MEM[2];
    for(int row = 0; row < 32; row++) {
        for(int col = 0; col < 32; col++) {
            if(row == 0 || row == 19 || col == 0 || col == 29) {
                map0[row * 32 + col] = 3;
            } else {
                map0[row * 32 + col] = 2;
            }
        }
    }
    map1[10 * 32 + 15 - 3] = 4;
    map1[10 * 32 + 15 - 1] = 5;
    map1[10 * 32 + 15 + 1] = 6;
    map1[10 * 32 + 15 + 3] = 7;
    
    /*
     * Enable background
     * 
     * Size 00, Screen Block 1, Color Mode 0, Tile Block 0, Depth 0
     * 0000 0001 0000 000
     */
    REG_BG0_CONTROL = 0x0101;
    REG_BG1_CONTROL = 0x0200;
}

void set_palletes(void) {
    BG_PALLETE0[1] = color(0x1F, 0x1F, 0x1F); // white
    BG_PALLETE0[2] = color(0x02, 0x07, 0x02); // dark green
    BG_PALLETE0[3] = color(0x00, 0x0D, 0x00); // green
    BG_PALLETE0[4] = color(0x06, 0x0E, 0x07); // alt green
    BG_PALLETE0[5] = color(0x00, 0x15, 0x01); // light green
    BG_PALLETE0[6] = color(0x00, 0x00, 0x00); // black
    BG_PALLETE0[7] = color(0x0A, 0x04, 0x00); // red-brown
    BG_PALLETE0[8] = color(0x11, 0x00, 0x00); // maroon
    
    OBJ_PALLETE0[1] = color(0x00, 0x00, 0x00); // black
    OBJ_PALLETE0[2] = color(0x1F, 0x1F, 0x1F); // white
    OBJ_PALLETE0[3] = color(0x11, 0x08, 0x00); // orange-brown
    OBJ_PALLETE0[4] = color(0x1F, 0x14, 0x00); // gold
    OBJ_PALLETE0[5] = color(0x11, 0x00, 0x00); // maroon
    OBJ_PALLETE0[6] = color(0x00, 0x00, 0x1F); // blue
    OBJ_PALLETE0[7] = color(0x1F, 0x00, 0x00); // red
    OBJ_PALLETE0[8] = color(0x0D, 0x02, 0x02); // dark red
    OBJ_PALLETE0[9] = color(0x10, 0x00, 0x00); // grey red
}
