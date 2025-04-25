#!/bin/bash

set -e

echo "🔧 Compiling kernel..."

# Erstelle Build-Ordner falls nicht vorhanden
mkdir -p build

# Assembler-Header
nasm -f elf32 boot/boot_header.asm -o build/boot_header.o

# C-Dateien
i686-elf-gcc -ffreestanding -m32 -c kernel/kernel.c -o build/kernel.o
i686-elf-gcc -ffreestanding -m32 -c kernel/terminal.c -o build/terminal.o

# Linken
i686-elf-ld -T linker.ld -o build/kernel.bin build/boot_header.o build/kernel.o build/terminal.o

# Kernel in ISO-Struktur kopieren
cp build/kernel.bin iso/boot/

echo "📦 Creating ISO..."

# ISO erzeugen
grub-mkrescue -o build/myos.iso iso/

echo "🚀 Starting QEMU..."
qemu-system-x86_64 -cdrom build/myos.iso -m 128M

