all: boot.img

boot.img: ./boot/bootloader.asm
	nasm -f bin ./boot/bootloader.asm -o build/boot.img

run: boot.img
	qemu-system-i386 -fda boot.img

clean:
	rm -f boot.img