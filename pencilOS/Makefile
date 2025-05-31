# 交叉编译器前缀
CC = i686-elf-gcc
CXX = i686-elf-g++
AS = i686-elf-as
LD = i686-elf-ld

# 编译选项
CFLAGS = -ffreestanding -O2 -Wall -Wextra
CXXFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS = -ffreestanding -nostdlib -lgcc

# 源文件
SRC = kernel/kernel.cpp
ASM = boot/boot.asm

# 目标文件
OBJ = $(ASM:.asm=.o) $(SRC:.cpp=.o)

# 最终内核映像
KERNEL = myos.bin
ISO = myos.iso

# 默认目标
all: $(ISO)

# 汇编文件编译
%.o: %.asm
	$(AS) -o $@ $<

# C++文件编译
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# 链接内核
$(KERNEL): $(OBJ)
	$(CC) -T linker.ld -o $@ $^ $(LDFLAGS)

# 创建ISO镜像
$(ISO): $(KERNEL)
	mkdir -p isodir/boot/grub
	cp $(KERNEL) isodir/boot/
	echo 'menuentry "MyOS" {' > isodir/boot/grub/grub.cfg
	echo '  multiboot /boot/$(KERNEL)' >> isodir/boot/grub/grub.cfg
	echo '  boot' >> isodir/boot/grub/grub.cfg
	echo '}' >> isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

# 清理
clean:
	rm -f $(OBJ) $(KERNEL) $(ISO)
	rm -rf isodir

# 运行QEMU
run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

.PHONY: all clean run