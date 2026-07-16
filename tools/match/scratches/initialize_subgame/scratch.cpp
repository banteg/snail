// initialize_subgame @ 0x4374b0 (thiscall)

#include <stddef.h>

#include "backdrop.h"
#include "border_manager.h"
#include "gui.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "galaxy_route_types.h"
#include "landscape_manager.h"
#include "runtime_config.h"
#include "segment_catalog_types.h"
#include "time_trial.h"
#include "times_up.h"
#include "game_time.h"
#include "transform_matrix.h"
#include "subgame_runtime.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);
extern "C" void* memset(void* destination, int value, unsigned int count);
#pragma intrinsic(memcpy)
#pragma intrinsic(memset)

extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_menu_background_script_path[]; // 0x4a347c
extern char g_blank_text[]; // 0x4dfb08
extern SubSegmentRaw* g_builtin_segment_definitions[]; // 0x4a63d0

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50
void rstrcpy_checked_ascii(char* destination, char* source); // @ 0x44e5b0
char* save_config_file(char* file_name, void* bytes, int byte_count); // @ 0x42f540
int report_errorf(char* format, ...); // @ 0x431cc0

void SubgameRuntime::initialize_subgame()
{
    int scratch[6];

    TrackRowCellFringeLinkView* cell = runtime_cell_fringe_links();
    for (int row = 0;
         row < (int)(sizeof(runtime_cells) / sizeof(runtime_cells[0]));
         ++row) {
        for (int lane = 0;
             lane < (int)(sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]));
             ++lane) {
            memset(cell, 0, offsetof(TrackRowCellFringeLinkView, next_cell));
            ++cell;
        }
    }

    int selector = subgame_rebuild_selector;
    if (selector == 2 || selector == 1) {
        cache_music_file(g_main_menu_music_path, 0, g_blank_text);
        int script_index =
            g_game->subgame.landscape_manager
                .load_landscape_script_by_name(g_menu_background_script_path);
        g_game->backdrop.change_backdrop(
                &g_game->subgame.landscape_manager.scripts[script_index],
                0);
        g_game->border_manager.set_border_justify_centre(25.0f);
    }

    int level_mode = this->level_mode;
    SubSolution* level_record;
    switch (level_mode) {
    case 0:
        level_record = &sub_high_score.postal_records[0];
        sub_high_score.active_record_bank = level_record;
        active_level_score = level_record->score;
        memcpy(&active_level_timer, &level_record->timer, sizeof(Time));
        break;
    case 1:
        level_record = &sub_high_score.survival_records[0];
        sub_high_score.active_record_bank = level_record;
        active_level_score = level_record->score;
        memcpy(&active_level_timer, &level_record->timer, sizeof(Time));
        break;
    case 4:
        level_record = &sub_high_score.time_trial_route_records[0];
        sub_high_score.active_record_bank = level_record;
        active_level_score = level_record->score;
        memcpy(&active_level_timer, &level_record->timer, sizeof(Time));
        break;
    }

    if (selected_level_record_persistent != 0)
        base_rate = selected_level_record->replay_speed_scalar;

    subgame_pause_gate = 0;
    resume_requested = 0;
    pause_fade = 0.0f;
    pause_fade_step = 0.0333333351f;
    sub_high_score.noop_runtime_ai();
    subgame_state = 0;
    times_up.state = TIMES_UP_STATE_INACTIVE;

    top_score_widget = g_game->border_manager.allocate_border();
    top_score_widget->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
        "0",
        0x14,
        400.0f,
        14.0f,
        ((tColour*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 0.0299999993f),
        3,
        300.0f);
    top_score_widget->font_scale = 1.5f;
    top_score_widget->texture_layer = 7;
    top_score_widget->text_buffer[0] = 0;

    if (this->level_mode == 0) {
        lives_icon_widget = g_game->border_manager.allocate_border();
        lives_icon_widget->initialize_frontend_sprite_button(
            FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_SPRITE_MODE,
            122,
            0.0f,
            58.0f,
            ((tColour*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0.0f,
            4);
        lives_icon_widget->hide_border_init();
        lives_icon_widget->sprite_shadow_offset = 0.0f;

        lives_text_widget = g_game->border_manager.allocate_border();
        lives_text_widget->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "0",
            0x14,
            47.0f,
            80.0f,
            ((tColour*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 0.0299999993f),
            0,
            0.0f);
        lives_text_widget->hide_border_init();
        lives_text_widget->font_scale = 0.699999988f;

        int icon_index = 0;
        FrontendWidget** icon_slot = life_stock_widgets;
        do {
            *icon_slot = g_game->border_manager.allocate_border();
            (*icon_slot)->initialize_frontend_sprite_button(
                FRONTEND_WIDGET_FLAG_FRAMELESS
                    | FRONTEND_WIDGET_FLAG_SPRITE_MODE,
                123,
                (float)icon_index * 24.0f + 13.0f,
                430.0f,
                ((tColour*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                0.0f,
                4);
            (*icon_slot)->sprite_shadow_offset = 0.0f;
            (*icon_slot)->hide_border_init();
            ++icon_index;
            ++icon_slot;
        } while (icon_index
            < (int)(sizeof(life_stock_widgets) / sizeof(life_stock_widgets[0])));
    }

    level_mode = this->level_mode;
    if (sub_high_score.current_result_record.replay_mode_id == level_mode) {
        if (level_mode == 4) {
            char* text =
                time_trial.format_time_trial_string(
                    &sub_high_score.current_result_record.timer);
            rstrcpy_checked_ascii(top_score_widget->text_buffer, text);
        } else {
            top_score_widget->border_add_text_number(
                sub_high_score.current_result_record.score);
        }
    } else {
        if (level_mode == 4) {
            ((Time*)scratch)->Zero();
            char* text =
                time_trial.format_time_trial_string(
                    (Time*)scratch);
            rstrcpy_checked_ascii(top_score_widget->text_buffer, text);
        } else {
            top_score_widget->border_add_text_number(0);
        }
    }

    bottom_score_widget = g_game->border_manager.allocate_border();
    bottom_score_widget->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
        "0",
        0x14,
        40.0f,
        14.0f,
        ((tColour*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 0.0299999993f),
        3,
        -71.0f);
    bottom_score_widget->font_scale = 1.5f;
    bottom_score_widget->texture_layer = 7;
    bottom_score_widget->text_buffer[0] = 0;

    switch (this->level_mode) {
    case 0:
        bottom_score_widget->border_add_text_number(active_level_score);
        break;
    case 1:
        bottom_score_widget->border_add_text_number(active_level_score);
        break;
    case 4: {
        char* text =
            time_trial.format_time_trial_string(&active_level_timer);
        rstrcpy_checked_ascii(bottom_score_widget->text_buffer, text);
        break;
    }
    case 2:
    case 3:
        bottom_score_widget->hide_border_init();
        top_score_widget->hide_border_init();
        break;
    default:
        break;
    }

    if (g_game->intro.hide_for_replay_latch != 0 || this->level_mode == 7) {
        bottom_score_widget->hide_border_init();
        top_score_widget->hide_border_init();
    }

    if (g_game->players[0].high_score_entry_pending != 0)
        return;

    g_game->players[0].high_score_entry_pending = 0;
    g_game->players[0].selected_high_score_rank = 0;
    level_definition_scratch.load_builtin_segment_definitions(
        g_builtin_segment_definitions);
    Player* player = embedded_player();
    player->live_transform()->set_matrix_identity();
    player->movement_mode_selector = 0;
    player->game = this;
    player->cached_camera_target_world = player->transform.position;
    player->attachment_exit_pending = 0;
    player->boost_one_tick = 0;
    player->lives = 0;
    player->list_flags &= ~0x20u;
    player->warning.initialize_warning();

    selector = subgame_rebuild_selector;
    if (selector != 0 && selector != 3) {
        if (selected_level_record_persistent == 0) {
            switch (this->level_mode) {
            case 0:
                if (selector == 1) {
                    ++level_mode_arg;
                    if (level_mode_arg > g_runtime_config.highest_galaxy_route_index) {
                        g_runtime_config.highest_galaxy_route_index = level_mode_arg;
                        save_config_file(
                            "SnailMail.cfg", &g_runtime_config, sizeof(g_runtime_config));
                    }
                    g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg;
                }
                // Native mode 0 continues into the galaxy setup path.
            case 4:
                galaxy.initialize_galaxy();
                reset_subgame();
                return;
            case 1:
                gui.initialize_challenge_setup_screen();
                reset_subgame();
                return;
            case 7:
                subgame_state = 0;
                reset_subgame();
                return;
            default:
                report_errorf("Unknown game mode");
                reset_subgame();
                return;
            }
        }
        base_rate = selected_level_record->replay_speed_scalar;
    }

    reset_subgame();
}
