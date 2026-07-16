// initialize_thanks_for_playing_screen @ 0x433fd0 (thiscall)

#include "backdrop.h"
#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "landscape_manager.h"
#include "sprite.h"
#include "star_manager.h"
#include "thanks_screen.h"

extern GameRoot* g_game; // data_4df904
extern char g_blank_text[]; // 0x4dfb08

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

void ThanksScreen::initialize_thanks_for_playing_screen()
{
    tColour color;

    g_game->star_manager.hide_star_field();
    cache_music_file("music/introtext.ogg", 0, g_blank_text);
    int script_index = g_game->subgame.landscape_manager
                           .load_landscape_script_by_name("Splash.txt");
    g_game->backdrop.change_backdrop(
        &g_game->subgame.landscape_manager.scripts[script_index], 0);
    g_game->border_manager.set_border_justify_centre(0.0f);

    message_widget = g_game->border_manager.allocate_border();
    message_widget->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FRAMELESS
            | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
        "Thanks For Playing!",
        0x14,
        0.0f,
        435.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    message_widget->font_scale = 1.2f;
    message_progress = 0.0f;
    message_progress_step = 0.00416666688f;
    message_state = 0;
}
