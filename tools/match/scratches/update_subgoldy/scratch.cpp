// update_subgoldy @ 0x43b120 (thiscall, ret) — cRSubGoldy::Update()
// The per-frame player step: pause early-out, follow lateral response,
// squidge, replay playback vs mouse steering + replay recording, row
// events/tips, attachment begin, velocity shaping, follow-vs-free motion
// integration, the five exit lanes, wall-14 stall, lane lean, the
// completion handoff state machine, camera target + jetpack wobble,
// ghost marking (mode 4), backdrop progress, exit-progress voice gates,
// slow commentary, collisions, anim managers, movement flags/emitters,
// and the replay cursor / times-up tail.

#include "high_score_record.h"
#include "presentation_animation_channel.h"

class Sprite;

float convert_math_type16_to_32(unsigned short value, float scale);
short convert_math_type32_to_16(float value, float scale);
float resolve_uncaptured_cursor_sensitivity_scale(float scale);

struct VoiceManager {
    void play_voice_manager(int voice, unsigned char flag, int arg);
    void reset_voice_manager();
};
extern VoiceManager g_voice_manager; // unk_751498

struct SoundEffectManager {
    void play_sound_effect(int sound_id);
};
extern SoundEffectManager g_sound_effect_manager;

extern float g_subgoldy_ghost_z;          // flt_643190
extern float g_replay_accum_z;            // unk_643194
extern unsigned char g_environment_flags; // byte_4B2F40
extern float g_steering_sensitivity[];    // flt_4DF950

struct FrontendFade {
    int state;
    void begin_frontend_fade_in();
    void begin_frontend_fade_out(int mode);
};

struct HudRow {
    int values[16];
};

// keep the App struct simple: members through +0x30c, far fields raw.
struct AppShell {
    char unknown_00[0x24];
    FrontendFade fade;     // +0x24
    char unknown_28[0x15c - 0x28];
    HudRow hud_source;     // +0x15c
    char unknown_19c[0x1b8 - 0x19c];
    int frontend_state;    // +0x1b8
    int frontend_substate; // +0x1bc
    char unknown_1c0[0x2cc - 0x1c0];
    HudRow hud_target;       // +0x2cc (the scroll float at +0x300 sits inside)
    unsigned char skip_flag; // +0x30c
};

extern AppShell* g_app; // data_4df904

struct TipDefinition {
    int flags;             // +0x00
    float layout_y;        // +0x04
    float text_scale;      // +0x08
    float dismiss_seconds; // +0x0c
    char* text;            // +0x10
};

struct TipManager {
    void enqueue_tip_message(TipDefinition* tip, int mode);
};

struct Backdrop {
    void set_backdrop_progress_fraction(float fraction);
};

struct RowEventDisplay {
    char unknown_00[0x14];
    int state;             // +0x14
    unsigned char gate_18; // +0x18

    void update_row_event_display();
    void flush_row_event_display();
};

struct TimesUp {
    int state;
    void show_times_up_message();
    void update_times_up();
};

struct TrackParcels {
    int state;
    void update_track_parcels();
};

struct Nuke {
    int state;
    void update_nuke();
    void uninit_nuke();
};

struct AttachmentSample {
    char unknown_00[0xa4];
    float lateral_source; // +0xa4
};

struct TrackRowCell;

struct AttachmentPathTemplate {
    char unknown_00[0x38];
    int kind; // +0x38: 15 DETOUR, 24 WORM
    char unknown_3c[0x44 - 0x3c];
    int segment_count; // +0x44
    char unknown_48[0x58 - 0x48];
    AttachmentSample* primary_samples; // +0x58

    void try_enter_track_attachment_from_swept_motion(Vector3 position, Vector3 sweep,
                                                      TrackRowCell* cell);
};

struct TrackRowCell {
    char unknown_00[0x10];
    Vector3 anchor_position; // +0x10
    char unknown_1c[0x38 - 0x1c];
    AttachmentPathTemplate* attachment_template_record; // +0x38
    unsigned char tile_id;       // +0x3c
    unsigned char tile_flags_3d; // +0x3d

    int get_track_cell_row_index();
    unsigned char is_open_neighbor_tile_family();
    unsigned char is_slide_cache_tile_family();
};

struct Player;

struct FollowState {
    unsigned char active; // +0x00
    char unknown_01[3];
    AttachmentPathTemplate* template_record; // +0x04
    TrackRowCell* source_cell;               // +0x08
    int sample_index;                        // +0x0c
    char unknown_10[0x2c - 0x10];
    Vector3 output_position; // +0x2c
    Player* player;          // +0x38
    unsigned char flag_3c;   // +0x3c
    char unknown_3d[3];

    void begin_track_attachment_follow_state(TrackRowCell* cell, Vector3* position,
                                             Player* player);
    int update_track_attachment_follow_state(float advance, Vector3* position,
                                             Vector3* velocity);
};

struct DamageGauge {
    int state; // +0x00: 2 = damaged slide
    char unknown_04[0x18 - 0x04];
    int skin_hold_ticks; // +0x18
    char unknown_1c[0x2c - 0x1c];

    void update_damage_gauge();
};

struct ProgressBar {
    int state;
    void update_progress_bar();
};

struct WarningActor {
    int state;
    float phase;
    float phase_step;
    void* target;

    void update_warning();
};

struct PlayerControlSource {
    int unknown_00;
    unsigned int control_flags_a; // +0x04
    int unknown_08;
    unsigned int control_flags_b; // +0x0c
    char unknown_10[0x28 - 0x10];
    float steering_x; // +0x28
};

struct JetpackGauge {
    float progress; // +0x00
    char unknown_04[0x0c - 0x04];
    int state; // +0x0c
    char unknown_10[0x14 - 0x10];
    float wobble_x;     // +0x14
    float wobble_y;     // +0x18
    float wobble_alpha; // +0x1c
    char unknown_20[0x214 - 0x20];

    void update_jetpack_gauge();
    void end_jetpack_hover();
};

struct VisualRoot {
    char unknown_00[0x80];
    float follow_lateral_response; // +0x80
    float squidge_primary;         // +0x84
    float squidge_secondary;       // +0x88
};

struct CutsceneAI {
    char unknown_00[0x0c];
    int state; // +0x0c (presentation +0x1964)
    char unknown_10[0x5c - 0x10];
};

struct Presentation {
    char unknown_00[0x24];
    VisualRoot* visual_root; // +0x24
    char unknown_28[0x48 - 0x28];
    float live_basis_up_x; // +0x48
    char unknown_4c[0x104 - 0x4c];
    AnimManager anim_manager; // +0x104
    char unknown_14c[0x64c - 0x14c];
    PresentationAnimationChannel weapon_channels[3]; // +0x64c, stride 0x3dc
    PresentationAnimationChannel jetpack_channel; // +0x11e0
    char unknown_15bc[0x1958 - 0x15bc];
    CutsceneAI cutscene_ai; // +0x1958, state at +0x1964
    char unknown_19b4[0x19c0 - 0x19b4];

    void dispatch_cutscene_animation(int animation, unsigned char flag, int arg);
    void initialize_cutscene();
};

struct Squidge {
    float y_output; // +0x00
    char unknown_04[0x0c - 0x04];
    float z_output; // +0x0c
    char unknown_10[0x18 - 0x10];

    void update_squidge();
    void start_squidge_y(float amount);
    void start_squidge_z(float amount);
};

struct Game {
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

    TrackRowCell* get_track_grid_cell_at_world_position(Vector3* position);
    float sample_track_floor_height_at_position(Vector3* position);
    void complete_subgame(int completed);
};

struct Player {
    char unknown_00[0x38];
    TransformMatrix live_matrix; // +0x38 (position at +0x68)
    char unknown_78[0x84 - 0x78];
    unsigned char resurrect_active; // +0x84
    char unknown_85[0x120 - 0x85];
    int movement_state; // +0x120
    char unknown_124[0x14c - 0x124];
    unsigned char row_event_cutscene_started; // +0x14c
    char unknown_14d[3];
    Nuke nuke; // +0x150
    char unknown_154[0x1d4 - 0x154];
    float damage_retrigger_timer; // +0x1d4
    float damage_retrigger_step;  // +0x1d8
    float surface_reaction_timer; // +0x1dc
    float surface_reaction_step;  // +0x1e0
    unsigned char trampoline_bounce_active; // +0x1e4
    char unknown_1e5[3];
    int row_event_id;            // +0x1e8
    TipDefinition row_event_tip; // +0x1ec
    char unknown_200[0x2d8 - 0x200];
    unsigned char control_override_active; // +0x2d8
    char unknown_2d9[0x2e8 - 0x2d9];
    TimerCounters timer_counters; // +0x2e8
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
    FollowState follow_state; // +0x384
    DamageGauge damage_gauge; // +0x3c4
    ProgressBar progress_bar; // +0x3f0
    WarningActor warning;     // +0x3f4
    int lives;                // +0x404
    Game* game;               // +0x408
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
    JetpackGauge jetpack_gauge;         // +0x2750
    Vector3 cached_camera_target_world; // +0x2964
    int steering_mode_selector;         // +0x2970
    char unknown_2974[0x2980 - 0x2974];
    float interaction_max_z;   // +0x2980
    Presentation presentation; // +0x2984
    Squidge squidge;           // +0x4344
    float slow_commentary_timer; // +0x435c
    float slow_commentary_step;  // +0x4360

    void update_subgoldy();
    void begin_post_follow_carryover();
    void handle_subgoldy_collisions();
    void update_subgoldy_resurrect();
    void initialize_subgoldy_death();
    void play_movement_state_sound();
    void update_movement_flag_emitters(Player* player);
    void update_player_movement_flags();
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

void Player::update_subgoldy()
{
    Game* current_game = game;
    if (current_game->subgame_pause_gate) {
        if (g_app->frontend_state != 9) {
            damage_gauge.update_damage_gauge();
            progress_bar.update_progress_bar();
            warning.update_warning();
            ((RowEventDisplay*)((char*)game + 0x12727d8))->update_row_event_display();
        }
        return;
    }

    if (follow_state.active == 1) {
        AttachmentPathTemplate* template_record = follow_state.template_record;
        int sample = follow_state.sample_index + 3;
        int segment_count = template_record->segment_count;
        if (sample >= segment_count)
            sample = segment_count - 1;
        presentation.visual_root->follow_lateral_response =
            (template_record->primary_samples[sample].lateral_source * -3.0f
             - presentation.visual_root->follow_lateral_response) * 0.1f
            + presentation.visual_root->follow_lateral_response;
    } else {
        presentation.visual_root->follow_lateral_response =
            (0.0f - presentation.visual_root->follow_lateral_response) * 0.1f
            + presentation.visual_root->follow_lateral_response;
    }

    squidge.update_squidge();
    presentation.visual_root->squidge_primary = squidge.y_output;
    presentation.visual_root->squidge_secondary = squidge.z_output;
    if (!game->level_mode)
        show_subgoldy_lives();

    switch (movement_mode_selector) {
    case 0:
    case 2:
        return;
    }

    Game* latch_game = game;
    if (*(int*)((char*)latch_game + 0xff25dc) > 20 && !*((unsigned char*)latch_game + 0xa854))
        *((unsigned char*)latch_game + 0xa854) = 1;

    Vector3* p_position;
    Game* replay_game = game;
    if (*((unsigned char*)replay_game + 0xff25d0)
        && *(int*)((char*)replay_game + 0xff25dc)
               < (*(HighScoreRecord**)((char*)replay_game + 0xff25d4))->replay_sample_count
        && movement_state != 2) {
        p_position = &live_matrix.position;
        live_matrix.position.x = convert_math_type16_to_32(
            (*(HighScoreRecord**)((char*)replay_game + 0xff25d4))
                ->run_records[*(int*)((char*)replay_game + 0xff25dc)]
                .lateral_x,
            16.0f);
        Game* flag_game = game;
        if ((*(HighScoreRecord**)((char*)flag_game + 0xff25d4))
                ->run_records[*(int*)((char*)flag_game + 0xff25dc)]
                .flags
            & 4)
            *((unsigned char*)flag_game + 0xa854) = 1;
        else
            *((unsigned char*)flag_game + 0xa854) = 0;
        if ((*(HighScoreRecord**)((char*)game + 0xff25d4))
                ->run_records[*(int*)((char*)game + 0xff25dc)]
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
                             - (presentation.live_basis_up_x + presentation.live_basis_up_x);
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
                    g_steering_sensitivity[steering_mode_selector]);
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
            if (movement_state != 2) {
                float pull = game->subgame_rate * 0.2f;
                float steer_delta = steer_target - live_matrix.position.x;
                live_matrix.position.x = pull * steer_delta + live_matrix.position.x;
            }
        }
        p_position = &live_matrix.position;
        float quantized_x = convert_math_type16_to_32(
            convert_math_type32_to_16(live_matrix.position.x, 16.0f), 16.0f);
        live_matrix.position.x = quantized_x;
        Game* record_game = game;
        ((ReplayRunRecord*)((char*)record_game + 0xfd2b80))[*(int*)((char*)record_game + 0xff25dc)]
            .lateral_x = convert_math_type32_to_16(quantized_x, 16.0f);
        Game* record_game_z = game;
        if (!*(int*)((char*)game + 0xff25dc)) {
            ((ReplayRunRecord*)((char*)record_game_z
                                + 0xfd2b80))[*(int*)((char*)record_game_z + 0xff25dc)]
                .delta_z = convert_math_type32_to_16(live_matrix.position.z, 32.0f);
            g_replay_accum_z = convert_math_type16_to_32(
                ((ReplayRunRecord*)((char*)game + 0xfd2b80))[*(int*)((char*)game + 0xff25dc)]
                    .delta_z,
                32.0f);
        } else {
            ((ReplayRunRecord*)((char*)record_game_z
                                + 0xfd2b80))[*(int*)((char*)record_game_z + 0xff25dc)]
                .delta_z =
                convert_math_type32_to_16(live_matrix.position.z - g_replay_accum_z, 32.0f);
            g_replay_accum_z =
                convert_math_type16_to_32(((ReplayRunRecord*)((char*)game + 0xfd2b80))
                                              [*(int*)((char*)game + 0xff25dc)]
                                                  .delta_z,
                                          32.0f)
                + g_replay_accum_z;
        }
        Game* fire_game = game;
        if (*((unsigned char*)fire_game + 0xa854)) {
            if (control_source->control_flags_a & 0x4000)
                *((unsigned char*)fire_game + 6 * *(int*)((char*)fire_game + 0xff25dc)
                  + 0xfd2b84) |= 1;
            if (control_source->control_flags_b & 0x4000)
                *((unsigned char*)game + 6 * *(int*)((char*)game + 0xff25dc) + 0xfd2b84) |= 2;
        }
        PlayerControlSource* source = control_source;
        if ((source->control_flags_b & 0x4000) == 0 && (source->control_flags_a & 0x4000) == 0)
            *((unsigned char*)game + 0xa854) = 1;
        Game* mark_game = game;
        if (*((unsigned char*)mark_game + 0xa854))
            *((unsigned char*)mark_game + 6 * *(int*)((char*)mark_game + 0xff25dc) + 0xfd2b84) |=
                4;
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

    TrackRowCell* source_cell = game->get_track_grid_cell_at_world_position(p_position);
    Game* event_game = game;
    char* row_record =
        (char*)event_game + 244 * source_cell->get_track_cell_row_index() + 0x5ccac8;
    int event_id = *(int*)(row_record + 0xf0);
    if (event_id > 0 && event_id != row_event_id
        && event_id < *(int*)((char*)event_game + 0xa874) + 1) {
        row_event_id = event_id;
        if (*((char*)game + 16928 * *(int*)(row_record + 0xf0) + 0xa670)) {
            row_event_tip.flags = 2;
            row_event_tip.text = (char*)game + 16928 * *(int*)(row_record + 0xf0) + 0xa670;
            row_event_tip.layout_y = 0.0f;
            row_event_tip.text_scale = 30.0f;
            row_event_tip.dismiss_seconds =
                *(float*)((char*)game + 16928 * *(int*)(row_record + 0xf0) + 0xa870);
            if (!row_event_cutscene_started) {
                row_event_cutscene_started = 1;
                if (p_position->x > 0.0f)
                    presentation.dispatch_cutscene_animation(4, 1, -1);
                else
                    presentation.dispatch_cutscene_animation(3, 1, -1);
                presentation.dispatch_cutscene_animation(1, 0, -1);
            }
            int definition = *(int*)(row_record + 0xf0);
            Game* voice_game = game;
            if (*(int*)((char*)voice_game + 16928 * definition + 0xa874) != -1)
                g_voice_manager.play_voice_manager(
                    13, 2, *(int*)((char*)voice_game + 16928 * definition + 0xa874));
            ((TipManager*)((char*)g_app + 0x12e6f58))->enqueue_tip_message(&row_event_tip, 1);
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
        Game* accel_game = game;
        if ((float)accel_game->first_block_row_count > live_matrix.position.z)
            velocity.z = accel_game->subgame_rate * accel_game->subgame_rate * 0.0040000002f
                       + velocity.z;
        if (velocity.z > 1.0f)
            velocity.z = 1.0f;
        if (movement_state == 2)
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
            TrackRowCell* slide_cell;
            if (game->get_track_grid_cell_at_world_position(p_position)->tile_id == 15
                || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 16
                || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 18
                || game->get_track_grid_cell_at_world_position(p_position)->tile_id == 19
                || damage_gauge.state == 2
                       && (slide_cell = game->get_track_grid_cell_at_world_position(p_position),
                           slide_cell->is_slide_cache_tile_family())) {
                float rate = game->subgame_rate;
                float quantum = rate * rate * 0.0040000002f;
                velocity.z = quantum + quantum + velocity.z;
                if ((float)game->first_block_row_count <= live_matrix.position.z
                    && live_matrix.position.z > slide_extension_threshold_z) {
                    slide_extension_threshold_z = live_matrix.position.z + 1.0f;
                }
            }
        }
        if (jetpack_gauge.state == 1) {
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
            TrackRowCell* landing_cell = game->get_track_grid_cell_at_world_position(p_position);
            if (attachment_exit_pending) {
                Game* drag_game = game;
                if ((*(int*)((char*)drag_game + 244 * landing_cell->get_track_cell_row_index()
                             + 0x5ccac8)
                     & 0x100) == 0
                    && !jetpack_gauge.state && !control_override_active) {
                    velocity.z = (1.0f - drag_game->subgame_rate * 0.2f) * velocity.z;
                }
                if (*((unsigned char*)game + 244 * landing_cell->get_track_cell_row_index()
                      + 0x5ccac8)
                    & 0x40) {
                    Vector3 swept;
                    swept.x = velocity.x * 1.05f;
                    swept.y = velocity.y * 1.05f;
                    swept.z = velocity.z * 1.05f;
                    (*(TrackRowCell**)((char*)game
                                       + 244 * landing_cell->get_track_cell_row_index()
                                       + 0x5ccb6c))
                        ->attachment_template_record
                        ->try_enter_track_attachment_from_swept_motion(
                            *p_position, swept,
                            *(TrackRowCell**)((char*)game
                                              + 244 * landing_cell->get_track_cell_row_index()
                                              + 0x5ccb6c));
                }
                if (attachment_exit_pending
                    && (*((unsigned char*)game + 244 * landing_cell->get_track_cell_row_index()
                          + 0x5ccac8)
                        & 0x80)) {
                    Vector3 swept;
                    swept.x = velocity.x * 1.05f;
                    swept.y = velocity.y * 1.05f;
                    swept.z = velocity.z * 1.05f;
                    (*(TrackRowCell**)((char*)game
                                       + 244 * landing_cell->get_track_cell_row_index()
                                       + 0x5ccb70))
                        ->attachment_template_record
                        ->try_enter_track_attachment_from_swept_motion(
                            *p_position, swept,
                            *(TrackRowCell**)((char*)game
                                              + 244 * landing_cell->get_track_cell_row_index()
                                              + 0x5ccb70));
                }
            }
            if (!follow_state.active) {
                if (live_matrix.position.y < 0.49000001f
                    && live_matrix.position.y > -0.16333334f
                    && !landing_cell->is_open_neighbor_tile_family()
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
                Game* probe_game = game;
                if (probe_game->level_mode == 3)
                    probe_game->get_track_grid_cell_at_world_position(p_position);
                if (((game->runtime_flags & 0x400) == 0 || (g_environment_flags & 2) != 0)
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
            TrackRowCell* trampoline_cell =
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

    Game* completion_game = game;
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
                timer_counters.advance_timer_counters(remaining);
            }
            Game* handoff_game = game;
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
            jetpack_gauge.end_jetpack_hover();
            presentation.cutscene_ai.state = 5;
            g_sound_effect_manager.play_sound_effect(0);
            boost_one_tick = 0;
        }
        completion_handoff_active = 1;
        Game* run_out_game = game;
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
        Game* display_game = game;
        *(int*)((char*)display_game + 0x1270fc8) = 2;
        if (completion_handoff_timer > 2.0f && !completion_handoff_voice_gate) {
            completion_handoff_voice_gate = 1;
            g_voice_manager.play_voice_manager(8, 2, -1);
        }
        if (completion_handoff_timer > 2.0f) {
            Game* skip_game = game;
            if (skip_game->level_mode == 0 || skip_game->level_mode == 1) {
                if (((RowEventDisplay*)((char*)skip_game + 0x12727d8))->gate_18 == 1
                    && (control_source->control_flags_a & 0x4000) != 0)
                    completion_handoff_timer = 5.0999999f;
                if (((RowEventDisplay*)((char*)skip_game + 0x12727d8))->state == 5)
                    completion_handoff_timer = 5.0999999f;
            }
        }
        if (completion_handoff_timer > 5.0f) {
            Game* hold_game = game;
            if ((hold_game->level_mode == 0 || hold_game->level_mode == 1)
                && ((RowEventDisplay*)((char*)hold_game + 0x12727d8))->state != 5)
                completion_handoff_timer =
                    completion_handoff_timer - completion_handoff_timer_step;
        }
        if (completion_handoff_timer > 5.0f) {
            int fade_state = g_app->fade.state;
            if (!fade_state) {
                g_app->fade.begin_frontend_fade_out(0);
            } else if (fade_state == 4) {
                Game* finish_game = game;
                if (((RowEventDisplay*)((char*)finish_game + 0x12727d8))->state)
                    ((RowEventDisplay*)((char*)finish_game + 0x12727d8))
                        ->flush_row_event_display();
                Game* dispatch_game = game;
                if (!dispatch_game->level_mode) {
                    if (dispatch_game->level_mode_arg
                        == *(int*)((char*)g_app + 0x12d4644) - 1) {
                        dispatch_game->complete_subgame(1);
                        g_app->frontend_substate = 29;
                        g_app->frontend_state = 26;
                        return;
                    }
                    dispatch_game->complete_subgame(0);
                    *(int*)((char*)game + 0x1270fc8) = 1;
                } else {
                    dispatch_game->complete_subgame(1);
                }
                Game* exit_game = game;
                if (exit_game->level_mode == 7) {
                    g_app->frontend_state = 26;
                    g_app->frontend_substate = 2;
                } else {
                    unsigned char persistent = *((unsigned char*)exit_game + 0xff25d1);
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
    jetpack_gauge.update_jetpack_gauge();
    if (completion_handoff_active) {
        g_app->hud_target = g_app->hud_source;
        *(float*)((char*)g_app + 0x300) = *(float*)((char*)g_app + 0x300) - 1.0f;
    }
    damage_gauge.update_damage_gauge();
    progress_bar.update_progress_bar();

    Vector3* camera_target = &cached_camera_target_world;
    float wobble_alpha = jetpack_gauge.wobble_alpha;
    *camera_target = *p_position;
    float forward_x = wobble_alpha * live_matrix.basis_forward.x;
    float forward_y = wobble_alpha * live_matrix.basis_forward.y;
    float forward_z = wobble_alpha * live_matrix.basis_forward.z;
    float wobble_y = jetpack_gauge.wobble_y;
    float up_x = wobble_y * live_matrix.basis_up.x;
    float up_y = wobble_y * live_matrix.basis_up.y;
    float up_z = wobble_y * live_matrix.basis_up.z;
    float wobble_x = jetpack_gauge.wobble_x;
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

    Game* ghost_game = game;
    if (ghost_game->level_mode == 4) {
        char* record_block = (char*)ghost_game + 129728 * ghost_game->level_mode_arg;
        if (*(int*)(record_block + 0x944150) == 1
            && !*((unsigned char*)ghost_game + 0xff25d0)) {
            int cursor = *(int*)((char*)ghost_game + 0xff25dc);
            if (cursor >= *(int*)(record_block + 0x9441bc))
                cursor = *(int*)(record_block + 0x9441bc);
            int anchor = ghost_anchor_cursor;
            int offset_cursor;
            float ghost_z;
            if (!anchor
                || (offset_cursor = *(int*)(record_block + 0x944174) - anchor + cursor) == 0)
                ghost_z = convert_math_type16_to_32(*(unsigned short*)(record_block + 0x9441c2),
                                                    32.0f);
            else
                ghost_z = convert_math_type16_to_32(
                              *(unsigned short*)(record_block + 6 * offset_cursor + 0x9441c2),
                              32.0f)
                        + g_subgoldy_ghost_z;
            g_subgoldy_ghost_z = ghost_z;
            if (*((unsigned char*)game + 0xff25d0))
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

    float backdrop_fraction = live_matrix.position.z / (float)game->runtime_row_count;
    ((Backdrop*)((char*)g_app + 0x4ec10))->set_backdrop_progress_fraction(backdrop_fraction);

    Game* horizon_game = game;
    float interaction_limit = (float)horizon_game->completion_row_start - 30.0f;
    float interaction_near = live_matrix.position.z - 8.0f;
    if (interaction_limit >= interaction_near)
        interaction_limit = interaction_near;
    int hover_state = jetpack_gauge.state;
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

    Game* commentary_game = game;
    float window_floor = commentary_game->subgame_rate * 0.17f;
    if ((commentary_game->subgame_rate * 0.5f - window_floor) * 0.1f + window_floor
            <= velocity.z
        || window_floor >= velocity.z || attachment_exit_pending || movement_state == 2) {
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
    ((TrackParcels*)((char*)game + 0x125e480))->update_track_parcels();
    presentation.initialize_cutscene();
    update_player_movement_flags();
    if (*(int*)((char*)g_app + 0x1066bf4) < 10)
        movement_fire_progress = movement_fire_progress_step;

    Game* emitter_game = game;
    if ((emitter_game->runtime_flags & 0x400000) != 0 && !completion_handoff_active
        && !control_override_active
        && (movement_state == 0 || movement_state == 4)) {
        if (movement_fire_progress > 0.0f) {
            float advanced = movement_fire_progress_step + movement_fire_progress;
            movement_fire_progress = advanced;
            if (advanced > 1.0f)
                movement_fire_progress = 0.0f;
        } else if (*((unsigned char*)emitter_game + 0xa854)) {
            if (*((unsigned char*)emitter_game + 0xff25d0)) {
                if ((*(HighScoreRecord**)((char*)emitter_game + 0xff25d4))
                        ->run_records[*(int*)((char*)emitter_game + 0xff25dc)]
                        .flags
                    & 1) {
                    play_movement_state_sound();
                    update_movement_flag_emitters(this);
                    movement_fire_progress = movement_fire_progress_step + 0.30000001f;
                } else if ((*(HighScoreRecord**)((char*)emitter_game + 0xff25d4))
                               ->run_records[*(int*)((char*)emitter_game + 0xff25dc)]
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

    ((RowEventDisplay*)((char*)game + 0x12727d8))->update_row_event_display();
    Game* tick_game = game;
    *(int*)((char*)tick_game + 0xfd2b7c) = *(int*)((char*)tick_game + 0xfd2b7c) + 1;
    Game* cursor_game = game;
    *(int*)((char*)cursor_game + 0xff25dc) = *(int*)((char*)cursor_game + 0xff25dc) + 1;
    Game* times_game = game;
    if (*(int*)((char*)times_game + 0xff25dc) == 21000)
        ((TimesUp*)((char*)times_game + 0x1272828))->show_times_up_message();
    ((TimesUp*)((char*)game + 0x1272828))->update_times_up();
}
