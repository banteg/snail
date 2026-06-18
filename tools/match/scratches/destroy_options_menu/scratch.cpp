// destroy_options_menu @ 0x41aee0 (thiscall)

#include "border_manager.h"
#include "options_menu.h"

extern char* g_game_base; // data_4df904
extern char g_config_blob; // 0x4df918

extern char* save_config_file(char* file_name, void* bytes, int byte_count);

char* OptionsMenu::destroy_options_menu()
{
    ((BorderManager*)(g_game_base + 0xb4c))->unhide_all_borders();
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(back_widget);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(music_volume_widget);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(sound_volume_widget);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(fullscreen_widget);
    return save_config_file("SnailMail.cfg", &g_config_blob, 0xc4);
}
