// kernel.cpp - 内核主文件
#include <stdint.h>

// 定义VGA文本模式缓冲区
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

// 当前光标位置
int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F; // 白字黑底

// 初始化终端
void term_init() {
    for (int y = 0; y < VGA_ROWS; y++) {
        for (int x = 0; x < VGA_COLS; x++) {
            const size_t index = y * VGA_COLS + x;
            vga_buffer[index] = (uint16_t)' ' | (uint16_t)term_color << 8;
        }
    }
}

// 输出一个字符
void term_putc(char c) {
    switch (c) {
        case '\n':
            term_col = 0;
            term_row++;
            break;
        default:
            const size_t index = term_row * VGA_COLS + term_col;
            vga_buffer[index] = (uint16_t)c | (uint16_t)term_color << 8;
            term_col++;
            break;
    }
    
    // 处理换行和滚屏
    if (term_col >= VGA_COLS) {
        term_col = 0;
        term_row++;
    }
    
    if (term_row >= VGA_ROWS) {
        // 简单的滚屏实现
        for (int y = 1; y < VGA_ROWS; y++) {
            for (int x = 0; x < VGA_COLS; x++) {
                vga_buffer[(y-1)*VGA_COLS + x] = vga_buffer[y*VGA_COLS + x];
            }
        }
        
        // 清空最后一行
        for (int x = 0; x < VGA_COLS; x++) {
            vga_buffer[(VGA_ROWS-1)*VGA_COLS + x] = (uint16_t)' ' | (uint16_t)term_color << 8;
        }
        
        term_row = VGA_ROWS - 1;
    }
}

// 输出字符串
void term_puts(const char* str) {
    while (*str) {
        term_putc(*str++);
    }
}

// 内核主函数
extern "C" void kernel_main() {
    term_init();
    term_puts("Hello, World from C++ Kernel!\n");
    term_puts("This is a simple operating system kernel.\n");
    term_puts("hello.\n");
    
    // 无限循环
    while (1) {
        asm volatile ("hlt");
    }
}
