// shoot_subgoldy @ 0x441ad0 (thiscall, ret 0x8)
// Free-scan the 20-slot sub-lazer pool, stagger the spawn y down by
// index * 0.01, route through the matched spawn, positional fire cue.

struct Vector3 {
    float x;
    float y;
    float z;
};

struct SubLazerSlot {
    void spawn_sub_lazer_projectile(const Vector3* origin, const Vector3* direction); // matched 98.4%

    char unknown_00[0x80];
    int state; // +0x80
    char unknown_84[0xb0 - 0x84];
};

void play_sound_effect_at_position(int sound_id, const float* position);

class SubLazerPool {
public:
    void shoot_subgoldy(const float* origin, const Vector3* direction);

    SubLazerSlot slots[20];
};

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
    float y = (float)index * -0.0099999998f + origin[1];
    staged.y = y;
    staged.z = z;
    slots[index].spawn_sub_lazer_projectile(&staged, direction);
    play_sound_effect_at_position(15, origin);
}
