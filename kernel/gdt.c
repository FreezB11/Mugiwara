///@file gdt.c
#include "gdt.h"

static struct gdt_entry gdt[3];
static struct gdt_descriptor desc;

static void set_entry(int i, unsigned int base, unsigned int limit, unsigned char access, unsigned char flags){
    gdt[i].base_low    = base & 0xFFFF;
    gdt[i].base_mid    = (base >> 16) & 0xFF;
    gdt[i].base_high   = (base >> 24) & 0xFF;
    gdt[i].limit_low   = limit & 0xFFFF;
    gdt[i].flags_limit = (limit >> 16) & 0x0F;
    gdt[i].flags_limit |= (flags & 0xF0);
    gdt[i].access      = access;
}

void gdt_init() {
    set_entry(0, 0, 0,          0x00, 0x00);   // null
    set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);   // kernel code
    set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);   // kernel data

    desc.size    = sizeof(gdt) - 1;
    desc.address = (unsigned int)gdt;

    __asm__ volatile (
        "lgdt (%0)\n"
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "jmp $0x08, $.flush\n"
        ".flush:\n"
        : : "r"(&desc) : "ax"
    );
}