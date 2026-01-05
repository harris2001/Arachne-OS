#pragma once
#include "stdio.hpp"
namespace std
{

/*
 * Sets the first 'len' bytes to 'val' 
 *
 * !WARNING! : This function does not handle misaligned memory accesses.
 *
 * @param dest : Pointer to the memory area to be set.
 * @param val  : Value to be set (interpreted as an unsigned char according to C standard).
 * @param len  : Number of bytes to be set to the value.
 * @return Pointer to the memory area 'dest'.
 */
void* memset(void* dest, int val, size_t len);

/* 
 * Copies 'len' bytes from memory src to dest.
 * The memory areas must not overlap otherwise an exception is thrown.
 *
 * @param dest : Pointer to the destination memory area.
 * @param src  : Pointer to the source memory area.
 * @param len  : Number of bytes to copy.
 * @return Pointer to the destination memory area.
 */
void* memcpy(void* dest, const void* src, size_t len);

/*
 * Compares the first 'n' bytes of 'p1' to the first 'n' bytes of 'p2'.
 *
 * @param p1 : Pointer to the first memory area.
 * @param p2 : Pointer to the second memory area.
 * @param n  : Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero (p1 < p2, p1 == p2, p1 > p2). 
 */
int memcmp(const void* s1, const void* s2, size_t n);

}  // namespace std
