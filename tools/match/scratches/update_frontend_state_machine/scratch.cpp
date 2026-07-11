// update_frontend_state_machine @ 0x4107d0 (thiscall)
// Root front-end dispatch loop and subgame bridge owner.
#include "game_root.h"
#include "runtime_config.h"
#include "transform_matrix.h"

extern GameRoot* g_game; // data_4df904
extern char aIntroIntroTxt[];
extern char aIntroCreditsTx[];

int GamePlayer::update_frontend_state_machine()
{
    redispatch_requested = 1;
    do {
        int state = frontend_state;
        redispatch_requested = 0;

        switch (state) {
        case 10:
            g_game->subgame.current_high_score_record.score = 0;
            g_game->subgame.initialize_subgame();
            frontend_state = 11;
        case 11: {
            GameRoot* owner = g_game;
            owner->subgame.update_subgame();
            break;
        }
        case 12:
        {
            GameRoot* owner = g_game;
            owner->intro_screen.initialize_intro_screen(aIntroIntroTxt);
            frontend_state = 13;
            break;
        }
        case 13:
            g_game->intro_screen.update_intro_screen();
            break;
        case 14:
        {
            GameRoot* owner = g_game;
            owner->intro_screen.initialize_intro_screen(aIntroCreditsTx);
            frontend_state = 15;
            break;
        }
        case 15: {
            GameRoot* owner = g_game;
            owner->intro_screen.update_intro_screen();
            break;
        }
        case 1:
            frontend_state = 0;
            mouse_cursor.capture_mouse_cursor();
            g_game->new_game_menu.replay_attract_bank_cursor = 0;
        {
            GameRoot* owner = g_game;
            owner->new_game_menu.initialize_new_game_menu();
            break;
        }
        case 2:
            frontend_state = 0;
            mouse_cursor.capture_mouse_cursor();
        {
            GameRoot* owner = g_game;
            owner->new_game_menu.initialize_new_game_menu();
        }
        case 0:
            g_game->new_game_menu.update_new_game_menu();
            break;
        case 3:
            frontend_state = 5;
            mouse_cursor.capture_mouse_cursor();
        {
            GameRoot* owner = g_game;
            owner->main_menu.initialize_main_menu();
            break;
        }
        case 4:
            frontend_state = 5;
            mouse_cursor.capture_mouse_cursor();
        {
            GameRoot* owner = g_game;
            owner->main_menu.initialize_main_menu();
        }
        case 5:
            g_game->main_menu.update_main_menu();
            break;
        case 6:
            frontend_state = 7;
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
            g_game->exit_prompt.initialize_exit_prompt();
            frontend_state = 9;
        case 9: {
            GameRoot* owner = g_game;
            owner->exit_prompt.update_completion_screen();
            break;
        }
        case 18:
            g_game->high_score_screen.initialize_high_score_screen(
                g_runtime_config.high_score_selected_bank, -1);
            frontend_state = 19;
            break;
        case 19: {
            GameRoot* owner = g_game;
            owner->high_score_screen.update_high_score_screen();
            break;
        }
        case 20: {
            GameRoot* game = g_game;
            game->high_score_screen.initialize_high_score_screen(
                game->players[0].selected_high_score_mode,
                game->players[0].selected_high_score_rank);
            frontend_state = 21;
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
            g_game->subgame.initialize_subgame();
            goto restore_saved_state;
        }
        case 28:
        {
            GameRoot* owner = g_game;
            owner->subgame.destroy_subgame();
        }
            g_game->subgame.subgame_rebuild_selector = 0;
            g_game->subgame.initialize_subgame();
        restore_saved_state: {
            int saved_state = saved_frontend_state;
            if (saved_state != -1)
                frontend_state = saved_state;
            break;
        }
        case 29:
            frontend_state = 30;
        {
            GameRoot* owner = g_game;
            owner->subgame.thanks_screen.initialize_thanks_for_playing_screen();
        }
        case 30: {
            GameRoot* owner = g_game;
            owner->subgame.thanks_screen.update_thanks_for_playing_screen();
            break;
        }
        case 31:
            frontend_state = 32;
            g_game->subgame.help_screen.initialize_help_screen();
        case 32: {
            GameRoot* owner = g_game;
            owner->subgame.help_screen.update_help_screen();
            break;
        }
        default:
            break;
        }
    } while (redispatch_requested == 1);

    GameInput* input_owner = game_input;
    float anchor_x = input_owner->input.authored_x;
    mouse_cursor.saved_x = anchor_x;
    float anchor_y = input_owner->input.authored_y;
    TransformMatrix* live_matrix = &transform;
    TransformMatrix* snapshot_matrix = &camera.transform;
    *snapshot_matrix = *live_matrix;
    mouse_cursor.saved_y = anchor_y;
    return (int)camera.view_matrix.invert_matrix_from_source(live_matrix);
}
