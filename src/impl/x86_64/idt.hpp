#pragma once

#include "../common/libk/stdtypes.hpp"

/*
 * Interrupt Descriptor Table (IDT) implementation for x86_64 architecture.
 * This class sets up the IDT with standard interrupt and exception handlers.
 */ 

namespace Arachne
{
namespace x86
{

class IDT
{
public:
    IDT();
    ~IDT();

private:
    struct idt_entry {
        uint16_t offset_low;
        uint16_t selector; // GDT code segment 0x08
        uint8_t reserved;
        uint8_t type_attr;
    };

};

}  // namespace x86
}  // namespace Arachne