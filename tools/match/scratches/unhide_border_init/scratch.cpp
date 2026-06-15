// unhide_border_init @ 0x401110 (thiscall, ret)

class FrontendWidget {
public:
    int unhide_border_init();

    char unknown_000[0x44];
    float hide_blend; // +0x44
    char unknown_048[0x1a0 - 0x048];
    int flags; // +0x1a0
};

int FrontendWidget::unhide_border_init()
{
    int result = flags;
    hide_blend = 1.0f;
    result &= ~0x1000;
    flags = result;
    return result;
}
