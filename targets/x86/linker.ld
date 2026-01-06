ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)

SECTIONS
{
    . = 1M; /* Set the starting address to 1MB so that GRUB can load it properly */

    .boot :
    {
        KEEP(*(.multiboot_header))
    }

    .text :
    {
        *(.text*)
        *(.rodata*)
    }

    .data :
    {
        start_ctors = .;
        KEEP(*(.init_array));
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)));
        end_ctors = .;

        *(.data*)
    }

    .bss :
    {
        *(.bss*)
        *(COMMON)
    }

    /DISCARD/ :
    {
        *(.comment)
        *(.fini_array*)
    }
}
