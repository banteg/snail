// update_banner @ 0x441d40 (thiscall, ret)
// Updates start/banner visibility and its vertical bob offset.

struct BannerRowSource {
    char unknown_00[0x70];
    float row_position; // +0x70
};

class Banner {
public:
    void update_banner();

    char unknown_00[0x04];
    int flags; // +0x04
    char unknown_08[0x14 - 0x08];
    float bob_y; // +0x14
    float reference_z; // +0x18
    char unknown_1c[0x38 - 0x1c];
    int visibility_mode; // +0x38
    char unknown_3c[0x54 - 0x3c];
    BannerRowSource* row_source; // +0x54
    float phase; // +0x58
    float phase_step; // +0x5c
};

float sine(float angle); // @ 0x44c9d0

void Banner::update_banner()
{
    switch (visibility_mode) {
    case 0:
        if (row_source->row_position < 40.0f)
            flags |= 0x20;
        else
            flags &= ~0x20;
        break;

    case 1:
        if (reference_z - row_source->row_position < 46.0f)
            flags |= 0x20;
        else
            flags &= ~0x20;
        break;
    }

    float next_phase = phase_step + phase;
    phase = next_phase;
    if (next_phase > 1.0f)
        phase = next_phase - 1.0f;

    bob_y = sine(phase * 6.2831855f) * 0.25999999f;
}
