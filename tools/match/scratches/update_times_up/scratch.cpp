// update_times_up @ 0x445e20 (thiscall, ret)

extern char* g_game_base; // data_4df904

struct Player {
    int kill_subgoldy();
};

class TimesUpController {
public:
    void update_times_up();
    void uninit_times_up();

    int state;                 // +0x00
    void* border;              // +0x04
    float progress;            // +0x08
    float progress_step;       // +0x0c
};

void TimesUpController::update_times_up()
{
    switch (state) {
        case 0:
            return;
        case 1:
            progress = progress_step + progress;
            if (progress > 1.0f) {
                state = 2;
            }
            break;
        case 2:
            uninit_times_up();
            ((Player*)(g_game_base + 0x42fd7c))->kill_subgoldy();
            state = 0;
            break;
    }
}
