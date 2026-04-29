// vga.c
#include "../util.h"

volatile u16* video = (u16*)0xB8000;
int cursor = 0;

void kprint(const char* str) {
    while (*str) {
        video[cursor++] = (0x0F << 8) | *str++;
    }
}

void kprint_char(char c) {
    video[cursor++] = (0x0F << 8) | c;
}