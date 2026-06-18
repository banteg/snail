// uninit_tutorial @ 0x448dd0 (thiscall, ret)

#include "new_game_menu.h"
#include "tip_manager.h"

void TutorialController::uninit_tutorial()
{
    ((TipManager*)(g_game_base + 0x12e6f58))->uninit_tips();
}
