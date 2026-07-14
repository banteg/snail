// Authored cRGUI front-end level-selection owner. Windows embeds the exact
// 0x28-byte object in SubgameRuntime and uses it for postal, challenge, and
// time-trial setup modes.
#ifndef GUI_H
#define GUI_H

#include "frontend_widget.h"

class SubgameRuntime;

class GUI {
public:
    void initialize_challenge_setup_screen(); // @ 0x415f50, cRGUI::Init
    void destroy_challenge_setup_screen(); // @ 0x4161f0, cRGUI::UnInit
    int update_challenge_setup_screen(); // @ 0x416370, cRGUI::AI

    SubgameRuntime* game; // +0x00, borrowed enclosing cRSubGame owner
    FrontendWidget* next_level_button; // +0x04
    FrontendWidget* previous_level_button; // +0x08
    FrontendWidget* level_name_widget; // +0x0c
    FrontendWidget* play_button; // +0x10
    char unknown_14[0x18 - 0x14];
    FrontendWidget* back_button; // +0x18
    FrontendWidget* speed_slider; // +0x1c
    FrontendWidget* difficulty_slider; // +0x20
    FrontendWidget* replay_button; // +0x24
};

typedef char GUI_must_be_0x28[(sizeof(GUI) == 0x28) ? 1 : -1];

#endif
