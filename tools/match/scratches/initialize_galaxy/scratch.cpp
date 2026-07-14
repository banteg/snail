// initialize_galaxy @ 0x408cf0 (thiscall)

#include "backdrop.h"
#include "border_manager.h"
#include "frontend_widget.h"
#include "galaxy_route_types.h"
#include "game_root.h"
#include "landscape_manager.h"
#include "mouse_cursor_state.h"
#include "runtime_config.h"
#include "star_manager.h"
#include "subgame_runtime.h"

extern GameRoot* g_game; // data_4df904
extern char g_blank_text[]; // data_4dfb08
extern char g_main_menu_music_path[]; // data_4a2128
extern char g_exit_text[]; // data_4a20f4
extern char g_back_text[]; // data_4a20ec

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

void Galaxy::initialize_galaxy()
{
    g_game->star_manager.hide_star_field();
    cache_music_file(g_main_menu_music_path, 0, g_blank_text);

    int landscape_index = g_game->subgame.landscape_manager
                              .load_landscape_script_by_name("StarMap.txt");
    g_game->backdrop.change_backdrop(
        &g_game->subgame.landscape_manager.scripts[landscape_index], 0);

    g_game->border_manager.set_border_justify_centre(0);
    g_game->players[0].mouse_cursor.capture_mouse_cursor();
    g_game->render_skip_countdown = 2;

    SubgameRuntime* progress = level_progress_base;
    if (progress->level_mode == 0) {
        int selected_mode = progress->subgame_rebuild_selector;
        if (selected_mode == 3 || selected_mode == 2) {
            route_state = 0;
            route_mode = 0;
            selected_index = g_runtime_config.landscape_backdrop_variant_selector;
        }
        if (progress->subgame_rebuild_selector == 1) {
            route_state = 1;
            route_mode = 1;
            selected_index = progress->level_mode_arg;
        }
    }
    if (progress->level_mode == 4) {
        route_state = 0;
        route_mode = 2;
        selected_index = g_runtime_config.landscape_backdrop_variant_selector;
    }

    {
        tColour color;
        route_title_widget = g_game->border_manager.allocate_border();
        route_title_widget->initialize_frontend_widget(
            0x400000,
            "Intergalactic Delivery Route",
            20,
            15.0f,
            15.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
        route_title_widget->font_scale = 0.83f;

        route_icon_widget = g_game->border_manager.allocate_border();
        route_icon_widget->initialize_frontend_sprite_button(
            0x20400802,
            138,
            370.0f,
            10.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0.0f,
            4);
    }

    exit_or_back_widget = g_game->border_manager.allocate_border();
    if (route_mode == 1) {
        tColour color;
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
        tColour color;
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
        int* clear_cursor = &route_slots[0].record.highlight_target_bits;
        do {
            clear_cursor[-1] = 0;
            clear_cursor[0] = 0;
            ++index;
            clear_cursor += sizeof(GalaxyRouteSlot) / sizeof(int);
        } while (index < record_count);
    }

    {
        tColour color;
        bounds_frame_widget = g_game->border_manager.allocate_border();
        bounds_frame_widget->initialize_frontend_widget(
            0x20010002,
            g_blank_text,
            20,
            30.0f,
            80.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0,
            0.0f);
        bounds_frame_widget->hot_fill_color.store_color4f(
            1.0f,
            1.0f,
            1.0f,
            1.0f);
        bounds_frame_widget->hide_border_init();
        bounds_frame_widget->border_texture_id = 152;
        bounds_frame_widget->frame_x = 320.0f;
        bounds_frame_widget->frame_y = 240.0f;
        bounds_frame_widget->frame_width = 200.0f;
        bounds_frame_widget->frame_height = 100.0f;

        selected_title_widget = g_game->border_manager.allocate_border();
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
        selected_title_widget->font_scale = 0.9f;
        selected_title_widget->stack_gap = 0.0f;

        selected_detail_widget = g_game->border_manager.allocate_border();
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
        selected_detail_widget->font_scale = 0.9f;
        selected_detail_widget->stack_gap = 0.0f;

        selected_description_widget = g_game->border_manager.allocate_border();
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
        selected_description_widget->font_scale = 0.7f;
        selected_description_widget->stack_gap = 0.0f;
    }

    play_or_deliver_widget = g_game->border_manager.allocate_border();
    if (level_progress_base->level_mode == 0) {
        tColour color;
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
        tColour color;
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
        tColour color;
        replay_widget = g_game->border_manager.allocate_border();
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
        replay_widget->font_scale = 0.8f;
        replay_widget->idle_padding = 4.0f;
        replay_widget->idle_padding = 8.0f;
    }

    open_galaxy_route(selected_index);
}
