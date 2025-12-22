#include "stdio.hpp"

namespace std
{

// Internal VGA state
namespace
{
volatile uint16_t* video_mem = reinterpret_cast<uint16_t*>(0xB8000);
size_t cursor_x = 0;
size_t cursor_y = 0;
}  // namespace

namespace vga
{

void init()
{
    cursor_x = 0;
    cursor_y = 0;
    clear();
}

void clear()
{
    for (size_t i = 0; i < WIDTH * HEIGHT; ++i) {
        video_mem[i] = COLOR_WHITE_ON_BLACK | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

void scroll()
{
    // Move all lines up by one
    for (size_t i = 0; i < (HEIGHT - 1) * WIDTH; ++i) {
        video_mem[i] = video_mem[i + WIDTH];
    }

    // Clear last line
    size_t start = (HEIGHT - 1) * WIDTH;
    for (size_t i = 0; i < WIDTH; ++i) {
        video_mem[start + i] = COLOR_WHITE_ON_BLACK | ' ';
    }
}

void putchar(char c)
{
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= HEIGHT) {
            scroll();
            cursor_y = HEIGHT - 1;
        }
        return;
    }

    size_t index = cursor_y * WIDTH + cursor_x;
    video_mem[index] = COLOR_WHITE_ON_BLACK | c;

    cursor_x++;
    if (cursor_x >= WIDTH) {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= HEIGHT) {
            scroll();
            cursor_y = HEIGHT - 1;
        }
    }
}

}  // namespace vga

namespace io
{

void putchar(char c)
{
    vga::putchar(c);
}

void print(const char* str)
{
    for (size_t i = 0; str[i] != '\0'; ++i) {
        vga::putchar(str[i]);
    }
}

void println(const char* str)
{
    print(str);
    vga::putchar('\n');
}

void clear()
{
    vga::clear();
}

}  // namespace io

}  // namespace std