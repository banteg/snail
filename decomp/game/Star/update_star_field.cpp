// cRStarManager::AI @ 0x4346f0 (thiscall)

#include "star_manager.h"
#include "runtime_config.h"


void cRStarManager::AI()
{
    switch (state) {
    case 0:
        if ((g_runtime_config.render_flags & RUNTIME_RENDER_STAR_FIELD) != 0) {
            state = 2;
            Init();
            state = 2;
            fade = 0.0f;
            fade_step = 0.020833334f;
            UpdateStars(0.0f);
        }
        return;
    case 2:
        UpdateStars(fade);
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
        UpdateStars(fade);
        if ((g_runtime_config.render_flags & RUNTIME_RENDER_STAR_FIELD) != 0) {
            state = 2;
        } else {
            fade = fade - fade_step;
            if (fade < 0.0f) {
                UnInit();
                state = 0;
            }
        }
        return;
    case 1:
        UpdateStars(1.0f);
        if ((g_runtime_config.render_flags & RUNTIME_RENDER_STAR_FIELD) == 0) {
            fade = 1.0f;
            fade_step = 0.020833334f;
            state = 3;
        }
        return;
    }
}
