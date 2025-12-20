#include "stdtypes.hpp"

static volatile uint16_t* const video_memory = (uint16_t*)0xb8000;

void printf(const char* str)
{
    for(size_t i = 0; str[i] != '\0'; i++)
    {
        video_memory[i] = 0x0F00 | str[i];  // 0x0F = white on black
    }
}

void _endline()
{
    
}