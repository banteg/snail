// start_squidge_y @ 0x444980 (thiscall, ret 4)

#include "squidge.h"

void Squidge::start_squidge_y(float value)
{
    y_phase = 0.0f;
    y_velocity = value * 0.5f;
}
