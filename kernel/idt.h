///@file:idt.h
#pragma once
#include "util.h"

#define KERN_CS 0x08

typedef struct{
    u16 low_offset;
    u16 select;
    u8 always0;
    u8 flags;
    u16 high_offset;
}__attribute__((packed)) idt_gate_t;

typedef struct{
    u16 limit;
    u32 base;
}__attribute__((packed)) idt_reg_t;

#define IDT_ENTRIES 256

void set_idt_gate(int n, u32 handler);
void set_idt();