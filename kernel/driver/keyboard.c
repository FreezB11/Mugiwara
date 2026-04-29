#include "../util.h"
#include "../isr.h"
#include "vga.h"

void keyboard_callback(registers_t *r) {
    kprint("K");
}