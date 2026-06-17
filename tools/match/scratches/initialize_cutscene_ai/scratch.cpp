// initialize_cutscene_ai @ 0x446130 (fastcall, ret)

#include "player.h"

extern char* g_game_base; // data_4df904

int CutsceneAI::initialize_cutscene_ai()
{
    PlayerPresentationController* presentation_ptr =
        (PlayerPresentationController*)(g_game_base + 0x432700);
    presentation = presentation_ptr;
    Player* player_ptr = (Player*)(g_game_base + 0x42fd7c);
    state = 0;
    player = player_ptr;
    return (int)presentation_ptr;
}
