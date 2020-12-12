#pragma once

/*
 * A big set of info for use in programming the GBA
 * Includes memory locations, keys, pointers, functions, etc
 */
/*
 * Explanation of memory:
 * 
 * Tiles in bitmap mode can use 4bpp and 8bpp versions
 * This uses 4bpp
 *
 * We give a value in a tile which refers to pallete memory
 * Which is at 0x05000000
 * 
 * It stores 512 sets of 16 bits (15-bit color) so 512 colors
 * We can stroe 2 pallettes of 256 or 32 palettes of 16
 * We're doing the latter
 * Each tile block in vram is 16 KB in size so 512 4bpp tiles in a block
 * with 6 blocks in vram
 * 
 * Vram is split between 0-3 backgrounds and 4-5 sprites
 * Palletes are split into 16 for backgrounds and 16 for sprites
 * 
 * Now we make sprites
 */

/*
 * Sprite attributes:
 * 
 * Goes in Object Attribute Memory (OAM)
 * They're rendered as entire objects
 * 
 * Attr 0 -> y coordinate, shape, and color mode (4bpp)
 * Attr 1 -> x coordinate, size
 * Attr 2 -> base tile index and color pallete
 */

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;

typedef uint16_t rgb15_t;

#define VIDEO_MODE0 0x0000
#define OBJ_ENABLE  0x1000
#define MAP_MODE_1D 0x0040
#define BG0_EN      0x0100
#define BG1_EN      0x0200

#define IO_MEM      0x04000000
#define PALLETE_MEM 0x05000000
#define VIDEO_MEM   0x06000000
#define OBJECT_MEM  0x07000000

#define REG_BG0_CONTROL     *((volatile uint16_t *) 0x04000008)
#define REG_BG1_CONTROL     *((volatile uint16_t *) 0x0400000A)
#define REG_BG2_CONTROL     *((volatile uint16_t *) 0x0400000C)
#define REG_BG3_CONTROL     *((volatile uint16_t *) 0x0400000E)

#define OAM                 ((volatile obj_attrs *) OBJECT_MEM)
#define TILE_MEM            ((volatile tile_block_t *) VIDEO_MEM)
#define SCREEN_BLOCK_MEM    ((volatile screen_block_t *) VIDEO_MEM)
#define OBJ_PALLETE0        ((volatile rgb15_t *) (PALLETE_MEM + 0x200))
#define BG_PALLETE0         ((volatile rgb15_t *) (PALLETE_MEM))
#define REG_DISPLAY         (*((volatile uint32_t *) (IO_MEM)))
#define REG_DISPLAY_VCONT   (*((volatile uint32_t *) (IO_MEM + 0x0006)))
#define REG_KEY_INPUT       (*((volatile uint32_t *) (IO_MEM + 0x0130)))

/*
 * Input is in IO Registers
 * 
 * Input state is read from KEYINPUT I/O register at 0x04000130
 * Use masks to get buttons
 */

#define KEY_UP      0x0040
#define KEY_DOWN    0x0080
#define KEY_LEFT    0x0020
#define KEY_RIGHT   0x0010
#define KEY_START   0x0008
#define KEY_SELECT  0x0004
#define KEY_A       0x0001
#define KEY_B       0x0002
#define KEY_L       0x0200
#define KEY_R       0x0100
#define KEY_ANY     0x03FF

#define SCREEN_WIDTH    240
#define SCREEN_HEIGHT   160

#define OBJ_Y   0x0FF
#define OBJ_X   0x1FF
typedef struct {
    uint16_t attr0;
    uint16_t attr1;
    uint16_t attr2;
    uint16_t pad;
} __attribute__((packed, aligned(4))) obj_attrs;
typedef uint32_t tile_4bpp_t[8];
typedef tile_4bpp_t tile_block_t[512];
typedef uint16_t screen_block_t[1024];

// Form a 15-bit BGR color from component values
static inline rgb15_t color(int r, int g, int b) {
    return r | (g << 5) | (b << 10);
}

// Set the position of object to a specified x and y position
static inline void set_obj_pos(volatile obj_attrs *obj, int x, int y) {
    obj->attr0 = (obj->attr0 & ~OBJ_Y) | (y & OBJ_Y);
    obj->attr1 = (obj->attr1 & ~OBJ_X) | (x & OBJ_X);
}

static inline double clamp(float value, float min, float max) {
    return (value < min ? min : (value > max ? max : value));
}

static inline uint16_t reverse_bits(uint16_t num) {
    uint16_t reverse_num = 0;
    for (int i = 0; i < 16; i++) {
        if(num & (1 << i)) {
           reverse_num |= 1 << ((16 - 1) - i);
        }
    } 
    return reverse_num; 
}

static inline uint16_t nybble_flip(uint16_t num) {
    return ((num & 0x0F0F) << 4) | ((num & 0xF0F0) >> 4);
}

static inline uint16_t nybble_reverse(uint16_t num) {
    return ((num & 0x000F) << 24) + ((num & 0x00F0) << 8)
        + ((num & 0x0F00) >> 8) + ((num & 0xF000) >> 24);
}
