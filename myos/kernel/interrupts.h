#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

void init_idt_with_defaults(void);
void set_idt_entry(int vector, uint32_t handler, uint16_t selector, uint8_t type_attr);
void load_idt(void);
void default_interrupt_handler_body(void);

#endif
