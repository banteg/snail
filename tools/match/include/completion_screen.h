// Completion and exit-prompt front-end controllers, partial.
#ifndef COMPLETION_SCREEN_H
#define COMPLETION_SCREEN_H

#include "frontend_widget.h"
#include "high_score_screen.h"
#include "new_game_menu.h"
#include "sprite.h"

class BorderManager {
public:
    FrontendWidget* allocate_border(); // @ 0x4032a0
    void hide_all_borders();           // @ 0x4033f0
    int unhide_all_borders();          // @ 0x403400
    void kill_border(FrontendWidget* border);
};

class SubgameController {
public:
    void initialize_subgame(); // @ 0x4374b0
    void complete_subgame(unsigned char completed); // @ 0x438700
    void destroy_subgame(); // @ 0x438850
};

class PauseMenu {
public:
    int uninit_pause_menu(); // @ 0x440600
    void initialize_pause_menu(); // @ 0x440660
    void* update_pause_menu(); // @ 0x4407a0

    FrontendWidget* options_widget; // +0x00
    FrontendWidget* end_game_widget; // +0x04
    FrontendWidget* resume_widget; // +0x08
};

class MainMenu {
public:
    void destroy_main_menu(); // @ 0x419b30, helper ignores this
    int update_main_menu(); // @ 0x419e00
};

class GalaxyRoute {
public:
    void destroy_galaxy(); // @ 0x408c10
    int update_galaxy(); // @ 0x4092f0
};

class CompletionGameView {
public:
    char unknown_000000[0x38];
    int frontend_quit_mode; // +0x38
    char unknown_00003c[0x1b8 - 0x3c];
    int frontend_next_state; // +0x1b8
    char unknown_0001bc[0x30d - 0x1bc];
    unsigned char frontend_state_dirty; // +0x30d
    char unknown_00030e[0x568 - 0x30e];
    unsigned char frontend_link_latch; // +0x568
    char unknown_000569[0x4f2dc - 0x569];
    NewGameMenu new_game_menu; // +0x4f2dc
    MainMenu main_menu; // +0x4f324
    char unknown_04f325[0x74618 - 0x4f325];
    SubgameController subgame; // +0x74618
    char unknown_074619[0x74621 - 0x74619];
    unsigned char pause_gate; // +0x74621
    char unknown_074622[0x7462c - 0x74622];
    PauseMenu pause_menu; // +0x7462c
    char unknown_074638[0x74658 - 0x74638];
    int selected_subgame_mode; // +0x74658
    char unknown_07465c[0x430060 - 0x7465c];
    int completion_base_score; // +0x430060
    char unknown_430064[0x1066bf0 - 0x430064];
    int replay_launch_return_state; // +0x1066bf0
    char unknown_1066bf4[0x12d4638 - 0x1066bf4];
    GalaxyRoute galaxy; // +0x12d4638
};

class CompletionResultScreen {
public:
    void initialize_completion_screen(int delivered_count, unsigned char perfect_delivery);

    FrontendWidget* title_widget; // +0x00
    FrontendWidget* delivered_count_widget; // +0x04
    FrontendWidget* bonus_summary_widget; // +0x08
    FrontendWidget* bonus_icon_widget; // +0x0c
    FrontendWidget* continue_widget; // +0x10
    int continue_state; // +0x14
    unsigned char continue_visible; // +0x18
    char unknown_19[0x1c - 0x19];
    int delivered_count; // +0x1c
    int perfect_delivery; // +0x20
    int delivered_count_progress; // +0x24
    int delivered_count_display; // +0x28
    float delivered_count_progress_limit; // +0x2c
    float delivered_count_progress_step; // +0x30
    char unknown_34[0x40 - 0x34];
    float bonus_progress; // +0x40
    float bonus_progress_step; // +0x44
    int bonus_score; // +0x48
    int total_score; // +0x4c
};

class CompletionPrompt {
public:
    int initialize_exit_prompt(); // @ 0x4060d0
    int destroy_completion_screen(); // @ 0x406060
    int update_completion_screen(); // @ 0x4067e0

    int state; // +0x00
    char unknown_04[0x08 - 0x04];
    int previous_frontend_state; // +0x08
    float prompt_y; // +0x0c
    FrontendWidget* prompt_title; // +0x10
    FrontendWidget* yes_button; // +0x14
    FrontendWidget* no_button; // +0x18
};

extern char* g_game_base; // data_4df904
extern int g_completion_bonus_x_source; // data_4df958
extern int g_completion_bonus_y_source; // data_4df960
extern int g_completion_bonus_y_table[]; // data_4a1194
extern int g_completion_bonus_x_table[]; // data_4a11ac
extern char g_click_to_continue_text[]; // aClickToContinu

int __cdecl launch_alpha72_url(char* url); // @ 0x433050

#endif
