// update_frontend_state_machine @ 0x4107d0 (thiscall)
// Root front-end dispatch loop and subgame bridge owner.
#include "transform_matrix.h"

struct CameraAnchor {
    char unknown_00[0x60];
    float camera_x; // +0x60
    float camera_y; // +0x64
};

struct MouseCursorState {
    void capture_mouse_cursor();
};

struct NewGameMenu {
    int replay_attract_controller; // +0x00, data_4df904 + 0x4f2dc

    void initialize_new_game_menu();
    void update_new_game_menu();
};

struct MainMenu {
    void initialize_main_menu();
    void update_main_menu();
};

struct OptionsMenu {
    void initialize_options_menu();
    void update_options_menu();
};

struct CompletionScreen {
    void initialize_exit_prompt();
    void update_completion_screen();
};

struct Subgame {
    void initialize_subgame();
    void update_subgame();
    void destroy_subgame();
};

struct IntroScreen {
    void initialize_intro_screen(char* script_path);
    void update_intro_screen();
};

struct HighScoreScreen {
    void initialize_high_score_screen(int mode, int rank);
    void update_high_score_screen();
};

struct ThanksForPlayingScreen {
    void initialize_thanks_for_playing_screen();
    void update_thanks_for_playing_screen();
};

struct HelpScreen {
    void initialize_help_screen();
    void update_help_screen();
};

struct GameRoot {
    char unknown_000000[0x38];
    int frontend_quit_requested; // +0x38
    char unknown_00003c[0x310 - 0x3c];
    int selected_high_score_rank; // +0x310
    int selected_high_score_mode; // +0x314
    char unknown_000318[0x4f2dc - 0x318];
    NewGameMenu new_game_menu; // +0x4f2dc
    char unknown_04f2e0[0x4f324 - 0x4f2e0];
    MainMenu main_menu; // +0x4f324
    char unknown_04f325[0x4f388 - 0x4f325];
    OptionsMenu options_menu; // +0x4f388
    char unknown_04f389[0x4f3ac - 0x4f389];
    CompletionScreen completion_screen; // +0x4f3ac
    char unknown_04f3ad[0x4f400 - 0x4f3ad];
    IntroScreen intro_screen; // +0x4f400
    char unknown_04f401[0x74618 - 0x4f401];
    Subgame subgame; // +0x74618
    char unknown_074619[0x104712c - 0x74619];
    int unknown_104712c; // +0x104712c
    char unknown_1047130[0x12d4620 - 0x1047130];
    HelpScreen help_screen; // +0x12d4620
    char unknown_12d4621[0x12d4624 - 0x12d4621];
    ThanksForPlayingScreen thanks_for_playing_screen; // +0x12d4624
    char unknown_12d4625[0x12e55e0 - 0x12d4625];
    int ordinary_rebuild_selector; // +0x12e55e0
    char unknown_12e55e4[0x12e6e50 - 0x12e55e4];
    HighScoreScreen high_score_screen; // +0x12e6e50
};

extern GameRoot* volatile g_game; // data_4df904
extern int g_high_score_selected_bank; // data_4df9c0
extern char aIntroIntroTxt[];
extern char aIntroCreditsTx[];

class FrontendStateMachine {
public:
    int update_frontend_state_machine();
};

int FrontendStateMachine::update_frontend_state_machine()
{
    char* self = (char*)this;

    *(unsigned char*)(self + 0x1e8) = 1;
    do {
        int state = *(int*)(self + 0x94);
        *(unsigned char*)(self + 0x1e8) = 0;

        switch (state) {
        case 10:
            g_game->unknown_104712c = 0;
            g_game->subgame.initialize_subgame();
            *(int*)(self + 0x94) = 11;
        case 11: {
            GameRoot* owner = g_game;
            owner->subgame.update_subgame();
            break;
        }
        case 12:
        {
            GameRoot* owner = g_game;
            owner->intro_screen.initialize_intro_screen(aIntroIntroTxt);
            *(int*)(self + 0x94) = 13;
            break;
        }
        case 13:
            g_game->intro_screen.update_intro_screen();
            break;
        case 14:
        {
            GameRoot* owner = g_game;
            owner->intro_screen.initialize_intro_screen(aIntroCreditsTx);
            *(int*)(self + 0x94) = 15;
            break;
        }
        case 15: {
            GameRoot* owner = g_game;
            owner->intro_screen.update_intro_screen();
            break;
        }
        case 1:
            *(int*)(self + 0x94) = 0;
            ((MouseCursorState*)(self + 0x16c))->capture_mouse_cursor();
            g_game->new_game_menu.replay_attract_controller = 0;
        {
            GameRoot* owner = g_game;
            owner->new_game_menu.initialize_new_game_menu();
            break;
        }
        case 2:
            *(int*)(self + 0x94) = 0;
            ((MouseCursorState*)(self + 0x16c))->capture_mouse_cursor();
        {
            GameRoot* owner = g_game;
            owner->new_game_menu.initialize_new_game_menu();
        }
        case 0:
            g_game->new_game_menu.update_new_game_menu();
            break;
        case 3:
            *(int*)(self + 0x94) = 5;
            ((MouseCursorState*)(self + 0x16c))->capture_mouse_cursor();
        {
            GameRoot* owner = g_game;
            owner->main_menu.initialize_main_menu();
            break;
        }
        case 4:
            *(int*)(self + 0x94) = 5;
            ((MouseCursorState*)(self + 0x16c))->capture_mouse_cursor();
        {
            GameRoot* owner = g_game;
            owner->main_menu.initialize_main_menu();
        }
        case 5:
            g_game->main_menu.update_main_menu();
            break;
        case 6:
            *(int*)(self + 0x94) = 7;
        {
            GameRoot* owner = g_game;
            owner->options_menu.initialize_options_menu();
        }
        case 7:
        {
            GameRoot* owner = g_game;
            owner->options_menu.update_options_menu();
            break;
        }
        case 8:
            g_game->completion_screen.initialize_exit_prompt();
            *(int*)(self + 0x94) = 9;
        case 9: {
            GameRoot* owner = g_game;
            owner->completion_screen.update_completion_screen();
            break;
        }
        case 18:
            g_game->high_score_screen.initialize_high_score_screen(g_high_score_selected_bank, -1);
            *(int*)(self + 0x94) = 19;
            break;
        case 19: {
            GameRoot* owner = g_game;
            owner->high_score_screen.update_high_score_screen();
            break;
        }
        case 20: {
            GameRoot* game = g_game;
            game->high_score_screen.initialize_high_score_screen(
                game->selected_high_score_mode,
                game->selected_high_score_rank);
            *(int*)(self + 0x94) = 21;
            break;
        }
        case 21: {
            GameRoot* owner = g_game;
            owner->high_score_screen.update_high_score_screen();
            break;
        }
        case 25:
            g_game->frontend_quit_requested = 1;
            break;
        case 26:
        {
            GameRoot* owner = g_game;
            owner->subgame.destroy_subgame();
            goto restore_saved_state;
        }
        case 27:
        {
            GameRoot* owner = g_game;
            owner->subgame.destroy_subgame();
            goto initialize_subgame_then_restore;
        }
        case 28:
        {
            GameRoot* owner = g_game;
            owner->subgame.destroy_subgame();
        }
            g_game->ordinary_rebuild_selector = 0;
        initialize_subgame_then_restore:
            g_game->subgame.initialize_subgame();
        restore_saved_state: {
            int saved_state = *(int*)(self + 0x98);
            if (saved_state != -1)
                *(int*)(self + 0x94) = saved_state;
            break;
        }
        case 29:
            *(int*)(self + 0x94) = 30;
        {
            GameRoot* owner = g_game;
            owner->thanks_for_playing_screen.initialize_thanks_for_playing_screen();
        }
        case 30: {
            GameRoot* owner = g_game;
            owner->thanks_for_playing_screen.update_thanks_for_playing_screen();
            break;
        }
        case 31:
            *(int*)(self + 0x94) = 32;
            g_game->help_screen.initialize_help_screen();
        case 32: {
            GameRoot* owner = g_game;
            owner->help_screen.update_help_screen();
            break;
        }
        default:
            break;
        }
    } while (*(unsigned char*)(self + 0x1e8) == 1);

    CameraAnchor* camera = *(CameraAnchor**)(self + 0x168);
    float camera_x = camera->camera_x;
    *(float*)(self + 0x178) = camera_x;
    float camera_y = camera->camera_y;
    TransformMatrix* live_matrix = (TransformMatrix*)(self + 0x38);
    TransformMatrix* snapshot_matrix = (TransformMatrix*)(self + 0xd8);
    *snapshot_matrix = *live_matrix;
    *(float*)(self + 0x17c) = camera_y;
    return (int)((TransformMatrix*)(self + 0x120))->invert_matrix_from_source(live_matrix);
}
