// unhide_gameplay_scores @ 0x445f40 (thiscall, ret)

#include "subgame_runtime.h"

void SubgameRuntime::unhide_gameplay_scores()
{
    score_widget_b->unhide_border_init();
    score_widget_a->unhide_border_init();
}
