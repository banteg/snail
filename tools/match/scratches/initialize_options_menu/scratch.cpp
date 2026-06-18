// initialize_options_menu @ 0x41ace0 (thiscall)

#include "border_manager.h"
#include "frontend_widget_virtual_layout.h"
#include "options_menu.h"

extern char* g_game_base; // data_4df904
extern float g_config_sample_volume; // 0x4df918
extern float g_config_stream_volume; // 0x4df91c
extern char g_blank_text[]; // 0x4dfb08
extern char g_sounds_volume_text[]; // 0x4a3d30
extern char g_music_volume_text[]; // 0x4a3d14
extern char g_back_text[]; // 0x4a20ec
void OptionsMenu::initialize_options_menu()
{
    Color4f color;

    ((BorderManager*)(g_game_base + 0xb4c))->hide_all_borders();
    *(g_game_base + 0x568) = 1;

    fullscreen_widget =
        (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
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
        (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
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
    sound_volume_widget->slider_value = g_config_sample_volume;
    sound_volume_widget->slider_target_value = g_config_sample_volume;
    ((FrontendWidgetVirtualLayout*)sound_volume_widget)->layout_frontend_widget();

    music_volume_widget =
        (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
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
    music_volume_widget->slider_value = g_config_stream_volume;
    music_volume_widget->slider_target_value = g_config_stream_volume;
    ((FrontendWidgetVirtualLayout*)music_volume_widget)->layout_frontend_widget();

    back_widget =
        (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
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
    previous_sample_volume = g_config_sample_volume;
}
