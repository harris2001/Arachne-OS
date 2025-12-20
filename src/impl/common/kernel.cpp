/* Author: @harris2001
 * Description: This is the main kernel file for the operating system.
 * It initializes the system, sets up hardware, and starts the main loop.
 */

#include "libk/stdio.hpp"
#include "arch/arch.hpp"


extern "C" void kernel_main(void* /*multiboot_structure*/, unsigned int /*magicnumber*/)
{
    Arachne::Arch& arch = Arachne::Arch::get_instance();
    arch.init();
    printf("\n\n\n\n\nKernel Initialized\n");
    // while (1);
    
}

