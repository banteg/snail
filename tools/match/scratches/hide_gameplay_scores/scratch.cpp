// hide_gameplay_scores @ 0x445f10 (thiscall, ret)

#include "game.h"

void Game::hide_gameplay_scores()
{
    FrontendWidget* widget_b = score_widget_b;
    if (widget_b != 0) {
        widget_b->hide_border_init();
    }

    FrontendWidget* widget_a = score_widget_a;
    if (widget_a != 0) {
        widget_a->hide_border_init();
    }
}
