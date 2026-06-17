// set_backdrop_texture_target @ 0x410f40 (thiscall, ret 0x4)

#include "backdrop.h"

int Backdrop::set_backdrop_texture_target(int texture_id)
{
    primary_blend = 1.0f - primary_blend;
    previous_primary_texture = current_primary_texture;
    int old_secondary = current_secondary_texture;
    current_primary_texture = texture_id;
    previous_secondary_texture = old_secondary;
    secondary_blend = 1.0f - secondary_blend;
    current_secondary_texture = texture_id;
    return texture_id;
}
