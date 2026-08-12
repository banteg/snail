// update_frontend_state_machine @ 0x4107d0 (thiscall)
// Root front-end dispatch loop and subgame bridge owner.
#include "game_root.h"
#include "runtime_config.h"
#include "transform_matrix.h"

extern char aIntroIntroTxt[];
extern char aIntroCreditsTx[];

void cRPlayer::AI()
{
    redispatch_requested = 1;
    do {
        int state = frontend_state;
        redispatch_requested = 0;

        switch (state) {
        case 10:
            g_game->subgame.current_high_score_record.score = 0;
            g_game->subgame.Init();
            frontend_state = 11;
        case 11: {
            GameRoot* owner = g_game;
            owner->subgame.AI();
            break;
        }
        case 12:
        {
            GameRoot* owner = g_game;
            owner->logo.Init(aIntroIntroTxt);
            frontend_state = 13;
            break;
        }
        case 13:
            g_game->logo.AI();
            break;
        case 14:
        {
            GameRoot* owner = g_game;
            owner->logo.Init(aIntroCreditsTx);
            frontend_state = 15;
            break;
        }
        case 15: {
            GameRoot* owner = g_game;
            owner->logo.AI();
            break;
        }
        case 1:
            frontend_state = 0;
            mouse_cursor.SetActive();
            g_game->intro.replay_attract_bank_cursor = 0;
        {
            GameRoot* owner = g_game;
            owner->intro.Init();
            break;
        }
        case 2:
            frontend_state = 0;
            mouse_cursor.SetActive();
        {
            GameRoot* owner = g_game;
            owner->intro.Init();
        }
        case 0:
            g_game->intro.AI();
            break;
        case 3:
            frontend_state = 5;
            mouse_cursor.SetActive();
        {
            GameRoot* owner = g_game;
            owner->main_menu.Init();
            break;
        }
        case 4:
            frontend_state = 5;
            mouse_cursor.SetActive();
        {
            GameRoot* owner = g_game;
            owner->main_menu.Init();
        }
        case 5:
            g_game->main_menu.AI();
            break;
        case 6:
            frontend_state = 7;
        {
            GameRoot* owner = g_game;
            owner->options.Init();
        }
        case 7:
        {
            GameRoot* owner = g_game;
            owner->options.AI();
            break;
        }
        case 8:
            g_game->exit_controller.Init();
            frontend_state = 9;
        case 9: {
            GameRoot* owner = g_game;
            owner->exit_controller.AI();
            break;
        }
        case 18:
            g_game->high_score.Init(
                g_runtime_config.high_score_selected_bank, -1);
            frontend_state = 19;
            break;
        case 19: {
            GameRoot* owner = g_game;
            owner->high_score.AI();
            break;
        }
        case 20: {
            GameRoot* game = g_game;
            game->high_score.Init(
                game->players[0].selected_high_score_mode,
                game->players[0].selected_high_score_rank);
            frontend_state = 21;
            break;
        }
        case 21: {
            GameRoot* owner = g_game;
            owner->high_score.AI();
            break;
        }
        case 25:
            g_game->frontend_quit_requested = 1;
            break;
        case 26:
        {
            GameRoot* owner = g_game;
            owner->subgame.UnInit();
            goto restore_saved_state;
        }
        case 27:
        {
            GameRoot* owner = g_game;
            owner->subgame.UnInit();
            g_game->subgame.Init();
            goto restore_saved_state;
        }
        case 28:
        {
            GameRoot* owner = g_game;
            owner->subgame.UnInit();
        }
            g_game->subgame.subgame_rebuild_selector = 0;
            g_game->subgame.Init();
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
            owner->subgame.splash.Init();
        }
        case 30: {
            GameRoot* owner = g_game;
            owner->subgame.splash.AI();
            break;
        }
        case 31:
            frontend_state = 32;
            g_game->subgame.help.Init();
        case 32: {
            GameRoot* owner = g_game;
            owner->subgame.help.AI();
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
    camera.view_matrix.Invert(*live_matrix);
}
