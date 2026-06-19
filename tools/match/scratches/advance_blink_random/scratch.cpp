// advance_blink_random @ 0x4408a0 (thiscall, ret)

#include "blink_random_table.h"

double BlinkRandomTable::advance_blink_random()
{
    int next_index = (index + 1) % 24;
    index = next_index;
    return samples[next_index];
}
