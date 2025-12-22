#pragma once
#include "stdtypes.hpp"

namespace std
{

// Terminal I/O namespace
namespace io
{
void putchar(char c);
void print(const char* str);
void println(const char* str);
void clear();
}  // namespace io

// VGA text mode driver
namespace vga
{
constexpr size_t WIDTH = 80;
constexpr size_t HEIGHT = 25;
constexpr uint16_t COLOR_WHITE_ON_BLACK = 0x0F00;

void init();
void putchar(char c);
void clear();
void scroll();
}  // namespace vga

}  // namespace std