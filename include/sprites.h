#pragma once

#include <gba.h>

#define SNAKE_HEAD_UP       4
#define SNAKE_HEAD_DOWN     2
#define SNAKE_HEAD_LEFT     3
#define SNAKE_HEAD_RIGHT    1
#define SNAKE_BODY          5
#define BLANK               6

extern uint16_t spr_snake_head_up[sizeof(tile_4bpp_t) / 2];
extern uint16_t spr_snake_head_down[sizeof(tile_4bpp_t) / 2];
extern uint16_t spr_snake_head_left[sizeof(tile_4bpp_t) / 2];
extern uint16_t spr_snake_head_right[sizeof(tile_4bpp_t) / 2];
extern uint16_t spr_snake_body[sizeof(tile_4bpp_t) / 2];
//extern uint32_t spr_frog[8];
extern uint16_t spr_blank[sizeof(tile_4bpp_t) / 2];

void load_sprites(void);
