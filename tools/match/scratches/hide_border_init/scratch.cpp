// hide_border_init @ 0x4010e0 (thiscall, ret)

class TooltipState {
public:
    int reset_tooltip();
};

class FrontendWidget {
public:
    int hide_border_init();

    char unknown_000[0x44];
    float hide_blend; // +0x44
    char unknown_048[0x1a0 - 0x048];
    int flags; // +0x1a0
    char unknown_1a4[0x28c - 0x1a4];
    TooltipState tooltip; // +0x28c
};

int FrontendWidget::hide_border_init()
{
    int result = flags;
    if ((result & 0x1000) != 0)
        return result;

    result |= 0x1000;
    hide_blend = 0.0f;
    flags = result;
    return tooltip.reset_tooltip();
}
