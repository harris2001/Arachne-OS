# Architecture Abstraction Layer

This directory contains the architecture abstraction layer for ArachneOS. The design allows the kernel to support multiple architectures (x86, ARM, RISC-V, etc.) through a clean interface.

## Usage

The kernel automatically uses the correct architecture implementation at build time. To build for a specific architecture:

```bash
# Build for x86 (default)
make

# Build for x86 (explicit)
make ARCH=x86

# Future: Build for ARM
# make ARCH=arm
```

# Adding a New Architecture

To add support for a new architecture (e.g., ARM), follow these steps:

1. **Create architecture implementation directory:**
   ```bash
   mkdir -p src/impl/arm/boot
   ```

2. **Create `src/impl/arm/arm_arch.hpp` and `arm_arch.cpp`:**
   ```cpp
   // arm_arch.hpp
   #pragma once
   #include "../common/arch/arch.hpp"
   
   namespace Arachne {
   namespace arm {
       class ARMArch : public Arch {
       public:
           ARMArch();
           ~ARMArch() override;
           void init() override;
       };
   }
   }
   
   // arm_arch.cpp
   #include "arm_arch.hpp"
   
   namespace Arachne {
   namespace arm {
       ARMArch::ARMArch() = default;
       ARMArch::~ARMArch() = default;
       
       void ARMArch::init() {
           // Initialize ARM-specific features
           // e.g., GIC, MMU, caches, etc.
       }
   }
   
   // Factory function
   Arch& Arch::get_instance() {
       static arm::ARMArch instance;
       return instance;
   }
   }
   ```

3. **Update the Makefile** to add ARM architecture support:
   - Add an `ifeq ($(ARCH),arm)` block with ARM-specific compiler flags
   - Define ARM-specific object files (bootloader, architecture init, etc.)
   - Set appropriate cross-compiler toolchain (e.g., `arm-none-eabi-gcc`)

4. **Create boot files** for ARM in `src/impl/arm/boot/`

5. **Create linker script** in `targets/arm/linker.ld`

6. **Test:**
   ```bash
   make ARCH=arm
   make run ARCH=arm
   ```

## Current Architecture: x86

The x86 implementation (`x86_arch.cpp`) currently initializes:
- **GDT (Global Descriptor Table)**: Sets up memory segmentation

Future additions will include:
- IDT (Interrupt Descriptor Table)
- Paging
- CPU features detection
- APIC/PIC initialization
