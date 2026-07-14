// update_subgoldy @ 0x43b120 (thiscall, ret) — cRSubGoldy::Update()
// The per-frame player step: pause early-out, follow lateral response,
// squidge, replay playback vs mouse steering + replay recording, row
// events/tips, attachment begin, velocity shaping, follow-vs-free motion
// integration, the five exit lanes, wall-14 stall, lane lean, the
// completion handoff state machine, camera target + jetpack wobble,
// ghost marking (mode 4), backdrop progress, exit-progress voice gates,
// slow commentary, collisions, anim managers, movement flags/emitters,
// and the replay cursor / times-up tail.

#include <stddef.h>

#include "attachment_sample.h"
#include "app_shell.h"
#include "audio_system.h"
#include "backdrop.h"
#include "cheat_state.h"
#include "click_start.h"
#include "completion.h"
#include "damage_guage.h"
#include "game_root.h"
#include "nuke.h"
#include "object_render_types.h"
#include "player.h"
#include "sub_solution.h"
#include "progress_bar.h"
#include "presentation_animation_channel.h"
#include "runtime_config.h"
#include "sub_hover.h"
#include "tip_manager.h"
#include "times_up.h"
#include "track_attachment_types.h"
#include "track_parcel_runtime.h"
#include "voice_manager.h"

class Sprite;

float convert_math_type16_to_32(unsigned short value, float scale);
short convert_math_type32_to_16(float value, float scale);
float resolve_uncaptured_cursor_sensitivity_scale(float scale);

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

extern float g_subgoldy_ghost_z;          // flt_643190
extern float g_replay_accum_z;            // unk_643194

enum {
    TIME_TRIAL_RECORD_BANK_FROM_SUBGAME =
        offsetof(SubgameRuntime, sub_high_score)
        + offsetof(SubHighScore, time_trial_route_records),
};

#define TIME_TRIAL_RECORD_AT(block_expr) \
    ((SubSolution*)((block_expr) + TIME_TRIAL_RECORD_BANK_FROM_SUBGAME))

// Caller-local cRPath prefix. This aggregate-argument declaration preserves
// the native VC6 push sequence in this large caller; the shared Path owner has
// the same fields and callee address with a scalar spelling.
struct SubgoldyPathView {
    char unknown_00[0x38];
    int kind; // +0x38: 15 DETOUR, 24 WORM
    char unknown_3c[0x44 - 0x3c];
    int segment_count; // +0x44
    char unknown_48[0x58 - 0x48];
    AttachmentSample* primary_samples; // +0x58

    void try_enter_track_attachment_from_swept_motion(
        Vector3 position, Vector3 sweep, SubLoc* cell);
};

// The standalone helper body is exact with a double source declaration, but
// this native caller consumes the x87 return as float arithmetic. Return type
// is not encoded in the MSVC thiscall symbol, so retain this caller-side ABI
// view without duplicating any SubgameRuntime storage.
struct SubgoldyFloorSamplerCallView {
    float sample_track_floor_height_at_position(Vector3* position);
};

// row records live at game + 244*row + 0x5ccac8: SubRowFlag dword at +0x00,
// attachment cells at +0xa4 (0x5ccb6c) / +0xa8 (0x5ccb70), the row event id /
// definition index at +0xf0 (0x5ccbb8). row event definitions live at
// game + 16928*index + 0xa670: text at +0x00, dismiss seconds at +0x200,
// voice id at +0x204 (0xa874); the flat 0xa874 read is
// level_segment_count.

void Player::update_subgoldy()
{
    SubgameRuntime* current_game = game;
    if (current_game->subgame_pause_gate) {
        if (g_app->frontend_state != 9) {
            damage_gauge.update_damage_gauge();
            progress_bar.update_progress_bar();
            warning.update_warning();
            game->completion.update_row_event_display();
        }
        return;
    }

    if (follow_state.active == 1) {
        Path* template_record = follow_state.template_record;
        int sample = follow_state.sample_index + 3;
        int segment_count = template_record->segment_count;
        if (sample >= segment_count)
            sample = segment_count - 1;
        presentation.object->distort.z_wave =
            (template_record->primary_samples[sample].lateral_source * -3.0f
             - presentation.object->distort.z_wave) * 0.1f
            + presentation.object->distort.z_wave;
    } else {
        presentation.object->distort.z_wave =
            (0.0f - presentation.object->distort.z_wave) * 0.1f
            + presentation.object->distort.z_wave;
    }

    squidge.update_squidge();
    presentation.object->distort.y_squash = squidge.y_output;
    presentation.object->distort.xyz_scale = squidge.z_output;
    if (!game->level_mode)
        show_subgoldy_lives();

    switch (movement_mode_selector) {
    case 0:
    case 2:
        return;
    }

    SubgameRuntime* latch_game = game;
    if (latch_game->replay_update_cursor > 20
        && !latch_game->track_state_latch)
        latch_game->track_state_latch = 1;

    Vector3* p_position;
    SubgameRuntime* replay_game = game;
    if (replay_game->selected_level_record_active
        && replay_game->replay_update_cursor
               < replay_game->selected_level_record->replay_sample_count
        && click_start.state != CLICK_START_STATE_WAITING_FOR_START) {
        p_position = &transform.position;
        transform.position.x = convert_math_type16_to_32(
            replay_game
                ->selected_level_record
                ->run_records[replay_game->replay_update_cursor]
                .lateral_x,
            16.0f);
        SubgameRuntime* flag_game = game;
        if (flag_game
                ->selected_level_record
                ->run_records[flag_game->replay_update_cursor]
                .flags
            & 4)
            flag_game->track_state_latch = 1;
        else
            flag_game->track_state_latch = 0;
        if (game
                ->selected_level_record
                ->run_records[game->replay_update_cursor]
                .flags
            & 8) {
            g_app->frontend_state = 26;
            g_app->frontend_substate = 10;
            g_app->skip_flag = 1;
            g_app->fade.begin_frontend_fade_in();
            return;
        }
    } else {
        if (follow_state.flag_3c && completion_handoff_active) {
            track_z_offset = 320.0f;
            track_z_anchor = 320.0f;
        } else {
            float resolved;
            if (control_override_active) {
                float pulled = track_z_offset
                             - (presentation.transform.basis_up.x
                                + presentation.transform.basis_up.x);
                track_z_offset = pulled;
                track_z_anchor = pulled;
                if (track_z_offset < 0.0f)
                    resolved = 0.0f;
                else if (track_z_offset > 639.0f)
                    resolved = 639.0f;
                else
                    resolved = track_z_offset;
            } else {
                resolve_uncaptured_cursor_sensitivity_scale(
                    g_runtime_config.steering_sensitivity[steering_mode_selector]);
                float advanced = control_source->steering_x - track_z_anchor + track_z_offset;
                track_z_offset = advanced;
                if (advanced < 0.0f)
                    advanced = 0.0f;
                else if (advanced > 639.0f)
                    advanced = 639.0f;
                track_z_offset = advanced;
                track_z_anchor = control_source->steering_x;
                if (steering_mode_selector != 1)
                    goto steering_stored;
                resolved = control_source->steering_x;
            }
            track_z_offset = resolved;
        }
steering_stored:
        if (!completion_handoff_active) {
            float steer_target = (320.0f - track_z_offset) * 0.0125f;
            if (steer_target < -3.7f)
                steer_target = -3.7f;
            else if (steer_target > 3.7f)
                steer_target = 3.7f;
            if (click_start.state != CLICK_START_STATE_WAITING_FOR_START) {
                float pull = game->subgame_rate * 0.2f;
                float steer_delta = steer_target - transform.position.x;
                transform.position.x = pull * steer_delta + transform.position.x;
            }
        }
        p_position = &transform.position;
        float quantized_x = convert_math_type16_to_32(
            convert_math_type32_to_16(transform.position.x, 16.0f), 16.0f);
        transform.position.x = quantized_x;
        SubgameRuntime* record_game = game;
        record_game
            ->current_high_score_record
            .run_records[record_game->replay_update_cursor]
            .lateral_x = convert_math_type32_to_16(quantized_x, 16.0f);
        SubgameRuntime* record_game_z = game;
        if (!game->replay_update_cursor) {
            record_game_z
                ->current_high_score_record
                .run_records[record_game_z->replay_update_cursor]
                .delta_z = convert_math_type32_to_16(transform.position.z, 32.0f);
            g_replay_accum_z = convert_math_type16_to_32(
                game
                    ->current_high_score_record
                    .run_records[game->replay_update_cursor]
                    .delta_z,
                32.0f);
        } else {
            record_game_z
                ->current_high_score_record
                .run_records[record_game_z->replay_update_cursor]
                .delta_z =
                convert_math_type32_to_16(transform.position.z - g_replay_accum_z, 32.0f);
            g_replay_accum_z =
                convert_math_type16_to_32(
                    game
                        ->current_high_score_record
                        .run_records[game->replay_update_cursor]
                        .delta_z,
                    32.0f)
                + g_replay_accum_z;
        }
        SubgameRuntime* fire_game = game;
        if (fire_game->track_state_latch) {
            if (control_source->control_flags_a & 0x4000)
                fire_game
                    ->current_high_score_record
                    .run_records[fire_game->replay_update_cursor]
                    .flags |= 1;
            if (control_source->control_flags_b & 0x4000)
                game
                    ->current_high_score_record
                    .run_records[game->replay_update_cursor]
                    .flags |= 2;
        }
        PlayerControlSource* source = control_source;
        if ((source->control_flags_b & 0x4000) == 0 && (source->control_flags_a & 0x4000) == 0)
            game->track_state_latch = 1;
        SubgameRuntime* mark_game = game;
        if (mark_game->track_state_latch)
            mark_game
                ->current_high_score_record
                .run_records[mark_game->replay_update_cursor]
                .flags |= 4;
    }

    if (p_position->x < -4.0f) {
        p_position->x = -4.0f;
        velocity.x = 0.0f;
    }
    if (p_position->x > 4.0f) {
        p_position->x = 4.0f;
        velocity.x = 0.0f;
    }

    if (resurrect_active)
        update_subgoldy_resurrect();

    SubLoc* source_cell = game->get_track_grid_cell_at_world_position(p_position);
    SubgameRuntime* event_game = game;
    SubRow* row_record =
        &event_game->runtime_rows[source_cell->get_track_cell_row_index()];
    int event_id = row_record->row_event_id;
    if (event_id > 0 && event_id != row_event.id
        && event_id < event_game->level_definition.segment_count + 1) {
        row_event.id = event_id;
        if (game
                ->level_definition
                .segment_slots[row_record->row_event_id - 1]
                .message_text[0]) {
            row_event.definition.flags = 2;
            row_event.definition.text = game
                                            ->level_definition
                                            .segment_slots[row_record->row_event_id - 1]
                                            .message_text;
            row_event.definition.layout_y = 0.0f;
            row_event.definition.text_scale = 30.0f;
            row_event.definition.dismiss_seconds = game
                                                        ->level_definition
                                                        .segment_slots[row_record->row_event_id - 1]
                                                        .message_duration.value;
            if (!row_event_cutscene_started) {
                row_event_cutscene_started = 1;
                if (p_position->x > 0.0f)
                    presentation.dispatch_cutscene_animation(
                        4, 1, OBJECT_ANIMATION_MODE_UNCHANGED);
                else
                    presentation.dispatch_cutscene_animation(
                        3, 1, OBJECT_ANIMATION_MODE_UNCHANGED);
                presentation.dispatch_cutscene_animation(
                    1, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
            }
            int definition = row_record->row_event_id;
            SubgameRuntime* voice_game = game;
            if (voice_game
                    ->level_definition
                    .segment_slots[definition - 1]
                    .message_sample_id
                != -1)
                g_voice_manager.play_voice_manager(
                    VOICE_SET_TUTORIAL, VOICE_PLAY_INTERRUPT,
                    voice_game
                        ->level_definition
                        .segment_slots[definition - 1]
                        .message_sample_id);
            ((GameRoot*)g_app)->tip_manager.enqueue_tip_message(
                &row_event.definition, 1);
        }
    }

    if (!attachment_exit_pending) {
        unsigned char tile_id = source_cell->tile_id;
        if ((tile_id == 29 || tile_id == 30) && !follow_state.active) {
            follow_state.begin_track_attachment_follow_state(
                source_cell, p_position, this);
            if (follow_state.template_record->kind == 24)
                g_voice_manager.play_voice_manager(
                    VOICE_SET_WORM_TUNNEL, VOICE_PLAY_IF_IDLE, -1);
        }
    }

    if (control_override_active) {
        if (velocity.z < 0.0f) {
            float rate = game->subgame_rate;
            float quantum = rate * rate * 0.0040000002f;
            velocity.z = quantum * 0.25f + velocity.z;
        }
        if (velocity.z > 0.0f)
            velocity.z = 0.0f;
    } else {
        SubgameRuntime* accel_game = game;
        if ((float)accel_game->first_block_row_count > transform.position.z)
            velocity.z = accel_game->subgame_rate * accel_game->subgame_rate * 0.0040000002f
                       + velocity.z;
        if (velocity.z > 1.0f)
            velocity.z = 1.0f;
        if (click_start.state == CLICK_START_STATE_WAITING_FOR_START)
            velocity.z = 0.0f;
    }

    if (follow_state.active == 1) {
        Vector3* p_velocity = &velocity;
        switch (follow_state.update_track_attachment_follow_state(velocity.z, p_position,
                                                                  &velocity)) {
        case 1:
        case 3:
            if (follow_state.active == 1)
                begin_post_follow_carryover();
            break;
        case 0:
            if (follow_state.template_record->kind != 15) {
                float rate = game->subgame_rate;
                float quantum = rate * rate * 0.0040000002f;
                velocity.z = quantum + quantum + velocity.z;
            }
        case 2:
            p_position->x = p_position->x + p_velocity->x;
            p_position->y = p_velocity->y + p_position->y;
            p_position->z = p_velocity->z + p_position->z;
            velocity.z = (1.0f - game->subgame_rate * 0.003f) * velocity.z;
            velocity.y = (1.0f - game->subgame_rate * 0.003f) * velocity.y;
            p_velocity->x = (1.0f - game->subgame_rate * 0.1f) * p_velocity->x;
            {
                float rate = game->subgame_rate;
                float gravity = rate * rate * -0.0099999998f;
                velocity.y = gravity + velocity.y;
            }
            if (p_position->x < -4.0f) {
                p_position->x = -4.0f;
                p_velocity->x = 0.0f;
            }
            if (p_position->x > 4.0f) {
                p_position->x = 4.0f;
                p_velocity->x = 0.0f;
            }
            break;
        default:
            break;
        }
    } else {
        p_position->x = velocity.x + p_position->x;
        p_position->y = velocity.y + p_position->y;
        p_position->z = velocity.z + p_position->z;
        if (p_position->x < -4.0f) {
            p_position->x = -4.0f;
            velocity.x = 0.0f;
        }
        if (p_position->x > 4.0f) {
            p_position->x = 4.0f;
            velocity.x = 0.0f;
        }
        if (!completion_handoff_active) {
            SubLoc* slide_cell;
            if (game->get_track_grid_cell_at_world_position(p_position)->tile_id == 15
                || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 16
                || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 18
                || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 19
                || damage_gauge.state == DAMAGE_GUAGE_STATE_DRAINING
                       && (slide_cell = game->get_track_grid_cell_at_world_position(p_position),
                           slide_cell->is_sub_loc_floor())) {
                float rate = game->subgame_rate;
                float quantum = rate * rate * 0.0040000002f;
                velocity.z = quantum + quantum + velocity.z;
                if ((float)game->first_block_row_count <= transform.position.z
                    && transform.position.z > slide_extension_threshold_z) {
                    slide_extension_threshold_z = transform.position.z + 1.0f;
                }
            }
        }
        if (sub_hover.state == SUB_HOVER_STATE_ACTIVE) {
            float rate = game->subgame_rate;
            float quantum = rate * rate * 0.0040000002f;
            velocity.z = quantum + quantum + velocity.z;
        }
        if (!trampoline_bounce_active)
            velocity.z = (1.0f - game->subgame_rate * 0.003f) * velocity.z;
        velocity.y = (1.0f - game->subgame_rate * 0.003f) * velocity.y;
        velocity.x = (1.0f - game->subgame_rate * 0.1f) * velocity.x;
        if (boost_one_tick) {
            float rate = game->subgame_rate;
            float quantum = rate * rate * 0.0040000002f;
            velocity.z = quantum + quantum + velocity.z;
            attachment_exit_pending = 0;
        } else {
            SubLoc* landing_cell = game->get_track_grid_cell_at_world_position(p_position);
            if (attachment_exit_pending) {
                SubgameRuntime* drag_game = game;
                if ((drag_game->runtime_rows[landing_cell->get_track_cell_row_index()]
                         .flags
                      & SUBROW_FLAG_NO_FALL)
                    == 0
                    && sub_hover.state == SUB_HOVER_STATE_INACTIVE
                    && !control_override_active) {
                    velocity.z = (1.0f - drag_game->subgame_rate * 0.2f) * velocity.z;
                }
                if (game
                        ->runtime_rows[landing_cell->get_track_cell_row_index()]
                        .flags
                    & SUBROW_FLAG_PRIMARY_ATTACHMENT) {
                    Vector3 swept;
                    swept.x = velocity.x * 1.05f;
                    swept.y = velocity.y * 1.05f;
                    swept.z = velocity.z * 1.05f;
                    ((SubgoldyPathView*)game
                         ->runtime_rows[landing_cell->get_track_cell_row_index()]
                         .primary_attachment_cell
                         ->attachment_template_record)
                        ->try_enter_track_attachment_from_swept_motion(
                            *p_position, swept,
                            game
                                ->runtime_rows[landing_cell->get_track_cell_row_index()]
                                .primary_attachment_cell);
                }
                if (attachment_exit_pending
                    && (game
                            ->runtime_rows[landing_cell->get_track_cell_row_index()]
                            .flags
                        & SUBROW_FLAG_SECONDARY_ATTACHMENT)) {
                    Vector3 swept;
                    swept.x = velocity.x * 1.05f;
                    swept.y = velocity.y * 1.05f;
                    swept.z = velocity.z * 1.05f;
                    ((SubgoldyPathView*)game
                         ->runtime_rows[landing_cell->get_track_cell_row_index()]
                         .secondary_attachment_cell
                         ->attachment_template_record)
                        ->try_enter_track_attachment_from_swept_motion(
                            *p_position, swept,
                            game
                                ->runtime_rows[landing_cell->get_track_cell_row_index()]
                                .secondary_attachment_cell);
                }
            }
            if (!follow_state.active) {
                if (transform.position.y < 0.49000001f
                    && transform.position.y > -0.16333334f
                    && !landing_cell->is_sub_loc_empty()
                    && landing_cell->tile_id != 22) {
                    transform.set_matrix_rotation_identity();
                    trampoline_bounce_active = 0;
                    if (velocity.y < -0.029999999f) {
                        float squidge_amount = velocity.y - 0.029999999f;
                        squidge.start_squidge_y(squidge_amount);
                    }
                    if (velocity.y <= 0.0f) {
                        transform.position.y = 0.49000001f;
                        velocity.y = 0.0f;
                    }
                    attachment_exit_pending = 0;
                }
                unsigned char landing_tile = landing_cell->tile_id;
                if ((!landing_tile || landing_tile == 35)
                    && transform.position.y < 0.49000001f && velocity.y <= 0.0f) {
                    float fraction = transform.position.z - (float)(int)transform.position.z;
                    unsigned char open_edge_mask = landing_cell->open_edge_mask;
                    float fraction_high;
                    if (!(open_edge_mask & SUBLOC_OPEN_NEXT_ROW))
                        fraction_high = 1.0f;
                    else
                        fraction_high = 0.80000001f;
                    float fraction_low = 0.0f;
                    if (open_edge_mask & SUBLOC_OPEN_PREVIOUS_ROW)
                        fraction_low = 0.2f;
                    if (fraction < fraction_high && fraction > fraction_low
                        && !attachment_exit_pending)
                        begin_post_follow_carryover();
                }
                SubgameRuntime* probe_game = game;
                if (probe_game->level_mode == 3)
                    probe_game->get_track_grid_cell_at_world_position(p_position);
                if (((game->runtime_flags & SUBGAME_RUNTIME_FLAG_ALLOW_FALLING) == 0
                        || (g_cheat_state.flags & 2) != 0)
                    && transform.position.y < 0.49000001f) {
                    squidge.start_squidge_y(velocity.y);
                    trampoline_bounce_active = 0;
                    velocity.y = 0.0f;
                    attachment_exit_pending = 0;
                    transform.position.y = 0.49000001f;
                }
                if (transform.position.y < -7.0f && !resurrect_active)
                    initialize_subgoldy_death();
            }
        }
        if (surface_reaction_timer != 0.0f) {
            float advanced = surface_reaction_step + surface_reaction_timer;
            surface_reaction_timer = advanced;
            if (advanced > 1.0f)
                surface_reaction_timer = 0.0f;
        }
        if (!attachment_exit_pending) {
            float floor_top =
                ((SubgoldyFloorSamplerCallView*)game)
                    ->sample_track_floor_height_at_position(p_position)
                + 0.49000001f;
            if (floor_top > transform.position.y) {
                if (velocity.y <= 0.0f)
                    transform.position.y = floor_top;
                if (game->get_track_grid_cell_at_world_position(p_position)->tile_id == 8
                    || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 9
                    || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 10
                    || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 11
                    || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 12
                    || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 13) {
                    velocity.y = game->subgame_rate * 0.30000001f;
                } else if (game->get_track_grid_cell_at_world_position(p_position)->tile_id == 2
                           || game->get_track_grid_cell_at_world_position(p_position)->tile_id
                                  == 3
                           || game->get_track_grid_cell_at_world_position(p_position)->tile_id
                                  == 4
                           || game->get_track_grid_cell_at_world_position(p_position)->tile_id
                                  == 5
                           || game->get_track_grid_cell_at_world_position(p_position)->tile_id
                                  == 6
                           || game->get_track_grid_cell_at_world_position(p_position)->tile_id
                                  == 7) {
                    if (surface_reaction_timer == 0.0f)
                        surface_reaction_timer = surface_reaction_step;
                    velocity.y = game->subgame_rate * 0.2f;
                    if (!control_override_active) {
                        if (p_position->x > 0.0f)
                            presentation.dispatch_cutscene_animation(
                                4, 1, OBJECT_ANIMATION_MODE_UNCHANGED);
                        else
                            presentation.dispatch_cutscene_animation(
                                3, 1, OBJECT_ANIMATION_MODE_UNCHANGED);
                        presentation.dispatch_cutscene_animation(
                            1, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
                    }
                } else if (game->get_track_grid_cell_at_world_position(p_position)->tile_id
                           && game->get_track_grid_cell_at_world_position(p_position)->tile_id
                                  != 35
                           && game->get_track_grid_cell_at_world_position(p_position)->tile_id
                                  != 22) {
                    trampoline_bounce_active = 0;
                    velocity.y = 0.0f;
                }
            } else {
                float rate = game->subgame_rate;
                float gravity = rate * rate * -0.0099999998f;
                velocity.y = gravity + velocity.y;
            }
            if (transform.position.y < 0.0f && velocity.y <= 0.0f)
                begin_post_follow_carryover();
        } else {
            {
                float rate = game->subgame_rate;
                float gravity = rate * rate * -0.0099999998f;
                velocity.y = gravity + velocity.y;
            }
            SubLoc* trampoline_cell =
                game->get_track_grid_cell_at_world_position(p_position);
            if (trampoline_cell->tile_id == 22
                && trampoline_cell->position.y + 0.49000001f > transform.position.y
                && trampoline_cell->position.y - 0.49000001f < transform.position.y) {
                squidge.start_squidge_y(velocity.y);
                velocity.y = game->subgame_rate * 0.30000001f;
                transform.position.y = trampoline_cell->position.y + 0.49000001f;
                attachment_exit_pending = 0;
                trampoline_bounce_active = 1;
                g_sound_effect_manager.play_sound_effect(41);
            }
        }
    }

    warning.update_warning();

    {
        Vector3 wall_probe;
        float probe_y;
        float probe_z;
        if (boost_one_tick || follow_state.active
            || (probe_y = p_position->y, probe_z = p_position->z + 0.49000001f,
                wall_probe.x = p_position->x, wall_probe.z = probe_z, wall_probe.y = probe_y,
                game->get_track_grid_cell_at_world_position(&wall_probe)->tile_id != 14)
            || transform.position.y >= 6.5f) {
            barrier_hold_progress = 0.0f;
        } else {
            velocity.z = 0.0f;
            transform.position.z = (float)(int)(transform.position.z + 0.49000001f) - 0.5f;
            if (squidge.z_output == 0.0f)
                g_sound_effect_manager.play_sound_effect(47);
            squidge.start_squidge_z(-0.33000001f);
            float advanced = barrier_hold_step + barrier_hold_progress;
            barrier_hold_progress = advanced;
            if (advanced > 1.0f) {
                barrier_hold_progress = 0.0f;
                if (!attachment_exit_pending)
                    begin_post_follow_carryover();
            }
        }
    }

    if (!lane_lean_state
        && (game->get_track_grid_cell_at_world_position(p_position)->tile_id == 2
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 4
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 5
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 7
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 10
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 8
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 10
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 11
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 13)
        && !attachment_exit_pending && transform.position.y <= 0.98000002f) {
        lane_lean_progress_step = game->subgame_rate * 0.037037037f;
        if (game->get_track_grid_cell_at_world_position(p_position)->tile_id == 2
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 5
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 8
            || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 11) {
            lane_lean_state = 1;
            lane_lean_amplitude = 1.0f;
        } else {
            lane_lean_state = 2;
            lane_lean_amplitude = -1.0f;
        }
    }

    if (damage_retrigger_timer != 0.0f) {
        float advanced = damage_retrigger_step + damage_retrigger_timer;
        damage_retrigger_timer = advanced;
        if (advanced > 1.0f)
            damage_retrigger_timer = 0.0f;
    }

    SubgameRuntime* completion_game = game;
    float completion_start = (float)completion_game->completion_row_start;
    if (transform.position.z < completion_start || attachment_exit_pending) {
        if (!boost_one_tick && !control_override_active) {
            float window = completion_game->subgame_rate * 0.17f;
            if (velocity.z >= window) {
                window = completion_game->subgame_rate * 0.5f;
                if (velocity.z <= window)
                    window = velocity.z;
            }
            velocity.z = window;
        }
    } else {
        if (!completion_handoff_active) {
            if (completion_game->level_mode == 4) {
                float remaining =
                    (1.0f - (transform.position.z - completion_start) / velocity.z)
                    * 0.016666668f;
                stopwatch.Add(remaining);
            }
            SubgameRuntime* handoff_game = game;
            completion_handoff_timer = 0.0f;
            completion_handoff_timer_step = 0.016666668f;
            completion_handoff_voice_gate = 0;
            float window = handoff_game->subgame_rate * 0.17f;
            if (velocity.z >= window) {
                window = handoff_game->subgame_rate * 0.5f;
                if (velocity.z <= window)
                    window = velocity.z;
            }
            velocity.z = window;
            g_voice_manager.reset_voice_manager();
            sub_hover.end_jetpack_hover();
            presentation.cutscene.state = 5;
            g_sound_effect_manager.play_sound_effect(0);
            boost_one_tick = 0;
        }
        completion_handoff_active = 1;
        SubgameRuntime* run_out_game = game;
        if ((float)run_out_game->completion_row_start + 2.5f < transform.position.z) {
            float rate = run_out_game->subgame_rate;
            float quantum = rate * rate * 0.0040000002f;
            float slowed = velocity.z - (quantum + quantum);
            velocity.z = slowed;
            if (slowed < 0.0f)
                velocity.z = 0.0f;
        }
        float cycle = completion_handoff_cycle_step + completion_handoff_cycle_progress;
        completion_handoff_cycle_progress = cycle;
        if (cycle > 1.0f)
            completion_handoff_cycle_progress = 0.0f;
        completion_handoff_timer += completion_handoff_timer_step;
        SubgameRuntime* display_game = game;
        display_game->subgame_rebuild_selector = 2;
        if (completion_handoff_timer > 2.0f && !completion_handoff_voice_gate) {
            completion_handoff_voice_gate = 1;
            g_voice_manager.play_voice_manager(
                VOICE_SET_VICTORY, VOICE_PLAY_INTERRUPT, -1);
        }
        if (completion_handoff_timer > 2.0f) {
            SubgameRuntime* skip_game = game;
            if (skip_game->level_mode == 0 || skip_game->level_mode == 1) {
                if (skip_game->completion.gate_18 == 1
                    && (control_source->control_flags_a & 0x4000) != 0)
                    completion_handoff_timer = 5.0999999f;
                if (skip_game->completion.state == COMPLETION_STATE_CONTINUE_ACCEPTED)
                    completion_handoff_timer = 5.0999999f;
            }
        }
        if (completion_handoff_timer > 5.0f) {
            SubgameRuntime* hold_game = game;
            if ((hold_game->level_mode == 0 || hold_game->level_mode == 1)
                && hold_game->completion.state != COMPLETION_STATE_CONTINUE_ACCEPTED)
                completion_handoff_timer =
                    completion_handoff_timer - completion_handoff_timer_step;
        }
        if (completion_handoff_timer > 5.0f) {
            int fade_state = g_app->fade.state;
            if (!fade_state) {
                g_app->fade.begin_frontend_fade_out(0);
            } else if (fade_state == 4) {
                SubgameRuntime* finish_game = game;
                if (finish_game->completion.state != COMPLETION_STATE_INACTIVE)
                    finish_game->completion.flush_row_event_display();
                SubgameRuntime* dispatch_game = game;
                if (!dispatch_game->level_mode) {
                    if (dispatch_game->level_mode_arg
                        == ((GameRoot*)g_app)->subgame.galaxy.record_count - 1) {
                        dispatch_game->complete_subgame(1);
                        g_app->frontend_substate = 29;
                        g_app->frontend_state = 26;
                        return;
                    }
                    dispatch_game->complete_subgame(0);
                    game->subgame_rebuild_selector = 1;
                } else {
                    dispatch_game->complete_subgame(1);
                }
                SubgameRuntime* exit_game = game;
                if (exit_game->level_mode == 7) {
                    g_app->frontend_state = 26;
                    g_app->frontend_substate = 2;
                } else {
                    unsigned char persistent =
                        exit_game->selected_level_record_persistent;
                    g_app->frontend_substate = g_app->frontend_state;
                    if (persistent)
                        g_app->frontend_state = 26;
                    else
                        g_app->frontend_state = 27;
                }
                return;
            }
        }
    }

    Vector3 stashed_position = *p_position;
    if (follow_state.active == 1)
        *p_position = follow_state.output_position;
    sub_hover.update_jetpack_gauge();
    if (completion_handoff_active) {
        g_app->hud_target = g_app->hud_source;
        g_app->hud_target.scroll_progress =
            g_app->hud_target.scroll_progress - 1.0f;
    }
    damage_gauge.update_damage_gauge();
    progress_bar.update_progress_bar();

    Vector3* camera_target = &cached_camera_target_world;
    *camera_target = *p_position;
    Vector3 camera_offset =
        transform.basis_right * sub_hover.wobble_x
        + transform.basis_up * sub_hover.wobble_y
        + transform.basis_forward * sub_hover.wobble_alpha;
    *camera_target += camera_offset;

    int hold_ticks = damage_gauge.skin_hold_ticks;
    if (hold_ticks > 0)
        damage_gauge.skin_hold_ticks = hold_ticks - 1;
    if (follow_state.active == 1)
        p_position->x = stashed_position.x;

    float lean_step = game->subgame_rate * 0.037037037f;
    lane_lean_progress_step = lean_step;
    if (lane_lean_state) {
        float advanced = lean_step + lane_lean_progress;
        lane_lean_progress = advanced;
        if (advanced > 1.0f) {
            lane_lean_progress = 0.0f;
            lane_lean_state = 0;
        }
    }
    if (timer_360_state) {
        float advanced = timer_360_step + timer_360_progress;
        timer_360_progress = advanced;
        if (advanced > 1.0f) {
            timer_360_progress = 0.0f;
            timer_360_state = 0;
        }
    }
    float nuke_step = game->subgame_rate * 0.022222223f;
    nuke_effect_progress_step = nuke_step;
    if (nuke_effect_progress > 0.0f) {
        float advanced = nuke_step + nuke_effect_progress;
        nuke_effect_progress = advanced;
        if (advanced > 1.0f) {
            nuke_effect_progress = 0.0f;
            nuke.uninit_nuke();
        } else {
            nuke.update_nuke();
        }
    }

    SubgameRuntime* ghost_game = game;
    if (ghost_game->level_mode == 4) {
        char* record_block =
            (char*)ghost_game + sizeof(SubSolution) * ghost_game->level_mode_arg;
        if (TIME_TRIAL_RECORD_AT(record_block)->active == 1
            && !ghost_game->selected_level_record_active) {
            int cursor = ghost_game->replay_update_cursor;
            if (cursor
                >= TIME_TRIAL_RECORD_AT(record_block)->replay_sample_count)
                cursor =
                    TIME_TRIAL_RECORD_AT(record_block)->replay_sample_count;
            int anchor = startup_track_index;
            int offset_cursor;
            float ghost_z;
            if (!anchor
                || (offset_cursor =
                        TIME_TRIAL_RECORD_AT(record_block)->source_tail
                            - anchor + cursor)
                    == 0)
                ghost_z = convert_math_type16_to_32(
                    (unsigned short)TIME_TRIAL_RECORD_AT(record_block)
                        ->run_records[0].delta_z,
                    32.0f);
            else
                ghost_z = convert_math_type16_to_32(
                              (unsigned short)TIME_TRIAL_RECORD_AT(record_block)
                                  ->run_records[offset_cursor].delta_z,
                              32.0f)
                        + g_subgoldy_ghost_z;
            g_subgoldy_ghost_z = ghost_z;
            if (game->selected_level_record_active)
                g_subgoldy_ghost_z = transform.position.z;
            float ghost_horizon = transform.position.z + 20.0f;
            float clamped_ghost_z;
            if (g_subgoldy_ghost_z < ghost_horizon)
                clamped_ghost_z = g_subgoldy_ghost_z;
            else
                clamped_ghost_z = ghost_horizon;
            set_subgoldy_ghost_z(clamped_ghost_z);
        }
    }

    float backdrop_zoom = transform.position.z / (float)game->runtime_row_count;
    ((GameRoot*)g_app)->backdrop.set_backdrop_zoom(backdrop_zoom);

    SubgameRuntime* horizon_game = game;
    float interaction_limit = (float)horizon_game->completion_row_start - 30.0f;
    float interaction_near = transform.position.z - 8.0f;
    if (interaction_limit >= interaction_near)
        interaction_limit = interaction_near;
    SubHoverState hover_state = sub_hover.state;
    interaction_max_z = interaction_limit;
    if (hover_state == SUB_HOVER_STATE_ACTIVE) {
        if (transform.position.y < 1.0f) {
            velocity.y = velocity.y * 0.89999998f;
            velocity.y = velocity.y - game->subgame_rate * game->subgame_rate * -0.0099999998f;
        }
        attachment_exit_pending = 0;
    }

    if (attachment_exit_pending) {
        float advanced = attachment_exit_progress_step + attachment_exit_progress;
        attachment_exit_progress = advanced;
        if (advanced > 0.69999999f && !attachment_exit_gate_a) {
            g_voice_manager.play_voice_manager(
                VOICE_SET_FALL, VOICE_PLAY_IF_IDLE, -1);
            unsigned char override_active = control_override_active;
            attachment_exit_gate_a = 1;
            if (!override_active && transform.position.y < -6.0f)
                presentation.dispatch_cutscene_animation(
                    5, 1, OBJECT_ANIMATION_MODE_UNCHANGED);
        }
        if (transform.position.y < -7.0f && !attachment_exit_gate_b) {
            g_voice_manager.play_voice_manager(
                VOICE_SET_DYING, VOICE_PLAY_INTERRUPT, -1);
            attachment_exit_gate_b = 1;
            attachment_exit_gate_a = 1;
        }
    }

    if (startup_voice_timer > 0.0f) {
        float advanced = startup_voice_step + startup_voice_timer;
        startup_voice_timer = advanced;
        if (advanced > 1.0f) {
            g_voice_manager.play_voice_manager(
                VOICE_SET_START, VOICE_PLAY_INTERRUPT, -1);
            startup_voice_timer = 0.0f;
        }
    }

    SubgameRuntime* commentary_game = game;
    float window_floor = commentary_game->subgame_rate * 0.17f;
    if ((commentary_game->subgame_rate * 0.5f - window_floor) * 0.1f + window_floor
            <= velocity.z
        || window_floor >= velocity.z || attachment_exit_pending
        || click_start.state == CLICK_START_STATE_WAITING_FOR_START) {
        slow_commentary_timer = 0.0f;
    } else {
        float advanced = slow_commentary_step + slow_commentary_timer;
        slow_commentary_timer = advanced;
        if (advanced > 1.0f) {
            slow_commentary_timer = 0.0f;
            g_voice_manager.play_voice_manager(
                VOICE_SET_SLOW, VOICE_PLAY_AFTER_GLOBAL_COOLDOWN, -1);
        }
    }

    handle_subgoldy_collisions();
    presentation.anim_manager.update_anim_manager();
    presentation.jetpack_channel.anim_manager.update_anim_manager();
    presentation.weapon_channels[0].anim_manager.update_anim_manager();
    presentation.weapon_channels[1].anim_manager.update_anim_manager();
    presentation.weapon_channels[2].anim_manager.update_anim_manager();
    game->parcel_manager.update_track_parcels();
    presentation.initialize_cutscene();
    update_player_movement_flags();
    if (((GameRoot*)g_app)->subgame.replay_update_cursor < 10)
        movement_fire_progress = movement_fire_progress_step;

    SubgameRuntime* emitter_game = game;
    if ((emitter_game->runtime_flags
            & SUBGAME_RUNTIME_FLAG_MOVEMENT_FIRE_EMITTERS)
            != 0
        && !completion_handoff_active
        && !control_override_active
        && (click_start.state == CLICK_START_STATE_INACTIVE
            || click_start.state == CLICK_START_STATE_TEARDOWN)) {
        if (movement_fire_progress > 0.0f) {
            float advanced = movement_fire_progress_step + movement_fire_progress;
            movement_fire_progress = advanced;
            if (advanced > 1.0f)
                movement_fire_progress = 0.0f;
        } else if (emitter_game->track_state_latch) {
            if (emitter_game->selected_level_record_active) {
                if (emitter_game
                        ->selected_level_record
                        ->run_records[emitter_game->replay_update_cursor]
                        .flags
                    & 1) {
                    play_movement_state_sound();
                    update_movement_flag_emitters(this);
                    movement_fire_progress = movement_fire_progress_step + 0.30000001f;
                } else if (emitter_game
                               ->selected_level_record
                               ->run_records[emitter_game->replay_update_cursor]
                               .flags
                           & 2) {
                    movement_fire_progress = movement_fire_progress_step;
                    play_movement_state_sound();
                    update_movement_flag_emitters(this);
                }
            } else if (control_source->control_flags_a & 0x4000) {
                play_movement_state_sound();
                update_movement_flag_emitters(this);
                movement_fire_progress = movement_fire_progress_step + 0.30000001f;
            } else if (control_source->control_flags_b & 0x4000) {
                movement_fire_progress = movement_fire_progress_step;
                play_movement_state_sound();
                update_movement_flag_emitters(this);
            }
        }
    }

    game->completion.update_row_event_display();
    SubgameRuntime* tick_game = game;
    tick_game->current_high_score_record.replay_sample_count =
        tick_game->current_high_score_record.replay_sample_count + 1;
    SubgameRuntime* cursor_game = game;
    cursor_game->replay_update_cursor = cursor_game->replay_update_cursor + 1;
    SubgameRuntime* times_game = game;
    if (times_game->replay_update_cursor == 21000)
        times_game->times_up.show_times_up_message();
    game->times_up.update_times_up();
}

#undef TIME_TRIAL_RECORD_AT
