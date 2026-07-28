// update_tutorial @ 0x448de0 (thiscall, ret) — cRTutorial::AI()
#include "golb.h"
#include "subgame_runtime.h"
#include "tutorial.h"

void Tutorial::update_tutorial()
{
    cRSubGame* owner = game;
    owner->LocFromPos(&owner->player.transform.position);
}
