/* Author: @harris2001
 * Description: This is the main kernel file for the operating system.
 * It initializes the system, sets up hardware, and starts the main loop.
 */

void printf(std::string_view str)
{
    static unsigned short* video_memory = (unsigned short*)0xb8000;

    for(int i = 0; str[i] != '\0'; i++)
    {
        video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
    }
}
