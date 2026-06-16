// initialize_render_camera_slot @ 0x44e920 (thiscall)

#include "render_camera_slot.h"

RenderCameraSlot* RenderCameraSlot::initialize_render_camera_slot()
{
    flags = 0;
    viewport_x = 0.0f;
    viewport_y = 0.0f;
    draw_world = 1;
    viewport_width = 1.0f;
    viewport_height = 1.0f;
    unknown_1c = 0.87249994f;
    return this;
}
