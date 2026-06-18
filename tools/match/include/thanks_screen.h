// Thanks-for-playing frontend screen view. Cross-checked by open, initialize,
// and uninit helpers.
#ifndef THANKS_SCREEN_H
#define THANKS_SCREEN_H

#include "frontend_widget.h"

class ThanksScreen {
public:
    void initialize_thanks_for_playing_screen(); // @ 0x433fd0
    void uninit_thanks_screen(); // @ 0x4340c0

    int field_00; // +0x00
    FrontendWidget* message_widget; // +0x04
    int field_08; // +0x08
    int field_0c; // +0x0c
    float field_10; // +0x10
};

class ThanksScreenOwner {
public:
    ThanksScreen* open_thanks_screen(); // @ 0x433fc0

    ThanksScreen* thanks_screen; // +0x00
};

#endif
