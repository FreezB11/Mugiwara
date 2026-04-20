ENTRY(kernel_main)

SECTIONS {
    . = 0x10000;        /* Bootloader loads us here */
    .text   : { *(.text)   }
    .rodata : { *(.rodata) }
    .data   : { *(.data)   }
    .bss    : { *(.bss) *(COMMON) }
}
