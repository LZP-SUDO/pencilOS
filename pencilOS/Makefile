# Makefile
ASM = nasm
CC = gcc
LD = ld
OBJCOPY = objcopy
GRUB_MKRESCUE = grub-mkrescue

CFLAGS = -ffreestanding -fno-builtin -fno-stack-protector -nostdlib -m32 -I.
LDFLAGS = -m elf_i386 -T kernel/linker.ld -nostdlib

KERNEL_OBJS = kernel/start.o kernel/kernel.o kernel/gfx.o

all: myos.iso

kernel/start.o: kernel/start.asm
	$(ASM) -f elf32 $< -o $@

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/kernel.bin: $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJS)

bootloader/boot.bin: bootloader/boot.asm
	$(ASM) -f bin $< -o $@

os-image.bin: bootloader/boot.bin kernel/kernel.bin
	cat $^ > $@

iso/boot/os-image.bin: os-image.bin
	cp $< $@

iso/boot/grub/grub.cfg:
	mkdir -p iso/boot/grub
	echo 'menuentry "MyOS" { multiboot /boot/os-image.bin; boot }' > $@

myos.iso: iso/boot/os-image.bin iso/boot/grub/grub.cfg
	$(GRUB_MKRESCUE) -o $@ iso

run: myos.iso
	qemu-system-x86_64 -cdrom myos.iso

clean:
	rm -f *.bin *.o *.iso kernel/*.o kernel/*.bin bootloader/*.bin
	rm -rf iso

.PHONY: all clean run