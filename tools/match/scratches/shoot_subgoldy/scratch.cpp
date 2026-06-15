// shoot_subgoldy @ 0x441ad0 (thiscall, ret 0x8)
// Free-scan the 20-slot sub-lazer pool, stagger the spawn y down by
// index * 0.01, route through the matched spawn, positional fire cue.

#include "sub_lazer_types.h"

void play_sound_effect_at_position(int sound_id, const float* position);

void SubLazerPool::shoot_subgoldy(const float* origin, const Vector3* direction)
{
    int index = 0;
    int* state = &slots[0].state;
    while (*state) {
        ++index;
        state += 44;
        if (index >= 20)
            return;
    }
    Vector3 staged;
    float z = origin[2];
    staged.x = origin[0];
    float stagger_y = (float)index * -0.0099999998f;
    float y = stagger_y + origin[1];
    staged.y = y;
    staged.z = z;
    slots[index].spawn_sub_lazer_projectile(&staged, direction);
    play_sound_effect_at_position(15, origin);
}
