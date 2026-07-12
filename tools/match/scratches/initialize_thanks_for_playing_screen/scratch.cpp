// initialize_thanks_for_playing_screen @ 0x433fd0 (thiscall)

#include "backdrop.h"
#include "border_manager.h"
#include "frontend_widget.h"
#include "landscape_manager.h"
#include "sprite.h"
#include "star_manager.h"
#include "thanks_screen.h"

extern char* g_game_base; // data_4df904
extern char g_blank_text[]; // 0x4dfb08

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

class ThanksBorderManager {
public:
    FrontendWidget* allocate_border();
};

void ThanksScreen::initialize_thanks_for_playing_screen()
{
    Color4f color;

    ((StarManager*)(g_game_base + 0x4f33c))->hide_star_field();
    cache_music_file("music/introtext.ogg", 0, g_blank_text);
    int script_index =
        ((LandscapeManager*)(g_game_base + 0x106c218))
            ->load_landscape_script_by_name("Splash.txt");
    ((Backdrop*)(g_game_base + 0x4ec10))
        ->change_backdrop(
            &((LandscapeManager*)(g_game_base + 0x106c218))
                ->scripts[script_index],
            0);
    ((BorderManager*)(g_game_base + 0xb4c))->set_border_justify_centre(0);

    message_widget = ((ThanksBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    message_widget->initialize_frontend_widget(
        0x20400002,
        "Thanks For Playing!",
        0x14,
        0.0f,
        435.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    *(float*)((char*)message_widget + 0x6f0) = 1.2f;
    message_progress = 0.0f;
    message_progress_step = 0.00416666688f;
    message_state = 0;
}
