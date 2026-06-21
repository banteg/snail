// update_subgoldy_resurrect @ 0x441fd0 (thiscall, ret)

#include "app_shell.h"
#include "player.h"

class SubgoldyResurrectGameView {
public:
    void complete_subgame(unsigned char completed);

    char unknown_000000[0x40];
    int level_mode; // +0x40
    char unknown_000044[0xff25d1 - 0x44];
    unsigned char selected_level_record_persistent; // +0xff25d1
    char unknown_ff25d2[0x1270fc8 - 0xff25d2];
    int subgame_rebuild_selector; // +0x1270fc8
};

void Player::update_subgoldy_resurrect()
{
    velocity.z = 0.0f;

    if (g_app->fade.state == 0) {
        float progress = resurrect_progress + resurrect_progress_step;
        resurrect_progress = progress;
        if (progress > 1.0f) {
            if (g_app->fade.state == 0)
                g_app->fade.begin_frontend_fade_out(0);
        }
    }

    if (resurrect_progress <= 1.0f || g_app->fade.state != 4)
        return;

    if (resurrect_final_loss == 0) {
        SubgoldyResurrectGameView* current_game = (SubgoldyResurrectGameView*)game;
        if (current_game->level_mode == 0)
            visible_life_stock -= 1;
        g_app->frontend_substate = g_app->frontend_state;
        g_app->frontend_state = 0x1c;
        return;
    }

    SubgoldyResurrectGameView* current_game = (SubgoldyResurrectGameView*)game;
    current_game->subgame_rebuild_selector = 2;
    ((SubgoldyResurrectGameView*)game)->complete_subgame(1);

    SubgoldyResurrectGameView* persistent_game = (SubgoldyResurrectGameView*)game;
    if (persistent_game->selected_level_record_persistent != 0) {
        AppShell* app = g_app;
        app->frontend_substate = app->frontend_state;
        g_app->frontend_state = 0x1a;
        return;
    }

    AppShell* app = g_app;
    app->frontend_substate = app->frontend_state;
    SubgoldyResurrectGameView* route_game = (SubgoldyResurrectGameView*)game;
    if (route_game->level_mode == 0) {
        AppShell* route_app = g_app;
        if (route_app->high_score_entry_pending == 0) {
            route_app->frontend_state = 0x1a;
            g_app->frontend_substate = 2;
            return;
        }
    }
    AppShell* route_app = g_app;
    route_app->frontend_state = 0x1b;
}
