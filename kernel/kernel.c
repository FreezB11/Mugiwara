#include "gdt.h"

void kernel_main(void) {
    gdt_init();
    volatile unsigned short *vga = (volatile unsigned short *)0xB8000;
    vga[0] = 0x0F00 | 'K';

    for (;;);
}