// initialize_blink_random @ 0x4408c0 (thiscall, ret)

#include "blink_random_table.h"

int next_math_random_value();

int BlinkRandomTable::initialize_blink_random()
{
    index = 0;
    float* sample = samples;
    int remaining = 24;
    int result;

    do {
        result = next_math_random_value();
        --remaining;
        *sample = 1.0f / (((float)result * 0.000030517578f + 1.0f) * 60.0f);
        ++sample;
    } while (remaining);

    return result;
}
