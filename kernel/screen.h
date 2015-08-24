#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "io.h"

enum Color
{
	BLACK = 0x00,
	BLUE = 0x01,
	GREEN = 0x02,
	CYAN = 0x03,
	RED = 0x04,
	MAGENTA = 0x05,
	BROWN = 0x06,
	LIGHT_GREY = 0x07,
	DARK_GREY = 0x08,
	LIGHT_BLUE = 0x09,
	LIGHT_GREEN = 0x0A,
	LIGHT_CYAN = 0x0B,
	LIGHT_RED = 0x0C,
	LIGHT_MAGENTA = 0x0D,
	LIGHT_BROWN = 0x0E,
	WHITE = 0x0F
};

char *VIDMEM;

uint16_t cursor_x, cursor_y;
uint8_t fore_color, back_color;

uint8_t makecolor(uint8_t fore, uint8_t back);
void sreen_clear();
void screen_put(char c);
void screen_write(char *message);
void screen_write_hex(int n);
void screen_write_dec(int n);
void move_cursor(uint16_t x, uint16_t y);
void update_cursor();

#endif