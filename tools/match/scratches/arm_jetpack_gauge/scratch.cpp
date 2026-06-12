// arm_jetpack_gauge @ 0x43a980 (thiscall, ret)

extern char* g_game_base; // data_4df904

class GlobalJetpackPresentationController {
public:
    void set_snail_jetpack(int state);
};

class JetpackGaugeController {
public:
    int arm_jetpack_gauge();

    float progress;          // +0x00
    float progress_step;     // +0x04
    int unknown_08;          // +0x08
    int state;               // +0x0c
    void* player;            // +0x10
    float wobble_x;          // +0x14
    float wobble_y;          // +0x18
    float wobble_alpha;      // +0x1c
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

        ((GlobalJetpackPresentationController*)(g_game_base + 0x432700))->set_snail_jetpack(1);
        result = initialize_jet_particles(this);
    }

    return result;
}
