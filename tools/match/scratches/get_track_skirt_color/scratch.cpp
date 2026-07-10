// get_track_skirt_color @ 0x442120 (thiscall, ret 0x4)

#include "subgame_runtime.h"

Color4f* SubgameRuntime::get_track_skirt_color(Color4f* out)
{
    Color4f color;
    *out = *color.set_color_rgba(
        level_definition.fringe_color.r,
        level_definition.fringe_color.g,
        level_definition.fringe_color.b,
        0.400000006f);
    return out;
}
