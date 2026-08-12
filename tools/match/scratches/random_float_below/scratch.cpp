// RAND @ 0x44dc90: cross-port RAND(float, char*)

#include "rmath_random.h"

extern "C" int __cdecl j_rand(void); // jmp thunk @ 0x44c920 to CRT rand

float __cdecl RAND(float upper_bound, char* tag)
{
    (void)tag;
    return j_rand() * upper_bound * 0.000030517578f;
}
