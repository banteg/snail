// initialize_blink_random @ 0x4408c0 (thiscall, ret)

#include "rmath_random.h"
#include "subgame_runtime.h"

void cRSubGame::BlinkRandInit()
{
    blink_random_index = 0;
    float* sample = blink_random_samples;
    int remaining = 24;

    do {
        int result = gRMathRand2();
        --remaining;
        *sample = 1.0f / (((float)result * 0.000030517578f + 1.0f) * 60.0f);
        ++sample;
    } while (remaining);
}
