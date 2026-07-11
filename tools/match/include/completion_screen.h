// Completion and exit-prompt front-end controllers, partial.
#ifndef COMPLETION_SCREEN_H
#define COMPLETION_SCREEN_H

#include "border_manager.h"
#include "frontend_widget.h"
#include "runtime_config.h"
#include "sprite.h"

class PauseMenu {
public:
    int uninit_pause_menu(); // @ 0x440600
    void initialize_pause_menu(); // @ 0x440660
    void* update_pause_menu(); // @ 0x4407a0

    FrontendWidget* options_widget; // +0x00
    FrontendWidget* end_game_widget; // +0x04
    FrontendWidget* resume_widget; // +0x08
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

typedef char CompletionPrompt_must_be_0x1c[
    (sizeof(CompletionPrompt) == 0x1c) ? 1 : -1];

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

extern int g_completion_bonus_y_table[]; // data_4a1194
extern int g_completion_bonus_x_table[]; // data_4a11ac
extern char g_click_to_continue_text[]; // aClickToContinu

int __cdecl launch_alpha72_url(char* url); // @ 0x433050

#endif
