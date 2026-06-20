// initialize_galaxy @ 0x408cf0 (thiscall)

#include "backdrop.h"
#include "border_runtime.h"
#include "frontend_widget.h"
#include "galaxy_route_types.h"
#include "landscape_script_bank.h"
#include "mouse_cursor_state.h"
#include "star_field.h"

extern char* g_game_base; // data_4df904
extern char g_blank_text[]; // data_4dfb08
extern char g_main_menu_music_path[]; // data_4a2128
extern char g_exit_text[]; // data_4a20f4
extern char g_back_text[]; // data_4a20ec
extern int g_landscape_backdrop_variant_selector; // data_4df9bc

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

class GalaxyBorderManager {
public:
    FrontendWidget* allocate_border();
};

FrontendWidget* GalaxyRoute::initialize_galaxy()
{
    ((StarField*)(g_game_base + 0x4f33c))->hide_star_field();
    cache_music_file(g_main_menu_music_path, 0, g_blank_text);

    int landscape_index =
        ((LandscapeScriptBank*)(g_game_base + 0x106c218))
            ->load_landscape_script_by_name("StarMap.txt");
    ((Backdrop*)(g_game_base + 0x4ec10))
        ->change_backdrop(
            (LandscapeScriptRecord*)(g_game_base + 0x106c7bc +
                landscape_index * sizeof(LandscapeScriptRecord)),
            0);

    ((BorderRuntime*)(g_game_base + 0xb4c))->set_border_justify_centre(0);
    ((MouseCursorState*)(g_game_base + 0x290))->capture_mouse_cursor();
    *(int*)(g_game_base + 0x56c) = 2;

    char* progress = level_progress_base;
    if (*(int*)(progress + 0x40) == 0) {
        int selected_mode = *(int*)(progress + 0x1270fc8);
        if (selected_mode == 3 || selected_mode == 2) {
            route_state = 0;
            route_mode = 0;
            selected_index = g_landscape_backdrop_variant_selector;
        }
        if (*(int*)(progress + 0x1270fc8) == 1) {
            route_state = 1;
            route_mode = 1;
            selected_index = *(int*)(progress + 0x44);
        }
    }
    if (*(int*)(progress + 0x40) == 4) {
        route_state = 0;
        route_mode = 2;
        selected_index = g_landscape_backdrop_variant_selector;
    }

    {
        Color4f color;
        route_title_widget = ((GalaxyBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        route_title_widget->initialize_frontend_widget(
            0x400000,
            "Intergalactic Delivery Route",
            20,
            15.0f,
            15.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
        *(int*)((char*)route_title_widget + 0x6f0) = 0x3f547ae1;

        route_icon_widget = ((GalaxyBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        route_icon_widget->initialize_frontend_sprite_button(
            0x20400802,
            138,
            370.0f,
            10.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0.0f,
            4);
    }

    exit_or_back_widget = ((GalaxyBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    if (route_mode == 1) {
        Color4f color;
        exit_or_back_widget->initialize_frontend_widget(
            0x20000014,
            g_exit_text,
            20,
            20.0f,
            420.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
    } else {
        Color4f color;
        exit_or_back_widget->initialize_frontend_widget(
            0x60000014,
            g_back_text,
            20,
            20.0f,
            420.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
    }

    int index = 0;
    if (record_count > 0) {
        int* clear_cursor = (int*)((char*)this + 0x2c);
        do {
            clear_cursor[-1] = 0;
            clear_cursor[0] = 0;
            ++index;
            clear_cursor += 168;
        } while (index < record_count);
    }

    {
        Color4f color;
        bounds_frame_widget = ((GalaxyBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        bounds_frame_widget->initialize_frontend_widget(
            0x20010002,
            g_blank_text,
            20,
            30.0f,
            80.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
        ((Color4f*)((char*)bounds_frame_widget + 0x1cc))->store_color4f(
            1.0f,
            1.0f,
            1.0f,
            1.0f);
        bounds_frame_widget->hide_border_init();
        *(int*)((char*)bounds_frame_widget + 0x48) = 152;
        *(int*)((char*)bounds_frame_widget + 0x4c) = 0x43a00000;
        *(int*)((char*)bounds_frame_widget + 0x50) = 0x43700000;
        *(int*)((char*)bounds_frame_widget + 0x54) = 0x43480000;
        *(int*)((char*)bounds_frame_widget + 0x58) = 0x42c80000;

        selected_title_widget = ((GalaxyBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        selected_title_widget->initialize_frontend_widget(
            0x20400002,
            g_blank_text,
            20,
            100.0f,
            80.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
        selected_title_widget->hide_border_init();
        *(int*)((char*)selected_title_widget + 0x6f0) = 0x3f666666;
        selected_title_widget->stack_gap = 0.0f;

        selected_detail_widget = ((GalaxyBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        selected_detail_widget->initialize_frontend_widget(
            0x20400002,
            g_blank_text,
            20,
            300.0f,
            440.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
        selected_detail_widget->hide_border_init();
        *(int*)((char*)selected_detail_widget + 0x6f0) = 0x3f666666;
        selected_detail_widget->stack_gap = 0.0f;

        selected_description_widget = ((GalaxyBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        selected_description_widget->initialize_frontend_widget(
            0x20400002,
            g_blank_text,
            20,
            300.0f,
            440.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
        selected_description_widget->hide_border_init();
        *(int*)((char*)selected_description_widget + 0x6f0) = 0x3f333333;
        selected_description_widget->stack_gap = 0.0f;
    }

    play_or_deliver_widget = ((GalaxyBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    if (*(int*)(level_progress_base + 0x40) == 0) {
        Color4f color;
        play_or_deliver_widget->initialize_frontend_widget(
            0x60000014,
            "Deliver!",
            20,
            300.0f,
            440.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            100.0f);
    } else {
        Color4f color;
        play_or_deliver_widget->initialize_frontend_widget(
            0x60000014,
            "Play",
            20,
            300.0f,
            440.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            100.0f);
    }
    play_or_deliver_widget->hide_border_init();
    play_or_deliver_widget->stack_gap = 20.0f;

    {
        Color4f color;
        replay_widget = ((GalaxyBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        replay_widget->initialize_frontend_widget(
            0x60000014,
            "Watch Best Trial",
            20,
            300.0f,
            440.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);
        replay_widget->hide_border_init();
        replay_widget->stack_gap = 10.0f;
        *(int*)((char*)replay_widget + 0x6f0) = 0x3f4ccccd;
        replay_widget->idle_padding = 4.0f;
        replay_widget->idle_padding = 8.0f;
    }

    return open_galaxy_route(selected_index);
}
