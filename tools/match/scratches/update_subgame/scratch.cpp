// update_subgame @ 0x438b90 (thiscall, ret)

#include <stddef.h>

#include "bod_list.h"
#include "bod_ai_dispatch.h"
#include "fringe_object.h"
#include "sub_solution.h"
#include "new_game_menu.h"
#include "player.h"
#include "runtime_config.h"
#include "salt_hazard_types.h"
#include "slug_voice_manager.h"
#include "sprite.h"
#include "star_manager.h"
#include "subgame_runtime.h"
#include "time_trial.h"
#include "game_time.h"
#include "game_root.h"
#include "main_loop_state.h"
#include "track_attachment_types.h"
#include "track_parcel_runtime.h"
#include "segment_cache.h"
#include "vector3.h"

struct RuntimeCellSlotBase {
    char before_cell[offsetof(SubgameRuntime, runtime_cells)];
    TrackRowCell cell;
};

extern GameRoot* g_game; // data_4df904

float random_float_below(float upper_bound, const char* tag);
int queue_axis_aligned_textured_quad_uv(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int flags,
    Color4f* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int layer,
    int blend);
void rstrcpy_checked_ascii(char* destination, char* source);
int report_errorf(char* format, ...);

void SubgameRuntime::update_subgame()
{
    char* game = (char*)this;
    int cell_index;
    int attachment_count;
    Color4f replay_color;
    Color4f replay_color_alt;
    Color4f skirt_color;

    calc_subgame_rate();
    int one = 1;

    switch (subgame_state) {
    case 3:
        subgame_state = 4;
        subgame_pause_gate = (unsigned char)one;
        pause_fade = pause_fade_step;
        pause_menu.initialize_pause_menu();
        // Native fallthrough: initialization immediately receives one update.
    case 4:
        pause_menu.update_pause_menu();
        return;

    case 7:
        if (selected_level_record_persistent == one) {
            selected_level_record_active = (unsigned char)one;
            build_subgame_level(0);
            subgame_state = 2;
            g_game->render_skip_count = one;
            return;
        }
        selected_level_record_active = 0;
        build_subgame_level(0);
        subgame_state = 2;
        g_game->render_skip_count = one;
        return;

    case 0: {
        int selector = subgame_rebuild_selector;
        subgame_state = one;
        if (selector == one)
            break;
        if (selector == 0 || selector == 3)
            goto build_selected_level;

        if (selected_level_record_persistent == one) {
            selected_level_record_active = (unsigned char)one;
            build_subgame_level(selected_level_record->replay_level_index);
            return;
        }

        selected_level_record_active = 0;
        g_game->star_manager.hide_star_field();
    }
        // Fresh state-zero setup enters the same front-end dispatch as state one.
    case 1: {
        random_float_below(1.0f, 0);
        completion_bonus_x_source = g_runtime_config.completion_bonus_y_source;
        completion_bonus_y_source = g_runtime_config.completion_bonus_x_source;

        int result;
        switch (level_mode) {
        case 0:
            result = galaxy.update_galaxy();
            if (result == one) {
                subgame_rebuild_selector = 3;
                g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg;
                build_subgame_level(level_mode_arg);
                return;
            }
            if (result == 2) {
                subgame_rebuild_selector = one;
                g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg;
                build_subgame_level(level_mode_arg);
                return;
            }
            if (result != 3)
                break;
            destroy_subgame();
            g_game->players[0].frontend_state = 2;
            return;

        case 4:
            result = galaxy.update_galaxy();
            if (result == one) {
                subgame_rebuild_selector = 2;
                g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg;
                goto build_selected_level;
            }
            if (result != 3)
                break;
            destroy_subgame();
            g_game->players[0].frontend_state = 2;
            return;

        case 1:
            result = gui.update_challenge_setup_screen();
            if (result == one) {
                subgame_rebuild_selector = 2;
                build_subgame_level(0);
                return;
            }
            if (result != 3)
                break;
            destroy_subgame();
            g_game->players[0].frontend_state = 2;
            return;

        case 7:
            subgame_rebuild_selector = 2;
            build_subgame_level(0);
            return;
        }
        break;
    }

    case 2: {
        int zero = 0;
        int three = 3;
        if (selected_level_record_active == one
            && g_game->intro.hide_for_replay_latch == zero) {
            if (level_mode == three) {
                queue_axis_aligned_textured_quad_uv(
                    27, 580.0f, 6.0f, 64.0f, 64.0f, 0x1000000,
                    replay_color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.400000006f),
                    0.0f, 0.0f, 1.0f, 1.0f, 1, 0);
            } else {
                queue_axis_aligned_textured_quad_uv(
                    27, 288.0f, 10.0f, 64.0f, 64.0f, 0x1000000,
                    replay_color_alt.set_color_rgba(1.0f, 1.0f, 1.0f, 0.400000006f),
                    0.0f, 0.0f, 1.0f, 1.0f, 1, 0);
            }
        }

        int two = 2;
        if (player.completion_handoff_active == zero
            && player.click_start.state != two)
            player.stopwatch.Add(1.0f);

        if (level_mode == 7)
            tutorial.update_tutorial();

        slug_voice_manager.update_slug_voice_manager();

        if (resume_requested == one) {
            subgame_pause_gate = (unsigned char)zero;
            resume_requested = (unsigned char)zero;
            g_sprite_manager.set_sprite_manager_paused(0);
        }

        GameRoot* app = g_game;
        if (!((selected_level_record_active != zero
                && pause_fade == 0.0f
                && (player.control_source->control_flags_a & 0x4000) != 0)
            || app->intro.hide_for_replay_latch != zero)) {

        if ((read_pressed_text_input_key_code() == 11 || g_window_deactivated == one)
            && g_game->fade.state == zero) {
            *(unsigned char*)(game + offsetof(SubgameRuntime, subgame_pause_gate)) = one;
            subgame_state = three;
            g_sprite_manager.set_sprite_manager_paused((char)one);
            if (player.click_start.state == two)
                player.click_start.prompt->hide_border_init();
            return;
        }

        if (pause_fade > 0.0f) {
            float fade = pause_fade_step + pause_fade;
            pause_fade = fade;
            if (fade > 1.0f)
                pause_fade = 0.0f;
            if (player.click_start.state == two)
                player.click_start.prompt->unhide_border_init();
        }

        if (scan_reset != zero) {
            runtime_row_scan_begin = zero;
            if (level_mode == two)
                runtime_row_scan_end = runtime_row_count;
            else
                runtime_row_scan_end = (int)player.interaction_max_z + 46;
        } else {
            int old_end = runtime_row_scan_end;
            runtime_row_scan_begin = old_end;
            if (level_mode == two) {
                runtime_row_scan_end = runtime_row_count;
            } else {
                int new_end = (int)player.interaction_max_z + 46;
                if (new_end > old_end)
                    runtime_row_scan_end = new_end;
            }
        }

        int scan_limit = completion_row_start + 20;
        if (runtime_row_scan_end > scan_limit)
            runtime_row_scan_end = scan_limit;

        cell_index = runtime_row_scan_begin;
        while (cell_index < runtime_row_scan_end) {
            if ((runtime_rows[cell_index].flags & 2) != zero) {
                BodNode* row_node = &runtime_rows[cell_index].row_model;
                if ((row_node->list_flags & 0x200) != zero) {
                    report_errorf("List ADD");
                } else {
                    BodNode** first_ref =
                        &g_game->active_bod_list.first;
                    BodNode* first = *first_ref;
                    if (first == 0) {
                        *first_ref = row_node;
                        row_node->list_prev = 0;
                        (*first_ref)->list_next = 0;
                    } else {
                        first->list_prev = row_node;
                        (*first_ref)->list_prev->list_next = *first_ref;
                        BodNode* new_first = (*first_ref)->list_prev;
                        *first_ref = new_first;
                        new_first->list_prev = 0;
                    }
                    row_node->list_flags |= 0x200;
                }
            }

            if ((runtime_rows[cell_index].flags & 0x10) != zero
                && (runtime_flags & 0x800000) != zero)
                spawn_track_parcel(
                    &runtime_rows[cell_index].projection_payload,
                    &player);

            attachment_count = zero;
            while (attachment_count < 8) {
                if (cell_index >= zero && cell_index < runtime_row_count) {
                    RuntimeCellSlotBase* cell_slot =
                        (RuntimeCellSlotBase*)(game
                            + sizeof(TrackRowCell) * (attachment_count + 8 * cell_index));
                    if ((cell_slot->cell.list_flags & 0x200) == zero) {
                        if ((cell_slot->cell.lane_and_flags & 0x4000) != zero) {
                            unsigned char tile = cell_slot->cell.tile_id;
                            if (tile == 29 || tile == 30) {
                                if (cell_slot->cell.object != 0) {
                                BodNode* node = &cell_slot->cell;
                                BodNode* active_list = &special_track_cell_list_head;
                                if ((node->list_flags & 0x200) != zero) {
                                    report_errorf("List ADDafter");
                                } else {
                                    node->list_prev = active_list;
                                    node->list_next = active_list->list_next;
                                    active_list->list_next = node;
                                    if (node->list_next != 0)
                                        node->list_next->list_prev = node;
                                    node->list_flags |= 0x200;
                                }

                                cell_slot->cell.render_arg_20 =
                                    (float)(cell_index % 8) * 0.125f;
                                node = &runtime_rows[cell_index].attachment_body;
                                active_list = &fringe_attachment_list_head;
                                if ((node->list_flags & 0x200) != zero) {
                                    report_errorf("List ADDafter");
                                } else {
                                    node->list_prev = active_list;
                                    node->list_next = active_list->list_next;
                                    active_list->list_next = node;
                                    if (node->list_next != 0)
                                        node->list_next->list_prev = node;
                                    node->list_flags |= 0x200;
                                }
                                runtime_rows[cell_index].attachment_body.position = cell_slot->cell.position;
                                }
                            } else {
                                BodNode* node = &cell_slot->cell;
                                BodNode* active_list = &track_body_list_head;
                                if ((node->list_flags & 0x200) != zero) {
                                    report_errorf("List ADDafter");
                                } else {
                                    node->list_prev = active_list;
                                    node->list_next = active_list->list_next;
                                    active_list->list_next = node;
                                    if (node->list_next != 0)
                                        node->list_next->list_prev = node;
                                    node->list_flags |= 0x200;
                                }
                            }
                            ((BodAiDispatch*)&cell_slot->cell)->update_bod_ai();
                        }

                        Fringe** fringe = &cell_slot->cell.fringe_front;
                        int fringe_count = 4;
                        do {
                            Fringe* object = *fringe;
                            if (object != 0) {
                                BodNode* node = (BodNode*)object;
                                BodNode* active_list = &fringe_attachment_list_head;
                                if ((node->list_flags & 0x200) != zero) {
                                    report_errorf("List ADDafter");
                                } else {
                                    node->list_prev = active_list;
                                    node->list_next = active_list->list_next;
                                    active_list->list_next = node;
                                    if (node->list_next != 0)
                                        node->list_next->list_prev = node;
                                    node->list_flags |= 0x200;
                                }
                                Color4f* color =
                                    g_game->subgame.get_track_skirt_color(&skirt_color);
                                (*fringe)->color = *color;
                            }
                            ++fringe;
                            --fringe_count;
                        } while (fringe_count != zero);

                        if (cell_slot->cell.tile_id == 23
                            && (runtime_flags & 0x800) != zero
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start)
                            spawn_track_health_pickup(&cell_slot->cell, &player);

                        if (cell_slot->cell.tile_id == 24
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start)
                            spawn_track_speedup(&cell_slot->cell, &player);

                        if (cell_slot->cell.tile_id == 25
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start)
                            spawn_track_jetpack_pickup(&cell_slot->cell, &player);

                        unsigned char hazard_tile = cell_slot->cell.tile_id;
                        if (hazard_tile == 33) {
                            spawn_track_garbage_hazard(
                                &cell_slot->cell, &player);
                        } else if ((cell_slot->cell.lane_and_flags & 0x10) == 0
                                && (hazard_tile == 1 || hazard_tile == 21)
                                && (runtime_flags & 2) != 0
                                && random_float_below(1.0f, "G")
                                    > (1.0f - garbage_frequency) * 0.2f
                                        + 0.8f
                                && (attachment_count == 0
                                    || (&cell_slot->cell)[-1].tile_id == 1
                                    || (&cell_slot->cell)[-1].tile_id == 20
                                    || (&cell_slot->cell)[-1].tile_id == 21
                                    || (&cell_slot->cell)[-1].tile_id == 32)
                                && (attachment_count == 7
                                    || (&cell_slot->cell)[1].tile_id == 1
                                    || (&cell_slot->cell)[1].tile_id == 20
                                    || (&cell_slot->cell)[1].tile_id == 21
                                    || (&cell_slot->cell)[1].tile_id == 32)
                                && cell_index >= first_block_row_count
                                && cell_index < completion_row_start
                                && player.click_start.state != 2
                                && (level_mode != 4
                                    || random_float_below(1.0f, "G2")
                                        <= base_subgame_rate * 0.3f + 0.7f)
                                && (level_mode != 0
                                    || random_float_below(1.0f, "G3")
                                        <= base_subgame_rate * 0.6f + 0.4f)) {
                            spawn_track_garbage_hazard(
                                &cell_slot->cell, &player);
                        }

                        hazard_tile = cell_slot->cell.tile_id;
                        if (hazard_tile == 34) {
                            if (cell_index >= first_block_row_count
                                && cell_index < completion_row_start) {
                                salt_hazards.spawn_salt_hazard(
                                    &cell_slot->cell.position);
                            }
                        } else if ((cell_slot->cell.lane_and_flags & 8) == 0
                            && (hazard_tile == 1 || hazard_tile == 15)
                            && player.click_start.state != 2
                            && (runtime_flags & 0x10000) != 0
                            && random_float_below(1.0f, "S")
                                > (1.0f - salt_frequency) * 0.02f
                                    + 0.98f
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start) {
                            salt_hazards.spawn_salt_hazard(
                                &cell_slot->cell.position);
                        }

                        if ((runtime_flags & 0x80) != 0
                            && cell_slot->cell.tile_id == 18
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start) {
                            spawn_slug_hazard(&cell_slot->cell, &player);
                        }

                        unsigned int ring_flags = runtime_rows[cell_index].flags;
                        if ((ring_flags & 0x200) == 0) {
                            if (cell_slot->cell.tile_id == 35) {
                                if ((ring_flags & 0x400) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 5, &player,
                                        runtime_rows[cell_index].ring_speed);
                                } else if ((ring_flags & 0x2000) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 8, &player,
                                        runtime_rows[cell_index].ring_speed);
                                } else if ((ring_flags & 0x800) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 6, &player,
                                        runtime_rows[cell_index].ring_speed);
                                } else if ((ring_flags & 0x1000) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 7, &player,
                                        runtime_rows[cell_index].ring_speed);
                                } else {
                                    goto after_authored_ring;
                                }
                                player.last_ring_spawn_z =
                                    cell_slot->cell.position.z;
after_authored_ring:
                                ;
                            } else if ((cell_slot->cell.tile_id == 2 || cell_slot->cell.tile_id == 3
                                    || cell_slot->cell.tile_id == 4 || cell_slot->cell.tile_id == 5
                                    || cell_slot->cell.tile_id == 6 || cell_slot->cell.tile_id == 7)
                                && player.last_ring_spawn_z + 10.0f
                                    < cell_slot->cell.position.z
                                && cell_index < completion_row_start) {
                                if ((ring_flags & 0x2000) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &(&cell_slot->cell)[6 * 8],
                                        8, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        (&cell_slot->cell)[6 * 8].position.z;
                                } else if ((ring_flags & 0x800) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &(&cell_slot->cell)[6 * 8],
                                        6, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        (&cell_slot->cell)[6 * 8].position.z;
                                } else if ((ring_flags & 0x1000) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &(&cell_slot->cell)[6 * 8],
                                        7, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        (&cell_slot->cell)[6 * 8].position.z;
                                } else if ((runtime_flags & 8) != 0
                                    && (random_float_below(1.0f, "R") > 0.7f
                                        || level_mode == 7)
                                    && cell_slot->cell.tile_id != 5 && cell_slot->cell.tile_id != 6
                                    && cell_slot->cell.tile_id != 7) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 4, &player, 0.0f);
                                    if (player.lives < 10)
                                        player.last_ring_spawn_z =
                                            cell_slot->cell.position.z;
                                    else
                                        player.last_ring_spawn_z =
                                            cell_slot->cell.position.z + 35.0f;
                                }
                            } else if ((cell_slot->cell.tile_id == 8 || cell_slot->cell.tile_id == 9
                                    || cell_slot->cell.tile_id == 10)
                                && player.last_ring_spawn_z + 10.0f
                                    < cell_slot->cell.position.z
                                && cell_index < completion_row_start) {
                                if ((ring_flags & 0x800) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 2, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z = cell_slot->cell.position.z;
                                } else if (random_float_below(1.0f, "R2") > 0.7f
                                    || level_mode == 7
                                    || ((runtime_rows[cell_index].flags & 0x800) != 0)) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 2, &player, 0.0f);
                                    player.last_ring_spawn_z = cell_slot->cell.position.z;
                                }
                            }
                        }
                    }
                }
                ++attachment_count;
            }
            ++cell_index;
            scan_reset = (unsigned char)zero;
        }

        segment_cache.update_track_render_cache_rows();

        if (level_mode == 4) {
            char* text = time_trial.format_time_trial_string(&player.stopwatch);
            rstrcpy_checked_ascii(top_score_widget->text_buffer, text);
            if (sub_high_score.time_trial_route_records[level_mode_arg].active
                == one) {
                text = time_trial.format_time_trial_string(
                    &sub_high_score.time_trial_route_records[level_mode_arg].timer);
                rstrcpy_checked_ascii(bottom_score_widget->text_buffer, text);
                break;
            }
            bottom_score_widget->hide_border_init();
            update_subgame_camera();
            return;
        }

        top_score_widget->text_buffer[0] = (char)zero;
        top_score_widget->border_add_text_number(player.total_score);
        if (player.total_score > active_level_score) {
            active_level_score = player.total_score;
            bottom_score_widget->text_buffer[0] = (char)zero;
            bottom_score_widget->border_add_text_number(active_level_score);
            update_subgame_camera();
            return;
        }
        break;
        } else {
            if (selected_level_record_persistent != zero) {
                app->players[0].saved_frontend_state =
                    app->players[0].frontend_state;
                g_game->players[0].frontend_state = 0x1a;
            } else {
                app->players[0].saved_frontend_state =
                    app->players[0].frontend_state;
                g_game->players[0].frontend_state = 0x1b;
            }
            if (g_game->intro.attract_reset_progress <= 1.0f)
                g_game->intro.hide_for_replay_latch = zero;
            return;
        }
    }
    }

    update_subgame_camera();
    return;

build_selected_level:
    build_subgame_level(level_mode_arg);
}
