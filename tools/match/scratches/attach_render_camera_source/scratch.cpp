// attach_render_camera_source @ 0x44e900 (thiscall, ret 0x4)

#include "render_camera_slot.h"

int RenderCameraSlot::attach_render_camera_source(RenderCamera* source_)
{
    source = source_;
    int result = flags;
    result |= 1;
    flags = result;
    return result;
}
