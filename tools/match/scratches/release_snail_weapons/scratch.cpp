// release_snail_weapons @ 0x442e40 (thiscall, ret)

#include "player.h"

int next_math_random_value();
float random_float_below(float upper_bound, int tag);

void Snail::release_snail_weapons()
{
    if (invincible_shell.channel_release_steps_active == 0) {
        float random_x =
            ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        float random_y = random_float_below(1.0f, 0);
        random_y = random_y + 0.5f;
        float forward_z = owner_player->velocity.z;
        Vector3* release_step = &jetpack_channel.release_step;
        *release_step = Vector3(random_x, random_y, forward_z) * 0.30000001f;

        random_x = ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        random_y = random_float_below(1.0f, 0);
        random_y = random_y + 0.5f;
        forward_z = owner_player->velocity.z;
        release_step = &weapon_channels[0].release_step;
        *release_step = Vector3(random_x, random_y, forward_z) * 0.30000001f;

        random_x = ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        random_y = random_float_below(1.0f, 0);
        random_y = random_y + 0.5f;
        forward_z = owner_player->velocity.z;
        release_step = &weapon_channels[2].release_step;
        *release_step = Vector3(random_x, random_y, forward_z) * 0.30000001f;

        random_x = ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        random_y = random_float_below(1.0f, 0);
        random_y = random_y + 0.5f;
        Player* owner = owner_player;
        forward_z = owner->velocity.z;
        release_step = &weapon_channels[1].release_step;
        *release_step = Vector3(random_x, random_y, forward_z) * 0.30000001f;
        owner->sub_hover.end_jetpack_hover();
    }
    invincible_shell.channel_release_steps_active = 1;
}
