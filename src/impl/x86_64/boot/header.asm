section .multiboot_header

header_start:
    dd 0xE85250D6                                                          ; multiboot2 magic number
    dd 0x0                                                                 ; architecture (protected mode for i386)
    dd header_end - header_start                                           ; total header length
    dd 0x100000000 - (0xE85250D6 + 0x0 + (header_end - header_start))      ; checksum

    ; end tag
    dw 0                                                                   ; tag type (0 = end)
    dw 0                                                                   ; flags (0 = none)
    dd 8                                                                   ; size of tag
header_end:
