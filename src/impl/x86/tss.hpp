#include "../common/libk/stdtypes.hpp"
/***
 * Task State Segment:
 * We need this on x86 to save information about tasks.
 *
 * It stores the following:
 *  - Registers
 *  - Segment Selectors
 *  - Instructor Pointer
 *  - EFLAGS Register
 *  - Control Register
 */

namespace x86
{
enum Mode
{
  Protected,
  Long
};

template <Mode M>
struct TSS; 


template <>
struct TSS<Mode::Protected>
{
  uint16_t LINK;  // Previous Task Link (selector)
  uint16_t reserved0;
  uint32_t ESP0;  // Stack Pointer for Ring 0
  uint16_t SS0;   // Stack Selector for Ring 0
  uint16_t reserved1;
  uint32_t ESP1;  // Stack Pointer for Ring 1
  uint16_t SS1;   // Stack Selector for Ring 1
  uint16_t reserved2;
  uint32_t ESP2;  // Stack Pointer for Ring 2
  uint16_t SS2;   // Stack Selector for Ring 2
  uint16_t reserved3;
  uint32_t CR3;     // Page Directory Control Register (Physical Base Address of Page Table Directory)
  uint32_t EIP;     // Instruction pointer
  uint32_t EFLAGS;  // Processor flags
  uint32_t EAX;     // General purpose registers
  uint32_t ECX;
  uint32_t EDX;
  uint32_t EBX;
  uint32_t ESP;
  uint32_t EBP;
  uint32_t ESI;
  uint32_t EDI;
  uint16_t ES;  // Segment selectors
  uint16_t reserved4;
  uint16_t CS;
  uint16_t reserved5;
  uint16_t SS;
  uint16_t reserved6;
  uint16_t DS;
  uint16_t reserved7;
  uint16_t FS;
  uint16_t reserved8;
  uint16_t GS;
  uint16_t reserved9;
  uint16_t LDTR;  // LDT segment selector
  uint16_t reserved10;
  uint16_t reserved11;
  uint16_t IOPB;  // I/O Map Base Address offset
  uint32_t SSP;   // Stack Shadow Pointer
} __attribute__((packed));
} // namespace x86
