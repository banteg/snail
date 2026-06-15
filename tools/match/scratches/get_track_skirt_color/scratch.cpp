// get_track_skirt_color @ 0x442120 (thiscall, ret 0x4)

#include "sprite.h"

class SubgameRuntime {
public:
    Color4f* get_track_skirt_color(Color4f* out);

    char unknown_00[0x1b0140];
    float track_skirt_r; // +0x1b0140
    float track_skirt_g; // +0x1b0144
    float track_skirt_b; // +0x1b0148
};

Color4f* SubgameRuntime::get_track_skirt_color(Color4f* out)
{
    Color4f color;
    *out = *color.set_color_rgba(
        track_skirt_r,
        track_skirt_g,
        track_skirt_b,
        0.400000006f);
    return out;
}
