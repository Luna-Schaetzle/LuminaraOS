// terminal.c
#include "terminal.h"
#include <stdint.h>

static uint16_t* video_memory = (uint16_t*)0xB8000;
static size_t row = 0;
static size_t col = 0;
static uint8_t color = 0x0F;

void terminal_putchar(char c) {
    if (c == '\n') {
        col = 0;
        if (++row == 25) row = 0;
        return;
    }

    const size_t index = row * 80 + col;
    video_memory[index] = (color << 8) | c;

    if (++col == 80) {
        col = 0;
        if (++row == 25) row = 0;
    }
}

void terminal_initialize(void) {
    for (size_t y = 0; y < 25; y++) {
        for (size_t x = 0; x < 80; x++) {
            const size_t index = y * 80 + x;
            video_memory[index] = (color << 8) | ' ';
        }
    }
    row = 0;
    col = 0;
}

void terminal_writestring(const char* str) {
    while (*str) terminal_putchar(*str++);
}
