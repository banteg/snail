// update_intro_screen @ 0x4199e0 (thiscall)

#include "bod_list.h"
#include "border_delay_lane.h"

extern char* g_game_base; // data_4df904

char read_pressed_text_input_key_code();

struct IntroRenderableSlot {
    BodNode bod; // +0x00
    char unknown_10[0x90 - sizeof(BodNode)];
};
typedef char IntroRenderableSlot_must_be_0x90[
    (sizeof(IntroRenderableSlot) == 0x90) ? 1 : -1];

class IntroScreenRuntime {
public:
    void update_intro_screen();
    int destroy_intro_screen();

    float progress; // +0x00
    float progress_step; // +0x04
    int state; // +0x08
    int saved_render_flags; // +0x0c
    float duration_seconds; // +0x10
    int renderable_count; // +0x14
    IntroRenderableSlot renderables[1]; // +0x18
};

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
