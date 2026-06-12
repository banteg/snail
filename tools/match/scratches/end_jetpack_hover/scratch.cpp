// end_jetpack_hover @ 0x43a370 (thiscall, ret)

class JetpackGaugeController {
public:
    void end_jetpack_hover();

    float progress;            // +0x00
    float progress_step;       // +0x04
    char unknown_08[0x4];
    int state;                 // +0x0c
};

void JetpackGaugeController::end_jetpack_hover()
{
    if (state == 1 && progress < 0.94f) {
        progress = 0.94f;
    }
}
