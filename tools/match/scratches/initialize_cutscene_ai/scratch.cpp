// initialize_cutscene_ai @ 0x446130 (fastcall, ret)

extern char* g_game_base; // data_4df904

class CutsceneAI {
public:
    int initialize_cutscene_ai();

    char* presentation;        // +0x00
    char* player;              // +0x04
    char unknown_08[0x0c - 0x08];
    int state;                 // +0x0c
};

int CutsceneAI::initialize_cutscene_ai()
{
    int result = (int)(g_game_base + 0x432700);
    presentation = (char*)result;
    char* player_ptr = g_game_base + 0x42fd7c;
    state = 0;
    player = player_ptr;
    return result;
}
