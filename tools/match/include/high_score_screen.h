// High-score front-end views, partial.
#ifndef HIGH_SCORE_SCREEN_H
#define HIGH_SCORE_SCREEN_H

#include "frontend_widget.h"
#include "game_base.h"
#include "high_score_record.h"
#include "sprite.h"

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
    FrontendWidget* cancel_name_button; // +0x24, Cancel/Escape
    FrontendWidget* submit_name_button; // +0x28, Submit/Enter
    char unknown_2c[0x7c - 0x2c];
    FrontendWidget* name_row_widgets[20]; // +0x7c
    FrontendWidget* replay_row_widgets[1]; // +0xcc, active_record_count entries
};

extern int g_high_score_selected_bank; // data_4df9c0
extern char g_last_entered_player_name[]; // data_4df978

void __cdecl rstrcpy_checked_ascii(char* destination, char* source); // @ 0x44e5b0

#endif
