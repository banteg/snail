// random_float_below @ 0x44dc90: cross-port RAND(float, char*)

#include "rmath_random.h"

extern "C" int __cdecl j_rand(void); // jmp thunk @ 0x44c920 to CRT rand

float __cdecl random_float_below(float upper_bound, const char* tag)
{
    (void)tag;
    return j_rand() * upper_bound * 0.000030517578f;
}
