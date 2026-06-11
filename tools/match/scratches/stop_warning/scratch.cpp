// stop_warning @ 0x446f50 (thiscall, tailcall)

struct FrontendWidget {
    void hide_border_init();
};

class WarningActor {
public:
    void stop_warning();

    int state;                 // +0x00
    float progress;            // +0x04
    float progress_step;       // +0x08
    FrontendWidget* border;    // +0x0c
};

void WarningActor::stop_warning()
{
    state = 0;
    border->hide_border_init();
}
