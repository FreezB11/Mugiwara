void kernel_main(void) {
    volatile unsigned short *vga = (volatile unsigned short *)0xB8000;
    vga[0] = 0x0F00 | 'K';

    for (;;);
}