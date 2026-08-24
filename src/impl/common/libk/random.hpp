#include "stdtypes.hpp"

/*
 * For entropy collection we use the following:
 * - Exact cycle count when hardware interrupt occurs
 * - Keyboard scan codes and mouse movement deltas
 * - Hardware RNGs
 * - CPU jitter (jitterentropy)
 */
#define ENTROPY_POOL_SIZE 512 //bytes
#define CHACHA20
namespace std
{
  /* Return number amount of random bytes from the hardware */
  uint8_t* get_random_bytes(int number);
}
