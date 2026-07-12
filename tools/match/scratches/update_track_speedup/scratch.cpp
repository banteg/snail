// update_track_speedup @ 0x43ee50 (thiscall, ret)

#include "bod_list.h"
#include "player.h"
#include "subgame_runtime.h"
#include "track_speedup.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

void SubSpeedUp::update_track_speedup()
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
        return;
    }
    return;

state_two:
    state = zero;
    ((BodList*)(g_game_base + 0x5a8))->remove_bod(this);
    sprite->kill_sprite();
    return;

state_one:
    if (world_position.z >= owner->interaction_max_z) {
        return;
    }

    state = zero;
    ((BodList*)(g_game_base + 0x5a8))->remove_bod(this);
    sprite->kill_sprite();
}
