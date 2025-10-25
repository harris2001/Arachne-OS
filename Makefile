NASM_FLAGS = -f elf32
GPP_FLAGS = -m32 -ffreestanding -O2 -Wall -Wextra # freestanding:= no standard library, or main
LD_FLAGS = -m elf_i386 
TARGET = targets/x86_64

SRC_DIR = src/impl/x86_64/boot
BUILD_DIR = build

BOOT_SRC = $(SRC_DIR)/boot.asm
BOOT_BIN = $(BUILD_DIR)/boot.bin

QEMU = qemu-system-x86_64
QEMU_FLAGS = -drive format=raw, file=$(BOOT_BIN)

objects = loader.o \
		  kernel.o

.PHONY: all clean run
# Default target
install: kernel.bin 
	if [ ! -d $(BUILD_DIR) ]; then mkdir -p $(BUILD_DIR); fi
	sudo cp $< $(BOOT_BIN)
	@echo "Build complete"


# Compiling cpp files
%.o: %.cpp
	g++ $(GPP_FLAGS) -c $< -o $@
# Compiling asm files
%.o: %.asm
	nasm $(NASM_FLAGS) $< -o $@

# Linking object files
kernel.bin: $(TARGET)/linker.ld $(objects) 
	ld $(LD_FLAGS) -T $< -o $@ $(objects)

# RUN in QEMU
run: $(BOOT_BIN)
	$(QEMU) $(QEMU_FLAGS) -nographic

clean:
	rm -f $(BOOT_BIN)
