#include "terminal.h"
#include "interrupts.h"
#include "keyboard.h"
#include "util.h"

void kernel_main(void) {
    terminal_initialize();
    init_idt_with_defaults();
    keyboard_init();
    enable_interrupts();

    terminal_writestring("Willkommen zu LuminaraOS!\n> ");

    char line[64];
    size_t len = 0;

    while (1) {
        char c = keyboard_read_char();

        if (c == '\n' || c == '\r') {
            terminal_putchar('\n');
            line[len] = '\0';

            if (strcmp(line, "help") == 0) {
                terminal_writestring("Befehle: help, echo <text>\n");
            } else if (strncmp(line, "echo ", 5) == 0) {
                terminal_writestring(line + 5);
                terminal_putchar('\n');
            } else if (len > 0) {
                terminal_writestring("Unbekannter Befehl\n");
            }

            terminal_writestring("> ");
            len = 0;
        } else if (c == '\b') {
            if (len > 0) {
                terminal_putchar('\b');
                terminal_putchar(' ');
                terminal_putchar('\b');
                len--;
            }
        } else {
            if (len < sizeof(line) - 1) {
                terminal_putchar(c);
                line[len++] = c;
            }
        }
    }
}
