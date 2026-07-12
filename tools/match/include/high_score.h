// Authored cRHighScore front-end owner. Windows proves controller storage
// through +0xf4; the following 0x14 root bytes remain unassigned before the
// exact TipManager boundary. cRSubHighScore is the separate persistent bank.
#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include "frontend_widget.h"
#include "game_base.h"
#include "sub_solution.h"
#include "runtime_config.h"
#include "sprite.h"

class HighScore {
public:
    int destroy_high_score_screen(); // @ 0x417220, cRHighScore::UnInit
    int update_high_score_screen(); // @ 0x417260, cRHighScore::AI
    int initialize_high_score_screen(int mode, int rank); // @ 0x416910, cRHighScore::Init
    int exit_high_score_screen(); // @ 0x417b50, cRHighScore::Exit

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
    FrontendWidget* row_background_widgets[10]; // +0x2c, full-row hit/tint strips
    FrontendWidget* rank_row_widgets[10]; // +0x54, displayed 1..10 ranks
    FrontendWidget* name_row_widgets[10]; // +0x7c, editable player names
    FrontendWidget* score_row_widgets[10]; // +0xa4, score/time values
    FrontendWidget* replay_row_widgets[10]; // +0xcc, replay actions
};

typedef char HighScore_known_extent_must_be_0xf4[
    (sizeof(HighScore) == 0xf4) ? 1 : -1];

void __cdecl rstrcpy_checked_ascii(char* destination, char* source); // @ 0x44e5b0

#endif
