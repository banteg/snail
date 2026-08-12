// draw_galaxy_line @ 0x409b00 (thiscall, ret 0x1c)

#include "font_system.h"
#include "galaxy_route_types.h"
#include "vector3.h"

void cRGalaxy::Line(
    int texture_id,
    float x0,
    float y0,
    float x1,
    float y1,
    float width,
    tColour& color)
{
    Vector3 normal;
    normal.x = x1 - x0;
    normal.y = y1 - y0;
    normal.z = 0.0f;
    normal.Normalize();

    float offset_x = normal.y * width * -0.5f;
    float offset_y = normal.x * width * 0.5f;

    OSDPrintUV(
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
        &color,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        15,
        0);
}
