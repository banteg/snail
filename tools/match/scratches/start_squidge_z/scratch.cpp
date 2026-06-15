// start_squidge_z @ 0x4449a0 (thiscall, ret 4)

#include "player.h"

void SquidgeState::start_squidge_z(float value)
{
    z_phase = value;
    z_velocity = value * -0.00300000003f;
}
