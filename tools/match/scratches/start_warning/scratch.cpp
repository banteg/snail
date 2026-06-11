// start_warning @ 0x446f30 (thiscall, tailcall)

struct FrontendWidget {
    void unhide_border_init();
};

class WarningActor {
public:
    void start_warning();

    int state;                 // +0x00
    float progress;            // +0x04
    float progress_step;       // +0x08
    FrontendWidget* border;    // +0x0c
};

void WarningActor::start_warning()
{
    progress = 1.0f;
    state = 2;
    border->unhide_border_init();
}
