// initialize_cutscene_ai @ 0x446130 (thiscall, ret)

#include "game_root.h"
#include "player.h"


void CutScene::initialize_cutscene_ai()
{
    presentation = &g_game->subgame.embedded_player()->presentation;
    player = g_game->subgame.embedded_player();
    state = CUT_SCENE_STATE_INACTIVE;
}
