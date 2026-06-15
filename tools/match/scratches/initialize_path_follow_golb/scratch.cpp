// initialize_path_follow_golb @ 0x421770 (thiscall, ret 0xc)
#include "golb.h"

int GolbPathFollowState::initialize_path_follow_golb(
    GolbPathSourceCell* cell, const Vector3* position, GolbShot* shot_)
{
    active = 1;
    template_record = cell->path_template;
    source_cell = cell;
    sample_index = 0;
    progress = position->z - cell->anchor_position.z;
    shot = shot_;
    vertical_offset = position->y - 0.49f;
    return (int)shot_;
}
