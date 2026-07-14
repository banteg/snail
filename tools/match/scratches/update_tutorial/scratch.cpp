// update_tutorial @ 0x448de0 (thiscall, ret) — cRTutorial::AI()
#include "golb.h"
#include "subgame_runtime.h"
#include "tutorial.h"

void* Tutorial::update_tutorial()
{
    SubgameRuntime* owner = game;
    return owner->get_track_grid_cell_at_world_position(&owner->player.transform.position);
}
