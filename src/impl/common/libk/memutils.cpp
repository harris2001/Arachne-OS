#include "memutils.hpp"
#include "exceptions.hpp" 
#include "stdio.hpp"

#define MEMORY_LIMIT 0xFFFFFFFF

namespace std
{

void* memset(void* dest, int val, size_t len)
{
    // if(dest == nullptr) {
    //     throw std::invalid_argument("memset: null pointer argument");
    // }

    // if(reinterpret_cast<uintptr_t>(dest) + len > MEMORY_LIMIT) {
    //     throw std::out_of_range("memset: out of range");
    // }

    unsigned char* ptr = static_cast<unsigned char*>(dest);
    for (size_t i = 0; i < len; ++i) {
        ptr[i] = static_cast<unsigned char>(val);
    }
    return dest;
}

void* memcpy(void* dest, const void* src, size_t len)
{
    // if(len == 0 || dest == src) {
    //     return dest;
    // }
    // if(dest == nullptr || src == nullptr) {
    //     throw std::invalid_argument("memcpy: null pointer argument");
    // }
    // if(&dest + len > src || &src + len > dest) {
    //     throw std::logic_error("memcpy: overlapping memory regions");
    // }

    unsigned char* d = static_cast<unsigned char*>(dest);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    for (size_t i = 0; i < len; ++i) {
        d[i] = s[i];
    }
    return dest;
}

int memcmp(const void* s1, const void* s2, size_t n)
{
    // if(s1 == nullptr || s2 == nullptr){
    //     throw std::invalid_argument("memcmp: null pointer argument");
    // }
    if(n == 0){
        return 0;
    }

    const unsigned char* p1 = static_cast<const unsigned char*>(s1);
    const unsigned char* p2 = static_cast<const unsigned char*>(s2);
    for (size_t i = 0; i < n; ++i) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}
}
