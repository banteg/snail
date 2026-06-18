// Game runtime view, partial. Keep this header for fields that are corroborated
// by multiple scratches before wider consolidation.
#ifndef GAME_H
#define GAME_H

#include "frontend_widget.h"

class Game {
public:
    void initialize_subgame(); // @ 0x4374b0
    void complete_subgame(unsigned char completed); // @ 0x438700
    void destroy_subgame(); // @ 0x438850
    void remove_subgame_bods(); // @ 0x440910
    void hide_gameplay_scores(); // @ 0x445f10
    void unhide_gameplay_scores(); // @ 0x445f40

    char unknown_000000[0x35bb88];
    FrontendWidget* score_widget_a; // +0x35bb88
    FrontendWidget* score_widget_b; // +0x35bb8c
    FrontendWidget* lives_icon_widget; // +0x35bb90
    FrontendWidget* lives_text_widget; // +0x35bb94
    FrontendWidget* life_stock_widgets[9]; // +0x35bb98
};
typedef char Game_hud_widgets_must_reach_0x35bbbc[
    (sizeof(Game) == 0x35bbbc) ? 1 : -1];

#endif
