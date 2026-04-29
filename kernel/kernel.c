#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "driver/vga.h"

void kernel_main(void) {
    gdt_init();
    isr_install();
    irq_install();

    extern void timer_init();
    timer_init();
    kprint("Kernel Alive\n");

    asm volatile("sti");

    for (;;);
}