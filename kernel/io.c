#include "io.h"

void outb(uint16_t port, uint8_t val) {
	__asm__("outb %%al, %%dx" : : "a"(val), "d"(port));
}

uint8_t inb(uint16_t port) {
	uint8_t result;
	__asm__("inb %%dx, %%al" : "=a"(result) : "d"(port));

	return result;
}

void outw(uint16_t port, uint16_t data) {
	__asm__("outw %%ax, %%dx" : : "a"(data), "d"(port));
}

uint16_t inw(uint16_t port) {
	uint16_t result;
	__asm__("inw %%dx, %%ax" : "=a"(result) : "d"(port));

	return result;
}