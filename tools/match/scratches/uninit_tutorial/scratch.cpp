// uninit_tutorial @ 0x448dd0 (thiscall, ret) — cRTutorial::UnInit()

#include "tip_manager.h"
#include "tutorial.h"

extern char* g_game_base; // data_4df904

void Tutorial::uninit_tutorial()
{
    ((TipManager*)(g_game_base + 0x12e6f58))->uninit_tips();
}
