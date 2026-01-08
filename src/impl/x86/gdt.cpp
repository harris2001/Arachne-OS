#include "gdt.hpp"

#include "../common/libk/memutils.hpp"

namespace Arachne
{
namespace x86
{

// Loading GDT in assembly
extern "C" void gdt_flush(GDT::gdt_ptr*);
extern void serial_debug_arch(const char*);

GDT::GDT()
{
    serial_debug_arch("[GDT] Constructor started\n");

    gdtr.limit = (sizeof(gdt_entry) * GDT_ENTRIES) - 1;
    gdtr.base = reinterpret_cast<uintptr_t>(&entries);

    serial_debug_arch("[GDT] Setting up descriptors\n");

    // Null descriptor
    set_gate(0, 0, 0, 0, 0);
    // Kernel Code Segment (0xC0 = 32-bit, 4KB granularity)
    // 1001 1010
    set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xC0);
    // Kernel Data Segment
    // 1001 0010
    set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xC0);
    // User Code Segment
    // 1111 1010
    set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xC0);
    // User Data Segment
    // 1111 0010
    set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xC0);

    // TSS Segment
    // Ring 0 stack segment selector is 0x10 (Kernel Data Segment)
    write_tss(5, 0x10, 0x0);

    serial_debug_arch("[GDT] About to flush GDT\n");
    // Load the GDT
    gdt_flush(&gdtr);

    serial_debug_arch("[GDT] GDT flushed, constructor done\n");
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
    serial_debug_arch("[GDT] write_tss: zeroing TSS manually\n");
    // Clear out the TSS structure manually (avoid potential memset issues)
    uint8_t* tss_bytes = reinterpret_cast<uint8_t*>(&tss);
    for (size_t i = 0; i < sizeof(tss_entry); ++i) {
        tss_bytes[i] = 0;
    }

    serial_debug_arch("[GDT] write_tss: TSS zeroed\n");
    tss.SS0 = static_cast<uint16_t>(ss0);
    tss.ESP0 = esp0;

    // We haven't implemented I/O permission bitmap yet so this is set to sizeof(tss)
    tss.IOPB = sizeof(tss_entry);

    serial_debug_arch("[GDT] write_tss: setting GDT descriptor\n");
    uintptr_t base = reinterpret_cast<uintptr_t>(&tss);
    uint32_t limit = sizeof(tss_entry);

    // Access byte: Present, Ring 0, 32-bit TSS Available (0x89)
    set_gate(idx, base, limit, 0x89, 0x40);

    serial_debug_arch("[GDT] write_tss: done\n");
}

}  // namespace x86
}  // namespace Arachne
