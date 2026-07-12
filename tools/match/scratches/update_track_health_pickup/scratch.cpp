// update_track_health_pickup @ 0x43ecc0 (thiscall, ret)

#include "player.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_health_pickup.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);
float sine(float radians);

void SubHealth::update_track_health_pickup()
{
    int zero = 0;

    if (owner_game->subgame_pause_gate != zero) {
        return;
    }

    int current_state = state - zero;
    switch (current_state) {
    case 0:
        break;
    case 1:
        goto state_one;
    case 2:
        goto state_two;
    default:
        goto update_bob;
    }
    return;

state_two:
    state = zero;
    ((BodList*)(g_game_base + 0x5a8))->remove_bod(this);
    sprite->kill_sprite();
    return;

state_one:
    if (world_position.z < owner->interaction_max_z) {
        state = zero;
        ((BodList*)(g_game_base + 0x5a8))->remove_bod(this);
        sprite->kill_sprite();
        return;
    }

update_bob:
    float advanced = bob_phase_step + bob_phase;
    bob_phase = advanced;
    if (advanced > 1.0f)
        bob_phase = advanced - 1.0f;
    sprite->position.y =
        (sine(bob_phase * 6.2831855f) + 1.0f) * 0.30000001f
        + world_position.y;
}
