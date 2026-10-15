// Authored cRSubPause owner embedded in cRSubGame at +0x14.
#ifndef SUB_PAUSE_H
#define SUB_PAUSE_H

#include "frontend_widget.h"

class cRSubPause {
public:
    void UnInit(); // @ 0x440600
    void Init(); // @ 0x440660
    void AI(); // @ 0x4407a0

    cRBorder* options_widget; // +0x00
    cRBorder* end_game_widget; // +0x04
    cRBorder* resume_widget; // +0x08
};

// Compatibility vocabulary retained for existing Windows-analysis callers.
typedef cRSubPause SubPause;

typedef char cRSubPause_must_be_0x0c[
    (sizeof(cRSubPause) == 0x0c) ? 1 : -1];
typedef char SubPause_must_be_0x0c[(sizeof(SubPause) == 0x0c) ? 1 : -1];

#endif
