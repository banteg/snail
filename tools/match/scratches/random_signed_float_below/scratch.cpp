// random_signed_float_below @ 0x44dc70 (cdecl)

// random_signed_float_below @ 0x44dc70: cross-port SRAND(float, char*)

#include "rmath_random.h"

extern "C" int __cdecl j_rand(); // jmp thunk @ 0x44c920 to CRT rand

float __cdecl random_signed_float_below(float upper_bound, const char* tag)
{
    (void)tag;
    return ((float)j_rand() - 16384.0f) * upper_bound * 0.000061035156f;
}
