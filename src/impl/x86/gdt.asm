[BITS 32]
global gdt_flush

gdt_flush:
    mov eax, [esp+4]     ; gdtr
    lgdt [eax]           ; load the GDT

    ; Set the offset of each segment to point to the GDT table (0x10)
    mov ax, 0x10

    mov ds, ax           
    mov es, ax           
    mov fs, ax           
    mov gs, ax           
    mov ss, ax           

    ; We need to use far jump to set the code segment
    jmp 0x08:.flush      

.flush:
    ret 
