#include "../util.h"
#include "../isr.h"
#include "../ports.h"
#include "vga.h"

int tick = 0;

void timer_callback(registers_t *r) {
    tick++;
    if (tick % 100 == 0) {
        kprint("Tick\n");
    }
}

void timer_init() {
    u32 freq = 100;
    u32 divisor = 1193180 / freq;

    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}