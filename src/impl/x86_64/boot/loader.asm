; We will be using GRUB as our bootloader.

section .text
global loader
extern kernel_main

loader:
    mov esp, kernel_stack_top         ; Set up the stack pointer
    push ebx                          ; Push multiboot info structure pointer (first parameter)
    push eax                          ; Push magic number (second parameter)
    call kernel_main                  ; Call the kernel's main function

_stop:
    cli                               ; Clear interrupts
    hlt                               ; Halt the CPU
    jmp _stop                         ; Infinite loop to prevent falling through

section .bss
align 16                              ; To prevent any hardware faults, force alignment 
kernel_stack_bottom:
    resb 4096                         ; Allocate 4KB for the kernel stack
kernel_stack_top:                     ; Label for the top of the stack

