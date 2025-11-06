/* Author: @harris2001
 * Description: This is the main kernel file for the operating system.
 * It initializes the system, sets up hardware, and starts the main loop.
 */

#include <string_view>
#include <stdint.h>       // for uint16_t

static volatile uint16_t* const video_memory = (uint16_t*)0xb8000;

void printf(std::string_view str)
{
    for(size_t i = 0; i < str.size(); i++)
    {
        video_memory[i] = 0x0F00 | str[i];  // 0x0F = white on black
    }
}

extern "C" void kernel_main(void* /*multiboot_structure*/, unsigned int /*magicnumber*/)
{
    printf("Kernel Initialized\n");

    while (1);
    
}

