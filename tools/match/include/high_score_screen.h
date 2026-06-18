// High-score front-end views, partial.
#ifndef HIGH_SCORE_SCREEN_H
#define HIGH_SCORE_SCREEN_H

#include "frontend_widget.h"
#include "high_score_bank.h"
#include "sprite.h"

class HighScoreRecordView {
public:
    void commit_high_score_entry_into_top_ten(int rank); // @ 0x417af0

    HighScoreRecord* active_record_bank; // +0x00
    int active_record_count; // +0x04
    char unknown_000008[0x17c108 - 0x08];
    HighScoreRecord name_submit_records[HIGH_SCORE_TOP_TEN_COUNT]; // +0x17c108
};

class HighScoreGameView {
public:
    char unknown_000000[0x1a4];
    char pending_player_name[2]; // +0x1a4
    char unknown_0001a6[0x1b8 - 0x1a6];
    int frontend_next_state; // +0x1b8
    char unknown_0001bc[0x30c - 0x1bc];
    unsigned char frontend_state_dirty; // +0x30c
    unsigned char high_score_entry_pending; // +0x30d
    char unknown_00030e[0x310 - 0x30e];
    int high_score_entry_rank; // +0x310
    int high_score_entry_bank; // +0x314
    char unknown_000318[0x74658 - 0x318];
    int selected_subgame_mode; // +0x74658
    char unknown_07465c[0x6ffae0 - 0x7465c];
    HighScoreRecordView high_score_records; // +0x6ffae0
    char unknown_after_high_score_records[
        0x1066be8 - 0x6ffae0 - sizeof(HighScoreRecordView)];
    unsigned char replay_launch_active; // +0x1066be8
    unsigned char replay_launch_from_frontend; // +0x1066be9
    char unknown_1066bea[0x1066bec - 0x1066bea];
    HighScoreRecord* replay_launch_record; // +0x1066bec
    int replay_launch_return_state; // +0x1066bf0
    char unknown_1066bf4[0x12e55e0 - 0x1066bf4];
    int ordinary_rebuild_selector; // +0x12e55e0
};

class HighScoreScreen {
public:
    int destroy_high_score_screen(); // @ 0x417220
    int update_high_score_screen(); // @ 0x417260
    int initialize_high_score_screen(int mode, int rank); // @ 0x416910
    int exit_high_score_screen(); // @ 0x417b50

    int field_00;
    int mode; // +0x04, front-end return mode
    int selected_bank; // +0x08
    char unknown_0c[0x10 - 0x0c];
    unsigned char entering_name; // +0x10
    char unknown_11[0x14 - 0x11];
    int selected_rank; // +0x14
    char unknown_18[0x1c - 0x18];
    FrontendWidget* back_button; // +0x1c
    FrontendWidget* bank_toggle_button; // +0x20
    FrontendWidget* submit_name_button; // +0x24
    FrontendWidget* cancel_name_button; // +0x28
    char unknown_2c[0x7c - 0x2c];
    FrontendWidget* name_row_widgets[20]; // +0x7c
    FrontendWidget* replay_row_widgets[1]; // +0xcc, active_record_count entries
};

extern char* g_game_base; // data_4df904
extern int g_high_score_selected_bank; // data_4df9c0
extern char g_last_entered_player_name[]; // data_4df978

void __cdecl rstrcpy_checked_ascii(char* destination, char* source); // @ 0x44e5b0

#endif
