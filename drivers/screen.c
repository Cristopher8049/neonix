#include "screen.h"
#include "ports.h"

#define VIDEO_MEMORY ((uint16_t *)0xB8000)
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_ON_BLACK 0x0F

static uint8_t cursor_row = 0;
static uint8_t cursor_col = 0;

static void update_cursor()
{
    uint16_t pos = cursor_row * SCREEN_WIDTH + cursor_col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void move_cursor(uint8_t row, uint8_t col)
{
    cursor_row = row;
    cursor_col = col;
    update_cursor();
}

void print_char(char c)
{
    if (c == '\n')
    {
        cursor_row++;
        cursor_col = 0;
    }
    else
    {
        uint16_t pos = cursor_row * SCREEN_WIDTH + cursor_col;
        VIDEO_MEMORY[pos] = (WHITE_ON_BLACK << 8) | c;
        cursor_col++;
        if (cursor_col >= SCREEN_WIDTH)
        {
            cursor_col = 0;
            cursor_row++;
        }
    }

    if (cursor_row >= SCREEN_HEIGHT)
    {
        cursor_row = 0;
    }

    update_cursor();
}

void print_string(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        print_char(str[i]);
    }
}

void print_at(const char *str, int row, int col)
{
    move_cursor(row, col);
    print_string(str);
}

void clear_screen()
{
    for (int row = 0; row < SCREEN_HEIGHT; row++)
    {
        for (int col = 0; col < SCREEN_WIDTH; col++)
        {
            int pos = row * SCREEN_WIDTH + col;
            VIDEO_MEMORY[pos] = (WHITE_ON_BLACK << 8) | ' ';
        }
    }
    move_cursor(0, 0);
}

void print_dec(int num)
{
    if (num == 0)
    {
        print_char('0');
        return;
    }

    if (num < 0)
    {
        print_char('-');
        num = -num;
    }

    char buffer[16];
    int i = 0;

    while (num > 0)
    {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        print_char(buffer[j]);
    }
}
void print_hex(uint32_t num)
{
    print_string("0x");

    for (int i = 7; i >= 0; i--)
    {
        uint8_t nibble = (num >> (i * 4)) & 0xF;
        char hex_char = (nibble < 10) ? ('0' + nibble) : ('A' + nibble - 10);
        print_char(hex_char);
    }
}
