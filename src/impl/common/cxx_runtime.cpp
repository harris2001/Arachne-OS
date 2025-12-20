#include "libk/stdtypes.hpp"

extern "C" void __cxa_pure_virtual()
{
    while (1) __asm__ volatile("hlt");
}

extern "C" int __cxa_guard_acquire(size_t* guard) 
{
    if (*((unsigned char*)guard) == 0) {
        *((unsigned char*)guard) = 1;
        return 1;
    }
    return 0;
}

extern "C" void __cxa_guard_release(size_t*) {}
extern "C" void __cxa_guard_abort(size_t*) {}

extern "C" int atexit(void (*)(void)) { return 0; }

void* operator new(size_t size) { return (void*)size; }
void* operator new[](size_t size) {return (void*)size; }

void operator delete(void*) noexcept {}
void operator delete(void*, size_t) noexcept {}
void operator delete[](void*) noexcept {}
void operator delete[](void*, size_t) noexcept {}
