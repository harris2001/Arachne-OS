ASM = nasm

SRC_DIR = src/impl/x86_64/boot
BUILD_DIR = build

BOOT_SRC = $(SRC_DIR)/boot.asm
BOOT_BIN = $(BUILD_DIR)/boot.bin

NASM_FLAGS = -f bin

QEMU = qemu-system-x86_64
QEMU_FLAGS = -drive format=raw,file=$(BOOT_BIN)

GDB_PORT = 1234

# Default target
all: $(BOOT_BIN)

# Assembling the bootloader
# dependencies are $< and $@ is the target
$(BOOT_BIN): $(BOOT_SRC)
	if [ ! -d $(BUILD_DIR) ]; then mkdir -p $(BUILD_DIR); fi
	nasm $(NASM_FLAGS) $< -o $@ 

# RUN in QEMU
run: $(BOOT_BIN)
	$(QEMU) $(QEMU_FLAGS) -nographic

clean:
	rm -f $(BOOT_BIN)
