#pragma once

/*
    * Global Descriptor Table (GDT) implementation for x86_64 architecture.
    * This class sets up the GDT with standard segments for kernel and user modes.
    *
    * Note: We will still need to implement paging for an x86_64 OS to function properly.
*/

class GDT {
    public:
        GDT();
        ~GDT();

    private:
        struct gdt_entry {
            uint16_t limit_low;
            uint16_t base_low;
            uint8_t base_middle;
            uint8_t access;

            uint8_t granularity;
            uint8_t base_high;
        } __attribute__((packed));

        struct gdt_ptr {
            uint16_t limit;
            unsigned int base;
        } __attribute__((packed));

        static const int GDT_ENTRIES = 5; // Null, Code, Data, User Code, User Data
        gdt_entry gdt[GDT_ENTRIES];
        gdt_ptr gdtr;

        void set_gate(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

        void load_gdt(unsigned int gdtr_address);
   
};