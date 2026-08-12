// Main-menu front-end controller, partial.
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "frontend_widget.h"

class cRMainMenu {
public:
    void destroy_main_menu(); // @ 0x419b30, cRMainMenu::UnInit, folded body
    void initialize_main_menu(); // @ 0x419b50
    void update_main_menu(); // @ 0x419e00

    cRBorder* new_game_widget; // +0x00
    cRBorder* high_scores_widget; // +0x04
    cRBorder* options_widget; // +0x08
    cRBorder* credits_widget; // +0x0c
    char unknown_10[0x14 - 0x10];
    cRBorder* exit_widget; // +0x14
};

typedef cRMainMenu MainMenu;
typedef char MainMenu_must_be_0x18[
    (sizeof(cRMainMenu) == 0x18) ? 1 : -1];

#endif
