// initialize_help_screen @ 0x416800 (thiscall)

#include "backdrop.h"
#include "border_runtime.h"
#include "help_screen.h"
#include "landscape_script_bank.h"

extern char* g_game_base; // data_4df904
extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_help_script_path[]; // 0x4a3488
extern char g_blank_text[]; // 0x4dfb08
extern char g_back_text[]; // 0x4a20ec

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

class HelpBorderManager {
public:
    FrontendWidget* allocate_border();
};

void HelpScreen::initialize_help_screen()
{
    Color4f color;

    cache_music_file(g_main_menu_music_path, 0, g_blank_text);
    int script_index =
        ((LandscapeScriptBank*)(g_game_base + 0x106c218))
            ->load_landscape_script_by_name(g_help_script_path);
    ((Backdrop*)(g_game_base + 0x4ec10))
        ->change_backdrop(
            (LandscapeScriptRecord*)(g_game_base + 0x106c7bc +
                script_index * sizeof(LandscapeScriptRecord)),
            0);
    ((BorderRuntime*)(g_game_base + 0xb4c))->set_border_justify_centre(0);

    back_button = ((HelpBorderManager*)(g_game_base + 0xb4c))->allocate_border();
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
