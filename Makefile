NASM_FLAGS = -f elf32
# freestanding:= no standard library, or main
# -fno-exceptions -fno-rtti := disable exceptions and RTTI
GPP_FLAGS = -m32 -ffreestanding -O2 -Wall -Wextra  -fno-exceptions -fno-rtti 
LD_FLAGS = -m elf_i386 

SRC_DIR = src/impl/x86_64/boot
BUILD_DIR = build
TARGET = targets/x86_64

ISO_DIR = $(TARGET)/iso
ISO_FILE = $(BUILD_DIR)/arachne_x86_64.iso

QEMU = qemu-system-x86_64
QEMU_FLAGS = -cdrom $(ISO_FILE) -m 512M -boot d -no-reboot -no-shutdown 

# Source files
OBJECTS = \
		$(SRC_DIR)/header.o \
		$(SRC_DIR)/loader.o \
		src/impl/common/kernel.o

# Default target
.PHONY: all clean run iso install

all: $(ISO_FILE)

# ===== Compiling to ISO =====

# Compiling C++
%.o: %.cpp
	g++ $(GPP_FLAGS) -c $< -o $@

# Compiling Assembly 
%.o: %.asm
	nasm $(NASM_FLAGS) $< -o $@

# ===== Linking Kernel ELF =====
$(BUILD_DIR)/kernel.bin: $(OBJECTS) $(TARGET)/linker.ld
	mkdir -p $(BUILD_DIR)
	ld $(LD_FLAGS) -T $(TARGET)/linker.ld -o $@ $(OBJECTS)

# ===== Building GRUB ISO =====
$(ISO_FILE): $(BUILD_DIR)/kernel.bin $(TARGET)/iso/boot/grub/grub.cfg
	mkdir -p $(ISO_DIR)/boot
	cp $(BUILD_DIR)/kernel.bin $(ISO_DIR)/boot/kernel.bin
	grub-mkrescue -o $(ISO_FILE) $(ISO_DIR)


# ===== RUN in QEMU =====
run: $(ISO_FILE)
	$(QEMU) $(QEMU_FLAGS)

# ===== INSTALL to /boot =====
install: $(BUILD_DIR)/kernel.bin
	sudo cp $< /boot/arachne_x86_64.bin
	@echo "Installed to /boot/arachne_x86_64.bin"

clean:
	rm -rf $(BUILD_DIR) $(SRC_DIR)/*.o src/impl/common/*.o 
