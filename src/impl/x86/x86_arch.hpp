#pragma once

#include "../common/arch/arch.hpp"

namespace Arachne
{
namespace x86
{

/**
 * x86 architecture implementation
 * Handles x86-specific initialization including GDT, IDT, etc.
 */
class X86_Arch : public Arch
{
public:
    X86_Arch();
    ~X86_Arch() override;

    void init() final;  // Implementation moved to .cpp for debug output
};

}  // namespace x86
}  // namespace Arachne
