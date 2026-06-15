// begin_frontend_fade_in @ 0x40abe0 (thiscall, ret)

class FrontendFade {
public:
    void begin_frontend_fade_in();

    int state;      // +0x00
    int alpha_bits; // +0x04
};

void FrontendFade::begin_frontend_fade_in()
{
    state = 1;
    alpha_bits = 0x3f800000;
}
