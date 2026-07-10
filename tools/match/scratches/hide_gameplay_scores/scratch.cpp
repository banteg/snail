// hide_gameplay_scores @ 0x445f10 (thiscall, ret)

#include "subgame_runtime.h"

void SubgameRuntime::hide_gameplay_scores()
{
    FrontendWidget* widget_b = bottom_score_widget;
    if (widget_b != 0) {
        widget_b->hide_border_init();
    }

    FrontendWidget* widget_a = top_score_widget;
    if (widget_a != 0) {
        widget_a->hide_border_init();
    }
}
