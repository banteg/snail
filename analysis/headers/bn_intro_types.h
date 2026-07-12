#ifndef BN_INTRO_TYPES_H
#define BN_INTRO_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct FrontendWidget FrontendWidget;

/* Exact Windows cRIntro owner at GameRoot +0x4f2dc. */
typedef struct Intro {
    int32_t replay_attract_bank_cursor;
    uint8_t hide_for_replay_latch;
    uint8_t _pad_05[0x3];
    float attract_reset_progress;
    float attract_reset_step;
    float replay_probe_progress;
    float replay_probe_step;
    uint8_t _pad_18[0x18];
    FrontendWidget* postal_button;
    FrontendWidget* time_trial_button;
    FrontendWidget* challenge_button;
    FrontendWidget* tutorial_button;
    FrontendWidget* help_button;
    FrontendWidget* back_button;
} Intro;
typedef Intro NewGameMenu;

void __thiscall initialize_new_game_menu(Intro* intro);
void __thiscall update_new_game_menu(Intro* intro);

#endif
