# 工具链配置
CC = i686-elf-g++
AS = nasm
LD = i686-elf-ld

# 编译选项
CFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
ASFLAGS = -f elf32
LDFLAGS = -T linker.ld -nostdlib

# 源文件
SRCS = kernel.cpp
OBJS = $(SRCS:.cpp=.o) boot.o

# 目标文件
TARGET = myos.elf
ISO = myos.iso

all: $(ISO)

$(ISO): $(TARGET)
    mkdir -p isodir/boot/grub
    cp $(TARGET) isodir/boot/myos.elf
    cp grub.cfg isodir/boot/grub/grub.cfg
    grub-mkrescue -o $(ISO) isodir

$(TARGET): $(OBJS)
    $(LD) $(LDFLAGS) -o $@ $^

%.o: %.cpp
    $(CC) $(CFLAGS) -c $< -o $@

boot.o: boot.asm
    $(AS) $(ASFLAGS) $< -o $@

clean:
    rm -f $(OBJS) $(TARGET) $(ISO)
    rm -rf isodir

run: $(ISO)
    qemu-system-i386 -cdrom $(ISO)

.PHONY: all clean run
