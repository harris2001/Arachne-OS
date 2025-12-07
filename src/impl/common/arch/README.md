# Architecture Abstraction Layer

This directory contains the architecture abstraction layer for ArachneOS. The design allows the kernel to support multiple architectures (x86, ARM, RISC-V, etc.) through a clean interface.

# Adding a New Architecture

To add support for a new architecture (e.g., ARM) we need to do the following:

1. Create `src/impl/arm/arm_arch.hpp` and `arm_arch.cpp`
2. Implement the `Arch` interface:
   ```cpp
   namespace arachne {
   namespace arm {
       class ARMArch : public Arch {
       public:
           void init() override {
               // Initialize ARM-specific features
           }
       };
   }
   
   Arch& Arch::get_instance() {
       static arm::ARMArch instance;
       return instance;
   }
   ```
3. Update the Makefile to select the appropriate architecture implementation based on the build target

## Current Architecture: x86

The x86 implementation (`x86_arch.cpp`) currently initializes:
- **GDT (Global Descriptor Table)**: Sets up memory segmentation

Future additions will include:
- IDT (Interrupt Descriptor Table)
- Paging
- CPU features detection
- APIC/PIC initialization
