// begin_track_attachment_follow_state @ 0x420c40 (thiscall, ret 0xc)
// Exact cRPathFollowGoldy::Init: void initializer on cRSubGoldy::follow_state.
#include "game_root.h"


void cRPathFollowGoldy::Init(
    cRSubLoc* cell, tVector& world_position, cRSubGoldy* owning_player)
{
    active = 1;
    template_record = cell->attachment_template_record;
    source_cell = cell;
    sample_index = 0;
    progress = world_position.z - cell->position.z;
    float height = world_position.y - 0.49f;
    player = owning_player;
    vertical_offset = height;
    int row_index = cell->Yi();
    SubRow* runtime_rows = g_game->subgame.runtime_rows;
    template_record->installed_heading_delta =
        runtime_rows[row_index].installed_heading_delta;
}
