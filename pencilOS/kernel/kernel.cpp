#include "screen.h"
#include "keyboard.h"
#include "mouse.h"
#include "gdt.h"
#include "idt.h"

// 全局对象
Screen screen;
Keyboard keyboard;
Mouse mouse;

// 窗口管理器类
class WindowManager {
public:
    void initialize() {
        // 初始化窗口系统
    }
    
    void draw_taskbar() {
        // 绘制任务栏
        screen.draw_rect(0, screen.get_height() - 40, screen.get_width(), 40, 0x00404040);
        screen.draw_rect(5, screen.get_height() - 35, 80, 30, 0x00808080);
        screen.draw_text(15, screen.get_height() - 30, "Start", 0x00FFFFFF);
    }
};

// 内核主函数
extern "C" void kernel_main() {
    // 初始化全局描述符表
    GDT::initialize();
    
    // 初始化中断描述符表
    IDT::initialize();
    
    // 初始化屏幕
    screen.initialize();
    
    // 初始化输入设备
    keyboard.initialize();
    mouse.initialize();
    
    // 初始化窗口管理器
    WindowManager wm;
    wm.initialize();
    
    // 清屏
    screen.clear(0x00000000);
    
    // 显示欢迎信息
    screen.draw_text(10, 10, "PencilOS Kernel Loaded", 0x00FFFFFF);
    
    // 主循环
    while (true) {
        // 绘制任务栏
        wm.draw_taskbar();
        
        // 处理输入
        if (keyboard.has_key()) {
            uint8_t key = keyboard.get_key();
            // 处理键盘输入
        }
        
        if (mouse.has_event()) {
            MouseEvent event = mouse.get_event();
            // 处理鼠标输入
        }
    }
}