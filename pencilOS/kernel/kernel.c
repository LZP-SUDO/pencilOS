// kernel/kernel.c
#include "kernel.h"

void kernel_main() {
    init_graphics();
    
    // 绘制窗口
    draw_window(50, 50, 220, 120, 0x1F);  // 蓝色窗口
    
    // 在窗口中显示文本
    draw_text(70, 70, "Welcome to pencilOS!", 0x0F);
    draw_text(70, 90, "If you see this text, the system has started successfully", 0x0E);
    
    // 保持显示
    while (1) {
        asm volatile ("hlt");
    }
}