// update_track_speedup @ 0x43ee50 (thiscall, ret)

#include "bod_list.h"
#include "game_root.h"
#include "player.h"
#include "subgame_runtime.h"
#include "track_speedup.h"

extern GameRoot* g_game; // data_4df904

int report_errorf(char* format, ...);

void SubSpeedUp::update_track_speedup()
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
        return;
    }
    return;

state_two:
    state = TRACK_PICKUP_STATE_INACTIVE;
    g_game->active_bod_list.remove_bod(this);
    sprite->kill_sprite();
    return;

state_one:
    if (transform.position.z >= owner->interaction_max_z) {
        return;
    }

    state = TRACK_PICKUP_STATE_INACTIVE;
    g_game->active_bod_list.remove_bod(this);
    sprite->kill_sprite();
}
