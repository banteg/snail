// Challenge setup/front-end level selection controller, partial.
#ifndef CHALLENGE_SETUP_SCREEN_H
#define CHALLENGE_SETUP_SCREEN_H

#include "frontend_widget.h"

class ChallengeSetupGameView {
public:
    char unknown_000000[0x40];
    int selected_subgame_mode; // +0x40
    int selected_level_index; // +0x44
};

class ChallengeSetupScreen {
public:
    void destroy_challenge_setup_screen(); // @ 0x4161f0

    ChallengeSetupGameView* game; // +0x00
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

#endif
