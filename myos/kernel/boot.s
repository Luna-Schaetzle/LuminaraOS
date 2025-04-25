[bits 16]
[global _start]

_start:
    ; Setze den Stackpointer
    cli
    xor ax, ax
    mov ss, ax
    mov sp, 0x7c00

    ; Springe zu unserem Kernel
    mov ax, 0x1000      ; Kernel Startadresse (z.B. 0x1000)
    jmp ax

times 510 - ($ - $$) db 0
dw 0xAA55
