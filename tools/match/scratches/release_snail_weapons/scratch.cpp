// release_snail_weapons @ 0x442e40 (thiscall, ret)

#include "player.h"

int next_math_random_value();
float random_float_below(float upper_bound, int tag);

void PlayerPresentationController::release_snail_weapons()
{
    if (invincible_shell.channel_release_steps_active == 0) {
        float random_x =
            ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        float random_y = random_float_below(1.0f, 0);
        random_y = random_y + 0.5f;
        float forward_z = owner_player->velocity.z;
        Vector3* release_step = &jetpack_channel.release_step;
        Vector3 staged_release_step;
        staged_release_step.z = forward_z;
        float step_x = random_x * 0.30000001f;
        float step_y = random_y * 0.30000001f;
        float step_z = staged_release_step.z * 0.30000001f;
        staged_release_step.x = step_x;
        staged_release_step.y = step_y;
        staged_release_step.z = step_z;
        *release_step = staged_release_step;

        random_x = ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        random_y = random_float_below(1.0f, 0);
        random_y = random_y + 0.5f;
        forward_z = owner_player->velocity.z;
        release_step = &weapon_channels[0].release_step;
        staged_release_step.z = forward_z;
        step_x = random_x * 0.30000001f;
        step_y = random_y * 0.30000001f;
        step_z = staged_release_step.z * 0.30000001f;
        staged_release_step.x = step_x;
        staged_release_step.y = step_y;
        staged_release_step.z = step_z;
        *release_step = staged_release_step;

        random_x = ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        random_y = random_float_below(1.0f, 0);
        random_y = random_y + 0.5f;
        forward_z = owner_player->velocity.z;
        release_step = &weapon_channels[2].release_step;
        staged_release_step.z = forward_z;
        step_x = random_x * 0.30000001f;
        step_y = random_y * 0.30000001f;
        step_z = staged_release_step.z * 0.30000001f;
        staged_release_step.x = step_x;
        staged_release_step.y = step_y;
        staged_release_step.z = step_z;
        *release_step = staged_release_step;

        random_x = ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        random_y = random_float_below(1.0f, 0);
        random_y = random_y + 0.5f;
        Player* owner = owner_player;
        forward_z = owner->velocity.z;
        release_step = &weapon_channels[1].release_step;
        staged_release_step.z = forward_z;
        step_x = random_x * 0.30000001f;
        step_y = random_y * 0.30000001f;
        step_z = staged_release_step.z * 0.30000001f;
        staged_release_step.x = step_x;
        staged_release_step.y = step_y;
        staged_release_step.z = step_z;
        *release_step = staged_release_step;
        owner->jetpack_gauge.end_jetpack_hover();
    }
    invincible_shell.channel_release_steps_active = 1;
}
