// show_subgoldy_lives @ 0x43af10 (thiscall, ret)

#include "game.h"
#include "player.h"

void Player::show_subgoldy_lives()
{
    int live_index = 0;
    for (int offset = (int)((Game*)0)->life_stock_widgets;
         offset < (int)(((Game*)0)->life_stock_widgets + 9);
         offset += sizeof(FrontendWidget*)) {
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
