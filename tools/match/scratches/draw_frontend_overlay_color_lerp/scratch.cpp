// draw_frontend_overlay_color_lerp @ 0x40ab40 (thiscall, ret)

#include "font_system.h"
#include "frontend_overlay_color_lerp.h"
#include "render_scene.h"

void FrontendOverlayColorLerp::draw_frontend_overlay_color_lerp()
{
    current.r = (target.r - current.r) * 0.145f + current.r;
    current.g = (target.g - current.g) * 0.145f + current.g;
    current.b = (target.b - current.b) * 0.145f + current.b;
    current.a = (target.a - current.a) * 0.145f + current.a;

    if (current.a > 0.01f) {
        queue_axis_aligned_textured_quad(
            2,
            0.0f,
            0.0f,
            640.0f,
            480.0f,
            state & RENDER_SCENE_MASK,
            &current,
            5);
    }
}
