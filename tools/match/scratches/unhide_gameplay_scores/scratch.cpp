// unhide_gameplay_scores @ 0x445f40 (thiscall, ret)

#include "frontend_widget.h"

class Game {
public:
    void unhide_gameplay_scores();

    char unknown_00[0x35bb88];
    FrontendWidget* score_widget_a; // +0x35bb88
    FrontendWidget* score_widget_b; // +0x35bb8c
};

void Game::unhide_gameplay_scores()
{
    score_widget_b->unhide_border_init();
    score_widget_a->unhide_border_init();
}
