// update_banner @ 0x441d40 (thiscall, ret)
// Updates start/banner visibility and its vertical bob offset.

#include "banner.h"

float sine(float angle); // @ 0x44c9d0

void Banner::update_banner()
{
    switch (visibility_mode) {
    case 0:
        if (owner_player->transform.position.z < 40.0f)
            list_flags |= 0x20;
        else
            list_flags &= ~0x20;
        break;

    case 1:
        if (position.z - owner_player->transform.position.z < 46.0f)
            list_flags |= 0x20;
        else
            list_flags &= ~0x20;
        break;
    }

    float next_phase = phase_step + phase;
    phase = next_phase;
    if (next_phase > 1.0f)
        phase = next_phase - 1.0f;

    position.y = sine(phase * 6.2831855f) * 0.25999999f;
}
