// initialize_path_follow_golb @ 0x421770 (thiscall, ret 0xc)
#include "golb.h"

int GolbPathFollowState::initialize_path_follow_golb(
    GolbPathTemplate* path_template, const Vector3* position, int slot)
{
    active = 1;
    sample_count = path_template->sample_count;
    path = path_template;
    progress = 0.0f;
    offset_z = position->z - path_template->base_z;
    search_slot = slot;
    offset_y = position->y - 0.49f;
    return slot;
}
