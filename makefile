ASM    = nasm
CC     = cc
LD     = ld
CFLAGS = -m32 -ffreestanding -O2 -nostdlib -fno-builtin -fno-stack-protector

# Auto-find all .c and .asm files in kernel/
C_SRCS   := $(wildcard kernel/*.c)
ASM_SRCS := $(wildcard kernel/*.asm)

# Turn them into .o files
C_OBJS   := $(C_SRCS:.c=.o)
ASM_OBJS := $(ASM_SRCS:.asm=.o)
OBJS     := $(ASM_OBJS) $(C_OBJS)

all: myos.img

boot/boot.bin: boot/boot.asm
	$(ASM) -f bin boot/boot.asm -o boot/boot.bin

kernel/%.o: kernel/%.asm
	$(ASM) -f elf32 $< -o $@

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/kernel.bin: $(OBJS) linker.ld
	$(LD) -m elf_i386 -T linker.ld -o kernel/kernel.elf $(OBJS)
	objcopy -O binary kernel/kernel.elf kernel/kernel.bin

myos.img: boot/boot.bin kernel/kernel.bin
	cat boot/boot.bin kernel/kernel.bin > myos.img
	truncate -s 1474560 myos.img

run: myos.img
	qemu-system-i386 -drive format=raw,file=myos.img

clean:
	find . -name "*.bin" -o -name "*.o" -o -name "*.elf" | xargs rm -f
	rm -f myos.img