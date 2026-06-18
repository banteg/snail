// update_frontend_transition_overlay @ 0x40abf0 (thiscall, ret)

#include "border_delay_lane.h"
#include "font_system.h"

void FrontendFade::update_frontend_transition_overlay()
{
    Color4f color;

    switch (state) {
    case 0:
        return;

    case 2:
        alpha = alpha + 0.0555555522f;
        if (alpha > 1.0f) {
            alpha = 1.0f;
            state = 3;
            hold_progress = 0.0f;
            hold_progress_step = 0.33333334f;
        }
        break;

    case 3:
        hold_progress = hold_progress + hold_progress_step;
        if (hold_progress > 1.0f) {
            state = 4;
        }
        break;

    case 4:
        state = 1;
        break;

    case 1:
        alpha = alpha - 0.0555555522f;
        if (alpha <= 0.0f) {
            alpha = 0.0f;
            state = 0;
        }
        break;
    }

    if (alpha > 0.01f) {
        queue_axis_aligned_textured_quad(
            2,
            0.0f,
            0.0f,
            640.0f,
            480.0f,
            0x1000000,
            color.set_color_rgba(0.0f, 0.0f, 0.0f, alpha),
            14);
    }
}
