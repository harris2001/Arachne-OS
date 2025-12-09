#pragma once

#include "../common/arch/arch.hpp"
#include "gdt.hpp"

namespace arachne {
namespace x86 {

/**
 * x86 architecture implementation
 * Handles x86-specific initialization including GDT, IDT, etc.
 */
class X86Arch : public Arch {
public:
    X86Arch();
    ~X86Arch() override;

    // Initialize x86-specific features
    void init() override;
};

} // namespace x86
} // namespace arachne
