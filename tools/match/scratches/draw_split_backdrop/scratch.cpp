// draw_split_backdrop @ 0x410f90 (thiscall, ret)
// Queues the active split backdrop textures side-by-side.

#include "backdrop.h"
#include "sprite.h"

int queue_axis_aligned_textured_quad_uv(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int flags,
    tColour* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int layer,
    int blend);

int Backdrop::draw_split_backdrop()
{
    tColour color;
    queue_axis_aligned_textured_quad_uv(
        active_primary_texture_id,
        0.0f,
        0.0f,
        512.0f,
        512.0f,
        0x8000000,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        0,
        0);

    return queue_axis_aligned_textured_quad_uv(
        active_secondary_texture_id,
        512.0f,
        0.0f,
        128.0f,
        512.0f,
        0x8000000,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        0,
        0);
}
