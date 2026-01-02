#include "x86_64_arch.hpp"

#include "gdt.hpp"

namespace Arachne
{
namespace x86_64
{

// Serial debug output
#define COM1 0x3F8
static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
void serial_debug_arch(const char* str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        while ((inb(COM1 + 5) & 0x20) == 0)
            ;
        outb(COM1, str[i]);
    }
}

X86_64_Arch::X86_64_Arch() = default;
X86_64_Arch::~X86_64_Arch() = default;

void X86_64_Arch::init()
{
    serial_debug_arch("[X86_64_Arch] init() called, about to create GDT\n");
    static GDT gdt_instance;
    serial_debug_arch("[X86_64_Arch] GDT instance created, init() done\n");
}

}  // namespace x86_64
}  // namespace Arachne

namespace Arachne
{

Arch& Arch::get_instance()
{
    static x86_64::X86_64_Arch instance;
    return instance;
}

}  // namespace Arachne
