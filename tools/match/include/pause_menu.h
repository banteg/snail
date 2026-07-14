// Authored cRSubPause owner embedded in cRSubGame at +0x14.
#ifndef SUB_PAUSE_H
#define SUB_PAUSE_H

#include "frontend_widget.h"

class SubPause {
public:
    void uninit_pause_menu(); // @ 0x440600
    void initialize_pause_menu(); // @ 0x440660
    void update_pause_menu(); // @ 0x4407a0

    FrontendWidget* options_widget; // +0x00
    FrontendWidget* end_game_widget; // +0x04
    FrontendWidget* resume_widget; // +0x08
};

typedef char SubPause_must_be_0x0c[(sizeof(SubPause) == 0x0c) ? 1 : -1];

#endif
