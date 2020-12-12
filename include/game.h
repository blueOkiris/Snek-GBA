#pragma once

/*
 * This file is for creating and loading sprites and other data for the game
 * It contains data and a single function for placing sprites in RAM
 */

#include <gba.h>

#define RIGHT   0
#define DOWN    1
#define LEFT    2
#define UP      3

#define TITLE   0
#define GAME    1
#define PAUSED  2
#define DEATH   3

typedef struct {
    volatile obj_attrs *plyr_head_obj;
    float plyr_head_x, plyr_head_y;
    int plyr_tile_x, plyr_tile_y;
    int plyr_width, plyr_height;
    int plyr_spd, plyr_dir;
    
    int num_bodies, max_bodies;
    volatile obj_attrs *plyr_bodies[101];
    float plyr_bodies_x[101];
    float plyr_bodies_y[101];
    
    uint32_t keys;
} game_state_t;

extern game_state_t g_state;

void set_palletes(void);
void reset(void);