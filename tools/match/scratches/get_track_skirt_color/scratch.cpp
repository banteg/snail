// get_track_skirt_color @ 0x442120 (thiscall, ret 0x4)

#include "subgame_runtime.h"

tColour* SubgameRuntime::get_track_skirt_color(tColour* out)
{
    tColour color;
    *out = *color.set_color_rgba(
        level_definition.fringe_color.r,
        level_definition.fringe_color.g,
        level_definition.fringe_color.b,
        0.400000006f);
    return out;
}
