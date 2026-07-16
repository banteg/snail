// update_track_health_pickup @ 0x43ecc0 (thiscall, ret)

#include "game_root.h"
#include "player.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_health_pickup.h"


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
    case TRACK_PICKUP_STATE_INACTIVE:
        break;
    case TRACK_PICKUP_STATE_ACTIVE:
        goto state_one;
    case TRACK_PICKUP_STATE_TEARDOWN_PENDING:
        goto state_two;
    default:
        goto update_bob;
    }
    return;

state_two:
    state = TRACK_PICKUP_STATE_INACTIVE;
    g_game->active_bod_list.remove_bod(this);
    sprite->kill_sprite();
    return;

state_one:
    if (position.z < owner->interaction_max_z) {
        state = TRACK_PICKUP_STATE_INACTIVE;
        g_game->active_bod_list.remove_bod(this);
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
        + position.y;
}
