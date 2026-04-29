#pragma once
#include "util.h"
#include "isr.h"

void irq_install();
void irq_handler(registers_t *r);  // pointer, not by value