#!/bin/bash

set -e

echo "🔧 Compiling kernel..."

mkdir -p build

# Stelle sicher, dass der Pfad zur boot.s-Datei korrekt ist
if [ ! -f boot.s ]; then
    echo "Fehler: boot.s nicht gefunden!"
    exit 1
fi

# Assemble bootloader
i686-elf-as boot.s -o build/boot.o

# Compile kernel C files
i686-elf-gcc -ffreestanding -m32 -c kernel/kernel.c -o build/kernel.o
i686-elf-gcc -ffreestanding -m32 -c kernel/terminal.c -o build/terminal.o
i686-elf-gcc -ffreestanding -m32 -c kernel/util.c -o build/util.o
i686-elf-gcc -ffreestanding -m32 -c kernel/interrupts.c -o build/interrupts.o
i686-elf-gcc -ffreestanding -m32 -c kernel/keyboard.c -o build/keyboard.o

# Link the kernel
i686-elf-ld -T linker.ld -o build/kernel.bin -nostdlib build/*.o

echo "📦 Building ISO..."

mkdir -p iso/boot/grub
cp build/kernel.bin iso/boot/kernel.bin

# Minimal GRUB config
cat > iso/boot/grub/grub.cfg <<EOF
set timeout=0
set default=0

menuentry "LuminaraOS" {
    multiboot /boot/kernel.bin
    boot
}
EOF

grub-mkrescue -o luminara.iso iso

echo "🚀 Launching QEMU..."
qemu-system-i386 -cdrom luminara.iso
