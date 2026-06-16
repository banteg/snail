// unhide_gameplay_scores @ 0x445f40 (thiscall, ret)

#include "game.h"

void Game::unhide_gameplay_scores()
{
    score_widget_b->unhide_border_init();
    score_widget_a->unhide_border_init();
}
