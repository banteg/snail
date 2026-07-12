// draw_galaxy_line @ 0x409b00 (thiscall, ret 0x1c)

#include "font_system.h"
#include "galaxy_route_types.h"
#include "vector3.h"

int Galaxy::draw_galaxy_line(
    int texture_id,
    float x0,
    float y0,
    float x1,
    float y1,
    float width,
    Color4f* color)
{
    Vector3 normal;
    normal.x = x1 - x0;
    normal.y = y1 - y0;
    normal.z = 0.0f;
    normal.normalize_vector();

    float offset_x = normal.y * width * -0.5f;
    float offset_y = normal.x * width * 0.5f;

    return queue_textured_quad_corners(
        texture_id,
        x0 - offset_x,
        y0 - offset_y,
        x1 - offset_x,
        y1 - offset_y,
        x1 + offset_x,
        y1 + offset_y,
        x0 + offset_x,
        y0 + offset_y,
        0,
        0,
        0x1000000,
        color,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        15,
        0);
}
