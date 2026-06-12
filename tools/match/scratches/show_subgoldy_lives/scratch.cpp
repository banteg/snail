// show_subgoldy_lives @ 0x43af10 (thiscall, ret)

struct FrontendWidget {
    void hide_border_init();
    void unhide_border_init();
};

class Player {
public:
    void show_subgoldy_lives();

    char unknown_00[0x408];
    char* game;                       // +0x408
    char unknown_40c[0x3f34];
    int current_lives;                // +0x4340
};

void Player::show_subgoldy_lives()
{
    int live_index = 0;
    for (int offset = 0x35bb98; offset < 0x35bbbc; offset += 4) {
        if (live_index < current_lives) {
            FrontendWidget* widget = *(FrontendWidget**)(game + offset);
            widget->unhide_border_init();
        } else {
            FrontendWidget* widget = *(FrontendWidget**)(game + offset);
            widget->hide_border_init();
        }
        live_index++;
    }
}
