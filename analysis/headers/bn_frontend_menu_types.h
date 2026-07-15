#ifndef BN_FRONTEND_MENU_TYPES_H
#define BN_FRONTEND_MENU_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct FrontendWidget FrontendWidget;

/* Exact Windows cRMainMenu owner at GameRoot +0x4f324. */
typedef struct MainMenu {
    FrontendWidget* new_game_widget;
    FrontendWidget* high_scores_widget;
    FrontendWidget* options_widget;
    FrontendWidget* credits_widget;
    uint8_t _pad_10[0x4];
    FrontendWidget* exit_widget;
} MainMenu;

/* Exact Windows cROptions owner at GameRoot +0x4f388. */
typedef struct Options {
    int32_t previous_frontend_state;
    uint8_t active;
    uint8_t _pad_05[0x0b];
    FrontendWidget* back_widget;
    FrontendWidget* fullscreen_widget;
    FrontendWidget* sound_volume_widget;
    FrontendWidget* music_volume_widget;
    float previous_sample_volume;
} Options;

/* Exact Windows cRExit owner at GameRoot +0x4f3ac. */
typedef struct Exit {
    int32_t state;
    uint8_t _pad_04[0x4];
    int32_t previous_frontend_state;
    float prompt_y;
    FrontendWidget* prompt_title;
    FrontendWidget* yes_button;
    FrontendWidget* no_button;
} Exit;

#endif
