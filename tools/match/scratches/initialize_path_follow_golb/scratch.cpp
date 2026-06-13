// initialize_path_follow_golb @ 0x421770 (thiscall, ret 0xc)
#include "golb.h"

int GolbPathFollowState::initialize_path_follow_golb(
    GolbPathSourceCell* cell, const Vector3* position, int slot)
{
    active = 1;
    template_record = cell->path_template;
    source_cell = cell;
    sample_index = 0;
    progress = position->z - cell->anchor_position.z;
    search_slot = slot;
    vertical_offset = position->y - 0.49f;
    return slot;
}
