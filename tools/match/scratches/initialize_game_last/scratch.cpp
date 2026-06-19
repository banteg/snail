// initialize_game_last @ 0x410720 (thiscall, ret)

#include "backdrop.h"
#include "game_root.h"

void GameRoot::initialize_game_last()
{
    ((Backdrop*)((char*)this + 0x4ec10))->initialize_backdrop(1);
}
