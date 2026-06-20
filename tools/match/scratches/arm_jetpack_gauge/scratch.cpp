// arm_jetpack_gauge @ 0x43a980 (thiscall, ret)

#include "jetpack_gauge.h"

extern char* g_game_base; // data_4df904

class ArmJetpackPresentationView {
public:
    void set_snail_jetpack(int state);
};

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

        ((ArmJetpackPresentationView*)(g_game_base + 0x432700))->set_snail_jetpack(1);
        result = initialize_jet_particles(this);
    }

    return result;
}
