/* Author: @harris2001
 * Description: This is the main kernel file for the operating system.
 * It initializes the system, sets up hardware, and starts the main loop.
 */

#include "arch/arch.hpp"
#include "libk/stdio.hpp"

extern "C" void kernel_main(void* /*multiboot_structure*/, unsigned int /*magicnumber*/)
{
    // Initialize VGA display
    std::vga::init();

    // Initialize architecture
    Arachne::Arch& arch = Arachne::Arch::get_instance();
    arch.init();

    // Print welcome message
    std::io::println("ArachneOS - Minimal Kernel");
    std::io::println("Architecture initialized successfully");

    // Halt CPU
    while (1) {
        __asm__ volatile("hlt");
    }
}
