#include "screen.h"

void main()
{
    clear_screen();
    print_string("Welcome to Neonix!\n");

    print_string("Decimal: ");
    print_dec(12345);
    print_char('\n');

    print_string("Hex: ");
    print_hex(0xB8000);
    print_char('\n');

    while (1)
    {
        __asm__ __volatile__("hlt");
    }
}