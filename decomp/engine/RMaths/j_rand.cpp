// j_rand @ 0x44c920 (cdecl)

#include "rmath_random.h"

extern "C" int __cdecl rand();

int __cdecl j_rand()
{
    return rand();
}
