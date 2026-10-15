// RAND @ 0x44dc90: cross-port RAND(float, char*)

#include "rmath_random.h"

float __cdecl RAND(float upper_bound, char* tag)
{
    (void)tag;
    return j_rand() * upper_bound * 0.000030517578f;
}
