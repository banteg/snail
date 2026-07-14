// initialize_options_menu @ 0x41ace0 (thiscall)

#include "frontend_widget_virtual_layout.h"
#include "game_root.h"
#include "options.h"
#include "runtime_config.h"

extern GameRoot* g_game; // data_4df904
extern char g_blank_text[]; // 0x4dfb08
extern char g_sounds_volume_text[]; // 0x4a3d30
extern char g_music_volume_text[]; // 0x4a3d14
extern char g_back_text[]; // 0x4a20ec
void Options::initialize_options_menu()
{
    tColour color;

    g_game->border_manager.hide_all_borders();
    g_game->frontend_link_latch = 1;

    fullscreen_widget =
        g_game->border_manager.allocate_border();
    fullscreen_widget->initialize_frontend_widget(
        0x14,
        g_blank_text,
        0x14,
        90.0f,
        75.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    fullscreen_widget->layout_anchor_y += 8.0f;

    sound_volume_widget =
        g_game->border_manager.allocate_border();
    sound_volume_widget->initialize_frontend_widget(
        0x900004,
        g_sounds_volume_text,
        0x14,
        90.0f,
        400.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    sound_volume_widget->stack_widget_below(fullscreen_widget);
    sound_volume_widget->slider_value = g_runtime_config.sample_volume;
    sound_volume_widget->slider_target_value = g_runtime_config.sample_volume;
    ((FrontendWidgetVirtualLayout*)sound_volume_widget)->layout_frontend_widget();

    music_volume_widget =
        g_game->border_manager.allocate_border();
    music_volume_widget->initialize_frontend_widget(
        0x100004,
        g_music_volume_text,
        0x14,
        90.0f,
        400.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    music_volume_widget->stack_widget_below(sound_volume_widget);
    music_volume_widget->slider_value = g_runtime_config.stream_volume;
    music_volume_widget->slider_target_value = g_runtime_config.stream_volume;
    ((FrontendWidgetVirtualLayout*)music_volume_widget)->layout_frontend_widget();

    back_widget =
        g_game->border_manager.allocate_border();
    back_widget->initialize_frontend_widget(
        0x14,
        g_back_text,
        0x14,
        90.0f,
        400.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    back_widget->stack_widget_below(music_volume_widget);
    previous_sample_volume = g_runtime_config.sample_volume;
}
