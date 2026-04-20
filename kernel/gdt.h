///@file gdt.h
#pragma once

// Each GDT entry is exactly 8 bytes
struct gdt_entry {
    unsigned short limit_low;    // bits 0-15 of limit
    unsigned short base_low;     // bits 0-15 of base
    unsigned char  base_mid;     // bits 16-23 of base
    unsigned char  access;       // ring, type, present
    unsigned char  flags_limit;  // flags + bits 16-19 of limit
    unsigned char  base_high;    // bits 24-31 of base
} __attribute__((packed));

// What you pass to LGDT — size and address of the table
struct gdt_descriptor {
    unsigned short size;         // size of GDT in bytes minus 1
    unsigned int   address;      // address of gdt_entries array
} __attribute__((packed));

void gdt_init();