; default_handler.asm
global default_interrupt_handler
default_interrupt_handler:
    pusha
    call default_handler_body
    popa
    iret

