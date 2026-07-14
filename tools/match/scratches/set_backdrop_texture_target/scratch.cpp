// set_backdrop_texture_target @ 0x410f40 (thiscall, ret 0x4)
// Cross-port authored name: cRBackdrop::SetWorld(int).

#include "backdrop.h"

void Backdrop::set_backdrop_world(int world)
{
    primary_world_blend.blend = 1.0f - primary_world_blend.blend;
    primary_world_blend.previous_world = primary_world_blend.current_world;
    int old_secondary = secondary_world_blend.current_world;
    primary_world_blend.current_world = world;
    secondary_world_blend.previous_world = old_secondary;
    secondary_world_blend.blend = 1.0f - secondary_world_blend.blend;
    secondary_world_blend.current_world = world;
}
