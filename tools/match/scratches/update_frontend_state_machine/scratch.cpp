// update_frontend_state_machine @ 0x4107d0 (thiscall)
// Root front-end dispatch loop and subgame bridge owner.
#include "game_root.h"
#include "transform_matrix.h"

struct CameraAnchor {
    char unknown_00[0x60];
    float camera_x; // +0x60
    float camera_y; // +0x64
};

struct MouseCursorState {
    void capture_mouse_cursor();
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
