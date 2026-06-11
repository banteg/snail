// uninit_warning @ 0x446f10 (thiscall, tailcall)

extern char* g_game_base; // data_4df904

struct FrontendWidget;

struct BorderManager {
    void kill_border(FrontendWidget* border);
};

class WarningActor {
public:
    void uninit_warning();

    int state;                 // +0x00
    float progress;            // +0x04
    float progress_step;       // +0x08
    FrontendWidget* border;    // +0x0c
};

void WarningActor::uninit_warning()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(border);
}
