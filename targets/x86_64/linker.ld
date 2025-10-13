ENTRY(start)

SECTIONS
{
    . = 1M; /* Set the starting address to 1MB */

    .boot :
    {
        KEEP(*(.multiboot_header))
    }

    .text:
    {
        *(.text)
    }
}

