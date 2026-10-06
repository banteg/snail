// release_snail_weapons @ 0x442e40 (thiscall, ret)

#include "player.h"
#include "rmath_random.h"

int gRMathRand2();

// Signed random in [-1, 1).
#define SIGNED_UNIT_RANDOM() (((float)gRMathRand2() - 16384.0f) * 0.000061035156f)
// Random in [0.5, 1.5).
#define RANDOM_FROM_HALF() (RAND(1.0f, 0) + 0.5f)

void cRSnail::ReleaseWeapons()
{
    if (channel_release_steps_active == 0) {
        jetpack_channel.release_step = Vector3(
            SIGNED_UNIT_RANDOM(),
            RANDOM_FROM_HALF(),
            owner_player->velocity.z) * 0.30000001f;

        float random_x = SIGNED_UNIT_RANDOM();
        float random_y = RANDOM_FROM_HALF();
        float forward_z = owner_player->velocity.z;
        Vector3* release_step = &weapon_channels[0].release_step;
        *release_step = Vector3(random_x, random_y, forward_z) * 0.30000001f;

        random_x = SIGNED_UNIT_RANDOM();
        random_y = RANDOM_FROM_HALF();
        forward_z = owner_player->velocity.z;
        release_step = &weapon_channels[2].release_step;
        *release_step = Vector3(random_x, random_y, forward_z) * 0.30000001f;

        random_x = SIGNED_UNIT_RANDOM();
        random_y = RANDOM_FROM_HALF();
        cRSubGoldy* owner = owner_player;
        forward_z = owner->velocity.z;
        release_step = &weapon_channels[1].release_step;
        *release_step = Vector3(random_x, random_y, forward_z) * 0.30000001f;
        owner->sub_hover.End();
    }
    channel_release_steps_active = 1;
}
