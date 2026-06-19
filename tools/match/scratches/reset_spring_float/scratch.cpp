// reset_spring_float @ 0x41aa30 (thiscall)

#include "spring_float.h"

void SpringFloat::reset_spring_float()
{
    output = 0.0f;
    target_velocity = 0.0f;
    target_output = 0.0f;
    velocity = 0.0f;
    phase = 0.0f;
}
