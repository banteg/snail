// initialize_tutorial @ 0x448da0 (fastcall, ret)

#include "new_game_menu.h"

extern char* g_game_base; // data_4df904

class Game {
public:
    char unknown_00[0x4c];
    int render_flags; // +0x4c
};

void TutorialController::initialize_tutorial()
{
    state = 0;
    game = (Game*)(g_game_base + 0x74618);
    game->render_flags |= 0x600000;

    Game* owner = game;
    int flags = owner->render_flags;
    flags &= 0xfffffffd;
    owner->render_flags = flags;
}
