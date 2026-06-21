// initialize_tutorial @ 0x448da0 (fastcall, ret)

#include "new_game_menu.h"
#include "subgame_runtime.h"

extern char* g_game_base; // data_4df904

void TutorialController::initialize_tutorial()
{
    state = 0;
    game = (SubgameRuntime*)(g_game_base + 0x74618);
    game->runtime_flags |= 0x600000;

    SubgameRuntime* owner = game;
    unsigned int flags = owner->runtime_flags;
    flags &= 0xfffffffd;
    owner->runtime_flags = flags;
}
