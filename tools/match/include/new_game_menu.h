// New-game menu front-end controller, partial.
#ifndef NEW_GAME_MENU_H
#define NEW_GAME_MENU_H

#include "frontend_widget.h"
#include "high_score_screen.h"
#include "mouse_cursor_state.h"

class NewGameInputSource {
public:
    char unknown_00[0x3c];
    unsigned int control_flags; // +0x3c, 0x4000 confirm/menu edge
};

class TutorialController {
public:
    void initialize_tutorial(); // @ 0x448da0
};

class NewGameMenu {
public:
    void update_new_game_menu(); // @ 0x417eb0
    void destroy_main_menu();    // @ 0x419b30, callsite member spelling

    int replay_attract_bank_cursor; // +0x00, cycles 0..4
    unsigned char hide_for_replay_latch; // +0x04
    char unknown_05[0x08 - 0x05];
    float attract_reset_progress; // +0x08, reset with +0x0c
    float attract_reset_step; // +0x0c, 1/3600 after replay probe
    float replay_probe_progress; // +0x10
    float replay_probe_step; // +0x14
    char unknown_18[0x30 - 0x18];
    FrontendWidget* postal_button; // +0x30
    FrontendWidget* challenge_button; // +0x34
    FrontendWidget* time_trial_button; // +0x38
    FrontendWidget* tutorial_button; // +0x3c
    FrontendWidget* help_button; // +0x40
    FrontendWidget* back_button; // +0x44
};

extern char* g_game_base; // data_4df904
extern unsigned char g_new_game_tutorial_started; // data_4df9d8

char read_pressed_text_input_key_code(); // @ 0x432440
int next_math_random_value(); // @ 0x44c900

#endif
