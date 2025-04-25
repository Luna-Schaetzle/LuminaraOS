[BITS 32]
[GLOBAL load_idt_asm]
[GLOBAL default_interrupt_handler_stub]

load_idt_asm:
    mov eax, [esp + 4]
    lidt [eax]
    ret

default_interrupt_handler_stub:
    pusha
    call default_interrupt_handler_body
    popa
    iretd
