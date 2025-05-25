// 内核主文件
#include <stdint.h>

// 定义基本类型
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// VGA文本模式缓冲区地址
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

// 当前光标位置
int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F; // 白字黑底

// 清屏
void term_clear() {
    for (int y = 0; y < VGA_ROWS; y++) {
        for (int x = 0; x < VGA_COLS; x++) {
            const int index = y * VGA_COLS + x;
            vga_buffer[index] = (uint16_t)term_color << 8 | ' ';
        }
    }
    term_col = 0;
    term_row = 0;
}

// 设置终端颜色
void term_setcolor(uint8_t color) {
    term_color = color;
}

// 在指定位置输出字符
void term_putentryat(char c, uint8_t color, int x, int y) {
    const int index = y * VGA_COLS + x;
    vga_buffer[index] = (uint16_t)color << 8 | c;
}

// 换行处理
void term_newline() {
    term_col = 0;
    if (++term_row == VGA_ROWS) {
        // 向上滚动一行
        for (int y = 1; y < VGA_ROWS; y++) {
            for (int x = 0; x < VGA_COLS; x++) {
                const int index_prev = (y - 1) * VGA_COLS + x;
                const int index_curr = y * VGA_COLS + x;
                vga_buffer[index_prev] = vga_buffer[index_curr];
            }
        }
        // 清空最后一行
        for (int x = 0; x < VGA_COLS; x++) {
            const int index = (VGA_ROWS - 1) * VGA_COLS + x;
            vga_buffer[index] = (uint16_t)term_color << 8 | ' ';
        }
        term_row = VGA_ROWS - 1;
    }
}

// 输出字符
void term_putchar(char c) {
    if (c == '\n') {
        term_newline();
    } else {
        term_putentryat(c, term_color, term_col, term_row);
        if (++term_col == VGA_COLS) {
            term_newline();
        }
    }
}

// 输出字符串
void term_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        term_putchar(data[i]);
    }
}

// 输出C风格字符串
void term_writestring(const char* str) {
    while (*str) {
        term_putchar(*str++);
    }
}

// 全局构造函数调用
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

// 内核主函数
extern "C" void kernel_main() {
    term_clear();
    term_setcolor(0x0A); // 亮绿色
    term_writestring("Welcome to SimpleOS!\n");
    term_setcolor(0x0F); // 白色
    
    term_writestring("Kernel initialized successfully.\n");
    term_writestring("This is a minimal operating system kernel written in C++.\n");
    
    while (1) {
        // 内核空闲循环
    }
}