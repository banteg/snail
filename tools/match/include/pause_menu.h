// Embedded pause-menu widget owner.
#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "frontend_widget.h"

class PauseMenu {
public:
    int uninit_pause_menu(); // @ 0x440600
    void initialize_pause_menu(); // @ 0x440660
    void* update_pause_menu(); // @ 0x4407a0

    FrontendWidget* options_widget; // +0x00
    FrontendWidget* end_game_widget; // +0x04
    FrontendWidget* resume_widget; // +0x08
};

#endif
