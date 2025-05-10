mov ah, 0x0e           ; Write to tty mode
mov al, 'A'
int 0x10
mov al, 'r'
int 0x10
mov al, 'a'
int 0x10
mov al, 'c'
int 0x10
mov al, 'h'
int 0x10
mov al, 'n'
int 0x10
mov al, 'e'
int 0x10
mov al, '.'
int 0x10
mov al, '.'
int 0x10
mov al, '.'
int 0x10







jmp $                    ; Keeping the CPU busy by entering an infinite loop

times 510 - ($-$$) db 0  ; Filling the rest of the sector with 0s
dw 0xAA55                ; Indicating that this is a boot sector


