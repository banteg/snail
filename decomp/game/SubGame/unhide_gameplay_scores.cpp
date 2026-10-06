// unhide_gameplay_scores @ 0x445f40 (thiscall, ret)

#include "subgame_runtime.h"

void cRSubGame::UnHideScores()
{
    bottom_score_widget->UnHideInit();
    top_score_widget->UnHideInit();
}
