// unhide_gameplay_scores @ 0x445f40 (thiscall, ret)

#include "subgame_runtime.h"

void cRSubGame::unhide_gameplay_scores()
{
    bottom_score_widget->unhide_border_init();
    top_score_widget->unhide_border_init();
}
