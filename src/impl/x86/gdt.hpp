#pragma once

#include "../common/libk/stdtypes.hpp"
#include "tss.hpp"

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

    ::x86::TSS<::x86::Protected> tss;
};

}  // namespace x86
}  // namespace Arachne
