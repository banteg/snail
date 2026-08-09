// Windows projection of the authored cRFade owner at GameRoot +0x24.
#ifndef FRONTEND_FADE_H
#define FRONTEND_FADE_H

typedef void (*FrontendFadeCallback)();

class cRFade {
public:
    // Windows folds this trivial initializer with cRBorderStack::Init().
    void Init(); // folded @ 0x404350
    void Start(FrontendFadeCallback completion_callback); // @ 0x40abc0
    void StartOn(); // @ 0x40abe0
    void AI(); // @ 0x40abf0

    int state; // +0x00
    union {
        int alpha_bits; // +0x04
        float alpha;
    };
    float hold_progress; // +0x08
    float hold_progress_step; // +0x0c
    FrontendFadeCallback completion_callback; // +0x10
};

// Compatibility vocabulary retained for existing Windows-analysis callers.
typedef cRFade FrontendFade;

typedef char cRFade_must_be_0x14[(sizeof(cRFade) == 0x14) ? 1 : -1];
typedef char FrontendFade_must_be_0x14[
    (sizeof(FrontendFade) == 0x14) ? 1 : -1];

#endif
