// kernel/kernel.h
#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

void put_pixel(int x, int y, uint8 color);
void draw_rect(int x, int y, int width, int height, uint8 color);
void draw_window(int x, int y, int width, int height, uint8 color);
void draw_text(int x, int y, const char* text, uint8 color);
void init_graphics();
void kernel_main();

#endif