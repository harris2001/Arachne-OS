# Arachne OS 🕸️  
*A high-performance operating system for fast, concurrent systems.*

<div align="center">
    <img src="icons/logo.png" alt="Arachne Logo" width="350"/>
</div>

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Technologies](#technologies)
- [Getting Started](#getting-started)
- [Project Layout](#project-layout)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)

---

## About

**Arachne** is a modular real-time operating system (RTOS) designed for AI-native workloads. It is built from scratch to support compiler-aware OS design and efficient on-device machine learning.

---

## Features

- Modular, preemptive kernel
- Deterministic task scheduling for real-time AI inference
- Compiler-aware runtime hooks
- Lightweight threading and message-passing
- Real-time memory management for concurrent workloads
- Simulated peripheral support (UART, timers, GPIO)


---

## Technologies

- Languages: C++, x86 Assembly
- Platform: Bare-metal, QEMU-compatible x86
- Build System: Make, NASM, LD
- Architecture: Modular design supporting multiple architectures (currently x86)

---

## Getting Started

### Requirements

- GCC/G++ compiler (`gcc`, `g++`)
- NASM assembler
- GNU Linker (`ld`)
- GRUB utilities (`grub-mkrescue`, `grub-pc-bin`)
- xorriso (for ISO creation)
- QEMU (`qemu-system-i386` or `qemu-system-x86`)

### Build & Run

```bash
# Clone the repository
git clone https://github.com/harris2001/Arachne
cd Arachne

# Build for default architecture (x86)
make

# Or specify architecture explicitly
make ARCH=x86

# Run in QEMU (opens graphical window)
make run
vncviewer localhost:5900

# Run in headless mode with serial output
make run-headless

# View build configuration
make info

# Clean build artifacts
make clean
```

### Supported Architectures

- **x86** (default) - 32-bit protected mode, i686 target
- More architectures coming soon: ARM, RISC-V

### Testing

```bash
# Run automated CI test
make test-ci
```

## Project Layout

```plaintext
Arachne/
├── build/               # Build artifacts
├── devs/                # Developers setup (if you want to contribute) 
├── icons/               # Project icons and logos 
├── src/                 # Source code
│   ├── impl/            # Architecture-specific code
│   │   └── x86       # x86 implementation
│   └── common/          # Architecture-independent code
├── targets/             # Build targets and configurations
│   └── x86/          # x86 target configuration
├── kernel/              # Scheduler, memory, syscalls
├── drivers/             # Basic device drivers
├── libs/                # Standard libraries and helpers
├── user/                # User-space test programs
├── tests/               # Unit and integration tests
├── docs/                # Design documentation
├── Makefile             # Build script
└── README.md            # Project overview
```

## Documentation

Architecture notes and design documents are available in the `docs/` directory.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request. For larger changes, please open an issue first to discuss your ideas.

## License

This project is licensed under the MIT License.
