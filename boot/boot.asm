[BITS 16]
[ORG 0x7C00]

    cli ; disable the interrupts -> no stack yet
    xor ax, ax ; ax = 0
    mov ds, ax ; data seg = 0
    mov ss, ax ; stack seg = 0
    mov sp, 0x7C00 ; stack ptr just below us, grows downward
    sti ; interrupts sage now, stack exist

    mov ax, 0x1000 ; load kernel (dst seg)
    mov es, ax ; es = 0x1000
    xor bx, bx ; bx = 0 -> es:bx = 0x1000:0x0000 = physical 0x100000
    mov ah, 0x02 ; bios func : read sector
    mov al, 32 ; read 32 sector = 16kb
    mov ch, 0 ; cylinder 0
    mov cl, 2 ; sector 2 (sector 1 = bootloader, so we start at 2)
    mov dh, 0 ; head 0
    mov dl, 0x80 ; drive 0x80 = first hard disk
    int 0x13 ; call bios, do the read

    cli
    lgdt [gdt_desc] ; load gdt
    mov eax, cr0 ; flip the protected mode
    or eax, 1
    mov cr0, eax
    jmp 0x08:pm_entry ; far jump to flush the pipeline

[BITS 32]
pm_entry:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov esp, 0x90000
    call 0x10000 ; jump to kernel

.hang:
    hlt
    jmp .hang

gdt:
    dq 0
    dw 0xFFFF, 0x0000
    db 0x00, 0x9A, 0xCF, 0x00
    dw 0xFFFF, 0x0000
    db 0x00, 0x92, 0xCF, 0x00

gdt_desc:
    dw 23
    dd gdt

times 510-($-$$) db 0
dw 0xAA55