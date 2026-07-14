// update_intro_screen @ 0x4199e0 (thiscall)

#include "game_root.h"
#include "intro_screen_runtime.h"

extern GameRoot* g_game; // data_4df904

char read_pressed_text_input_key_code();

void Logo::update_intro_screen()
{
    GameRoot* game = g_game;
    if (game->fade.state == 0) {
        int flags = game->players[0].game_input->input.pressed_buttons;
        if ((flags & 0x4000) != 0 || read_pressed_text_input_key_code() == 0xb) {
            g_game->fade.begin_frontend_fade_out(0);
        }
    }

    if (g_game->fade.state == 4) {
        destroy_intro_screen();
    }

    switch (state) {
    case 0: {
        float duration_frames = duration_seconds * 60.0f;
        progress = 0.0f;
        state = 1;
        progress_step = 1.0f / duration_frames;
        break;
    }
    case 1:
        progress = progress_step + progress;
        if (progress > 1.0f) {
            g_game->fade.begin_frontend_fade_out(0);
            ++state;
        }
        break;
    }
}
