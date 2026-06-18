// update_options_menu @ 0x41af60 (thiscall)

#include "audio_system.h"
#include "completion_screen.h"
#include "options_menu.h"

extern char* g_game_base; // data_4df904
extern float g_config_sample_volume; // 0x4df918
extern float g_config_stream_volume; // 0x4df91c
extern char g_config_fullscreen_enabled; // 0x4df920
extern char g_fullscreen_on_text[]; // 0x4a3d5c
extern char g_fullscreen_off_text[]; // 0x4a3d4c

void rstrcpy_checked_ascii(char* destination, char* source);
void set_fullscreen_mode(int enabled);

void OptionsMenu::update_options_menu()
{
    g_config_stream_volume = music_volume_widget->slider_value;
    g_config_sample_volume = sound_volume_widget->slider_value;

    if (g_config_fullscreen_enabled != 0)
        rstrcpy_checked_ascii(fullscreen_widget->text_buffer, g_fullscreen_on_text);
    else
        rstrcpy_checked_ascii(fullscreen_widget->text_buffer, g_fullscreen_off_text);

    unsigned int flags = fullscreen_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        fullscreen_widget->widget_flags = flags & ~0x20u;
        if (g_config_fullscreen_enabled != 0) {
            set_fullscreen_mode(0);
            g_config_fullscreen_enabled = 0;
        } else {
            set_fullscreen_mode(1);
            g_config_fullscreen_enabled = 1;
        }
    }

    flags = sound_volume_widget->widget_flags;
    if ((flags & 0x20) != 0)
        sound_volume_widget->widget_flags = flags & ~0x20u;

    flags = back_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        back_widget->widget_flags = flags & ~0x20u;
        destroy_options_menu();
        CompletionGameView* game = (CompletionGameView*)g_game_base;
        game->frontend_link_latch = 0;
        game = (CompletionGameView*)g_game_base;
        game->frontend_next_state = previous_frontend_state;
    }

    apply_audio_config_volumes();
    if (previous_sample_volume != g_config_sample_volume) {
        g_sound_effect_manager.play_sound_effect(8);
        previous_sample_volume = g_config_sample_volume;
    }
}
