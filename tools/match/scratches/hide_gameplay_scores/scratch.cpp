// hide_gameplay_scores @ 0x445f10 (thiscall, ret)

#include "subgame_runtime.h"

void cRSubGame::HideScores()
{
    FrontendWidget* widget_b = bottom_score_widget;
    if (widget_b != 0) {
        widget_b->HideInit();
    }

    FrontendWidget* widget_a = top_score_widget;
    if (widget_a != 0) {
        widget_a->HideInit();
    }
}
