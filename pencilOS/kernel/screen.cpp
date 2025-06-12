// screen.cpp
#include "screen.h"
#include "io.h"

void Screen::initialize() {
    // 这里应该通过VBE或硬件特定方式初始化图形模式
    // 简化为直接映射到线性帧缓冲区
    framebuffer = (uint32_t*)0xE0000000; // 假设的帧缓冲区地址
    width = 1024;
    height = 768;
    pitch = width * 4;
}

void Screen::clear(uint32_t color) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            framebuffer[y * width + x] = color;
        }
    }
}

void Screen::draw_rect(int x, int y, int w, int h, uint32_t color) {
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            int px = x + dx;
            int py = y + dy;
            if (px >= 0 && px < width && py >= 0 && py < height) {
                framebuffer[py * width + px] = color;
            }
        }
    }
}

void Screen::draw_text(int x, int y, const char* text, uint32_t color) {
    // 简化的文本绘制
    while (*text) {
        // 这里应该使用字体位图
        // 简化实现: 只绘制字符的ASCII值
        draw_rect(x, y, 8, 16, color | (*text << 24));
        x += 8;
        text++;
    }
}