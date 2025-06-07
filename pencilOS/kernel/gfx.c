// kernel/gfx.c
#include "kernel.h"

volatile uint8* vga = (uint8*)0xA0000;

void init_graphics() {
    asm volatile (
        "mov $0x13, %%ax\n"
        "int $0x10\n"
        : : : "ax"
    );
}

void put_pixel(int x, int y, uint8 color) {
    if (x >= 0 && x < 320 && y >= 0 && y < 200) {
        vga[y * 320 + x] = color;
    }
}

void draw_rect(int x, int y, int width, int height, uint8 color) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            put_pixel(x + j, y + i, color);
        }
    }
}

void draw_window(int x, int y, int width, int height, uint8 color) {
    // 窗口背景
    draw_rect(x + 2, y + 2, width - 4, height - 4, color);
    
    // 窗口边框
    draw_rect(x, y, width, 2, 0x0F);          // 上边框
    draw_rect(x, y + height - 2, width, 2, 0x0F); // 下边框
    draw_rect(x, y, 2, height, 0x0F);          // 左边框
    draw_rect(x + width - 2, y, 2, height, 0x0F); // 右边框
    
    // 窗口标题栏
    draw_rect(x + 2, y + 2, width - 4, 10, 0x30); // 青色标题栏
}

// 简单字体渲染 (8x8)
void draw_text(int x, int y, const char* text, uint8 color) {
    while (*text) {
        // 简单绘制字符
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i + j) % 2 == 0) {
                    put_pixel(x + j, y + i, color);
                }
            }
        }
        x += 8;
        text++;
    }
}