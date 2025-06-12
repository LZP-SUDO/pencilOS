// screen.h
#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

class Screen {
public:
    void initialize();
    void clear(uint32_t color);
    void draw_rect(int x, int y, int w, int h, uint32_t color);
    void draw_text(int x, int y, const char* text, uint32_t color);
    int get_width() const { return width; }
    int get_height() const { return height; }

private:
    uint32_t* framebuffer;
    int width;
    int height;
    int pitch;
};

#endif