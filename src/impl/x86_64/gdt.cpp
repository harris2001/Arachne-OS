#include "gdt.hpp"

namespace Arachne
{
namespace x86_64
{

// Loading GDT in assembly
extern "C" void gdt_flush(GDT::gdt_ptr*);

GDT::GDT()
{
    gdtr.limit = (sizeof(gdt_entry) * GDT_ENTRIES) - 1;
    gdtr.base = reinterpret_cast<uintptr_t>(&entries);

    // Null descriptor
    set_gate(0, 0, 0, 0, 0);
    // Kernel Code Segment (0xC0 = 32-bit, 4KB granularity)
    set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xC0);
    // Kernel Data Segment
    set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xC0);
    // User Code Segment
    set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xC0);
    // User Data Segment
    set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xC0);
    // TSS Segment
    write_tss(5, 0x10, 0x0);  // Ring 0 stack segment selector is 0x10 (Kernel Data Segment) 

    // Load the GDT
    gdt_flush(&gdtr);
}

GDT::~GDT() = default;

// For reference: https://wiki.osdev.org/Global_Descriptor_Table
void GDT::set_gate(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    entries[idx].base_low = (base & 0xFFFF);
    entries[idx].base_middle = (base >> 16) & 0xFF;
    entries[idx].base_high = (base >> 24) & 0xFF;

    entries[idx].limit_low = (limit & 0xFFFF);
    entries[idx].granularity = (limit >> 16) & 0x0F;

    entries[idx].granularity |= (flags & 0xF0);
    entries[idx].access = access;
}

void GDT::write_tss(int idx, uint32_t ss0, uint32_t esp0)
{
    tss_entry* tss = reinterpret_cast<tss_entry*>(&entries[idx]);

    // Clear out the TSS
    memset(tss, 0, sizeof(tss_entry));

    tss->SS0 = ss0;
    tss->ESP0 = esp0;

    uint32_t base = reinterpret_cast<uint32_t>(tss);
    uint32_t limit = sizeof(tss_entry);

    set_gate(idx, base, limit, 0x89, 0x00);  // Access byte: Present, Ring 0, TSS (0x89)
}

}  // namespace x86_64
}  // namespace Arachne
