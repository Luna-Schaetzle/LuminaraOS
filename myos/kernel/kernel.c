// kernel/kernel.c
#include "terminal.h"

// Verhindert C-Name‐Munging
void kernel_main(void);

void kernel_main(void) {
    terminal_initialize();
    terminal_writestring("Willkommen zu LuminaraOS!\n");
    while (1) {
        // Endlosschleife – hier später Eingabe/Parser ergänzen
    }
}
