#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void outw(uint16_t port, uint16_t data);
uint16_t inw(uint16_t port);

#endif