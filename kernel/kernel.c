#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "logo.h"

#define WHITE_TXT 0x07
#define GREEN_TXT 0x0B

void k_clear_screen();
unsigned int k_printf(char *message, uint32_t x, uint32_t y);
void update_cursor(int row, int col);
static inline void outb(uint16_t, uint8_t val);

k_main()
{
	k_clear_screen();
	k_printf(LOGO, 10, 1);
	k_printf("OSome v0.0.1", 10, 15);
	k_printf("(c) 2010-2015 Jacinto Mba Cantero. GNU Public License", 10, 16);

	k_printf("#", 1, 20);
	update_cursor(20, 2);
}

void k_clear_screen()
{
	char *vidmem = (char *)0xb8000;
	unsigned int i = 0;
	while(i < (80 * 25 * 2)) {
		vidmem[i] = ' ';
		i++;
		vidmem[i] = GREEN_TXT;
		i++;
	}

	update_cursor(0, 0);
}

unsigned int k_printf(char *message, uint32_t x, uint32_t y)
{
	char *vidmem = (char *)0xb8000;
	unsigned int i = 0;

	i = (y * 80 * 2) + (x * 2);

	while(*message != 0) {
		if(*message == 10) {
			y++;
			i = (y * 80 * 2) + (x * 2);
			*message++;
		} else {
			if(*message != 13) vidmem[i] = *message;
			*message++;
			i++;
			vidmem[i] = GREEN_TXT;
			i++;
		}
	}

	return 1;
}

void update_cursor(int row, int col) {
	uint16_t position = (row * 80) + col;

	outb(0x3d4, 14);
	outb(0x3d5, position >> 8);

	outb(0x3d4, 15);
	outb(0x3d5, position);
}

static inline void outb(uint16_t port, uint8_t val) {
	asm volatile("outb %1, %0" : : "dN"(port), "a"(val));
}