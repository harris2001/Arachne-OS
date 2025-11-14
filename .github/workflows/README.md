# CI/CD Configuration

## Overview
The GitHub Actions workflow automatically builds and tests ArachneOS using Docker on every push and pull request to the `main` branch.

## What It Does

1. **Build Docker Image**: Creates the development environment from `devs/Dockerfile`
2. **Build Kernel**: Compiles the kernel inside Docker container
3. **Verify Build**: Checks that both kernel.bin and the ISO were created
4. **Test Boot**: Runs the OS in QEMU (headless) for 10 seconds to verify it boots
5. **Upload Artifacts**: Saves the compiled kernel and ISO for download (30 days retention)

## Docker Environment

The Docker container includes:
- `gcc-cross-x86_64-elf` - Cross-compiler toolchain
- `nasm` - Assembly compiler
- `xorriso` - ISO 9660 filesystem tool
- `grub-pc-bin` & `grub-common` - GRUB bootloader
- `qemu-system-x86` - x86_64 emulator for testing

## Local Testing

To test the CI locally using Docker:

```bash
# Build the Docker image
cd devs
docker build . -t arachne-dev

# Build the kernel
cd ..
docker run --rm -v $(pwd):/root/env arachne-dev make

# Test in QEMU
docker run --rm -v $(pwd):/root/env arachne-dev make test-ci

# Interactive development
docker run --rm -it -v $(pwd):/root/env arachne-dev
```

## Artifacts

After each successful build, you can download:
- `build/kernel.bin` - The compiled kernel binary
- `build/arachne_x86_64.iso` - Bootable ISO image

These are available in the Actions tab under "Artifacts" for each workflow run.
