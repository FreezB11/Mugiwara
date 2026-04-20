#include "gdt.h"
#include "idt.h"
#include "isr.h"

void kernel_main(void) {
    gdt_init();
    isr_install();
    volatile unsigned short *vga = (volatile unsigned short *)0xB8000;
    vga[0] = 0x0F00 | 'K';

    for (;;);
}