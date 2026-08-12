// initialize_path_follow_golb @ 0x421770 (thiscall, ret 0xc)
#include "golb.h"
#include "track_attachment_types.h"

int cRPathFollowGolb::initialize_path_follow_golb(
    cRSubLoc* cell, const Vector3* position, cRSubGolb* shot_)
{
    active = 1;
    template_record = cell->attachment_template_record;
    source_cell = cell;
    sample_index = 0;
    progress = position->z - cell->position.z;
    shot = shot_;
    vertical_offset = position->y - 0.49f;
    return (int)shot_;
}
