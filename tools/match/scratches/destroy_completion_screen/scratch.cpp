// destroy_completion_screen @ 0x406060 (thiscall, ret)

#include "completion_screen.h"

int CompletionPrompt::destroy_completion_screen()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(prompt_title);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(yes_button);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(no_button);
    int result = ((BorderManager*)(g_game_base + 0xb4c))->unhide_all_borders();
    ((CompletionGameView*)g_game_base)->frontend_next_state = previous_frontend_state;
    return result;
}
