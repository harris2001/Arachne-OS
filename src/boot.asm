section .data
msg db 'Arachne is booting...', 0

section .text
_start:
    ; Set up segment registers
    xor ax, ax
    mov ds, ax

    mov si, msg          ; Point SI to message string

print_loop:
    lodsb                ; Load byte from [SI] into AL, increment SI
    cmp al, 0            ; Null terminator?
    je done
    mov ah, 0x0E         ; BIOS teletype output
    int 0x10
    jmp print_loop

done:
    jmp $                ; Infinite loop (halt CPU)

; Pad boot sector to 512 bytes
times 510 - ($-$$) db 0
dw 0xAA55                ; Boot signature
