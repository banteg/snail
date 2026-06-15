// uninit_thanks_screen @ 0x4340c0 (thiscall, ret)

extern char* g_game_base; // data_4df904

class BorderManager {
public:
    int kill_border(void* border);
};

class ThanksScreen {
public:
    void uninit_thanks_screen();

    void* field_00;
    void* border; // +0x04
};

void ThanksScreen::uninit_thanks_screen()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(border);
    *(int*)(g_game_base + 0x1b8) = 14;
}
