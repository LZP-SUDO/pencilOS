#pragma once
#include "io.hpp"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

class Terminal {
public:
    static const size_t WIDTH = 80;
    static const size_t HEIGHT = 25;
    
    void initialize() {
        row = 0;
        column = 0;
        color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
        buffer = (uint16_t*)0xB8000;
        clear();
    }
    
    void clear() {
        for (size_t y = 0; y < HEIGHT; y++) {
            for (size_t x = 0; x < WIDTH; x++) {
                put_char(' ', x, y);
            }
        }
        row = 0;
        column = 0;
    }
    
    void write_string(const char* str) {
        for (size_t i = 0; str[i] != '\0'; i++) {
            put_char(str[i]);
        }
    }
    
    void read_string(char* buffer, size_t length) {
        size_t index = 0;
        while (true) {
            char c = read_char();
            if (c == '\n' || index >= length - 1) {
                buffer[index] = '\0';
                put_char('\n');
                return;
            } else if (c == '\b' && index > 0) {
                index--;
                put_char('\b');
            } else if (c >= ' ' && c <= '~') {
                buffer[index++] = c;
                put_char(c);
            }
        }
    }
    
private:
    enum VGAColor {
        COLOR_BLACK = 0,
        COLOR_BLUE = 1,
        COLOR_GREEN = 2,
        COLOR_CYAN = 3,
        COLOR_RED = 4,
        COLOR_MAGENTA = 5,
        COLOR_BROWN = 6,
        COLOR_LIGHT_GREY = 7,
        COLOR_DARK_GREY = 8,
        COLOR_LIGHT_BLUE = 9,
        COLOR_LIGHT_GREEN = 10,
        COLOR_LIGHT_CYAN = 11,
        COLOR_LIGHT_RED = 12,
        COLOR_LIGHT_MAGENTA = 13,
        COLOR_LIGHT_BROWN = 14,
        COLOR_WHITE = 15,
    };
    
    size_t row;
    size_t column;
    uint8_t color;
    uint16_t* buffer;
    
    uint8_t make_color(VGAColor fg, VGAColor bg) {
        return fg | bg << 4;
    }
    
    uint16_t make_vgaentry(char c, uint8_t color) {
        return (uint16_t)c | (uint16_t)color << 8;
    }
    
    void put_char(char c, size_t x, size_t y) {
        buffer[y * WIDTH + x] = make_vgaentry(c, color);
    }
    
    void put_char(char c) {
        if (c == '\n') {
            column = 0;
            if (++row == HEIGHT) {
                scroll();
                row--;
            }
            return;
        } else if (c == '\b') {
            if (column > 0) {
                column--;
            } else if (row > 0) {
                row--;
                column = WIDTH - 1;
            }
            put_char(' ', column, row);
            return;
        }
        
        put_char(c, column, row);
        if (++column == WIDTH) {
            column = 0;
            if (++row == HEIGHT) {
                scroll();
                row--;
            }
        }
    }
    
    char read_char() {
        while (!(inb(0x64) & 0x1));
        return inb(0x60);
    }
    
    void scroll() {
        for (size_t y = 1; y < HEIGHT; y++) {
            for (size_t x = 0; x < WIDTH; x++) {
                buffer[(y - 1) * WIDTH + x] = buffer[y * WIDTH + x];
            }
        }
        
        for (size_t x = 0; x < WIDTH; x++) {
            buffer[(HEIGHT - 1) * WIDTH + x] = make_vgaentry(' ', color);
        }
    }
};