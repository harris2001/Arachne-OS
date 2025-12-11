# ===== Architecture Configuration =====
# Override with: make ARCH=x86_64
# Supported architectures: x86_64
ARCH ?= x86_64

# Architecture-specific settings
ifeq ($(ARCH),x86_64)
    NASM_FLAGS = -f elf32
    GPP = g++
    GPP_FLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -nostdinc++ -fno-use-cxa-atexit -Isrc/impl/common
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
    $(error Unsupported architecture: $(ARCH). Supported: x86_64)
endif

BUILD_DIR = build
ISO_DIR = $(TARGET_DIR)/iso
ISO_FILE = $(BUILD_DIR)/$(ISO_NAME)
QEMU_FLAGS = -cdrom $(ISO_FILE) -m 512M -boot d -no-reboot -no-shutdown 

# ===== Source Files =====
# Common kernel objects (architecture-independent)
COMMON_OBJECTS = \
    src/impl/common/kernel.o \
    src/impl/common/cxx_runtime.o

# All object files
OBJECTS = $(BOOT_OBJECTS) $(COMMON_OBJECTS) $(ARCH_OBJECTS)

# Default target
.PHONY: all clean run iso install

all: $(ISO_FILE)

# ===== Compiling to ISO =====

# Compiling C++
%.o: %.cpp
	$(GPP) $(GPP_FLAGS) -c $< -o $@

# Compiling Assembly 
%.o: %.asm
	nasm $(NASM_FLAGS) $< -o $@

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

# ===== CI Testing =====
test-ci: $(ISO_FILE)
	@echo "Running headless QEMU test..."
	timeout 10s $(QEMU) -cdrom $(ISO_FILE) -display none -serial stdio -m 512M -no-reboot -no-shutdown || true
	@echo "CI test completed"

# ===== INSTALL to /boot =====
install: $(BUILD_DIR)/kernel.bin
	sudo cp $< /boot/arachne_x86_64.bin
	@echo "Installed to /boot/arachne_x86_64.bin"

clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR) src/impl/*/boot/*.o src/impl/common/*.o src/impl/*/*.o
	@echo "Clean complete"

# Print current configuration
info:
	@echo "=== ArachneOS Build Configuration ==="
	@echo "Architecture: $(ARCH)"
	@echo "Compiler: $(GPP)"
	@echo "Linker: $(LD)"
	@echo "QEMU: $(QEMU)"
	@echo "ISO File: $(ISO_FILE)"
	@echo "====================================" 
