#pragma once

/* Architecture abstraction layer
 *
 * This interface provides an abstraction for architecture-specific
 * initialization and operations. Each target architecture (x86, ARM, RISC-V, etc.)
 * should implement this interface.
 *
 * Usage:
 *   Arch& arch = Arch::get_instance();
 *   arch.init();
 */

namespace Arachne
{

class Arch
{
public:
    virtual ~Arch() = default;

    // This implementation should be used to initialize
    // architecture-specific features (GDT, IDT, paging, etc.)
    virtual void init() = 0;

    static Arch& get_instance();

protected:
    Arch() = default;

    Arch(Arch&&) = delete;
    Arch& operator=(Arch&&) = delete;
    Arch(const Arch&) = delete;
    Arch& operator=(const Arch&) = delete;
};

}  // namespace Arachne