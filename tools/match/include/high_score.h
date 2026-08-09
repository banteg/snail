// Authored cRHighScore front-end owner. Windows proves controller storage
// through +0xf4; the following 0x14 root bytes remain unassigned before the
// exact cRTipManager boundary. cRSubHighScore is the separate persistent bank.
#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include "frontend_widget.h"
#include "game_base.h"
#include "rstring.h"
#include "sub_high_score.h"
#include "runtime_config.h"
#include "sprite.h"

class cRHighScore {
public:
    void Init(int mode, int rank); // @ 0x416910
    void UnInit(); // @ 0x417220
    void AI(); // @ 0x417260
    void Exit(); // @ 0x417b50

    int field_00;
    int mode; // +0x04, front-end return mode
    int selected_bank; // +0x08
    char unknown_0c[0x10 - 0x0c];
    unsigned char entering_name; // +0x10
    char unknown_11[0x14 - 0x11];
    int selected_rank; // +0x14
    FrontendWidget* title_widget; // +0x18, heading or name-entry prompt
    FrontendWidget* back_button; // +0x1c
    FrontendWidget* bank_toggle_button; // +0x20
    FrontendWidget* cancel_name_button; // +0x24, Cancel/Escape
    FrontendWidget* submit_name_button; // +0x28, Submit/Enter
    FrontendWidget*
        row_background_widgets[SUB_HIGH_SCORE_TOP_TEN_COUNT]; // +0x2c
    FrontendWidget* rank_row_widgets[SUB_HIGH_SCORE_TOP_TEN_COUNT]; // +0x54
    FrontendWidget* name_row_widgets[SUB_HIGH_SCORE_TOP_TEN_COUNT]; // +0x7c
    FrontendWidget* score_row_widgets[SUB_HIGH_SCORE_TOP_TEN_COUNT]; // +0xa4
    FrontendWidget* replay_row_widgets[SUB_HIGH_SCORE_TOP_TEN_COUNT]; // +0xcc
};

typedef cRHighScore HighScore;

typedef char cRHighScore_known_extent_must_be_0xf4[
    (sizeof(cRHighScore) == 0xf4) ? 1 : -1];
typedef char HighScore_known_extent_must_be_0xf4[
    (sizeof(HighScore) == 0xf4) ? 1 : -1];

#endif
