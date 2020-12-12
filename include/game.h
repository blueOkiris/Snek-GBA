#pragma once

/*
 * This file is for creating and loading sprites and other data for the game
 * It contains data and a single function for placing sprites in RAM
 */

#include <gba.h>

typedef struct {
    int player_width, player_height;
    int ball_width, ball_height;
    
    int player_vel;
    int ball_vel_x, ball_vel_y;
    
    int player_x, player_y;
    int ball_x, ball_y;
    
    volatile obj_attrs *player_obj;
    volatile obj_attrs *ball_obj;
    
    uint32_t keys;
} game_state_t;

extern game_state_t g_state;

void set_sprites(void);
void set_palletes(void);
void reset(void);