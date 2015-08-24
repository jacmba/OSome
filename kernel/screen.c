#include "screen.h"

char *VIDMEM = (char*)0xb8000;
uint16_t cursor_x = 0;
uint16_t cursor_y = 0;
uint8_t fore_color = GREEN;
uint8_t back_color = BLACK;

uint8_t makecolor(uint8_t fore, uint8_t back) {
	return fore | back << 4;

}

void screen_clear()
{
	uint8_t attr = makecolor(fore_color, back_color);
	unsigned int i = 0;
	while(i < (80 * 25 * 2)) {
		VIDMEM[i] = ' ';
		i++;
		VIDMEM[i] = attr;
		i++;
	}

	update_cursor(0, 0);
}

void screen_put(char c) {
	uint32_t i = (cursor_y * 80 * 2) + (cursor_x * 2);
	uint16_t attr = makecolor(fore_color, back_color);

	if(c == 10) {
		cursor_y++;
		cursor_x = 0;
	} else {
		if(c != 13) VIDMEM[i] = c;
		i++;
		VIDMEM[i] = attr;
		cursor_x++;

		if(cursor_x >= 80) {
			cursor_x = 0;
			cursor_y ++;
		}
	}
}

void screen_write(char *message)
{
	while(*message != 0) {
		screen_put(*message);
		*message++;
	}
}

void screen_write_hex(int n) {
	int num = n;
	char tmp[12];
	char digits[] = "0123456789ABCDEF";
	int pos = 1;
	tmp[0] = 0; //End of string

	//ABS
	if(num < 0) {
		num *= (-1);
	}

	while(num > 0x10) {
		int least = num % 0x10;

		tmp[pos] = digits[least];
		pos++;

		num /= 0x10;
	}

	tmp[pos] = digits[num];
	pos++;
	tmp[pos] = 'x';
	pos++;

	tmp[pos] = '0';

	if(n < 0x0) {
		pos++;
		tmp[pos] = '-';
	}

	//Reverse and create hex string
	char result[pos + 1];

	int i, j;
	for(i=pos, j=0; i>=0; i--, j++) {
		result[j] = tmp[i];
	}

	//Print hex string
	screen_write(result);
}

void screen_write_dec(int n){
	int num = n;
	char tmp[20];
	char digits[] = "0123456789";
	int pos = 1;
	tmp[0] = 0;

	if(num < 0) {
		num *= -1;
	}

	while(num > 10) {
		int least = num % 10;

		tmp[pos] = digits[least];
		pos++;

		num /= 10;
	}

	tmp[pos] = digits[num];

	if(n < 0) {
		pos++;
		tmp[pos] = '-';
	}

	char result[pos + 1];

	int i,j;
	for(i=pos, j=0; i>=0; i--, j++) {
		result[j] = tmp[i];
	}

	screen_write(result);
}

void move_cursor(uint16_t x, uint16_t y) {
	cursor_x = x;
	cursor_y = y;
}

void update_cursor() {
	uint16_t position = (cursor_y * 80) + cursor_x;

	outb(0x3d4, 14);
	outb(0x3d5, position >> 8);

	outb(0x3d4, 15);
	outb(0x3d5, position);
}