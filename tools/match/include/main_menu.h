// Main-menu front-end controller, partial.
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "frontend_widget.h"

class MainMenu {
public:
    void destroy_main_menu(); // @ 0x419b30, cRMainMenu::UnInit, folded body
    void initialize_main_menu(); // @ 0x419b50
    void update_main_menu(); // @ 0x419e00

    FrontendWidget* new_game_widget; // +0x00
    FrontendWidget* high_scores_widget; // +0x04
    FrontendWidget* options_widget; // +0x08
    FrontendWidget* credits_widget; // +0x0c
    char unknown_10[0x14 - 0x10];
    FrontendWidget* exit_widget; // +0x14
};

typedef char MainMenu_must_be_0x18[(sizeof(MainMenu) == 0x18) ? 1 : -1];

#endif
