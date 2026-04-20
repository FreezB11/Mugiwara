# Requirements:
#   nasm           → sudo apt install nasm
#   i686-elf-gcc   → build a cross compiler (see osdev wiki)
#   qemu-system-i386 → sudo apt install qemu-system-x86

ASM = nasm
CC  = cc
LD  = ld

CFLAGS = -m32 -ffreestanding -O2 -nostdlib -fno-builtin -fno-stack-protector

all: myos.img

boot/boot.bin: boot/boot.asm
	$(ASM) -f bin boot/boot.asm -o boot/boot.bin

kernel/entry.o: kernel/entry.asm
	$(ASM) -f elf32 kernel/entry.asm -o kernel/entry.o

kernel/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel/kernel.o

kernel/kernel.bin: kernel/entry.o kernel/kernel.o linker.ld
	$(LD) -m elf_i386 -T linker.ld -o kernel/kernel.elf kernel/entry.o kernel/kernel.o
	objcopy -O binary kernel/kernel.elf kernel/kernel.bin

myos.img: boot/boot.bin kernel/kernel.bin
	cat boot/boot.bin kernel/kernel.bin > myos.img
	truncate -s 1474560 myos.img    # Pad to floppy size

run: myos.img
	qemu-system-i386 -drive format=raw,file=myos.img

clean:
	find . -name "*.bin" -o -name "*.o" -o -name "*.elf" | xargs rm -f
	rm -f myos.img