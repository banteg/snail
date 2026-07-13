// initialize_help_screen @ 0x416800 (thiscall)

#include "backdrop.h"
#include "border_manager.h"
#include "game_root.h"
#include "help.h"
#include "landscape_manager.h"

extern GameRoot* g_game; // data_4df904
extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_help_script_path[]; // 0x4a3488
extern char g_blank_text[]; // 0x4dfb08
extern char g_back_text[]; // 0x4a20ec

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

void Help::initialize_help_screen()
{
    Color4f color;

    cache_music_file(g_main_menu_music_path, 0, g_blank_text);
    int script_index = g_game->subgame.landscape_manager
                           .load_landscape_script_by_name(g_help_script_path);
    g_game->backdrop.change_backdrop(
        &g_game->subgame.landscape_manager.scripts[script_index], 0);
    g_game->border_manager.set_border_justify_centre(0);

    back_button = g_game->border_manager.allocate_border();
    back_button->initialize_frontend_widget(
        0x40000014,
        g_back_text,
        0x14,
        0.0f,
        420.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
}
