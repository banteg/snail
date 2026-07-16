// destroy_options_menu @ 0x41aee0 (thiscall)

#include "game_root.h"
#include "options.h"
#include "runtime_config.h"

extern char* save_config_file(char* file_name, void* bytes, int byte_count);

void Options::destroy_options_menu()
{
    g_game->border_manager.unhide_all_borders();
    g_game->border_manager.kill_border(back_widget);
    g_game->border_manager.kill_border(music_volume_widget);
    g_game->border_manager.kill_border(sound_volume_widget);
    g_game->border_manager.kill_border(fullscreen_widget);
    save_config_file("SnailMail.cfg", &g_runtime_config, sizeof(g_runtime_config));
}
