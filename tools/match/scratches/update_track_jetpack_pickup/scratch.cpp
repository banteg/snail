// update_track_jetpack_pickup @ 0x43efb0 (thiscall, ret)
// State 2 -> list remove + kill_sprite; state 1 -> cull behind the owner
// kill plane or advance the wrapped sine bob on the nested sprite. The
// embedded renderable bodies live below the pickup parent; this update only
// manages the parent state and sprite bob.

#include "game_root.h"
#include "player.h"
#include "subgame_runtime.h"
#include "track_jetpack_pickup.h"

extern GameRoot* g_game; // data_4df904
int report_errorf(char* format, ...);
float sine(float radians);

void JetPack::update_track_jetpack_pickup()
{
    int zero = 0;

    if (owner_game->subgame_pause_gate != zero)
        return;

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
    g_game->active_bod_list.remove_bod(this);
    sprite->kill_sprite();
    return;

state_one:
    if (position.z < owner->interaction_max_z) {
        state = zero;
        g_game->active_bod_list.remove_bod(this);
        sprite->kill_sprite();
        return;
    }

update_bob:
    float advanced = bob_phase_step + bob_phase;
    bob_phase = advanced;
    if (advanced > 1.0f)
        bob_phase = advanced - 1.0f;
    sprite->position.y = sine(bob_phase * 6.2831855f) * 0.30000001f + position.y;
}
