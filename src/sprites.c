#include <sprites.h>

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
    }
}
