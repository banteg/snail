// destroy_high_score_screen @ 0x417220 (thiscall, ret)

extern char* g_game_base; // data_4df904
extern int g_high_score_selected_bank; // data_4df9c0

class BorderManager {
public:
    int kill_all_borders();
};

class HighScoreScreen {
public:
    int destroy_high_score_screen();

    int field_00;
    int field_04;
    int selected_bank; // +0x08
};

int HighScoreScreen::destroy_high_score_screen()
{
    g_high_score_selected_bank = selected_bank;
    ((BorderManager*)(g_game_base + 0xb4c))->kill_all_borders();
    *(char*)(g_game_base + 0x30d) = 0;
    *(int*)(g_game_base + 0x310) = 0;
    return 0;
}
