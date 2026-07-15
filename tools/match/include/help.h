// Authored cRHelp front-end owner embedded in SubgameRuntime.
#ifndef HELP_H
#define HELP_H

#include "frontend_widget.h"

class Help {
public:
    void initialize_help_screen(); // @ 0x416800, cRHelp::Init
    void destroy_help_screen(); // @ 0x4168c0, cRHelp::UnInit
    void update_help_screen(); // @ 0x4168d0, cRHelp::AI

    FrontendWidget* back_button; // +0x00
};

typedef char Help_must_be_0x04[(sizeof(Help) == 0x04) ? 1 : -1];

#endif
