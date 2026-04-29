#include "irq.h"
#include "idt.h"
#include "ports.h"

extern void irq0();
extern void irq1();

static void pic_remap() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20); // Master offset 32
    outb(0xA1, 0x28); // Slave offset 40

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void irq_install() {
    pic_remap();
    set_idt_gate(32, (u32)irq0);
    set_idt_gate(33, (u32)irq1);
}

void irq_handler(registers_t *r) {
    // Send EOI
    if (r->int_no >= 40)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);

    // Dispatch
    if (r->int_no == 32) {
        extern void timer_callback(registers_t *r);
        timer_callback(r);
    }
    if (r->int_no == 33) {
        extern void keyboard_callback(registers_t *r);
        keyboard_callback(r);
    }
}