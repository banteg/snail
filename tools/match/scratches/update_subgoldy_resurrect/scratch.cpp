// update_subgoldy_resurrect @ 0x441fd0 (thiscall, ret)

struct FrontendFade {
    int state; // +0x00

    void begin_frontend_fade_out(int mode);
};

struct AppShell {
    char unknown_000[0x24];
    FrontendFade fade; // +0x24
    char unknown_028[0x1b8 - 0x28];
    int frontend_state;    // +0x1b8
    int frontend_substate; // +0x1bc
    char unknown_1c0[0x30d - 0x1c0];
    unsigned char unknown_30d; // +0x30d
};

extern AppShell* g_app; // data_4df904

class Game {
public:
    void complete_subgame(unsigned char completed);

    char unknown_000000[0x40];
    int level_mode; // +0x40
    char unknown_000044[0xff25d1 - 0x44];
    unsigned char selected_level_record_persistent; // +0xff25d1
    char unknown_ff25d2[0x1270fc8 - 0xff25d2];
    int subgame_rebuild_selector; // +0x1270fc8
};

#include "player.h"

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
        Game* current_game = game;
        if (current_game->level_mode == 0)
            visible_life_stock -= 1;
        g_app->frontend_substate = g_app->frontend_state;
        g_app->frontend_state = 0x1c;
        return;
    }

    Game* current_game = game;
    current_game->subgame_rebuild_selector = 2;
    game->complete_subgame(1);

    Game* persistent_game = game;
    if (persistent_game->selected_level_record_persistent != 0) {
        AppShell* app = g_app;
        app->frontend_substate = app->frontend_state;
        g_app->frontend_state = 0x1a;
        return;
    }

    AppShell* app = g_app;
    app->frontend_substate = app->frontend_state;
    Game* route_game = game;
    if (route_game->level_mode == 0) {
        AppShell* route_app = g_app;
        if (route_app->unknown_30d == 0) {
            route_app->frontend_state = 0x1a;
            g_app->frontend_substate = 2;
            return;
        }
    }
    AppShell* route_app = g_app;
    route_app->frontend_state = 0x1b;
}
