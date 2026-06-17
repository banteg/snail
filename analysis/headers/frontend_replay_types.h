#ifndef FRONTEND_REPLAY_TYPES_H
#define FRONTEND_REPLAY_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct FrontendWidget FrontendWidget;
typedef struct HighScoreRecord HighScoreRecord;

typedef struct HighScoreScreen {
    int32_t field_00;
    int32_t mode;
    int32_t selected_bank;
    uint8_t _pad_0c[0x10 - 0x0c];
    uint8_t entering_name;
    uint8_t _pad_11[0x14 - 0x11];
    int32_t selected_rank;
    uint8_t _pad_18[0x1c - 0x18];
    FrontendWidget* back_button;
    FrontendWidget* bank_toggle_button;
    FrontendWidget* submit_name_button;
    FrontendWidget* cancel_name_button;
    uint8_t _pad_2c[0x7c - 0x2c];
    FrontendWidget* name_row_widgets[20];
    FrontendWidget* replay_row_widgets[1];
} HighScoreScreen;

typedef struct NewGameMenu {
    int32_t replay_attract_bank_cursor;
    uint8_t hide_for_replay_latch;
    uint8_t _pad_05[0x08 - 0x05];
    float attract_reset_progress;
    float attract_reset_step;
    float replay_probe_progress;
    float replay_probe_step;
    uint8_t _pad_18[0x30 - 0x18];
    FrontendWidget* postal_button;
    FrontendWidget* challenge_button;
    FrontendWidget* time_trial_button;
    FrontendWidget* tutorial_button;
    FrontendWidget* help_button;
    FrontendWidget* back_button;
} NewGameMenu;

typedef struct HighScoreRecord {
    int32_t active;
    uint8_t _pad_04[0x2c - 0x04];
    int32_t level_mode;
    uint8_t _pad_30[0x54 - 0x30];
    char player_name[2];
} HighScoreRecord;

#endif
