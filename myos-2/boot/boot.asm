; boot/boot.asm
BITS 16
ORG 0x7C00

start:
    cli                 ; Interrupts aus
    mov ax, 0x0000
    mov ds, ax          ; Segment-Register initialisieren
    mov es, ax

    ; Hier könnte später ein Lese-Routine für Stage2 folgen

    ; Endlosschleife (bis Stage2 kommt)
hang:
    jmp hang

; Bootsektor-Signatur
times 510-($-$$) db 0
dw 0xAA55
