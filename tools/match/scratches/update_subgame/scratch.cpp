// update_subgame @ 0x438b90 (thiscall, ret)

#include <stddef.h>

#include "bod_list.h"
#include "bod_ai_dispatch.h"
#include "fringe_object.h"
#include "sub_solution.h"
#include "new_game_menu.h"
#include "player.h"
#include "rmath_random.h"
#include "rstring.h"
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


int OSDPrintUV(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    int flags,
    tColour* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int blend_mode,
    float rotation);
int report_errorf(char* format, ...);

void cRSubGame::AI()
{
    int cell_index;
    int attachment_count;
    tColour replay_color;
    tColour replay_color_alt;
    tColour skirt_color;

    CalcRate();

    switch (subgame_state) {
    case 3:
        subgame_state = 4;
        subgame_pause_gate = (unsigned char)1;
        pause_fade = pause_fade_step;
        sub_pause.Init();
        // Native fallthrough: initialization immediately receives one update.
    case 4:
        sub_pause.AI();
        return;

    case 7:
        if (selected_level_record_persistent == 1) {
            selected_level_record_active = (unsigned char)1;
            StartLevel(0);
            subgame_state = 2;
            g_game->render_skip_count = 1;
            return;
        }
        selected_level_record_active = 0;
        StartLevel(0);
        subgame_state = 2;
        g_game->render_skip_count = 1;
        return;

    case 0: {
        int selector = subgame_rebuild_selector;
        subgame_state = 1;
        if (selector == 1)
            break;
        if (selector == 0 || selector == 3)
            goto build_selected_level;

        if (selected_level_record_persistent == 1) {
            selected_level_record_active = (unsigned char)1;
            StartLevel(selected_level_record->replay_level_index);
            return;
        }

        selected_level_record_active = 0;
        g_game->star_manager.Hide();
    }
        // Fresh state-zero setup enters the same front-end dispatch as state one.
    case 1: {
        RAND(1.0f, 0);
        int challenge_speed = g_runtime_config.challenge_speed_percent;
        int challenge_difficulty =
            g_runtime_config.challenge_difficulty_percent;
        challenge_speed_value = challenge_speed;
        challenge_difficulty_value = challenge_difficulty;

        int result;
        switch (level_mode) {
        case 0:
            result = galaxy.AI();
            if (result == 1) {
                subgame_rebuild_selector = 3;
                g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg;
                StartLevel(level_mode_arg);
                return;
            }
            if (result == 2) {
                subgame_rebuild_selector = 1;
                g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg;
                StartLevel(level_mode_arg);
                return;
            }
            if (result != 3)
                break;
            UnInit();
            g_game->players[0].frontend_state = 2;
            return;

        case 4:
            result = galaxy.AI();
            if (result == 1) {
                subgame_rebuild_selector = 2;
                g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg;
                goto build_selected_level;
            }
            if (result != 3)
                break;
            UnInit();
            g_game->players[0].frontend_state = 2;
            return;

        case 1:
            result = gui.AI();
            if (result == 1) {
                subgame_rebuild_selector = 2;
                StartLevel(0);
                return;
            }
            if (result != 3)
                break;
            UnInit();
            g_game->players[0].frontend_state = 2;
            return;

        case 7:
            subgame_rebuild_selector = 2;
            StartLevel(0);
            return;
        }
        break;
    }

    case 2: {
        if (selected_level_record_active == 1
            && g_game->intro.hide_for_replay_latch == 0) {
            if (level_mode == 3) {
                OSDPrintUV(
                    27, 580.0f, 6.0f, 64.0f, 64.0f, 0x1000000,
                    replay_color.Set(1.0f, 1.0f, 1.0f, 0.400000006f),
                    0.0f, 0.0f, 1.0f, 1.0f, 1, 0);
            } else {
                OSDPrintUV(
                    27, 288.0f, 10.0f, 64.0f, 64.0f, 0x1000000,
                    replay_color_alt.Set(1.0f, 1.0f, 1.0f, 0.400000006f),
                    0.0f, 0.0f, 1.0f, 1.0f, 1, 0);
            }
        }

        if (player.completion_handoff_active == 0
            && player.click_start.state != CLICK_START_STATE_WAITING_FOR_START)
            player.stopwatch.Add(1.0f);

        if (level_mode == 7)
            tutorial.AI();

        slug_voice_manager.AI();

        if (resume_requested == 1) {
            subgame_pause_gate = (unsigned char)0;
            resume_requested = (unsigned char)0;
            g_sprite_manager.Pause(0);
        }

        GameRoot* app = g_game;
        if (!((selected_level_record_active != 0
                && pause_fade == 0.0f
                && (player.control_source->control_flags_a
                        & INPUT_BUTTON_PRIMARY)
                    != 0)
            || app->intro.hide_for_replay_latch != 0)) {

        if ((read_pressed_text_input_key_code() == 11 || g_window_deactivated == 1)
            && g_game->fade.state == 0) {
            subgame_pause_gate = (unsigned char)1;
            subgame_state = 3;
            g_sprite_manager.Pause((char)1);
            if (player.click_start.state == CLICK_START_STATE_WAITING_FOR_START)
                player.click_start.prompt->HideInit();
            return;
        }

        if (pause_fade > 0.0f) {
            float fade = pause_fade_step + pause_fade;
            pause_fade = fade;
            if (fade > 1.0f)
                pause_fade = 0.0f;
            if (player.click_start.state == CLICK_START_STATE_WAITING_FOR_START)
                player.click_start.prompt->UnHideInit();
        }

        if (scan_reset != 0) {
            runtime_row_scan_begin = 0;
            if (level_mode == 2)
                runtime_row_scan_end = runtime_row_count;
            else
                runtime_row_scan_end = (int)player.active_window_min_z + 46;
        } else {
            int old_end = runtime_row_scan_end;
            runtime_row_scan_begin = old_end;
            if (level_mode == 2) {
                runtime_row_scan_end = runtime_row_count;
            } else {
                int new_end = (int)player.active_window_min_z + 46;
                if (new_end > old_end)
                    runtime_row_scan_end = new_end;
            }
        }

        int scan_limit = completion_row_start + 20;
        if (runtime_row_scan_end > scan_limit)
            runtime_row_scan_end = scan_limit;

        cell_index = runtime_row_scan_begin;
        while (cell_index < runtime_row_scan_end) {
            if ((runtime_rows[cell_index].flags
                    & SUBROW_FLAG_ROW_MODEL_PRESENT)
                != 0) {
                BodNode* row_node = &runtime_rows[cell_index].row_model;
                g_game->active_bod_list.add_bod(row_node);
            }

            if ((runtime_rows[cell_index].flags
                    & SUBROW_FLAG_PARCEL_SPAWN_REQUESTED)
                != 0
                && (runtime_flags & SUBGAME_RUNTIME_FLAG_PARCEL_SPAWNS) != 0)
                AddParcel(
                    &runtime_rows[cell_index].parcel_spawn_position,
                    &player);

            attachment_count = 0;
            while (attachment_count < SUBGAME_TRACK_LANE_COUNT) {
                if (cell_index >= 0 && cell_index < runtime_row_count) {
                    if ((runtime_cells[cell_index][attachment_count].list_flags & BOD_FLAG_LINKED) == 0) {
                        if ((runtime_cells[cell_index][attachment_count].lane_and_flags
                                & SUBLOC_FLAG_UNCACHED_BODY)
                            != 0) {
                            unsigned char tile = runtime_cells[cell_index][attachment_count].tile_id;
                            if (tile == 29 || tile == 30) {
                                if (runtime_cells[cell_index][attachment_count].object != 0) {
                                BodNode* node = &runtime_cells[cell_index][attachment_count];
                                BodNode* active_list = &special_track_cell_list_head;
                                node->add_bod_after(active_list);

                                runtime_cells[cell_index][attachment_count].render_arg_20 =
                                    (float)(cell_index % SUBGAME_TRACK_LANE_COUNT)
                                    * 0.125f;
                                node = &runtime_rows[cell_index].attachment_body;
                                active_list = &fringe_attachment_list_head;
                                node->add_bod_after(active_list);
                                runtime_rows[cell_index].attachment_body.position = runtime_cells[cell_index][attachment_count].position;
                                }
                            } else {
                                BodNode* node = &runtime_cells[cell_index][attachment_count];
                                BodNode* active_list = &track_body_list_head;
                                node->add_bod_after(active_list);
                            }
                            ((BodAiDispatch*)&runtime_cells[cell_index][attachment_count])->update_bod_ai();
                        }

                        Fringe** fringe = runtime_cells[cell_index][attachment_count].fringes;
                        int fringe_count = (int)(sizeof(runtime_cells[cell_index][attachment_count].fringes)
                            / sizeof(runtime_cells[cell_index][attachment_count].fringes[0]));
                        do {
                            Fringe* object = *fringe;
                            if (object != 0) {
                                BodNode* node = (BodNode*)object;
                                BodNode* active_list = &fringe_attachment_list_head;
                                node->add_bod_after(active_list);
                                tColour* color =
                                    g_game->subgame.GetSkirtColour(&skirt_color);
                                (*fringe)->color = *color;
                            }
                            ++fringe;
                            --fringe_count;
                        } while (fringe_count != 0);

                        if (runtime_cells[cell_index][attachment_count].tile_id == SUBLOC_TILE_HEALTH_PICKUP
                            && (runtime_flags & SUBGAME_RUNTIME_FLAG_HEALTH_PICKUPS)
                                != 0
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start)
                            AddHealth(&runtime_cells[cell_index][attachment_count], &player);

                        if (runtime_cells[cell_index][attachment_count].tile_id == SUBLOC_TILE_SPEEDUP_PICKUP
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start)
                            AddSpeedUp(&runtime_cells[cell_index][attachment_count], &player);

                        if (runtime_cells[cell_index][attachment_count].tile_id == SUBLOC_TILE_JETPACK_PICKUP
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start)
                            AddJetPack(&runtime_cells[cell_index][attachment_count], &player);

                        unsigned char hazard_tile = runtime_cells[cell_index][attachment_count].tile_id;
                        if (hazard_tile == SUBLOC_TILE_GARBAGE_HAZARD) {
                            AddGarbage(
                                &runtime_cells[cell_index][attachment_count], &player);
                        } else if ((runtime_cells[cell_index][attachment_count].lane_and_flags
                                        & SUBLOC_FLAG_SUPPRESS_GARBAGE_SPAWN)
                                == 0
                                && (hazard_tile == SUBLOC_TILE_FLOOR_DOT
                                    || hazard_tile == SUBLOC_TILE_FLOOR_DASH)
                                && (runtime_flags
                                        & SUBGAME_RUNTIME_FLAG_AMBIENT_GARBAGE)
                                    != 0
                                && RAND(1.0f, "G")
                                    > (1.0f - garbage_frequency) * 0.2f
                                        + 0.8f
                                && (attachment_count == 0
                                    || (&runtime_cells[cell_index][attachment_count])[-1].tile_id
                                        == SUBLOC_TILE_FLOOR_DOT
                                    || (&runtime_cells[cell_index][attachment_count])[-1].tile_id
                                        == SUBLOC_TILE_FLOOR_VARIANT_14
                                    || (&runtime_cells[cell_index][attachment_count])[-1].tile_id
                                        == SUBLOC_TILE_FLOOR_DASH
                                    || (&runtime_cells[cell_index][attachment_count])[-1].tile_id
                                        == SUBLOC_TILE_FLOOR_HASH_MARKER)
                                && (attachment_count == SUBGAME_TRACK_LANE_COUNT - 1
                                    || (&runtime_cells[cell_index][attachment_count])[1].tile_id
                                        == SUBLOC_TILE_FLOOR_DOT
                                    || (&runtime_cells[cell_index][attachment_count])[1].tile_id
                                        == SUBLOC_TILE_FLOOR_VARIANT_14
                                    || (&runtime_cells[cell_index][attachment_count])[1].tile_id
                                        == SUBLOC_TILE_FLOOR_DASH
                                    || (&runtime_cells[cell_index][attachment_count])[1].tile_id
                                        == SUBLOC_TILE_FLOOR_HASH_MARKER)
                                && cell_index >= first_block_row_count
                                && cell_index < completion_row_start
                                && player.click_start.state
                                    != CLICK_START_STATE_WAITING_FOR_START
                                && (level_mode != 4
                                    || RAND(1.0f, "G2")
                                        <= base_subgame_rate * 0.3f + 0.7f)
                                && (level_mode != 0
                                    || RAND(1.0f, "G3")
                                        <= base_subgame_rate * 0.6f + 0.4f)) {
                            AddGarbage(
                                &runtime_cells[cell_index][attachment_count], &player);
                        }

                        hazard_tile = runtime_cells[cell_index][attachment_count].tile_id;
                        if (hazard_tile == SUBLOC_TILE_SALT_HAZARD) {
                            if (cell_index >= first_block_row_count
                                && cell_index < completion_row_start) {
                                salt_hazards.Add(runtime_cells[cell_index][attachment_count].position);
                            }
                        } else if ((runtime_cells[cell_index][attachment_count].lane_and_flags
                                        & SUBLOC_FLAG_SUPPRESS_SALT_SPAWN)
                                == 0
                            && (hazard_tile == SUBLOC_TILE_FLOOR_DOT
                                || hazard_tile == SUBLOC_TILE_SLIDE_UNDERSCORE)
                            && player.click_start.state
                                != CLICK_START_STATE_WAITING_FOR_START
                            && (runtime_flags & SUBGAME_RUNTIME_FLAG_AMBIENT_SALT)
                                != 0
                            && RAND(1.0f, "S")
                                > (1.0f - salt_frequency) * 0.02f
                                    + 0.98f
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start) {
                            salt_hazards.Add(runtime_cells[cell_index][attachment_count].position);
                        }

                        if ((runtime_flags & SUBGAME_RUNTIME_FLAG_SLUG_HAZARDS) != 0
                            && runtime_cells[cell_index][attachment_count].tile_id == SUBLOC_TILE_SLUG_HAZARD
                            && cell_index >= first_block_row_count
                            && cell_index < completion_row_start) {
                            AddSlug(&runtime_cells[cell_index][attachment_count], &player);
                        }

                        unsigned int ring_flags = runtime_rows[cell_index].flags;
                        if ((ring_flags & SUBROW_FLAG_RING_NONE) == 0) {
                            if (runtime_cells[cell_index][attachment_count].tile_id == SUBLOC_TILE_RING_MARKER) {
                                if ((ring_flags & SUBROW_FLAG_RING_NORMAL) != 0) {
                                    AddRing(
                                        &runtime_cells[cell_index][attachment_count], SUB_RING_KIND_NORMAL_AUTHORED, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        runtime_cells[cell_index][attachment_count].position.z;
                                } else if ((ring_flags & SUBROW_FLAG_RING_POWER_UP) != 0) {
                                    AddRing(
                                        &runtime_cells[cell_index][attachment_count], SUB_RING_KIND_POWER_UP_AUTHORED, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        runtime_cells[cell_index][attachment_count].position.z;
                                } else if ((ring_flags & SUBROW_FLAG_RING_EXPLODE) != 0) {
                                    AddRing(
                                        &runtime_cells[cell_index][attachment_count], SUB_RING_KIND_EXPLODE_AUTHORED, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        runtime_cells[cell_index][attachment_count].position.z;
                                } else if ((ring_flags & SUBROW_FLAG_RING_SLOW) != 0) {
                                    AddRing(
                                        &runtime_cells[cell_index][attachment_count], SUB_RING_KIND_SLOW_AUTHORED, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        runtime_cells[cell_index][attachment_count].position.z;
                                }
                            } else if ((runtime_cells[cell_index][attachment_count].tile_id
                                            == SUBLOC_TILE_RAMP_LEFT_BRACE
                                    || runtime_cells[cell_index][attachment_count].tile_id
                                        == SUBLOC_TILE_RAMP_GREATER
                                    || runtime_cells[cell_index][attachment_count].tile_id
                                        == SUBLOC_TILE_RAMP_RIGHT_BRACE
                                    || runtime_cells[cell_index][attachment_count].tile_id
                                        == SUBLOC_TILE_RAMP_LEFT_BRACKET
                                    || runtime_cells[cell_index][attachment_count].tile_id
                                        == SUBLOC_TILE_RAMP_LESS
                                    || runtime_cells[cell_index][attachment_count].tile_id
                                        == SUBLOC_TILE_RAMP_RIGHT_BRACKET)
                                && player.last_ring_spawn_z + 10.0f
                                    < runtime_cells[cell_index][attachment_count].position.z
                                && cell_index < completion_row_start) {
                                if ((ring_flags & SUBROW_FLAG_RING_POWER_UP) != 0) {
                                    AddRing(
                                        &runtime_cells[cell_index + 6][attachment_count],
                                        SUB_RING_KIND_POWER_UP_AUTHORED, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        runtime_cells[cell_index + 6][attachment_count]
                                            .position.z;
                                } else if ((ring_flags & SUBROW_FLAG_RING_EXPLODE) != 0) {
                                    AddRing(
                                        &runtime_cells[cell_index + 6][attachment_count],
                                        SUB_RING_KIND_EXPLODE_AUTHORED, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        runtime_cells[cell_index + 6][attachment_count]
                                            .position.z;
                                } else if ((ring_flags & SUBROW_FLAG_RING_SLOW) != 0) {
                                    AddRing(
                                        &runtime_cells[cell_index + 6][attachment_count],
                                        SUB_RING_KIND_SLOW_AUTHORED, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z =
                                        runtime_cells[cell_index + 6][attachment_count]
                                            .position.z;
                                } else if ((runtime_flags
                                                & SUBGAME_RUNTIME_FLAG_DEFAULT_RAMP_RINGS)
                                            != 0
                                    && (RAND(1.0f, "R") > 0.7f
                                        || level_mode == 7)
                                    && runtime_cells[cell_index][attachment_count].tile_id
                                        != SUBLOC_TILE_RAMP_LEFT_BRACKET
                                    && runtime_cells[cell_index][attachment_count].tile_id
                                        != SUBLOC_TILE_RAMP_LESS
                                    && runtime_cells[cell_index][attachment_count].tile_id
                                        != SUBLOC_TILE_RAMP_RIGHT_BRACKET) {
                                    AddRing(
                                        &runtime_cells[cell_index][attachment_count], SUB_RING_KIND_NORMAL_DEFAULT,
                                        &player, 0.0f);
                                    if (player.lives < 10)
                                        player.last_ring_spawn_z =
                                            runtime_cells[cell_index][attachment_count].position.z;
                                    else
                                        player.last_ring_spawn_z =
                                            runtime_cells[cell_index][attachment_count].position.z + 35.0f;
                                }
                            } else if ((runtime_cells[cell_index][attachment_count].tile_id
                                            == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
                                    || runtime_cells[cell_index][attachment_count].tile_id
                                        == SUBLOC_TILE_RAMP_GREATER_RAISED
                                    || runtime_cells[cell_index][attachment_count].tile_id
                                        == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED)
                                && player.last_ring_spawn_z + 10.0f
                                    < runtime_cells[cell_index][attachment_count].position.z
                                && cell_index < completion_row_start) {
                                if ((ring_flags & SUBROW_FLAG_RING_EXPLODE) != 0) {
                                    AddRing(
                                        &runtime_cells[cell_index][attachment_count], SUB_RING_KIND_EXPLODE_RAMP, &player,
                                        runtime_rows[cell_index].ring_speed);
                                    player.last_ring_spawn_z = runtime_cells[cell_index][attachment_count].position.z;
                                } else if (RAND(1.0f, "R2") > 0.7f
                                    || level_mode == 7
                                    || ((runtime_rows[cell_index].flags
                                            & SUBROW_FLAG_RING_EXPLODE)
                                        != 0)) {
                                    AddRing(
                                        &runtime_cells[cell_index][attachment_count], SUB_RING_KIND_EXPLODE_RAMP,
                                        &player, 0.0f);
                                    player.last_ring_spawn_z = runtime_cells[cell_index][attachment_count].position.z;
                                }
                            }
                        }
                    }
                }
                ++attachment_count;
            }
            ++cell_index;
            scan_reset = (unsigned char)0;
        }

        segment_cache.update_track_render_cache_rows();

        if (level_mode == 4) {
            char* text = time_trial.format_time_trial_string(&player.stopwatch);
            Rstrcpy(top_score_widget->text_buffer, text);
            if (sub_high_score.time_trial_route_records[level_mode_arg].active
                == 1) {
                text = time_trial.format_time_trial_string(
                    &sub_high_score.time_trial_route_records[level_mode_arg].timer);
                Rstrcpy(bottom_score_widget->text_buffer, text);
                break;
            }
            bottom_score_widget->HideInit();
            update_subgame_camera();
            return;
        }

        top_score_widget->text_buffer[0] = (char)0;
        top_score_widget->AddTextNumber(player.total_score);
        if (player.total_score > active_level_score) {
            active_level_score = player.total_score;
            bottom_score_widget->text_buffer[0] = (char)0;
            bottom_score_widget->AddTextNumber(active_level_score);
            update_subgame_camera();
            return;
        }
        break;
        } else {
            if (selected_level_record_persistent != 0) {
                app->players[0].saved_frontend_state =
                    app->players[0].frontend_state;
                g_game->players[0].frontend_state = 0x1a;
            } else {
                app->players[0].saved_frontend_state =
                    app->players[0].frontend_state;
                g_game->players[0].frontend_state = 0x1b;
            }
            if (g_game->intro.attract_reset_progress <= 1.0f)
                g_game->intro.hide_for_replay_latch = 0;
            return;
        }
    }
    }

    update_subgame_camera();
    return;

build_selected_level:
    StartLevel(level_mode_arg);
}
