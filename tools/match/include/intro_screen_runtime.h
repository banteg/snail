// Shared intro-screen runtime view used by update/destroy paths.
#ifndef INTRO_SCREEN_RUNTIME_H
#define INTRO_SCREEN_RUNTIME_H

#include "bod_list.h"

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

    float progress;                 // +0x00
    float progress_step;            // +0x04
    int state;                      // +0x08
    int saved_render_flags;         // +0x0c
    float duration_seconds;         // +0x10
    int renderable_count;           // +0x14
    IntroRenderableSlot renderables[1]; // +0x18
};

#endif
