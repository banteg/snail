// Shared root-level game owner view.
#ifndef GAME_ROOT_H
#define GAME_ROOT_H

#include "vector3.h"

class GameRootNewGameMenu {
public:
    int replay_attract_controller; // +0x00

    void initialize_new_game_menu();
    void update_new_game_menu();
};

class GameRootMainMenu {
public:
    void initialize_main_menu();
    void update_main_menu();
};

class GameRootOptionsMenu {
public:
    void initialize_options_menu();
    void update_options_menu();
};

class GameRootCompletionScreen {
public:
    void initialize_exit_prompt();
    void update_completion_screen();
};

class GameRootSubgame {
public:
    void initialize_subgame();
    void update_subgame();
    void destroy_subgame();
};

class GameRootIntroScreen {
public:
    void initialize_intro_screen(char* script_path);
    void update_intro_screen();
};

class GameRootHighScoreScreen {
public:
    void initialize_high_score_screen(int mode, int rank);
    void update_high_score_screen();
};

class GameRootThanksForPlayingScreen {
public:
    void initialize_thanks_for_playing_screen();
    void update_thanks_for_playing_screen();
};

class GameRootHelpScreen {
public:
    void initialize_help_screen();
    void update_help_screen();
};

class GameRoot {
public:
    char unknown_000000[0x38];
    int frontend_quit_requested; // +0x38
    int fixed_update_count;      // +0x3c
    char unknown_000040[0x310 - 0x40];
    int selected_high_score_rank; // +0x310
    int selected_high_score_mode; // +0x314
    char unknown_000318[0x6d4 - 0x318];
    Vector3 star_spawn_direction; // +0x6d4
    char unknown_0006e0[0x6e4 - 0x6e0];
    Vector3 star_spawn_origin; // +0x6e4
    char unknown_0006f0[0x4f2dc - 0x6f0];
    GameRootNewGameMenu new_game_menu; // +0x4f2dc
    char unknown_04f2e0[0x4f324 - 0x4f2e0];
    GameRootMainMenu main_menu; // +0x4f324
    char unknown_04f325[0x4f388 - 0x4f325];
    GameRootOptionsMenu options_menu; // +0x4f388
    char unknown_04f389[0x4f3ac - 0x4f389];
    GameRootCompletionScreen completion_screen; // +0x4f3ac
    char unknown_04f3ad[0x4f400 - 0x4f3ad];
    GameRootIntroScreen intro_screen; // +0x4f400
    char unknown_04f401[0x74618 - 0x4f401];
    GameRootSubgame subgame; // +0x74618
    char unknown_074619[0x104712c - 0x74619];
    int unknown_104712c; // +0x104712c
    char unknown_1047130[0x12d4620 - 0x1047130];
    GameRootHelpScreen help_screen; // +0x12d4620
    char unknown_12d4621[0x12d4624 - 0x12d4621];
    GameRootThanksForPlayingScreen thanks_for_playing_screen; // +0x12d4624
    char unknown_12d4625[0x12e55e0 - 0x12d4625];
    int ordinary_rebuild_selector; // +0x12e55e0
    char unknown_12e55e4[0x12e6e50 - 0x12e55e4];
    GameRootHighScoreScreen high_score_screen; // +0x12e6e50

    int run_frame_update();          // @ 0x40a2a0
    char initialize_game_assets_and_world(); // @ 0x40acf0
    void initialize_game_last();     // @ 0x410720
    int render_game_frame();         // @ 0x40a490
};

#endif
