// update_intro_screen @ 0x4199e0 (thiscall)

#include "frontend_fade.h"
#include "intro_screen_runtime.h"

extern char* g_game_base; // data_4df904

char read_pressed_text_input_key_code();

void IntroScreenRuntime::update_intro_screen()
{
    char* game = g_game_base;
    if (*(int*)(game + 0x24) == 0) {
        int flags = *(int*)(*(char**)(game + 0x28c) + 0x3c);
        if ((flags & 0x4000) != 0 || read_pressed_text_input_key_code() == 0xb) {
            ((FrontendFade*)(g_game_base + 0x24))->begin_frontend_fade_out(0);
        }
    }

    if (*(int*)(g_game_base + 0x24) == 4) {
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
            ((FrontendFade*)(g_game_base + 0x24))->begin_frontend_fade_out(0);
            ++state;
        }
        break;
    }
}
