#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "driver/vga.h"

void kernel_main(void) {
    gdt_init();
    isr_install();

    kprint("Kernel start\n");

    asm volatile("int $0x0"); // Divide by zero interrupt

    for (;;);
}