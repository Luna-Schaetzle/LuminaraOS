// kernel/terminal.c
#include "terminal.h"

static uint16_t* const VGA_BUFFER = (uint16_t*) 0xB8000;
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = (0 /*Schwarz*/ << 4) | 15 /*Weiß*/;
    for (size_t y = 0; y < 25; y++) {
        for (size_t x = 0; x < 80; x++) {
            VGA_BUFFER[y * 80 + x] = (uint16_t)(' ' | terminal_color << 8);
        }
    }
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == 25) terminal_row = 0;
        return;
    }
    VGA_BUFFER[terminal_row * 80 + terminal_column] =
        (uint16_t)(c | terminal_color << 8);
    if (++terminal_column == 80) {
        terminal_column = 0;
        if (++terminal_row == 25) terminal_row = 0;
    }
}

void terminal_writestring(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        terminal_putchar(str[i]);
    }
}
