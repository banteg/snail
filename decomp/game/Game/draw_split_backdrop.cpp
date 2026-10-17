// draw_split_backdrop @ 0x410f90 (thiscall, ret)
// Queues the active split backdrop textures side-by-side.

#include "backdrop.h"
#include "font_system.h"
#include "sprite.h"

int cRBackdrop::draw_split_backdrop()
{
    tColour color;
    OSDPrintUV(
        active_primary_texture_id,
        0.0f,
        0.0f,
        512.0f,
        512.0f,
        0x8000000,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        0,
        0);

    return OSDPrintUV(
        active_secondary_texture_id,
        512.0f,
        0.0f,
        128.0f,
        512.0f,
        0x8000000,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        0,
        0);
}
