// uninit_times_up @ 0x445e70 (thiscall, ret)

extern char* g_game_base; // data_4df904

struct FrontendWidget;

struct BorderManager {
    void kill_border(FrontendWidget* border);
};

class TimesUpController {
public:
    void uninit_times_up();

    int state;                 // +0x00
    FrontendWidget* border;    // +0x04
    float progress;            // +0x08
    float progress_step;       // +0x0c
};

void TimesUpController::uninit_times_up()
{
    if (state != 0) {
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(border);
    }
}
