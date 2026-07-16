// update_subgoldy_resurrect @ 0x441fd0 (thiscall, ret)

#include "game_root.h"


void Player::update_subgoldy_resurrect()
{
    velocity.z = 0.0f;

    if (g_game->fade.state == 0) {
        float progress = resurrect_progress + resurrect_progress_step;
        resurrect_progress = progress;
        if (progress > 1.0f) {
            if (g_game->fade.state == 0)
                g_game->fade.begin_frontend_fade_out(0);
        }
    }

    if (resurrect_progress <= 1.0f || g_game->fade.state != 4)
        return;

    if (resurrect_final_loss == 0) {
        SubgameRuntime* current_game = game;
        if (current_game->level_mode == 0)
            visible_life_stock -= 1;
        g_game->players[0].saved_frontend_state =
            g_game->players[0].frontend_state;
        g_game->players[0].frontend_state = 0x1c;
        return;
    }

    SubgameRuntime* current_game = game;
    current_game->subgame_rebuild_selector = 2;
    game->complete_subgame(1);

    SubgameRuntime* persistent_game = game;
    if (persistent_game->selected_level_record_persistent != 0) {
        GameRoot* app = g_game;
        app->players[0].saved_frontend_state = app->players[0].frontend_state;
        g_game->players[0].frontend_state = 0x1a;
        return;
    }

    GameRoot* app = g_game;
    app->players[0].saved_frontend_state = app->players[0].frontend_state;
    SubgameRuntime* route_game = game;
    if (route_game->level_mode == 0) {
        GameRoot* route_app = g_game;
        if (route_app->players[0].high_score_entry_pending == 0) {
            route_app->players[0].frontend_state = 0x1a;
            g_game->players[0].saved_frontend_state = 2;
            return;
        }
    }
    GameRoot* route_app = g_game;
    route_app->players[0].frontend_state = 0x1b;
}
