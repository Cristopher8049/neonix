# Makefile to build MiOS

# Paths
BOOTLOADER = boot/bootloader.asm
KERNEL_ASM = kernel/kernel_entry.asm
KERNEL_C = kernel/kernel.c
BUILD_DIR = build
ISO_DIR = iso

# Tools
AS = nasm
CC = i386-elf-gcc
LD = i386-elf-ld

# Flags
CFLAGS = -ffreestanding -m32 -g -c
LDFLAGS = -Ttext 0x1000 --oformat binary

# Output files
BOOT_BIN = $(BUILD_DIR)/boot.bin
KERNEL_ENTRY_OBJ = $(BUILD_DIR)/kernel_entry.o
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
KERNEL_BIN = $(BUILD_DIR)/full_kernel.bin
OS_BIN = $(ISO_DIR)/NeonixOS.bin

.PHONY: all run clean

all: $(OS_BIN)

$(BUILD_DIR) $(ISO_DIR):
	mkdir -p $@

$(BOOT_BIN): $(BOOTLOADER) | $(BUILD_DIR)
	$(AS) $< -f bin -o $@

$(KERNEL_ENTRY_OBJ): $(KERNEL_ASM) | $(BUILD_DIR)
	$(AS) $< -f elf -o $@

$(KERNEL_OBJ): $(KERNEL_C) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(KERNEL_OBJ)
	$(LD) -o $@ $(LDFLAGS) $(KERNEL_ENTRY_OBJ) $(KERNEL_OBJ)

$(OS_BIN): $(BOOT_BIN) $(KERNEL_BIN) | $(ISO_DIR)
	cat $(BOOT_BIN) $(KERNEL_BIN) > $@

run: $(OS_BIN)
	qemu-system-x86_64 -drive format=raw,file=$(OS_BIN),index=0,if=floppy -m 128M

clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR)
