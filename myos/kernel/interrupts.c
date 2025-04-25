#include "interrupts.h"
#include "terminal.h"

#define IDT_ENTRIES 256

struct IDTEntry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attr;
    uint16_t offset_high;
} __attribute__((packed));

static struct IDTEntry idt[IDT_ENTRIES];

extern void load_idt_asm(void*);
extern void default_interrupt_handler_stub(void);

void set_idt_entry(int vector, uint32_t handler, uint16_t selector, uint8_t type_attr) {
    idt[vector].offset_low = handler & 0xFFFF;
    idt[vector].selector = selector;
    idt[vector].zero = 0;
    idt[vector].type_attr = type_attr;
    idt[vector].offset_high = (handler >> 16) & 0xFFFF;
}

void load_idt() {
    struct {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed)) idt_ptr = {
        .limit = sizeof(idt) - 1,
        .base = (uint32_t)&idt
    };
    load_idt_asm(&idt_ptr);
}

void init_idt_with_defaults() {
    for (int i = 0; i < IDT_ENTRIES; i++) {
        set_idt_entry(i, (uint32_t)default_interrupt_handler_stub, 0x08, 0x8E);
    }
    load_idt();
}

void default_interrupt_handler_body(void) {
    terminal_writestring("[!] Unbehandelter Interrupt!\n");
}
