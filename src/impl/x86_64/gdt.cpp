#include "gdt.hpp"

namespace Arachne
{
namespace x86
{

// Loading GDT in assembly
extern "C" void gdt_flush(uint32_t);

GDT::GDT()
{
    gdtr.limit = (sizeof(gdt_entry) * GDT_ENTRIES) - 1;
    gdtr.base = (uint32_t)&gdt;

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

    // Load the GDT
    gdt_flush((uint32_t)&gdtr);
}

GDT::~GDT() = default;

// For reference: https://wiki.osdev.org/Global_Descriptor_Table
void GDT::set_gate(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    gdt[idx].base_low = (base & 0xFFFF);
    gdt[idx].base_middle = (base >> 16) & 0xFF;
    gdt[idx].base_high = (base >> 24) & 0xFF;

    gdt[idx].limit_low = (limit & 0xFFFF);
    gdt[idx].granularity = (limit >> 16) & 0x0F;

    gdt[idx].granularity |= (flags & 0xF0);
    gdt[idx].access = access;
}

}  // namespace x86
}  // namespace Arachne