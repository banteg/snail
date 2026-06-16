// uninit_tutorial @ 0x448dd0 (cdecl, ret)

#include "tip_manager.h"

extern char* g_game_base; // data_4df904

void uninit_tutorial()
{
    ((TipManager*)(g_game_base + 0x12e6f58))->uninit_tips();
}
