// keyboard.c
#include "keyboard.h"
#include <stdint.h>

static char scancode_to_ascii[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0,'*', 0,' ', 0,
    // Rest leer
};

static inline uint8_t inb(uint16_t port) {
    uint8_t data;
    asm volatile ("inb %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

void enable_interrupts(void) {
    asm volatile("sti");
}

void keyboard_init(void) {
    // Nichts nötig für dieses Minimalbeispiel
}

char keyboard_read_char(void) {
    uint8_t scancode = inb(0x60);
    if (scancode > 0 && scancode < 128) {
        return scancode_to_ascii[scancode];
    }
    return 0;
}
