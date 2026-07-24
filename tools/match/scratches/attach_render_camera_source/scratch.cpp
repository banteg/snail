// attach_render_camera_source @ 0x44e900 (thiscall, ret 0x4)

#include "viewport.h"

int Viewport::attach_render_camera_source(RenderCamera* camera_)
{
    camera = camera_;
    int result = flags;
    result |= 1;
    flags = result;
    return result;
}
