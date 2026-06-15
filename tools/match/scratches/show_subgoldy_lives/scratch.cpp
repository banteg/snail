// show_subgoldy_lives @ 0x43af10 (thiscall, ret)

struct FrontendWidget {
    void hide_border_init();
    void unhide_border_init();
};

#include "player.h"

void Player::show_subgoldy_lives()
{
    int live_index = 0;
    for (int offset = 0x35bb98; offset < 0x35bbbc; offset += 4) {
        if (live_index < visible_life_stock) {
            FrontendWidget* widget = *(FrontendWidget**)((char*)game + offset);
            widget->unhide_border_init();
        } else {
            FrontendWidget* widget = *(FrontendWidget**)((char*)game + offset);
            widget->hide_border_init();
        }
        live_index++;
    }
}
