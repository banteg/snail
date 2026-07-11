// initialize_cutscene_ai @ 0x446130 (thiscall, ret)

#include "player.h"

extern char* g_game_base; // data_4df904

void CutScene::initialize_cutscene_ai()
{
    presentation = (Snail*)(g_game_base + 0x432700);
    player = (Player*)(g_game_base + 0x42fd7c);
    state = 0;
}
