#pragma once

class GlobalDescriptorTable {
    public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

    private:
        struct gdt_entry {
            uint16_t limit_low;
            uint16_t base_low;
            uint8_t base_middle;
            uint8_t access;
            uint8_t flags;
            uint8_t base_high;
        } __attribute__((packed));

        struct gdt_ptr {
            uint16_t limit;
            unsigned int base;
        } __attribute__((packed));
   
}