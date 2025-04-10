ASM = nasm

SRC_DIR = src
BUILD_DIR = build

BOOT_SRC = $(SRC_DIR)/simple_boot.asm
BOOT_BIN = $(BUILD_DIR)/simple_boot.bin

NASM_FLAGS = -f bin

QEMU = qemu-system-x86_64
QEMU_FLAGS = -drive format=raw,file=$(BOOT_BIN)

GDB_PORT = 1234

# Default target
all: $(BOOT_BIN)

# Assembling the bootloader
# dependencies are $< and $@ is the target
$(BOOT_BIN): $(BOOT_SRC)
	nasm $(NASM_FLAGS) $< -o $@ 

# RUN in QEMU
run: $(BOOT_BIN)
	$(QEMU) $(QEMU_FLAGS)

# When we don't want to use GUI (for debugging)
run-debug: $(BOOT_BIN)
	$(QEMU) $(QEMU_FLAGS) -nographic

# Run QEMU with gdb server running on $(GDB_PORT) for better debugging
debug: $(BOOT_BIN)
	$(QEMU) $(QEMU_FLAGS) -gdb tcp::$(GDB_PORT) -S

# Run gdb and connect to the  vnc server running on port 1234
gdb:
	gdb -ex "target remote localhost:$(GDB_PORT)" -ex "layout asm" 

# Run with VNC (we can connect to it using a `vncviewer localhost:5900`)
run-vnc: $(BOOT_BIN)
	$(QEMU) $(QEMU_FLAGS) -vnc :0

clean:
	rm -f $(BOOT_BIN)
