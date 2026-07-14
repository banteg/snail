// update_star_field @ 0x4346f0 (thiscall)

#include "star_manager.h"
#include "runtime_config.h"


void StarManager::update_star_field()
{
    switch (state) {
    case 0:
        if ((g_runtime_config.render_flags & RUNTIME_RENDER_STAR_FIELD) != 0) {
            state = 2;
            initialize_star_field();
            state = 2;
            fade = 0.0f;
            fade_step = 0.020833334f;
            update_star_positions(0.0f);
        }
        return;
    case 2:
        update_star_positions(fade);
        if ((g_runtime_config.render_flags & RUNTIME_RENDER_STAR_FIELD) == 0) {
            state = 3;
        } else {
            fade = fade_step + fade;
            if (fade > 1.0f) {
                state = 1;
            }
        }
        return;
    case 3:
        update_star_positions(fade);
        if ((g_runtime_config.render_flags & RUNTIME_RENDER_STAR_FIELD) != 0) {
            state = 2;
        } else {
            fade = fade - fade_step;
            if (fade < 0.0f) {
                destroy_star_field();
                state = 0;
            }
        }
        return;
    case 1:
        update_star_positions(1.0f);
        if ((g_runtime_config.render_flags & RUNTIME_RENDER_STAR_FIELD) == 0) {
            fade = 1.0f;
            fade_step = 0.020833334f;
            state = 3;
        }
        return;
    }
}
