/* Author: @harris2001
 * Description: This is the main kernel file for the operating system.
 * It initializes the system, sets up hardware, and starts the main loop.
 */

#include <libk/stdint.hpp>

static volatile uint16_t* const video_memory = (uint16_t*)0xb8000;

void printf(const char* str)
{
    for(size_t i = 0; str[i] != '\0'; i++)
    {
        video_memory[i] = 0x0F00 | str[i];  // 0x0F = white on black
    }
}

extern "C" void kernel_main(void* /*multiboot_structure*/, unsigned int /*magicnumber*/)
{
    // Clear screen first
    for(size_t i = 0; i < 80 * 25; i++)
    {
        video_memory[i] = 0x0F20;  // space with white on black
    }
    
    printf("Kernel Initialized");

    while (1);
    
}

