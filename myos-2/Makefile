# Makefile (Auszug)
ASM      = nasm
ASMFLAGS = -f bin
CC       = i686-elf-gcc
CFLAGS   = -ffreestanding -O2 -Wall -Wextra -std=gnu11 -m32
LD       = i686-elf-ld
LDFLAGS  = -T kernel/linker.ld

all: build/boot.bin build/kernel.bin build/myos.iso

build/boot.bin: boot/boot.asm
	$(ASM) $(ASMFLAGS) $< -o $@

build/kernel.o: kernel/kernel.c kernel/terminal.h
	$(CC) $(CFLAGS) -c $< -o build/kernel.o

build/terminal.o: kernel/terminal.c kernel/terminal.h
	$(CC) $(CFLAGS) -c $< -o build/terminal.o

build/kernel.bin: build/kernel.o build/terminal.o
	$(LD) $(LDFLAGS) $^ -o build/kernel.bin

build/myos.iso: build/boot.bin build/kernel.bin iso/boot/grub/grub.cfg
	mkdir -p iso/boot/grub
	cp build/kernel.bin iso/boot/
	cp iso/boot/grub/grub.cfg iso/boot/grub/
	grub-mkrescue -o $@ iso/

clean:
	rm -rf build/* iso/boot/*
