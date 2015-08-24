#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "logo.h"
#include "screen.h"

k_main()
{
	screen_clear();
	move_cursor(0, 1);
	screen_write(LOGO);
	move_cursor(10, 15);
	screen_write("OSome v0.0.1");
	move_cursor(10, 16);
	screen_write("(c) 2010-2015 Jacinto Mba Cantero. GNU Public License");

	move_cursor(1, 20);
	screen_put('#');
	move_cursor(2, 20);
	update_cursor();
}