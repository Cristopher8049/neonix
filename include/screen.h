#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

void clear_screen();
void print_char(char c);
void print_string(const char *str);
void print_at(const char *str, int row, int col);

void move_cursor(uint8_t row, uint8_t col);

void print_dec(int num);
void print_hex(uint32_t num);

#endif