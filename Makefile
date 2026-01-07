# ===== Architecture Configuration =====
# Override with: make ARCH=x86_64
# Supported architectures: x86
ARCH ?= x86
DEBUG ?= 1

# Architecture-specific settings
ifeq ($(ARCH),x86)
    NASM_FLAGS = -f elf32
    GPP = g++
    GPP_FLAGS = -m32 -ffreestanding -O0 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -nostdinc++ -fno-use-cxa-atexit -Isrc/impl/common
	ifeq ($(DEBUG),1)
		GPP_FLAGS += -g -DDEBUG
	else
		GPP_FLAGS += -DNDEBUG
	endif
    LD = ld
    LD_FLAGS = -m elf_i386
    QEMU = qemu-system-i386
    ARCH_BOOT_DIR = src/impl/$(ARCH)/boot
    ARCH_IMPL_DIR = src/impl/$(ARCH)
    TARGET_DIR = targets/$(ARCH)
    ISO_NAME = arachne_i686.iso
    
    # x86-specific object files
    ARCH_OBJECTS = \
        $(ARCH_IMPL_DIR)/gdt.o \
        $(ARCH_IMPL_DIR)/gdt_asm.o \
        $(ARCH_IMPL_DIR)/x86_arch.o
    
    BOOT_OBJECTS = \
        $(ARCH_BOOT_DIR)/header.o \
        $(ARCH_BOOT_DIR)/loader.o
else
    $(error Unsupported architecture: $(ARCH). Supported: x86)
endif

BUILD_DIR = build
ISO_DIR = $(TARGET_DIR)/iso
ISO_FILE = $(BUILD_DIR)/$(ISO_NAME)
QEMU_FLAGS = -cdrom $(ISO_FILE) -m 512M -boot d -no-reboot -no-shutdown 

# ===== Source Files =====
# Common kernel objects (architecture-independent)
COMMON_OBJECTS = \
    src/impl/common/kernel.o \
    src/impl/common/cxx_runtime.o \
    src/impl/common/libk/stdio.o \
	src/impl/common/libk/memutils.o

# All object files
OBJECTS = $(BOOT_OBJECTS) $(COMMON_OBJECTS) $(ARCH_OBJECTS)

# Default target
.PHONY: all clean run iso install format format-check info

all: $(ISO_FILE)

# ===== Compiling to ISO =====

# Compiling C++
%.o: %.cpp
	$(GPP) $(GPP_FLAGS) -c $< -o $@

# Compiling Assembly (default 32-bit)
%.o: %.asm
	nasm $(NASM_FLAGS) $< -o $@

# Boot assembly files must be 32-bit for multiboot/GRUB compatibility
$(ARCH_BOOT_DIR)/%.o: $(ARCH_BOOT_DIR)/%.asm
	nasm -f elf32 $< -o $@

# Special rule for GDT assembly (gdt.asm -> gdt_asm.o to avoid conflict with gdt.cpp)
$(ARCH_IMPL_DIR)/gdt_asm.o: $(ARCH_IMPL_DIR)/gdt.asm
	nasm $(NASM_FLAGS) $< -o $@

# ===== Linking Kernel ELF =====
$(BUILD_DIR)/kernel.bin: $(OBJECTS) $(TARGET_DIR)/linker.ld
	@echo "Linking kernel for architecture: $(ARCH)"
	mkdir -p $(BUILD_DIR)
	$(LD) $(LD_FLAGS) -T $(TARGET_DIR)/linker.ld -o $@ $(OBJECTS)
	@echo "Kernel binary created: $@"

# ===== Building GRUB ISO =====
$(ISO_FILE): $(BUILD_DIR)/kernel.bin $(TARGET_DIR)/iso/boot/grub/grub.cfg
	@echo "Creating bootable ISO for $(ARCH)..."
	mkdir -p $(ISO_DIR)/boot
	cp $(BUILD_DIR)/kernel.bin $(ISO_DIR)/boot/kernel.bin
	grub-mkrescue -o $(ISO_FILE) $(ISO_DIR)
	@echo "ISO created: $(ISO_FILE)"


# ===== RUN in QEMU =====
run: $(ISO_FILE)
	$(QEMU) $(QEMU_FLAGS)

# Run QEMU in headless mode (for Docker/SSH environments)
run-headless: $(ISO_FILE)
	$(QEMU) $(QEMU_FLAGS) -display none -serial stdio

# Debugging with GDB
# Run QEMU with -s -S flags and connect GDB to localhost:1234
run-gdb: $(ISO_FILE)
	$(QEMU) $(QEMU_FLAGS) -s -S
# Need to use: gdb -ex "target remote localhost:1234" build/kernel.bin

# ===== CI Testing =====
test-ci: $(ISO_FILE)
	@echo "Running headless QEMU test..."
	timeout 10s $(QEMU) -cdrom $(ISO_FILE) -display none -serial stdio -m 512M -no-reboot -no-shutdown || true
	@echo "CI test completed"

# ===== INSTALL to /boot =====
install: $(BUILD_DIR)/kernel.bin
	sudo cp $< /boot/arachne_$(ARCH).bin
	@echo "Installed to /boot/arachne_$(ARCH).bin"

clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR) src/impl/*/boot/*.o src/impl/common/*.o src/impl/*/*.o src/impl/common/libk/*.o
	@echo "Clean complete"

# ===== Code Formatting =====
format:
	@echo "Formatting source files..."
	@find src -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i
	@echo "Formatting complete"

format-check:
	@echo "Checking code formatting..."
	@find src -name '*.cpp' -o -name '*.hpp' | xargs clang-format --dry-run --Werror
	@echo "✓ All files are properly formatted"

# Print current configuration
info:
	@echo "=== ArachneOS Build Configuration ==="
	@echo "Architecture: $(ARCH)"
	@echo "Compiler: $(GPP)"
	@echo "Linker: $(LD)"
	@echo "QEMU: $(QEMU)"
	@echo "ISO File: $(ISO_FILE)"
	@echo "====================================" 
