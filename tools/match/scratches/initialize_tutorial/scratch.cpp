// initialize_tutorial @ 0x448da0 (thiscall, ret) — cRTutorial::Init()

#include "game_root.h"
#include "subgame_runtime.h"
#include "tutorial.h"

extern GameRoot* g_game; // data_4df904

void Tutorial::initialize_tutorial()
{
    state = 0;
    game = &g_game->subgame;
    game->runtime_flags |= SUBGAME_RUNTIME_FLAGS_TUTORIAL_INIT_OR_MASK;

    SubgameRuntime* owner = game;
    unsigned int flags = owner->runtime_flags;
    flags &= ~SUBGAME_RUNTIME_FLAG_AMBIENT_GARBAGE;
    owner->runtime_flags = flags;
}
