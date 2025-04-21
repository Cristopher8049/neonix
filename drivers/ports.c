#include "ports.h"

void outb(uint16_t port, uint8_t val)
{
    __asm__("out %%al, %%dx" : : "a"(val), "d"(port));
}