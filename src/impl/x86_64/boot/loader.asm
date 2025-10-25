; We will be using GRUB as our bootloader.

section .text
global loader
extern kernel_main

loader:
    mov esp, kernel_stack + 4096      ; Set up the stack pointer
    push eax                          ; Push multiboot struct onto the stack
    push ebx
    call kernel_main                  ; Call the kernel's main function

_stop:
    cli                               ; Clear interrupts
    hlt                               ; Halt the CPU
    jmp _stop                         ; Infinite loop to prevent falling through

section .bss
align 16                              ; To prevent any hardware faults force alignment 
kernel_stack: resb 4096               ; Allocate 4KB for the kernel stack

