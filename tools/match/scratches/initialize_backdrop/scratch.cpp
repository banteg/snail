// initialize_backdrop @ 0x410e20 (thiscall, ret 0x4)

#include "backdrop.h"

extern unsigned char g_render_flags; // byte_4df934

void Backdrop::initialize_backdrop(int last_mode)
{
    unknown_65c = 1;
    unknown_660 = 0;
    active_primary_texture_id = -1;
    backdrop_change_queued = 0;
    progress_fraction = 0.0f;
    unknown_6c4 = 5;
    unknown_6bc = 0.0f;
    unknown_6c0 = 0.003333333414f;

    set_backdrop_texture_target(5);

    unsigned char render_flags = g_render_flags;
    if ((render_flags & 1) != 0) {
        backdrop_refresh_pending = 1;
        unknown_664 = 1.0f;
    } else {
        backdrop_refresh_pending = 0;
        unknown_664 = 0.0f;
    }

    unknown_668 = 0.020833333954f;
    switch (last_mode) {
    case 0:
        unknown_66c = 0.0f;
        unknown_670 = 0.001308996929f;
        unknown_674 = 0.0f;
        unknown_678 = 0.001745329355f;
        break;
    case 1:
        unknown_66c = 0.0f;
        unknown_670 = -0.002617993858f;
        unknown_674 = 0.0f;
        unknown_678 = -0.003490658710f;
        break;
    default:
        set_backdrop_texture_target(0);
        set_backdrop_distort(0.0f);
        return;
    }

    previous_primary_texture = 0;
    current_primary_texture = 0;
    primary_blend = 1.0f;
    primary_blend_step = 0.005555555690f;
    previous_secondary_texture = 0;
    current_secondary_texture = 0;
    secondary_blend = 1.0f;
    secondary_blend_step = 0.004166666884f;

    set_backdrop_texture_target(0);
    set_backdrop_distort(0.0f);
}
