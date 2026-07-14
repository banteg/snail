// uninit_tutorial @ 0x448dd0 (thiscall, ret) — cRTutorial::UnInit()

#include "game_root.h"
#include "tip_manager.h"
#include "tutorial.h"

extern GameRoot* g_game; // data_4df904

void Tutorial::uninit_tutorial()
{
    g_game->tip_manager.uninit_tips();
}
