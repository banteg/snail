// initialize_game_last @ 0x410720 (thiscall, ret)

#include "backdrop.h"

class GameRoot {
public:
    void initialize_game_last();
};

void GameRoot::initialize_game_last()
{
    ((Backdrop*)((char*)this + 0x4ec10))->initialize_backdrop(1);
}
