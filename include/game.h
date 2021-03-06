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
    volatile obj_attrs *plyr_bodies[64];
    float plyr_bodies_x[64];
    float plyr_bodies_y[64];
    
    volatile obj_attrs *frog;
    int frog_x, frog_y;
    
    uint32_t keys;
    uint32_t score;
    volatile obj_attrs *score_display[10];
} game_state_t;

extern game_state_t g_state;

void reset(void);
void display_score();
