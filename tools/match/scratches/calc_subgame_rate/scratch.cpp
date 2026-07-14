// calc_subgame_rate @ 0x4404d0 (thiscall, ret)

#include "subgame_runtime.h"

float sine(float angle);

void SubgameRuntime::calc_subgame_rate()
{
    if (subgame_state == 2) {
        float completion_fraction = player.transform.position.z / (float)completion_row_start;
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

        DamageGuageState damage_state = player.damage_gauge.state;
        if (damage_state == DAMAGE_GUAGE_STATE_DRAINING) {
            float bonus;
            if (mode == 1) {
                bonus = 0.400000006f;
            } else {
                bonus = 0.600000024f;
                if (mode == 4)
                    bonus = 0.400000006f;
            }
            if (player.damage_gauge.display_fill >= 0.25
                && player.damage_gauge.display_fill <= 0.75) {
                subgame_rate += bonus;
            } else {
                float envelope =
                    (1.0f
                        - sine(
                            player.damage_gauge.display_fill * 12.566371f
                            + 1.57079637f))
                    * 0.5f;
                subgame_rate += envelope * bonus;
            }
        }

        if (player.sub_hover.state == 1)
            subgame_rate += player.sub_hover.warning_intensity_latch * 0.5f;
    } else {
        subgame_rate = base_rate;
    }
}
