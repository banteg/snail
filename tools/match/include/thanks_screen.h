// Thanks-for-playing frontend screen view. Cross-checked by open, initialize,
// and uninit helpers.
#ifndef THANKS_SCREEN_H
#define THANKS_SCREEN_H

#include "frontend_widget.h"

class SubgameRuntime;

class ThanksScreen {
public:
    void initialize_thanks_for_playing_screen(); // @ 0x433fd0
    void update_thanks_for_playing_screen(); // @ 0x4340f0
    void uninit_thanks_screen(); // @ 0x4340c0

    SubgameRuntime* game; // +0x00, borrowed enclosing cRSubGame owner
    FrontendWidget* message_widget; // +0x04
    int message_state; // +0x08
    float message_progress; // +0x0c
    float message_progress_step; // +0x10
};

// Field-first owner-link view shared by ChallengeSetupScreen and ThanksScreen.
// Both concrete controllers keep their own layouts; this does not assert a
// common C++ base class merely because their identical setup was folded.
class SubgameOwnerLink {
public:
    SubgameRuntime* bind_subgame_owner(); // @ 0x433fc0

    SubgameRuntime* game; // +0x00
};

#endif
