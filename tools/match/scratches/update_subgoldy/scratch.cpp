// update_subgoldy @ 0x43b120 (thiscall, ret) — cRSubGoldy::Update()
// The per-frame player step: pause early-out, follow lateral response,
// squidge, replay playback vs mouse steering + replay recording, row
// events/tips, attachment begin, velocity shaping, follow-vs-free motion
// integration, the five exit lanes, wall-14 stall, lane lean, the
// completion handoff state machine, camera target + jetpack wobble,
// ghost marking (mode 4), backdrop progress, exit-progress voice gates,
// slow commentary, collisions, anim managers, movement flags/emitters,
// and the replay cursor / times-up tail.

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

extern float g_subgoldy_ghost_z;          // flt_643190
extern float g_replay_accum_z;            // unk_643194

struct SubgoldyTrackRowCellView;

struct SubgoldyPathView {
    char unknown_00[0x38];
    int kind; // +0x38: 15 DETOUR, 24 WORM
    char unknown_3c[0x44 - 0x3c];
    int segment_count; // +0x44
    char unknown_48[0x58 - 0x48];
    AttachmentSample* primary_samples; // +0x58

    void try_enter_track_attachment_from_swept_motion(Vector3 position, Vector3 sweep,
                                                      SubgoldyTrackRowCellView* cell);
};

struct SubgoldyTrackRowCellView {
    char unknown_00[0x10];
    Vector3 anchor_position; // +0x10
    char unknown_1c[0x38 - 0x1c];
    SubgoldyPathView* attachment_template_record; // +0x38
    unsigned char tile_id;       // +0x3c
    unsigned char tile_flags_3d; // +0x3d

    int get_track_cell_row_index();
    unsigned char is_sub_loc_empty();
    unsigned char is_sub_loc_floor();
};

struct SubgoldyPlayerView;

struct SubgoldyFollowStateView {
    unsigned char active; // +0x00
    char unknown_01[3];
    SubgoldyPathView* template_record; // +0x04
    SubgoldyTrackRowCellView* source_cell;               // +0x08
    int sample_index;                        // +0x0c
    char unknown_10[0x2c - 0x10];
    Vector3 output_position; // +0x2c
    SubgoldyPlayerView* player; // +0x38
    unsigned char flag_3c;   // +0x3c
    char unknown_3d[3];

    SubgoldyPathView* begin_track_attachment_follow_state(
        SubgoldyTrackRowCellView* cell, const Vector3* position,
        SubgoldyPlayerView* player);
    int update_track_attachment_follow_state(float advance, Vector3* position,
                                             Vector3* velocity);
};

struct SubgoldyGameView {
    char unknown_00[0x09];
    unsigned char subgame_pause_gate; // +0x09
    char unknown_0a[0x38 - 0x0a];
    float subgame_rate; // +0x38
    char unknown_3c[0x40 - 0x3c];
    int level_mode;     // +0x40
    int level_mode_arg; // +0x44
    char unknown_48[0x4c - 0x48];
    unsigned int runtime_flags; // +0x4c
    int first_block_row_count;  // +0x50
    int runtime_row_count;      // +0x54
    int completion_row_start;   // +0x58

    SubgoldyTrackRowCellView* get_track_grid_cell_at_world_position(Vector3* position);
    float sample_track_floor_height_at_position(Vector3* position);
    void complete_subgame(unsigned char completed);
};

struct SubgoldyPlayerView {
    char unknown_00[0x38];
    TransformMatrix live_matrix; // +0x38 (position at +0x68)
    char unknown_78[0x84 - 0x78];
    unsigned char resurrect_active; // +0x84
    char unknown_85[0xa0 - 0x85];
    ClickStart click_start; // +0xa0, authored cRClickStart
    unsigned char row_event_cutscene_started; // +0x14c
    char unknown_14d[3];
    Nuke nuke; // +0x150, authored cRNuke owner
    char unknown_1cc[0x1d4 - 0x1cc];
    float damage_retrigger_timer; // +0x1d4
    float damage_retrigger_step;  // +0x1d8
    float surface_reaction_timer; // +0x1dc
    float surface_reaction_step;  // +0x1e0
    unsigned char trampoline_bounce_active; // +0x1e4
    char unknown_1e5[3];
    PlayerRowEventState row_event; // +0x1e8, authored row-event child
    char unknown_200[0x2d8 - 0x200];
    unsigned char control_override_active; // +0x2d8
    char unknown_2d9[0x2e8 - 0x2d9];
    Time stopwatch; // +0x2e8, authored cRTime value
    char unknown_300[0x304 - 0x300];
    int ghost_anchor_cursor; // +0x304
    char unknown_308[0x328 - 0x308];
    float wall_stall_timer; // +0x328
    float wall_stall_step;  // +0x32c
    float exit_voice_timer; // +0x330
    float exit_voice_step;  // +0x334
    char unknown_338[0x350 - 0x338];
    int lane_lean_state;           // +0x350
    float lane_lean_amplitude;     // +0x354
    float lane_lean_progress;      // +0x358
    float lane_lean_progress_step; // +0x35c
    int timer_360_state;           // +0x360
    int unknown_364;
    float timer_360_progress; // +0x368
    float timer_360_step;     // +0x36c
    int unknown_370;
    float nuke_effect_progress;      // +0x374
    float nuke_effect_progress_step; // +0x378
    char unknown_37c[0x384 - 0x37c];
    SubgoldyFollowStateView follow_state; // +0x384
    DamageGuage damage_gauge; // +0x3c4, authored cRDamageGuage owner
    ProgressBar progress_bar; // +0x3f0
    Warning warning; // +0x3f4, authored cRWarning owner
    int lives;                // +0x404
    SubgoldyGameView* game;               // +0x408
    int movement_mode_selector; // +0x40c
    Vector3 velocity;           // +0x410
    unsigned char boost_one_tick;          // +0x41c
    unsigned char attachment_exit_pending; // +0x41d
    char unknown_41e[0x434 - 0x41e];
    float attachment_exit_progress;      // +0x434
    float attachment_exit_progress_step; // +0x438
    PlayerControlSource* control_source; // +0x43c
    unsigned char completion_handoff_active; // +0x440
    char unknown_441[3];
    float completion_handoff_timer;       // +0x444
    float completion_handoff_timer_step;  // +0x448
    unsigned char attachment_exit_gate_a; // +0x44c
    unsigned char attachment_exit_gate_b; // +0x44d
    unsigned char completion_handoff_voice_gate; // +0x44e
    char unknown_44f[0x2730 - 0x44f];
    float movement_fire_progress;      // +0x2730
    float movement_fire_progress_step; // +0x2734
    float slide_extension_threshold_z; // +0x2738
    float track_z_offset;              // +0x273c
    float track_z_anchor;              // +0x2740
    float completion_handoff_cycle_progress; // +0x2744
    float completion_handoff_cycle_step;     // +0x2748
    int unknown_274c;
    SubHover sub_hover;                 // +0x2750, authored cRSubHover
    Vector3 cached_camera_target_world; // +0x2964
    int steering_mode_selector;         // +0x2970
    char unknown_2974[0x2980 - 0x2974];
    float interaction_max_z;   // +0x2980
    Snail presentation; // +0x2984, authored cRSnail owner
    char unknown_4338[0x4344 - 0x4338];
    Squidge squidge; // +0x4344, authored cRSquidge owner
    float slow_commentary_timer; // +0x435c
    float slow_commentary_step;  // +0x4360

    void update_subgoldy();
    void begin_post_follow_carryover();
    void handle_subgoldy_collisions();
    void update_subgoldy_resurrect();
    int initialize_subgoldy_death();
    void play_movement_state_sound();
    void update_movement_flag_emitters(SubgoldyPlayerView* player);
    int update_player_movement_flags();
    Sprite* set_subgoldy_ghost_z(float ghost_z);
    void show_subgoldy_lives();
};

// row records live at game + 244*row + 0x5ccac8: flags dword at +0x00
// (0x40 primary owner, 0x80 secondary owner, 0x100 no-drag), attachment
// cells at +0xa4 (0x5ccb6c) / +0xa8 (0x5ccb70), the row event id /
// definition index at +0xf0 (0x5ccbb8). row event definitions live at
// game + 16928*index + 0xa670: text at +0x00, dismiss seconds at +0x200,
// voice id at +0x204 (0xa874); the flat 0xa874 read is
// level_segment_count.

void SubgoldyPlayerView::update_subgoldy()
{
    SubgoldyGameView* current_game = game;
    if (current_game->subgame_pause_gate) {
        if (g_app->frontend_state != 9) {
            damage_gauge.update_damage_gauge();
            progress_bar.update_progress_bar();
            warning.update_warning();
            ((SubgameRuntime*)game)->completion.update_row_event_display();
        }
        return;
    }

    if (follow_state.active == 1) {
        SubgoldyPathView* template_record = follow_state.template_record;
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

    SubgoldyGameView* latch_game = game;
    if (((SubgameRuntime*)latch_game)->replay_update_cursor > 20
        && !((SubgameRuntime*)latch_game)->track_state_latch)
        ((SubgameRuntime*)latch_game)->track_state_latch = 1;

    Vector3* p_position;
    SubgoldyGameView* replay_game = game;
    if (((SubgameRuntime*)replay_game)->selected_level_record_active
        && ((SubgameRuntime*)replay_game)->replay_update_cursor
               < ((SubgameRuntime*)replay_game)
                     ->selected_level_record->replay_sample_count
        && click_start.state != 2) {
        p_position = &live_matrix.position;
        live_matrix.position.x = convert_math_type16_to_32(
            ((SubgameRuntime*)replay_game)
                ->selected_level_record
                ->run_records[((SubgameRuntime*)replay_game)->replay_update_cursor]
                .lateral_x,
            16.0f);
        SubgoldyGameView* flag_game = game;
        if (((SubgameRuntime*)flag_game)
                ->selected_level_record
                ->run_records[((SubgameRuntime*)flag_game)->replay_update_cursor]
                .flags
            & 4)
            ((SubgameRuntime*)flag_game)->track_state_latch = 1;
        else
            ((SubgameRuntime*)flag_game)->track_state_latch = 0;
        if (((SubgameRuntime*)game)
                ->selected_level_record
                ->run_records[((SubgameRuntime*)game)->replay_update_cursor]
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
                             - (presentation.live_matrix.basis_up.x
                                + presentation.live_matrix.basis_up.x);
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
            if (click_start.state != 2) {
                float pull = game->subgame_rate * 0.2f;
                float steer_delta = steer_target - live_matrix.position.x;
                live_matrix.position.x = pull * steer_delta + live_matrix.position.x;
            }
        }
        p_position = &live_matrix.position;
        float quantized_x = convert_math_type16_to_32(
            convert_math_type32_to_16(live_matrix.position.x, 16.0f), 16.0f);
        live_matrix.position.x = quantized_x;
        SubgoldyGameView* record_game = game;
        ((SubgameRuntime*)record_game)
            ->current_high_score_record
            .run_records[((SubgameRuntime*)record_game)->replay_update_cursor]
            .lateral_x = convert_math_type32_to_16(quantized_x, 16.0f);
        SubgoldyGameView* record_game_z = game;
        if (!((SubgameRuntime*)game)->replay_update_cursor) {
            ((SubgameRuntime*)record_game_z)
                ->current_high_score_record
                .run_records[((SubgameRuntime*)record_game_z)->replay_update_cursor]
                .delta_z = convert_math_type32_to_16(live_matrix.position.z, 32.0f);
            g_replay_accum_z = convert_math_type16_to_32(
                ((SubgameRuntime*)game)
                    ->current_high_score_record
                    .run_records[((SubgameRuntime*)game)->replay_update_cursor]
                    .delta_z,
                32.0f);
        } else {
            ((SubgameRuntime*)record_game_z)
                ->current_high_score_record
                .run_records[((SubgameRuntime*)record_game_z)->replay_update_cursor]
                .delta_z =
                convert_math_type32_to_16(live_matrix.position.z - g_replay_accum_z, 32.0f);
            g_replay_accum_z =
                convert_math_type16_to_32(
                    ((SubgameRuntime*)game)
                        ->current_high_score_record
                        .run_records[((SubgameRuntime*)game)->replay_update_cursor]
                        .delta_z,
                    32.0f)
                + g_replay_accum_z;
        }
        SubgoldyGameView* fire_game = game;
        if (((SubgameRuntime*)fire_game)->track_state_latch) {
            if (control_source->control_flags_a & 0x4000)
                ((SubgameRuntime*)fire_game)
                    ->current_high_score_record
                    .run_records[((SubgameRuntime*)fire_game)->replay_update_cursor]
                    .flags |= 1;
            if (control_source->control_flags_b & 0x4000)
                ((SubgameRuntime*)game)
                    ->current_high_score_record
                    .run_records[((SubgameRuntime*)game)->replay_update_cursor]
                    .flags |= 2;
        }
        PlayerControlSource* source = control_source;
        if ((source->control_flags_b & 0x4000) == 0 && (source->control_flags_a & 0x4000) == 0)
            ((SubgameRuntime*)game)->track_state_latch = 1;
        SubgoldyGameView* mark_game = game;
        if (((SubgameRuntime*)mark_game)->track_state_latch)
            ((SubgameRuntime*)mark_game)
                ->current_high_score_record
                .run_records[((SubgameRuntime*)mark_game)->replay_update_cursor]
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

    SubgoldyTrackRowCellView* source_cell = game->get_track_grid_cell_at_world_position(p_position);
    SubgoldyGameView* event_game = game;
    SubRow* row_record = &((SubgameRuntime*)event_game)
                              ->runtime_rows[source_cell->get_track_cell_row_index()];
    int event_id = row_record->row_event_id;
    if (event_id > 0 && event_id != row_event.id
        && event_id < ((SubgameRuntime*)event_game)->level_definition.segment_count + 1) {
        row_event.id = event_id;
        if (((SubgameRuntime*)game)
                ->level_definition
                .segment_slots[row_record->row_event_id - 1]
                .message_text[0]) {
            row_event.definition.flags = 2;
            row_event.definition.text = ((SubgameRuntime*)game)
                                            ->level_definition
                                            .segment_slots[row_record->row_event_id - 1]
                                            .message_text;
            row_event.definition.layout_y = 0.0f;
            row_event.definition.text_scale = 30.0f;
            row_event.definition.dismiss_seconds = ((SubgameRuntime*)game)
                                                        ->level_definition
                                                        .segment_slots[row_record->row_event_id - 1]
                                                        .message_duration.value;
            if (!row_event_cutscene_started) {
                row_event_cutscene_started = 1;
                if (p_position->x > 0.0f)
                    presentation.dispatch_cutscene_animation(4, 1, -1);
                else
                    presentation.dispatch_cutscene_animation(3, 1, -1);
                presentation.dispatch_cutscene_animation(1, 0, -1);
            }
            int definition = row_record->row_event_id;
            SubgoldyGameView* voice_game = game;
            if (((SubgameRuntime*)voice_game)
                    ->level_definition
                    .segment_slots[definition - 1]
                    .message_sample_id
                != -1)
                g_voice_manager.play_voice_manager(
                    13, 2,
                    ((SubgameRuntime*)voice_game)
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
            follow_state.begin_track_attachment_follow_state(source_cell, p_position, this);
            if (follow_state.template_record->kind == 24)
                g_voice_manager.play_voice_manager(12, 0, -1);
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
        SubgoldyGameView* accel_game = game;
        if ((float)accel_game->first_block_row_count > live_matrix.position.z)
            velocity.z = accel_game->subgame_rate * accel_game->subgame_rate * 0.0040000002f
                       + velocity.z;
        if (velocity.z > 1.0f)
            velocity.z = 1.0f;
        if (click_start.state == 2)
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
            SubgoldyTrackRowCellView* slide_cell;
            if (game->get_track_grid_cell_at_world_position(p_position)->tile_id == 15
                || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 16
                || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 18
                || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 19
                || damage_gauge.state == 2
                       && (slide_cell = game->get_track_grid_cell_at_world_position(p_position),
                           slide_cell->is_sub_loc_floor())) {
                float rate = game->subgame_rate;
                float quantum = rate * rate * 0.0040000002f;
                velocity.z = quantum + quantum + velocity.z;
                if ((float)game->first_block_row_count <= live_matrix.position.z
                    && live_matrix.position.z > slide_extension_threshold_z) {
                    slide_extension_threshold_z = live_matrix.position.z + 1.0f;
                }
            }
        }
        if (sub_hover.state == 1) {
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
            SubgoldyTrackRowCellView* landing_cell = game->get_track_grid_cell_at_world_position(p_position);
            if (attachment_exit_pending) {
                SubgoldyGameView* drag_game = game;
                if ((((SubgameRuntime*)drag_game)
                         ->runtime_rows[landing_cell->get_track_cell_row_index()]
                         .flags
                      & 0x100)
                    == 0
                    && !sub_hover.state && !control_override_active) {
                    velocity.z = (1.0f - drag_game->subgame_rate * 0.2f) * velocity.z;
                }
                if (((SubgameRuntime*)game)
                        ->runtime_rows[landing_cell->get_track_cell_row_index()]
                        .flags
                    & 0x40) {
                    Vector3 swept;
                    swept.x = velocity.x * 1.05f;
                    swept.y = velocity.y * 1.05f;
                    swept.z = velocity.z * 1.05f;
                    ((SubgoldyTrackRowCellView*)((SubgameRuntime*)game)
                         ->runtime_rows[landing_cell->get_track_cell_row_index()]
                         .primary_attachment_cell)
                        ->attachment_template_record
                        ->try_enter_track_attachment_from_swept_motion(
                            *p_position, swept,
                            (SubgoldyTrackRowCellView*)((SubgameRuntime*)game)
                                ->runtime_rows[landing_cell->get_track_cell_row_index()]
                                .primary_attachment_cell);
                }
                if (attachment_exit_pending
                    && (((SubgameRuntime*)game)
                            ->runtime_rows[landing_cell->get_track_cell_row_index()]
                            .flags
                        & 0x80)) {
                    Vector3 swept;
                    swept.x = velocity.x * 1.05f;
                    swept.y = velocity.y * 1.05f;
                    swept.z = velocity.z * 1.05f;
                    ((SubgoldyTrackRowCellView*)((SubgameRuntime*)game)
                         ->runtime_rows[landing_cell->get_track_cell_row_index()]
                         .secondary_attachment_cell)
                        ->attachment_template_record
                        ->try_enter_track_attachment_from_swept_motion(
                            *p_position, swept,
                            (SubgoldyTrackRowCellView*)((SubgameRuntime*)game)
                                ->runtime_rows[landing_cell->get_track_cell_row_index()]
                                .secondary_attachment_cell);
                }
            }
            if (!follow_state.active) {
                if (live_matrix.position.y < 0.49000001f
                    && live_matrix.position.y > -0.16333334f
                    && !landing_cell->is_sub_loc_empty()
                    && landing_cell->tile_id != 22) {
                    live_matrix.set_matrix_rotation_identity();
                    trampoline_bounce_active = 0;
                    if (velocity.y < -0.029999999f) {
                        float squidge_amount = velocity.y - 0.029999999f;
                        squidge.start_squidge_y(squidge_amount);
                    }
                    if (velocity.y <= 0.0f) {
                        live_matrix.position.y = 0.49000001f;
                        velocity.y = 0.0f;
                    }
                    attachment_exit_pending = 0;
                }
                unsigned char landing_tile = landing_cell->tile_id;
                if ((!landing_tile || landing_tile == 35)
                    && live_matrix.position.y < 0.49000001f && velocity.y <= 0.0f) {
                    float fraction = live_matrix.position.z - (float)(int)live_matrix.position.z;
                    unsigned char flags_3d = landing_cell->tile_flags_3d;
                    float fraction_high;
                    if (!(flags_3d & 2))
                        fraction_high = 1.0f;
                    else
                        fraction_high = 0.80000001f;
                    float fraction_low = 0.0f;
                    if (flags_3d & 1)
                        fraction_low = 0.2f;
                    if (fraction < fraction_high && fraction > fraction_low
                        && !attachment_exit_pending)
                        begin_post_follow_carryover();
                }
                SubgoldyGameView* probe_game = game;
                if (probe_game->level_mode == 3)
                    probe_game->get_track_grid_cell_at_world_position(p_position);
                if (((game->runtime_flags & 0x400) == 0 || (g_cheat_state.flags & 2) != 0)
                    && live_matrix.position.y < 0.49000001f) {
                    squidge.start_squidge_y(velocity.y);
                    trampoline_bounce_active = 0;
                    velocity.y = 0.0f;
                    attachment_exit_pending = 0;
                    live_matrix.position.y = 0.49000001f;
                }
                if (live_matrix.position.y < -7.0f && !resurrect_active)
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
                game->sample_track_floor_height_at_position(p_position) + 0.49000001f;
            if (floor_top > live_matrix.position.y) {
                if (velocity.y <= 0.0f)
                    live_matrix.position.y = floor_top;
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
                            presentation.dispatch_cutscene_animation(4, 1, -1);
                        else
                            presentation.dispatch_cutscene_animation(3, 1, -1);
                        presentation.dispatch_cutscene_animation(1, 0, -1);
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
            if (live_matrix.position.y < 0.0f && velocity.y <= 0.0f)
                begin_post_follow_carryover();
        } else {
            {
                float rate = game->subgame_rate;
                float gravity = rate * rate * -0.0099999998f;
                velocity.y = gravity + velocity.y;
            }
            SubgoldyTrackRowCellView* trampoline_cell =
                game->get_track_grid_cell_at_world_position(p_position);
            if (trampoline_cell->tile_id == 22
                && trampoline_cell->anchor_position.y + 0.49000001f > live_matrix.position.y
                && trampoline_cell->anchor_position.y - 0.49000001f < live_matrix.position.y) {
                squidge.start_squidge_y(velocity.y);
                velocity.y = game->subgame_rate * 0.30000001f;
                live_matrix.position.y = trampoline_cell->anchor_position.y + 0.49000001f;
                attachment_exit_pending = 0;
                trampoline_bounce_active = 1;
                g_sound_effect_manager.play_sound_effect(41);
            }
        }
    }

    warning.update_warning();

    Vector3 wall_probe;
    float probe_y;
    float probe_z;
    if (boost_one_tick || follow_state.active
        || (probe_y = p_position->y, probe_z = p_position->z + 0.49000001f,
            wall_probe.x = p_position->x, wall_probe.z = probe_z, wall_probe.y = probe_y,
            game->get_track_grid_cell_at_world_position(&wall_probe)->tile_id != 14)
        || live_matrix.position.y >= 6.5f) {
        wall_stall_timer = 0.0f;
    } else {
        velocity.z = 0.0f;
        live_matrix.position.z = (float)(int)(live_matrix.position.z + 0.49000001f) - 0.5f;
        if (squidge.z_output == 0.0f)
            g_sound_effect_manager.play_sound_effect(47);
        squidge.start_squidge_z(-0.33000001f);
        float advanced = wall_stall_step + wall_stall_timer;
        wall_stall_timer = advanced;
        if (advanced > 1.0f) {
            wall_stall_timer = 0.0f;
            if (!attachment_exit_pending)
                begin_post_follow_carryover();
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
        && !attachment_exit_pending && live_matrix.position.y <= 0.98000002f) {
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

    SubgoldyGameView* completion_game = game;
    float completion_start = (float)completion_game->completion_row_start;
    if (live_matrix.position.z < completion_start || attachment_exit_pending) {
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
                    (1.0f - (live_matrix.position.z - completion_start) / velocity.z)
                    * 0.016666668f;
                stopwatch.Add(remaining);
            }
            SubgoldyGameView* handoff_game = game;
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
        SubgoldyGameView* run_out_game = game;
        if ((float)run_out_game->completion_row_start + 2.5f < live_matrix.position.z) {
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
        SubgoldyGameView* display_game = game;
        ((SubgameRuntime*)display_game)->subgame_rebuild_selector = 2;
        if (completion_handoff_timer > 2.0f && !completion_handoff_voice_gate) {
            completion_handoff_voice_gate = 1;
            g_voice_manager.play_voice_manager(8, 2, -1);
        }
        if (completion_handoff_timer > 2.0f) {
            SubgoldyGameView* skip_game = game;
            if (skip_game->level_mode == 0 || skip_game->level_mode == 1) {
                if (((SubgameRuntime*)skip_game)->completion.gate_18 == 1
                    && (control_source->control_flags_a & 0x4000) != 0)
                    completion_handoff_timer = 5.0999999f;
                if (((SubgameRuntime*)skip_game)->completion.state == 5)
                    completion_handoff_timer = 5.0999999f;
            }
        }
        if (completion_handoff_timer > 5.0f) {
            SubgoldyGameView* hold_game = game;
            if ((hold_game->level_mode == 0 || hold_game->level_mode == 1)
                && ((SubgameRuntime*)hold_game)->completion.state != 5)
                completion_handoff_timer =
                    completion_handoff_timer - completion_handoff_timer_step;
        }
        if (completion_handoff_timer > 5.0f) {
            int fade_state = g_app->fade.state;
            if (!fade_state) {
                g_app->fade.begin_frontend_fade_out(0);
            } else if (fade_state == 4) {
                SubgoldyGameView* finish_game = game;
                if (((SubgameRuntime*)finish_game)->completion.state)
                    ((SubgameRuntime*)finish_game)
                        ->completion.flush_row_event_display();
                SubgoldyGameView* dispatch_game = game;
                if (!dispatch_game->level_mode) {
                    if (dispatch_game->level_mode_arg
                        == ((GameRoot*)g_app)->subgame.galaxy.record_count - 1) {
                        dispatch_game->complete_subgame(1);
                        g_app->frontend_substate = 29;
                        g_app->frontend_state = 26;
                        return;
                    }
                    dispatch_game->complete_subgame(0);
                    ((SubgameRuntime*)game)->subgame_rebuild_selector = 1;
                } else {
                    dispatch_game->complete_subgame(1);
                }
                SubgoldyGameView* exit_game = game;
                if (exit_game->level_mode == 7) {
                    g_app->frontend_state = 26;
                    g_app->frontend_substate = 2;
                } else {
                    unsigned char persistent =
                        ((SubgameRuntime*)exit_game)->selected_level_record_persistent;
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
    float wobble_alpha = sub_hover.wobble_alpha;
    *camera_target = *p_position;
    float forward_x = wobble_alpha * live_matrix.basis_forward.x;
    float forward_y = wobble_alpha * live_matrix.basis_forward.y;
    float forward_z = wobble_alpha * live_matrix.basis_forward.z;
    float wobble_y = sub_hover.wobble_y;
    float up_x = wobble_y * live_matrix.basis_up.x;
    float up_y = wobble_y * live_matrix.basis_up.y;
    float up_z = wobble_y * live_matrix.basis_up.z;
    float wobble_x = sub_hover.wobble_x;
    wall_probe.x = wobble_x * live_matrix.basis_right.x;
    wall_probe.y = wobble_x * live_matrix.basis_right.y;
    float right_z = wobble_x * live_matrix.basis_right.z;
    float lateral_x = wall_probe.x + up_x;
    float lateral_y = wall_probe.y + up_y;
    wall_probe.x = lateral_x + forward_x;
    wall_probe.y = lateral_y + forward_y;
    camera_target->x = wall_probe.x + camera_target->x;
    camera_target->y = wall_probe.y + camera_target->y;
    camera_target->z = forward_z + up_z + right_z + camera_target->z;

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

    SubgoldyGameView* ghost_game = game;
    if (ghost_game->level_mode == 4) {
        char* record_block =
            (char*)ghost_game + sizeof(SubSolution) * ghost_game->level_mode_arg;
        if (((SubSolution*)(record_block + 0x944150))->active == 1
            && !((SubgameRuntime*)ghost_game)->selected_level_record_active) {
            int cursor = ((SubgameRuntime*)ghost_game)->replay_update_cursor;
            if (cursor
                >= ((SubSolution*)(record_block + 0x944150))->replay_sample_count)
                cursor =
                    ((SubSolution*)(record_block + 0x944150))->replay_sample_count;
            int anchor = ghost_anchor_cursor;
            int offset_cursor;
            float ghost_z;
            if (!anchor
                || (offset_cursor =
                        ((SubSolution*)(record_block + 0x944150))->source_tail
                            - anchor + cursor)
                    == 0)
                ghost_z = convert_math_type16_to_32(
                    (unsigned short)((SubSolution*)(record_block + 0x944150))
                        ->run_records[0].delta_z,
                    32.0f);
            else
                ghost_z = convert_math_type16_to_32(
                              (unsigned short)((SubSolution*)(record_block + 0x944150))
                                  ->run_records[offset_cursor].delta_z,
                              32.0f)
                        + g_subgoldy_ghost_z;
            g_subgoldy_ghost_z = ghost_z;
            if (((SubgameRuntime*)game)->selected_level_record_active)
                g_subgoldy_ghost_z = live_matrix.position.z;
            float ghost_horizon = live_matrix.position.z + 20.0f;
            float clamped_ghost_z;
            if (g_subgoldy_ghost_z < ghost_horizon)
                clamped_ghost_z = g_subgoldy_ghost_z;
            else
                clamped_ghost_z = ghost_horizon;
            set_subgoldy_ghost_z(clamped_ghost_z);
        }
    }

    float backdrop_zoom = live_matrix.position.z / (float)game->runtime_row_count;
    ((GameRoot*)g_app)->backdrop.set_backdrop_zoom(backdrop_zoom);

    SubgoldyGameView* horizon_game = game;
    float interaction_limit = (float)horizon_game->completion_row_start - 30.0f;
    float interaction_near = live_matrix.position.z - 8.0f;
    if (interaction_limit >= interaction_near)
        interaction_limit = interaction_near;
    int hover_state = sub_hover.state;
    interaction_max_z = interaction_limit;
    if (hover_state == 1) {
        if (live_matrix.position.y < 1.0f) {
            velocity.y = velocity.y * 0.89999998f;
            velocity.y = velocity.y - game->subgame_rate * game->subgame_rate * -0.0099999998f;
        }
        attachment_exit_pending = 0;
    }

    if (attachment_exit_pending) {
        float advanced = attachment_exit_progress_step + attachment_exit_progress;
        attachment_exit_progress = advanced;
        if (advanced > 0.69999999f && !attachment_exit_gate_a) {
            g_voice_manager.play_voice_manager(3, 0, -1);
            unsigned char override_active = control_override_active;
            attachment_exit_gate_a = 1;
            if (!override_active && live_matrix.position.y < -6.0f)
                presentation.dispatch_cutscene_animation(5, 1, -1);
        }
        if (live_matrix.position.y < -7.0f && !attachment_exit_gate_b) {
            g_voice_manager.play_voice_manager(1, 2, -1);
            attachment_exit_gate_b = 1;
            attachment_exit_gate_a = 1;
        }
    }

    if (exit_voice_timer > 0.0f) {
        float advanced = exit_voice_step + exit_voice_timer;
        exit_voice_timer = advanced;
        if (advanced > 1.0f) {
            g_voice_manager.play_voice_manager(7, 2, -1);
            exit_voice_timer = 0.0f;
        }
    }

    SubgoldyGameView* commentary_game = game;
    float window_floor = commentary_game->subgame_rate * 0.17f;
    if ((commentary_game->subgame_rate * 0.5f - window_floor) * 0.1f + window_floor
            <= velocity.z
        || window_floor >= velocity.z || attachment_exit_pending || click_start.state == 2) {
        slow_commentary_timer = 0.0f;
    } else {
        float advanced = slow_commentary_step + slow_commentary_timer;
        slow_commentary_timer = advanced;
        if (advanced > 1.0f) {
            slow_commentary_timer = 0.0f;
            g_voice_manager.play_voice_manager(6, 1, -1);
        }
    }

    handle_subgoldy_collisions();
    presentation.anim_manager.update_anim_manager();
    presentation.jetpack_channel.anim_manager.update_anim_manager();
    presentation.weapon_channels[0].anim_manager.update_anim_manager();
    presentation.weapon_channels[1].anim_manager.update_anim_manager();
    presentation.weapon_channels[2].anim_manager.update_anim_manager();
    ((SubgameRuntime*)game)->parcel_manager.update_track_parcels();
    presentation.initialize_cutscene();
    update_player_movement_flags();
    if (((GameRoot*)g_app)->subgame.replay_update_cursor < 10)
        movement_fire_progress = movement_fire_progress_step;

    SubgoldyGameView* emitter_game = game;
    if ((emitter_game->runtime_flags & 0x400000) != 0 && !completion_handoff_active
        && !control_override_active
        && (click_start.state == 0 || click_start.state == 4)) {
        if (movement_fire_progress > 0.0f) {
            float advanced = movement_fire_progress_step + movement_fire_progress;
            movement_fire_progress = advanced;
            if (advanced > 1.0f)
                movement_fire_progress = 0.0f;
        } else if (((SubgameRuntime*)emitter_game)->track_state_latch) {
            if (((SubgameRuntime*)emitter_game)->selected_level_record_active) {
                if (((SubgameRuntime*)emitter_game)
                        ->selected_level_record
                        ->run_records[((SubgameRuntime*)emitter_game)
                                          ->replay_update_cursor]
                        .flags
                    & 1) {
                    play_movement_state_sound();
                    update_movement_flag_emitters(this);
                    movement_fire_progress = movement_fire_progress_step + 0.30000001f;
                } else if (((SubgameRuntime*)emitter_game)
                               ->selected_level_record
                               ->run_records[((SubgameRuntime*)emitter_game)
                                                 ->replay_update_cursor]
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

    ((SubgameRuntime*)game)->completion.update_row_event_display();
    SubgoldyGameView* tick_game = game;
    ((SubgameRuntime*)tick_game)->current_high_score_record.replay_sample_count =
        ((SubgameRuntime*)tick_game)
                ->current_high_score_record.replay_sample_count
            + 1;
    SubgoldyGameView* cursor_game = game;
    ((SubgameRuntime*)cursor_game)->replay_update_cursor =
        ((SubgameRuntime*)cursor_game)->replay_update_cursor + 1;
    SubgoldyGameView* times_game = game;
    if (((SubgameRuntime*)times_game)->replay_update_cursor == 21000)
        ((SubgameRuntime*)times_game)->times_up.show_times_up_message();
    ((SubgameRuntime*)game)->times_up.update_times_up();
}
