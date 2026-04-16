#ifndef BN_PLAYER_PRESENTATION_TYPES_H
#define BN_PLAYER_PRESENTATION_TYPES_H

/*
 * Narrow Binary Ninja type-import slice derived from path_template_types.h.
 *
 * Keep this focused on the presentation/controller surface that the BN bridge
 * can ingest quickly; the broader checked-in header stays authoritative for
 * full layout recovery and IDA sync.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef short int16_t;

struct Player;
struct SnailVisual;
struct PathTemplate;
struct TrackRowCell;
struct PlayerControlSource;
struct PlayerPresentationController;
typedef struct RowEventDisplayController RowEventDisplayController;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

typedef struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
} TransformMatrix;

typedef struct SelectedLevelReplaySample {
    int16_t lateral_x;
    int16_t secondary_lane_raw;
    uint8_t flags;
    uint8_t _pad_05;
} SelectedLevelReplaySample;

typedef struct SelectedLevelRecord {
    uint32_t active;
    uint32_t score;
    uint8_t _pad_08[0x20];
    uint32_t replay_level_index;
    uint32_t replay_mode_id;
    uint8_t _pad_30[0x8];
    uint32_t runtime_build_flags;
    uint8_t _pad_3c[0xc];
    float replay_speed_scalar;
    uint32_t challenge_speed_value;
    uint32_t challenge_difficulty_value;
    char name[0x14];
    uint32_t runtime_build_seed;
    uint32_t replay_sample_count;
    SelectedLevelReplaySample replay_samples[1];
} SelectedLevelRecord;

typedef struct RowEventDisplayController {
    void* widget_a;
    void* widget_b;
    void* widget_c;
    void* widget_d;
    void* widget_e;
    int32_t state;
    uint8_t gate_18;
    uint8_t _pad_19[0x3];
    int32_t parcel_target_count;
    int32_t bonus_enabled;
    int32_t staged_parcel_count;
    int32_t delivered_parcel_count;
    float progress;
    float progress_step;
    float widget_world_x;
    float widget_world_y;
    float widget_world_z;
    float bonus_blink_progress;
    float bonus_blink_step;
    int32_t bonus_score;
    int32_t display_token;
} RowEventDisplayController;

typedef struct Game {
    uint8_t _pad_00[0x34];
    float challenge_difficulty_scalar;
    float track_center_x;
    uint8_t _pad_3c[0x4];
    int32_t level_mode;
    int32_t level_mode_arg;
    float base_subgame_rate;
    uint32_t runtime_flags;
    int32_t first_block_row_count;
    int32_t runtime_row_count;
    int32_t completion_row_start;
    uint8_t _pad_54[0xa800];
    uint8_t track_state_latch;
    uint8_t _pad_a855[0xfe7d7b];
    uint8_t selected_level_record_active;
    uint8_t selected_level_record_persistent;
    uint8_t _pad_ff25d2[0x2];
    SelectedLevelRecord* selected_level_record;
    int32_t selected_level_record_saved_return_owner;
    int32_t runtime_track_index;
    uint8_t _pad_ff25e0[0x2801f8];
    RowEventDisplayController row_event_display;
} Game;

typedef struct PathTemplate {
    uint8_t _pad_00[0x38];
    int32_t kind;
    uint8_t _pad_3c[0x10];
    float segment_count_f;
} PathTemplate;

typedef struct TrackRowCell {
    uint8_t _pad_00[0x10];
    Vec3 anchor_position;
    uint8_t _pad_1c[0x1c];
    struct PathTemplate* attachment_template_record;
    uint8_t tile_id;
    uint8_t tile_flags_3d;
} TrackRowCell;

typedef struct PlayerControlSource {
    uint8_t _pad_00[0x4];
    uint32_t control_flags_a;
    uint8_t _pad_08[0x4];
    uint32_t control_flags_b;
    uint8_t _pad_10[0x18];
    float steering_x;
} PlayerControlSource;

typedef struct AnimationDispatchState {
    int32_t active;
    float progress;
    float progress_step;
    void* active_keyframe;
    uint8_t edge_latched;
    uint8_t _pad_11[0x3];
    int32_t queued_animation_ids[10];
    int32_t queued_animation_count;
    void* self_ref;
    void* queue_sentinel;
} AnimationDispatchState;

typedef struct PresentationAnimationChannel {
    uint8_t _pad_00[0x4];
    uint32_t visual_flags;
    uint8_t _pad_08[0x1c];
    struct SnailVisual* visual_root;
    uint8_t _pad_28[0x10];
    TransformMatrix live_matrix;
    void* active_anim_manager;
    uint8_t _pad_7c[0x88];
    int32_t selected_state;
    AnimationDispatchState anim_manager;
    uint8_t _pad_150[0x24];
    uint8_t animation_slot_table[0x25c];
    Vec3 release_step;
} PresentationAnimationChannel;

typedef struct SnailSkinTransitionState {
    int32_t selected_slot;
    int32_t slot_ids[3];
    void* owner_render_state;
    int32_t active;
    float progress;
    float progress_step;
} SnailSkinTransitionState;

typedef struct PresentationWobbleController {
    float roll_phase;
    float roll_phase_step;
    float lift_phase;
    float lift_phase_step;
    uint8_t _pad_10[0x38];
} PresentationWobbleController;

typedef struct InvincibleShellController {
    uint8_t _pad_00[0x80];
    int32_t state;
    float spin_phase;
    float spin_phase_step;
    float fade_progress;
    float fade_step;
    uint8_t _pad_90[0x10];
} InvincibleShellController;

typedef struct FollowState {
    uint8_t active;
    uint8_t _pad_01[0x3];
    struct PathTemplate* template_record;
    struct TrackRowCell* source_cell;
    uint32_t sample_index;
    float progress;
    float vertical_offset;
    float orientation_a;
    float orientation_b;
    float orientation_c;
    float orientation_d;
    float orientation_e;
    Vec3 output_position;
    struct Player* player;
    uint8_t _pad_3c[0x4];
} FollowState;

typedef struct SquidgeState {
    float y_output;
    float y_velocity;
    float y_phase;
    float z_output;
    float z_velocity;
    float z_phase;
} SquidgeState;

typedef struct CutsceneAI {
    struct PlayerPresentationController* presentation;
    struct Player* player;
    int32_t unresolved_08;
    int32_t state;
    TransformMatrix live_matrix;
    float progress;
    float progress_step;
    uint8_t unresolved_58;
    uint8_t _pad_59[0xb];
} CutsceneAI;

typedef struct PlayerPresentationController {
    uint8_t _pad_00[0x4];
    uint32_t visual_flags;
    uint8_t _pad_08[0x1c];
    struct SnailVisual* visual_root;
    uint8_t _pad_28[0x10];
    TransformMatrix live_matrix;
    uint8_t _pad_78[0x8];
    TransformMatrix previous_live_matrix;
    TransformMatrix cached_cutscene_matrix;
    struct Player* owner_player;
    AnimationDispatchState anim_manager;
    uint8_t _pad_14c[0x500];
    PresentationAnimationChannel weapon_channels[3];
    PresentationAnimationChannel jetpack_channel;
    PresentationWobbleController wobble;
    TransformMatrix snail_hotspot_source_matrix_a;
    uint8_t _pad_1644[0x40];
    TransformMatrix snail_hotspot_source_matrix_b;
    uint8_t _pad_16c4[0x8];
    Vec3 snail_hotspots_local[19];
    Vec3 snail_hotspots_world[19];
    InvincibleShellController invincible_shell;
    SnailSkinTransitionState snail_skin_transition;
    CutsceneAI cutscene_ai;
} PlayerPresentationController;

typedef struct Player {
    uint8_t _pad_00[0x38];
    TransformMatrix live_matrix;
    uint8_t _pad_78[0x8];
    int32_t resurrect_final_loss;
    int32_t flag84;
    uint8_t _pad_88[0x4];
    float resurrect_progress;
    float resurrect_progress_step;
    uint8_t _pad_94[0x8c];
    int32_t movement_state;
    uint8_t unresolved_pre_row_event[0x28];
    uint8_t row_event_cutscene_started;
    uint8_t _pad_14d[0x18b];
    uint8_t control_override_active;
    uint8_t _pad_2d9[0x3];
    float cutscene_pitch_cycle;
    float cutscene_pitch_cycle_step;
    uint8_t _pad_2e4[0x24];
    int32_t movement_flag_selector;
    uint8_t _pad_30c[0x1c];
    float barrier_hold_progress;
    float barrier_hold_step;
    float startup_voice_timer;
    float startup_voice_step;
    uint32_t movement_flags;
    uint32_t previous_movement_flags;
    uint8_t _pad_340[0x10];
    int32_t lane_lean_state;
    float lane_lean_amplitude;
    float lane_lean_progress;
    float lane_lean_progress_step;
    uint8_t _pad_360[0x10];
    float heading_roll;
    uint8_t _pad_374[0x10];
    FollowState follow_state;
    uint8_t _pad_3c4[0x44];
    struct Game* game;
    int32_t movement_mode_selector;
    Vec3 velocity;
    uint8_t _pad_41c[0x1];
    uint8_t attachment_exit_pending;
    uint8_t _pad_41e[0x2];
    float attachment_exit_anchor_z;
    uint8_t _pad_424[0x8];
    float post_follow_value_a;
    float post_follow_value_b;
    float attachment_exit_progress;
    float attachment_exit_progress_step;
    struct PlayerControlSource* control_source;
    int32_t completion_handoff_active;
    float completion_handoff_timer;
    float completion_handoff_timer_step;
    uint8_t attachment_exit_gate_a;
    uint8_t attachment_exit_gate_b;
    uint8_t completion_handoff_voice_gate;
    uint8_t _pad_44f[0x22e1];
    float movement_progress;
    float movement_rate_scalar;
    uint8_t _pad_2738[0x4];
    float track_z_offset;
    float track_z_anchor;
    uint8_t _pad_2744[0x220];
    Vec3 cached_camera_target_world;
    int32_t steering_mode_selector;
    uint8_t _pad_2974[0xc];
    float interaction_max_z;
    PlayerPresentationController presentation;
    int32_t visible_life_stock;
    SquidgeState squidge;
    float slow_commentary_timer;
    float slow_commentary_step;
} Player;

#endif
