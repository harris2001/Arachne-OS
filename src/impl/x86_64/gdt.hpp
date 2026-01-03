#pragma once

#include "../common/libk/stdtypes.hpp"

/*
 * Global Descriptor Table (GDT) implementation for x86_64 architecture.
 * This class sets up the GDT with standard segments for kernel and user modes.
 *
 * Note: We will still need to implement paging for an x86_64 OS to function properly.
 */

namespace Arachne
{
namespace x86_64
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

    struct tss_entry {
        uint32_t SSP;
        uint16_t IOPB;
        uint16_t LDTR;
        uint16_t GS;
        uint16_t FS;
        uint16_t DS;
        uint16_t SS;
        uint16_t CS;
        uint16_t ES;
        uint32_t EDI;
        uint32_t ESI;
        uint32_t EBP;
        uint32_t ESP;
        uint32_t EBX;
        uint32_t EDX;
        uint32_t ECX;
        uint32_t EAX;
        uint32_t EFLAGS;
        uint32_t EIP;
        uint32_t CR3;
        uint16_t SS2;
        uint32_t ESP2;
        uint16_t SS1;
        uint32_t ESP1;
        uint16_t SS0;        // Segment selector for Ring 0 stack
        uint32_t ESP0;
        uint16_t LINK;       // Previous Task Link field (Contains the segment selector of the previous TSS)
   } __attribute__((packed));

    static const int GDT_ENTRIES = 6;  // Null, Code, Data, User Code, User Data, TSS
    gdt_entry entries[GDT_ENTRIES];
    gdt_ptr gdtr;

    void set_gate(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

    void load_gdt(uint32_t gdtr_address);

    void write_tss(uint32_t idx, uint32_t ss0, uint32_t esp0);
};

}  // namespace x86_64
}  // namespace Arachne
