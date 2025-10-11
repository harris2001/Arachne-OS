org 0x7C00               ; BIOS loads boot sector here
bits 16                  ; we're in 16-bit real mode

section .text
start:
    cli                  ; disable interrupts while we set up segments/stack

    ; Set up a flat segment model for the bootloader:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax

    ; SP is an offset relative to SS:SS:SP => 0x0000:0x8000 => linear 0x8000
    mov sp, 0x8000

    sti                  ; Enabling interrupts so that HLT is resumable

    ; Point SI to the message. 
    mov si, msg

print_loop:
    lodsb                ; AL = [DS:SI++]
    cmp al, 0
    je .done
    mov ah, 0x0E         ; BIOS teletype output (TTY)
    int 0x10
    jmp print_loop

.done:
    ; Halt loop: repeatedly HLT. 
		; TODO: Enable interrupts and issue an IRQ to wake CPU.
.halt_loop:
    hlt
    jmp .halt_loop

section .data
msg:    db 'Arachne is booting...', 0

times 510 - ($ - $$) db 0
dw 0xAA55
