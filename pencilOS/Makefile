# Makefile for Simple OS

# 工具链
ASM = nasm
CC = i686-elf-gcc
CXX = i686-elf-g++
LD = i686-elf-ld

# 编译选项
ASMFLAGS = -f elf32
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
CXXFLAGS = -std=gnu++11 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib

# 源文件
BOOT_SRC = boot/boot.asm
KERNEL_SRCS = $(wildcard kernel/*.cpp) $(wildcard kernel/*.c)
OBJS = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(KERNEL_SRCS))) boot/boot.o

# 目标文件
TARGET = simple_os.bin
ISO = simple_os.iso

all: $(TARGET)

$(TARGET): $(OBJS)
    $(LD) $(LDFLAGS) -o $@ $^

boot/boot.o: $(BOOT_SRC)
    $(ASM) -f bin -o $@ $<

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.c
    $(CC) $(CFLAGS) -c -o $@ $<

iso: $(TARGET)
    mkdir -p iso/boot/grub
    cp $(TARGET) iso/boot/
    echo 'menuentry "PencilOS" {' > iso/boot/grub/grub.cfg
    echo '  multiboot /boot/$(TARGET)' >> iso/boot/grub/grub.cfg
    echo '  boot' >> iso/boot/grub/grub.cfg
    echo '}' >> iso/boot/grub/grub.cfg
    grub-mkrescue -o $(ISO) iso

clean:
    rm -f $(OBJS) $(TARGET) $(ISO)
    rm -rf iso

run: $(TARGET)
    qemu-system-i386 -kernel $(TARGET)

run-iso: iso
    qemu-system-i386 -cdrom $(ISO)

.PHONY: all clean run run-iso iso