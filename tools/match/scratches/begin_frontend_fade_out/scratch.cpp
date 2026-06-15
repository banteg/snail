// begin_frontend_fade_out @ 0x40abc0 (thiscall, ret 0x4)

class FrontendFade {
public:
    int begin_frontend_fade_out(int hold_state_);

    int state;      // +0x00
    int alpha_bits; // +0x04
    int field_08;
    int field_0c;
    int hold_state; // +0x10
};

int FrontendFade::begin_frontend_fade_out(int hold_state_)
{
    state = 2;
    alpha_bits = 0;
    hold_state = hold_state_;
    return hold_state_;
}
