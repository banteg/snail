// shoot_subgoldy @ 0x441ad0 (thiscall, ret 0x8)

struct Vector3 {
    float x;
    float y;
    float z;
};

class SubLazerSlot {
public:
    void spawn_sub_lazer_projectile(const Vector3* origin, const Vector3* direction);

    char unknown_00[0x80];
    int state;
    char unknown_84[0xb0 - 0x84];
};

class SubLazerPool {
public:
    void shoot_subgoldy(const Vector3* origin, const Vector3* direction);
};

class PositionalSoundEffectPlayer {
public:
    void play_sound_effect_at_position(int sound_id, const Vector3* position);
};

extern PositionalSoundEffectPlayer g_positional_sound_effect_player; // 0x78ff88

void SubLazerPool::shoot_subgoldy(const Vector3* origin, const Vector3* direction)
{
    int slot_index = 0;
    volatile int* slot_state = (volatile int*)((char*)this + 0x80);
    while (*slot_state != 0) {
        ++slot_index;
        slot_state = (volatile int*)((char*)slot_state + 0xb0);
        if (slot_index >= 20)
            return;
    }

    int origin_x = *(const int*)&origin->x;
    int origin_z = *(const int*)&origin->z;
    float spawn_y = (float)slot_index * -0.0099999998f + origin->y;
    Vector3 spawn_origin;
    *(int*)&spawn_origin.x = origin_x;
    spawn_origin.y = spawn_y;
    *(int*)&spawn_origin.z = origin_z;
    SubLazerSlot* slot = (SubLazerSlot*)((char*)this + 0xb0 * slot_index);
    slot->spawn_sub_lazer_projectile(&spawn_origin, direction);
    g_positional_sound_effect_player.play_sound_effect_at_position(15, origin);
}
