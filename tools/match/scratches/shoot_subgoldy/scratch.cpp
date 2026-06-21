// shoot_subgoldy @ 0x441ad0 (thiscall, ret 0x8)
// Free-scan the 20-slot sub-lazer pool, stagger the spawn y down by
// index * 0.01, route through the matched spawn, positional fire cue.

#include "sub_lazer_types.h"
#include "sound_effect_manager.h"

void SubLazerPool::shoot_subgoldy(const float* origin, const Vector3* direction)
{
    int index = 0;
    int* state = &slots[0].state;
    while (index < 20) {
        if (*state == 0)
            goto found_slot;
        index++;
        state += 44;
    }
    return;

found_slot:
    Vector3 raw;
    Vector3 staged;
    raw.x = origin[0];
    float stagger_y = (float)index * -0.0099999998f;
    float y = stagger_y + origin[1];
    raw.y = y;
    raw.z = origin[2];
    staged = raw;
    slots[index].spawn_sub_lazer_projectile(&staged, direction);
    g_sound_effect_manager.play_sound_effect_at_position(15, origin);
}
