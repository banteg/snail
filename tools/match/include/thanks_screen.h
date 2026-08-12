// Windows cRSplash post-run controller. Mobile preserves the authored class
// name and lifecycle, while its leading exit flag makes the port layout 0x18
// instead of this independently recovered 0x14-byte Windows owner.
#ifndef THANKS_SCREEN_H
#define THANKS_SCREEN_H

#include "frontend_widget.h"

class cRSubGame;

class cRSplash {
public:
    void initialize_thanks_for_playing_screen(); // @ 0x433fd0
    void update_thanks_for_playing_screen(); // @ 0x4340f0
    void uninit_thanks_screen(); // @ 0x4340c0

    cRSubGame* game; // +0x00, borrowed enclosing cRSubGame owner
    cRBorder* message_widget; // +0x04
    int message_state; // +0x08
    float message_progress; // +0x0c
    float message_progress_step; // +0x10
};

// Field-first owner-link view shared by GUI and cRSplash.
// Both concrete controllers keep their own layouts; this does not assert a
// common C++ base class merely because their identical setup was folded.
class SubgameOwnerLink {
public:
    cRSubGame* bind_subgame_owner(); // @ 0x433fc0

    cRSubGame* game; // +0x00
};

#endif
