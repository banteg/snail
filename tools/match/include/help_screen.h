// Help front-end controller, partial.
#ifndef HELP_SCREEN_H
#define HELP_SCREEN_H

#include "frontend_widget.h"

class HelpScreen {
public:
    void initialize_help_screen(); // @ 0x416800
    void update_help_screen(); // @ 0x4168d0

    FrontendWidget* back_button; // +0x00
};

typedef char HelpScreen_must_be_0x04[(sizeof(HelpScreen) == 0x04) ? 1 : -1];

#endif
