
#include <stdint.h>

void main()
{
    const char *str = "Hello world!";
    uint16_t *video_memory = (uint16_t *)0xB8000;

    // color: fondo negro (0), texto blanco (15)
    uint8_t color = (0 << 4) | (15 & 0x0F);

    for (int i = 0; str[i] != '\0'; i++)
    {
        video_memory[i] = (color << 8) | str[i];
    }

    while (1)
    {
        // Halt the CPU to avoid spinning forever
        __asm__ __volatile__("hlt");
    }
}
