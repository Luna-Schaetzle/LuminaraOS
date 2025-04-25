// kernel/serial.c
#include "serial.h"
#include <stdint.h>
#include "io.h" // für outb()

#define COM1 0x3F8

void serial_init() {
    outb(COM1 + 1, 0x00); // Disable interrupts
    outb(COM1 + 3, 0x80); // Enable DLAB
    outb(COM1 + 0, 0x03); // 38400 baud (divisor 3)
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03); // 8N1
    outb(COM1 + 2, 0xC7); // FIFO, clear, 14-byte threshold
    outb(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int serial_is_transmit_empty() {
    return inb(COM1 + 5) & 0x20;
}

void serial_write(char c) {
    while (serial_is_transmit_empty() == 0);
    outb(COM1, c);
}

void serial_writestring(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        serial_write(str[i]);
    }
}

