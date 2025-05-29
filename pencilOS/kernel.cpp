#include <stdint.h>
#include <stddef.h>
#include <string.h>

// 定义基本类型
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// ================== 文本模式部分 ==================
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F;

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

void term_setcolor(uint8_t color) {
    term_color = color;
}

void term_putentryat(char c, uint8_t color, int x, int y) {
    const int index = y * VGA_COLS + x;
    vga_buffer[index] = (uint16_t)color << 8 | c;
}

void term_newline() {
    term_col = 0;
    if (++term_row == VGA_ROWS) {
        for (int y = 1; y < VGA_ROWS; y++) {
            for (int x = 0; x < VGA_COLS; x++) {
                const int index_prev = (y - 1) * VGA_COLS + x;
                const int index_curr = y * VGA_COLS + x;
                vga_buffer[index_prev] = vga_buffer[index_curr];
            }
        }
        for (int x = 0; x < VGA_COLS; x++) {
            const int index = (VGA_ROWS - 1) * VGA_COLS + x;
            vga_buffer[index] = (uint16_t)term_color << 8 | ' ';
        }
        term_row = VGA_ROWS - 1;
    }
}

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

void term_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        term_putchar(data[i]);
    }
}

void term_writestring(const char* str) {
    while (*str) {
        term_putchar(*str++);
    }
}

// ================== 图形模式部分 ==================
struct FrameBufferInfo {
    uint32_t* address;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint8_t bpp;
    bool available;
};

FrameBufferInfo fb_info = {0};

class FrameBuffer {
public:
    FrameBuffer(uint32_t* address, uint32_t width, uint32_t height, uint32_t pitch)
        : buffer(address), width(width), height(height), pitch(pitch) {}
    
    void put_pixel(uint32_t x, uint32_t y, uint32_t color) {
        if(x >= width || y >= height) return;
        buffer[y * (pitch/4) + x] = color;
    }
    
    void clear(uint32_t color) {
        for(uint32_t y = 0; y < height; y++) {
            for(uint32_t x = 0; x < width; x++) {
                put_pixel(x, y, color);
            }
        }
    }
    
    void draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) {
        for(uint32_t dy = 0; dy < h; dy++) {
            for(uint32_t dx = 0; dx < w; dx++) {
                put_pixel(x+dx, y+dy, color);
            }
        }
    }
    
private:
    uint32_t* buffer;
    uint32_t width, height, pitch;
};

FrameBuffer* global_fb = nullptr;

// 通过Multiboot信息获取帧缓冲（需要GRUB启动）
void init_graphics_from_multiboot(uint32_t addr) {
    struct MultibootInfo {
        uint32_t flags;
        uint32_t mem_lower;
        uint32_t mem_upper;
        // ... 其他字段
        uint32_t framebuffer_addr;
        uint32_t framebuffer_pitch;
        uint32_t framebuffer_width;
        uint32_t framebuffer_height;
        uint8_t framebuffer_bpp;
        // ... 其他字段
    } __attribute__((packed));
    
    MultibootInfo* mb_info = (MultibootInfo*)addr;
    
    if(mb_info->flags & (1 << 12)) { // 检查帧缓冲标志位
        fb_info.address = (uint32_t*)mb_info->framebuffer_addr;
        fb_info.width = mb_info->framebuffer_width;
        fb_info.height = mb_info->framebuffer_height;
        fb_info.pitch = mb_info->framebuffer_pitch;
        fb_info.bpp = mb_info->framebuffer_bpp;
        fb_info.available = true;
        
        global_fb = new FrameBuffer(fb_info.address, fb_info.width, fb_info.height, fb_info.pitch);
    }
}

// 简单图形界面演示
void graphics_demo() {
    if(!global_fb) return;
    
    // 清屏为深灰色
    global_fb->clear(0x333333);
    
    // 绘制一个蓝色矩形
    global_fb->draw_rect(100, 100, 200, 150, 0x0000FF);
    
    // 绘制一个绿色矩形
    global_fb->draw_rect(150, 150, 200, 150, 0x00FF00);
    
    // 绘制一个红色矩形
    global_fb->draw_rect(200, 200, 200, 150, 0xFF0000);
}

// ================== 内核主函数 ==================
extern "C" void kernel_main(uint32_t multiboot_info_addr) {
    term_clear();
    term_setcolor(0x0A);
    term_writestring("Welcome to SimpleOS with Graphics!\n");
    term_setcolor(0x0F);
    
    // 尝试初始化图形模式
    init_graphics_from_multiboot(multiboot_info_addr);
    
    if(fb_info.available) {
        term_writestring("Graphics mode initialized: ");
        term_writestring(itoa(fb_info.width, 10));
        term_writestring("x");
        term_writestring(itoa(fb_info.height, 10));
        term_writestring("\n");
        
        // 运行图形演示
        graphics_demo();
    } else {
        term_writestring("Falling back to text mode\n");
    }
    
    term_writestring("Kernel initialized successfully.\n");
    
    while(1) {
        // 内核空闲循环
    }
}

// 简单的整数转字符串函数（仅用于演示）
const char* itoa(int value, int base) {
    static char buf[32] = {0};
    int i = 30;
    for(; value && i ; --i, value /= base) {
        buf[i] = "0123456789abcdef"[value % base];
    }
    return &buf[i+1];
}
