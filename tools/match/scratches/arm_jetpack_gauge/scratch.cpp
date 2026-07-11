// arm_jetpack_gauge @ 0x43a980 (thiscall, ret)

#include "game_root.h"
#include "jetpack_gauge.h"

extern GameRoot* g_game; // data_4df904

int __fastcall initialize_jet_particles(JetpackGaugeController* gauge);

int JetpackGaugeController::arm_jetpack_gauge()
{
    int result = 0;

    if (state == 0) {
        state = 1;
        progress = 0.0f;
        wobble_alpha = 0.0f;
        wobble_y = 0.0f;
        wobble_x = 0.0f;

        g_game->subgame.embedded_player()->presentation.set_snail_jetpack(1);
        result = initialize_jet_particles(this);
    }

    return result;
}
