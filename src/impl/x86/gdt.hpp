#pragma once

#include "../common/libk/stdtypes.hpp"

/*
 * Global Descriptor Table (GDT) implementation for x86 architecture.
 * This class sets up the GDT with standard segments for kernel and user modes.
 *
 * Note: We will still need to implement paging for an x86 OS to function properly.
 */

namespace Arachne
{
namespace x86
{

class GDT
{
public:
    GDT();
    ~GDT();

    struct gdt_ptr {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed));

private:
    struct gdt_entry {
        uint16_t limit_low;
        uint16_t base_low;
        uint8_t base_middle;
        uint8_t access;
        uint8_t granularity;
        uint8_t base_high;
    } __attribute__((packed));

    // x86 Task State Segment structure (32-bit) in correct memory order
    struct tss_entry {
        uint16_t LINK;  // Previous Task Link (selector)
        uint16_t reserved0;
        uint32_t ESP0;  // Stack Pointer for Ring 0
        uint16_t SS0;   // Stack Selector for Ring 0
        uint16_t reserved1;
        uint32_t ESP1;  // Stack Pointer for Ring 1
        uint16_t SS1;   // Stack Selector for Ring 1
        uint16_t reserved2;
        uint32_t ESP2;  // Stack Pointer for Ring 2
        uint16_t SS2;   // Stack Selector for Ring 2
        uint16_t reserved3;
        uint32_t CR3;     // Page Directory Control Register (Physical Base Address of Page Table Directory)
        uint32_t EIP;     // Instruction pointer
        uint32_t EFLAGS;  // Processor flags
        uint32_t EAX;     // General purpose registers
        uint32_t ECX;
        uint32_t EDX;
        uint32_t EBX;
        uint32_t ESP;
        uint32_t EBP;
        uint32_t ESI;
        uint32_t EDI;
        uint16_t ES;  // Segment selectors
        uint16_t reserved4;
        uint16_t CS;
        uint16_t reserved5;
        uint16_t SS;
        uint16_t reserved6;
        uint16_t DS;
        uint16_t reserved7;
        uint16_t FS;
        uint16_t reserved8;
        uint16_t GS;
        uint16_t reserved9;
        uint16_t LDTR;  // LDT segment selector
        uint16_t reserved10;
        uint16_t reserved11;
        uint16_t IOPB;  // I/O Map Base Address offset
        uint32_t SSP;   // Stack Shadow Pointer
    } __attribute__((packed));

    /*
     * Sets a GDT entry at the specified index.
     *
     * @param idx Index of the GDT entry to set.
     * @param base Base address of the segment.
     * @param limit Limit of the segment.
     * @param access Access flags for the segment.
     * @param flags Additional flags for the segment.
     */
    void set_gate(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

    /*
     * Loads the GDT into the CPU's GDTR register.
     *
     * @param gdtr_address Address of the GDT pointer structure.
     */
    void load_gdt(uint32_t gdtr_address);

    /*
     * Writes a Task State Segment (TSS) entry into the GDT.
     *
     * @param idx Index of the GDT entry to write the TSS to.
     * @param ss0 Stack segment selector for Ring 0.
     * @param esp0 Stack pointer for Ring 0.
     */
    void write_tss(int idx, uint32_t ss0, uint32_t esp0);

    static const int GDT_ENTRIES = 6;  // Null, Code, Data, User Code, User Data, TSS
    gdt_entry entries[GDT_ENTRIES];

    gdt_ptr gdtr;

    tss_entry tss;
};

}  // namespace x86
}  // namespace Arachne
