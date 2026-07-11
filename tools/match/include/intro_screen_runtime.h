// Root-owned intro/credits runtime at GameRoot +0x4f400. The two fixed
// renderable banks close exactly on SubgameRuntime +0x74618.
#ifndef INTRO_SCREEN_RUNTIME_H
#define INTRO_SCREEN_RUNTIME_H

#include "bod_types.h"

enum {
    INTRO_SCREEN_RENDERABLE_COUNT = 0x400,
    INTRO_SCREEN_LOGO_RENDERABLE_COUNT = 0x20,
};

class IntroLogoRenderable : public RenderableBod {
public:
    IntroLogoRenderable* initialize_intro_logo_renderable(); // @ 0x408490
    void update_intro_logo_renderable(); // @ 0x419a90

    char unknown_078[0x80 - 0x78];
    Vector3 velocity; // +0x80
    unsigned char glyph; // +0x8c, 0xff for image records
    char unknown_08d[0x90 - 0x8d];
};
typedef char IntroLogoRenderable_must_be_0x90[
    (sizeof(IntroLogoRenderable) == 0x90) ? 1 : -1];

class IntroScreenRuntime {
public:
    int open_logo(); // @ 0x419110
    int initialize_intro_screen(char* file_name); // @ 0x4191e0
    void update_intro_screen();
    int destroy_intro_screen();

    float progress;                 // +0x00
    float progress_step;            // +0x04
    int state;                      // +0x08
    int saved_render_flags;         // +0x0c
    float duration_seconds;         // +0x10
    int renderable_count;           // +0x14
    IntroLogoRenderable renderables[INTRO_SCREEN_RENDERABLE_COUNT]; // +0x18
    IntroLogoRenderable logo_renderables[INTRO_SCREEN_LOGO_RENDERABLE_COUNT]; // +0x24018
};

typedef char IntroScreenRuntime_must_be_0x25218[
    (sizeof(IntroScreenRuntime) == 0x25218) ? 1 : -1];

#endif
