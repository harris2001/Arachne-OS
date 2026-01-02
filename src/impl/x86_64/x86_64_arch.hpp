#pragma once

#include "../common/arch/arch.hpp"

namespace Arachne
{
namespace x86_64
{

/**
 * x86 architecture implementation
 * Handles x86-specific initialization including GDT, IDT, etc.
 */
class X86_64_Arch : public Arch
{
public:
    X86_64_Arch();
    ~X86_64_Arch() override;

    void init() final;  // Implementation moved to .cpp for debug output
};

}  // namespace x86_64
}  // namespace Arachne
