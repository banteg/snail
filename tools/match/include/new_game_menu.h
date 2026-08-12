// Windows cRIntro front-end controller at GameRoot +0x4f2dc. Mobile ports add
// a Pro-Challenge widget and therefore use a different tail layout.
#ifndef NEW_GAME_MENU_H
#define NEW_GAME_MENU_H

#include "frontend_widget.h"
#include "runtime_config.h"
#include "input_state.h"
#include "mouse_cursor_state.h"

class cRIntro {
public:
    void Init();   // @ 0x417bc0
    void AI();     // @ 0x417eb0
    void UnInit(); // @ 0x419b30, folded with cRMainMenu::UnInit

    int replay_attract_bank_cursor; // +0x00, cycles 0..4
    unsigned char hide_for_replay_latch; // +0x04
    char unknown_05[0x08 - 0x05];
    float attract_reset_progress; // +0x08, reset with +0x0c
    float attract_reset_step; // +0x0c, 1/3600 after replay probe
    float replay_probe_progress; // +0x10
    float replay_probe_step; // +0x14
    char unknown_18[0x30 - 0x18];
    cRBorder* postal_button; // +0x30
    cRBorder* time_trial_button; // +0x34
    cRBorder* challenge_button; // +0x38
    cRBorder* tutorial_button; // +0x3c
    cRBorder* help_button; // +0x40
    cRBorder* back_button; // +0x44
};
typedef cRIntro Intro;
typedef cRIntro NewGameMenu;
typedef char Intro_must_be_0x48[(sizeof(cRIntro) == 0x48) ? 1 : -1];


char read_pressed_text_input_key_code(); // @ 0x432440
int next_math_random_value(); // @ 0x44c900

#endif
