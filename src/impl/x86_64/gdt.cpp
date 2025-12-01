#include "gdt.hpp"

// Loading GDT in assembly
extern "C" void gdt_flush(unsigned int);

GDT::GDT() {
    gdtr.limit = (sizeof(gdt_entry) * GDT_ENTRIES) - 1;
    gdtr.base = (unsigned int)&gdt;

    // Null descriptor
    set_gate(0, 0, 0, 0, 0);
    // Kernel Code Segment
    set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xA0);
    // Kernel Data Segment
    set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xA0);
    // User Code Segment
    set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xA0);
    // User Data Segment
    set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xA0);

    // Load the GDT
    gdt_flush((unsigned int)&gdtr);
}
  
GDT::~GDT() {
    //Log Destructor called
}

// FOr reference: https://wiki.osdev.org/Global_Descriptor_Table
void GDT::set_gate(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt[idx].base_low = (base & 0xFFFF);
    gdt[idx].base_middle = (base >> 16) & 0xFF;
    gdt[idx].base_high = (base >> 24) & 0xFF;

    gdt[idx].limit_low = (limit & 0xFFFF);
    gdt[idx].granularity = (limit >> 16) & 0x0F;

    gdt[idx].granularity |= (flags & 0xF0);
    gdt[idx].access = access;
}