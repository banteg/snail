// calc_subgame_rate @ 0x4404d0 (thiscall, ret)

#include "subgame_runtime.h"

float sine(float angle);

void SubgameRuntime::calc_subgame_rate()
{
    if (subgame_state == 2) {
        float completion_fraction = completion_progress_z / (float)completion_row_start;
        if (completion_fraction < 0.0f)
            completion_fraction = 0.0f;
        else if (completion_fraction > 1.0f)
            completion_fraction = 1.0f;

        int mode = level_mode;
        if (mode == 1 || mode == 3) {
            subgame_rate = completion_fraction * 0.550000012f + base_rate;
        } else if (mode == 4) {
            subgame_rate = completion_fraction * 0.400000006f + base_rate + 0.200000003f;
        } else {
            subgame_rate = completion_fraction * 0.200000003f + base_rate;
        }

        if (bonus_rate_state == 2) {
            float bonus;
            if (mode == 1) {
                bonus = 0.400000006f;
            } else {
                bonus = 0.600000024f;
                if (mode == 4)
                    bonus = 0.400000006f;
            }
            if (bonus_rate_phase >= 0.25 && bonus_rate_phase <= 0.75) {
                subgame_rate += bonus;
            } else {
                float envelope = (1.0f - sine(bonus_rate_phase * 12.566371f + 1.57079637f))
                    * 0.5f;
                subgame_rate += envelope * bonus;
            }
        }

        if (nuke_rate_state == 1)
            subgame_rate += nuke_rate_progress * 0.5f;
    } else {
        subgame_rate = base_rate;
    }
}
