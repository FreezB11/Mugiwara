#include "idt.h"
#include "util.h"

idt_gate_t idt[IDT_ENTRIES];
idt_reg_t idt_reg;

void set_idt_gate(int n, u32 handler){
    idt[n].low_offset = handler & 0xffff;
    idt[n].select = KERN_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = (handler & 0Xffff0000) >> 16;
}

void set_idt(){
    idt_reg.base = (u32)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}