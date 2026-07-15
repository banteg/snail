// Shared frontend fade overlay controller at GameRoot +0x24.
#ifndef FRONTEND_FADE_H
#define FRONTEND_FADE_H

class FrontendFade {
public:
    // Windows folds this trivial initializer with cRBorderStack::Init().
    void initialize_frontend_fade(); // @ 0x404350
    int begin_frontend_fade_out(int hold_state);
    void begin_frontend_fade_in();
    void update_frontend_transition_overlay();

    int state; // +0x00
    union {
        int alpha_bits; // +0x04
        float alpha;
    };
    float hold_progress; // +0x08
    float hold_progress_step; // +0x0c
    int hold_state; // +0x10
};

#endif
