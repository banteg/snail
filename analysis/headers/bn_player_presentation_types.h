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
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef short int16_t;

/* Empty C++ cRPathManager occupies one byte in the Windows root layout. */
typedef struct PathManager {
    uint8_t _empty;
} PathManager;

struct Player;
struct Path;
struct TrackRowCell;
struct TrackAttachmentRuntimeRow;
struct SubSegment;
struct PlayerControlSource;
struct Snail;
struct Object;
struct SubgameRuntime;
typedef struct TransformMatrix TransformMatrix;
typedef struct Sprite Sprite;
typedef struct FrontendWidget FrontendWidget;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color4f {
    float r;
    float g;
    float b;
    float a;
} Color4f;

typedef struct BodNode BodNode;
struct BodNode {
    void* vtable;
    uint32_t list_flags;
    BodNode* list_prev;
    BodNode* list_next;
};

typedef struct BodBase {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
} BodBase;

/* Two authored cRBanner actors are embedded at SubgameRuntime +0x359080. */
typedef struct Banner {
    BodBase bod;
    int32_t visibility_mode;
    uint8_t _pad_3c[0x54 - 0x3c];
    struct Player* owner_player;
    float phase;
    float phase_step;
} Banner;

typedef struct BannerPool {
    Banner slots[2];
} BannerPool;

/* Exact 0x94-byte Windows cRVapour owner. */
typedef struct Vapour {
    void* vtable;
    int32_t flags;
    uint8_t _pad_08[0x24 - 0x08];
    struct Object* owner;
    uint8_t _pad_28[0x80 - 0x28];
    int32_t point_count;
    int32_t capacity;
    union {
        int32_t half_width_bits;
        float half_width;
    };
    float* z_floor;
    TransformMatrix* points;
} Vapour;

/* Exact 0x19c-byte Windows cRJetPack singleton. */
typedef struct JetPack {
    BodNode bod;
    Vec3 world_position;
    uint8_t _pad_1c[0x38 - 0x1c];
    int32_t state;
    struct Player* owner;
    uint8_t _pad_40[0x44 - 0x40];
    struct SubgameRuntime* owner_game;
    uint8_t _pad_48[0x64 - 0x48];
    Sprite* sprite;
    struct TrackRowCell* source_cell;
    float bob_phase;
    float bob_phase_step;
    Vapour vapour_a;
    Vapour vapour_b;
} JetPack;

typedef struct FringeObject {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
} FringeObject;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

typedef struct SnailVisual {
    uint8_t _pad_00[0x10];
    uint32_t flags;
    uint8_t _pad_14[0x4];
    int32_t material_index;
    uint8_t _pad_1c[0x64];
    float follow_lateral_response;
    float squidge_primary;
    float squidge_secondary;
} SnailVisual;

typedef struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
} TransformMatrix;

typedef struct RenderableBod {
    BodBase bod;
    TransformMatrix transform;
} RenderableBod;

typedef struct Time {
    float total_seconds;
    int32_t minutes;
    int32_t seconds;
    int32_t display_hundredths;
    int32_t display_thousandths;
    float second_fraction;
} Time;

typedef struct SelectedLevelReplaySample {
    int16_t lateral_x;
    int16_t delta_z;
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

typedef struct Tutorial {
    int32_t state;
    int32_t _pad_04;
    int32_t _pad_08;
    void* game;
    uint8_t _pad_10[0xc];
} Tutorial;

typedef struct Completion {
    void* widget_a;
    void* delivered_count_widget;
    void* bonus_widget;
    void* widget_d;
    void* continue_widget;
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
} Completion;

/* Authored empty cRProgressBar at Player +0x3f0. */
typedef struct ProgressBar {
    uint8_t _empty;
} ProgressBar;

/* Authored cRWarning, exact 0x10-byte Windows owner at Player +0x3f4. */
typedef struct Warning {
    int32_t state;
    float phase;
    float phase_step;
    FrontendWidget* border;
} Warning;

typedef struct TimesUp {
    int32_t state;
    FrontendWidget* border;
    float progress;
    float progress_step;
} TimesUp;

/* Authored cRCameraman, exact 0xd8-byte follow-camera owner. */
typedef struct Cameraman {
    TransformMatrix live_matrix;
    TransformMatrix desired_matrix;
    TransformMatrix previous_desired_matrix;
    struct Player* player;
    struct SubgameRuntime* game;
    float fov_degrees;
    uint8_t unresolved_cc;
    uint8_t _pad_cd[0x3];
    float attachment_lift_envelope;
    float smoothed_attachment_lift_envelope;
} Cameraman;

typedef struct Path {
    uint8_t _pad_00[0x24];
    void* strip_mesh;
    uint8_t _pad_28[0x10];
    int32_t kind;
    uint8_t is_mirrored_x;
    uint8_t _pad_3d[0x3];
    uint32_t side_exit_mode;
    uint32_t segment_count;
    uint32_t row_span_count;
    float segment_count_f;
    float width_or_scale;
    uint32_t width_cells;
    void* primary_samples;
    void* secondary_samples;
    uint8_t _pad_60[0x38];
    float installed_heading_delta;
    uint8_t has_entry_mesh_transition;
    uint8_t _pad_9d[0x3];
    void* entry_transition_strip_mesh;
    void* entry_base_strip_mesh;
} Path;

typedef struct PathPair {
    Path primary;
    Path secondary;
} PathPair;

typedef struct TrackRowCell {
    BodNode bod;
    Vec3 anchor_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
    struct Path* attachment_template_record;
    uint8_t tile_id;
    uint8_t tile_flags_3d;
    uint8_t _pad_3e[0x2];
    uint32_t lane_and_flags;
    FringeObject* fringe_front;
    FringeObject* fringe_right;
    FringeObject* fringe_left;
    FringeObject* fringe_back;
} TrackRowCell;

/* Authored cross-port name retained as an alias for the Windows 0x54 layout. */
typedef TrackRowCell SubLoc;

typedef struct TrackAttachmentRuntimeRow {
    uint32_t flags;
    RenderableBod primary_body;
    uint8_t _pad_7c[0x8];
    Vec3 authored_object_velocity;
    Vec3 projection_payload;
    int32_t parcel_set_id;
    int32_t attachment_template_index;
    TrackRowCell* primary_attachment_cell;
    TrackRowCell* secondary_attachment_cell;
    float installed_heading_delta;
    BodBase attachment_body;
    float ring_speed;
    struct SubSegment* source_segment;
    int32_t row_event_id;
} TrackAttachmentRuntimeRow;

typedef struct PlayerControlSource {
    uint8_t _pad_00[0x4];
    uint32_t control_flags_a;
    uint8_t _pad_08[0x4];
    uint32_t control_flags_b;
    uint8_t _pad_10[0x18];
    float steering_x;
} PlayerControlSource;

typedef struct ObjectAnimation {
    uint16_t flags;
    uint8_t _pad_02[0x2];
    int32_t generated_frame_count;
    void* frames;
    float progress;
    float progress_step;
} ObjectAnimation;

/* Authored cRAnimManager, exact 0x48-byte queued animation owner. */
typedef struct AnimManager {
    int32_t state;
    float progress;
    float progress_step;
    ObjectAnimation* active_animation;
    uint8_t completed;
    uint8_t _pad_11[0x3];
    int32_t queued_animations[10];
    int32_t queue_count;
    void* target_model;
    uint8_t* animation_slot_base_minus_24;
} AnimManager;

typedef struct PresentationAnimationChannel {
    void* vtable;
    uint32_t visual_flags;
    uint8_t _pad_08[0x1c];
    struct SnailVisual* visual_root;
    uint8_t _pad_28[0x10];
    TransformMatrix live_matrix;
    void* active_anim_manager;
    uint8_t _pad_7c[0x88];
    int32_t selected_state;
    AnimManager anim_manager;
    uint8_t _pad_150[0x24];
    uint8_t animation_slot_table[0x25c];
    Vec3 release_step;
} PresentationAnimationChannel;

/* Authored cRSnailSkin, exact 0x20-byte material-selection owner. */
typedef struct SnailSkin {
    int32_t selected_slot;
    int32_t slot_ids[3];
    struct Snail* owner_snail;
    int32_t active;
    float progress;
    float progress_step;
} SnailSkin;

/* Authored cRDamageGuage, exact 0x2c contact-damage owner. */
typedef struct DamageGuage {
    int32_t state;
    float pulse_progress;
    float pulse_step;
    uint8_t unresolved_byte_0c;
    uint8_t _pad_0d[0x3];
    float warning_transition_progress;
    float warning_transition_step;
    int32_t skin_hold_ticks;
    float fill;
    float display_fill;
    float hit_flash_progress;
    float hit_flash_step;
} DamageGuage;

typedef struct JetParticleSlot {
    Sprite* sprite;
    float wobble_x;
    float wobble_y;
    float wobble_alpha;
} JetParticleSlot;

/* Authored cRSubHover, exact 0x214-byte hover and jet-VFX owner. */
typedef struct SubHover {
    float progress;
    float progress_step;
    uint8_t _pad_08[0x4];
    int32_t state;
    struct Player* player;
    float wobble_x;
    float wobble_y;
    float wobble_alpha;
    JetParticleSlot particle_slots[30];
    struct SubgameRuntime* game;
    uint8_t _pad_204[0x8];
    float warning_intensity_latch;
    float warning_intensity;
} SubHover;

/* Authored cRNuke, exact 0x7c-byte collision-ring effect owner. */
typedef struct Nuke {
    int32_t state;
    struct Player* owner_player;
    float orbit_center_z_step;
    float orbit_center_z;
    float orbit_phase;
    float orbit_phase_step;
    Sprite* sprite_slots[25];
} Nuke;

/* Authored empty cRFireWork; an empty C++ child occupies one byte. */
typedef struct FireWork {
    uint8_t _empty;
} FireWork;

/* Authored cRClickStart, exact 0xac-byte RenderableBod child. */
typedef struct ClickStart {
    RenderableBod bod;
    uint8_t _pad_78[0x8];
    int32_t state;
    FrontendWidget* prompt;
    float teardown_progress;
    float teardown_progress_step;
    uint8_t _pad_90[0x8];
    struct Player* player;
    uint8_t _pad_9c[0xc];
    uint8_t hide_prompt;
    uint8_t _pad_a9[0x3];
} ClickStart;

typedef struct TipData {
    uint32_t flags;
    float layout_y;
    float text_scale;
    float dismiss_seconds;
    char* text;
} TipData;
typedef TipData TipMessageDefinition;

typedef struct Tip {
    int32_t active;
    int32_t previous_outer_owner;
    TipData* definition;
    void* widget_main;
    void* widget_ok;
    void* widget_disable;
    float dismiss_progress;
    float dismiss_step;
} Tip;
typedef Tip TipSlot;

typedef struct TipManager {
    BodBase bod;
    Tip tips[3];
} TipManager;

typedef struct PlayerRowEventState {
    int32_t id;
    TipData tip_definition;
} PlayerRowEventState;

typedef struct PresentationWobbleController {
    float roll_phase;
    float roll_phase_step;
    float lift_phase;
    float lift_phase_step;
    uint8_t _pad_10[0x38];
} PresentationWobbleController;

/* Authored cRInvincible, exact 0xa4-byte spinning shell visual owner. */
typedef struct Invincible {
    void* vtable;
    uint8_t _pad_04[0x24];
    Color4f color;
    TransformMatrix transform;
    uint8_t _pad_78[0x8];
    int32_t state;
    float spin_phase;
    float spin_phase_step;
    float fade_progress;
    float fade_step;
    uint8_t _pad_94[0x4];
    float cutscene_roll_progress;
    float cutscene_roll_step;
    uint8_t channel_release_steps_active;
    uint8_t _pad_a1[0x3];
} Invincible;

typedef struct FollowState {
    uint8_t active;
    uint8_t _pad_01[0x3];
    struct Path* template_record;
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

/* Authored cRSquidge, exact 0x18-byte two-axis spring oscillator. */
typedef struct Squidge {
    float y_output;
    float y_velocity;
    float y_phase;
    float z_output;
    float z_velocity;
    float z_phase;
} Squidge;

/* Authored cRCutScene, exact 0x5c-byte camera state-machine owner. */
typedef struct CutScene {
    struct Snail* presentation;
    struct Player* player;
    int32_t camera_mode;
    int32_t state;
    TransformMatrix live_matrix;
    float progress;
    float progress_step;
    uint8_t force_camera_update;
    uint8_t _pad_59[0x3];
} CutScene;

/* Authored cRSnail, exact 0x19b4-byte Player presentation owner. */
typedef struct Snail {
    void* vtable;
    uint32_t visual_flags;
    uint8_t _pad_08[0x1c];
    struct SnailVisual* visual_root;
    uint8_t _pad_28[0x10];
    TransformMatrix live_matrix;
    uint8_t _pad_78[0x8];
    TransformMatrix previous_live_matrix;
    TransformMatrix cached_cutscene_matrix;
    struct Player* owner_player;
    AnimManager anim_manager;
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
    Invincible invincible_shell;
    SnailSkin snail_skin;
    CutScene cutscene;
} Snail;

typedef struct GolbShot {
    uint8_t _pad_000[0x244];
    int32_t state;
    uint8_t _pad_248[0xa0];
} GolbShot;

typedef struct Player {
    uint8_t _pad_00[0x38];
    TransformMatrix live_matrix;
    uint8_t _pad_78[0x8];
    int32_t resurrect_final_loss;
    int32_t resurrect_active;
    uint8_t _pad_88[0x4];
    float resurrect_progress;
    float resurrect_progress_step;
    uint8_t _pad_94[0x4];
    Sprite* ghost_sprite_a;
    Sprite* ghost_sprite_b;
    ClickStart click_start;
    uint8_t row_event_cutscene_started;
    uint8_t _pad_14d[0x3];
    Nuke nuke;
    int32_t movement_sound_variant_sample;
    FireWork firework;
    uint8_t _pad_1d1[0x3];
    float damage_retrigger_timer;
    float damage_retrigger_step;
    float surface_reaction_timer;
    float surface_reaction_step;
    uint8_t trampoline_bounce_active;
    uint8_t _pad_1e5[0x3];
    PlayerRowEventState row_event;
    Cameraman cameraman;
    uint8_t control_override_active;
    uint8_t _pad_2d9[0x3];
    float cutscene_pitch_cycle;
    float cutscene_pitch_cycle_step;
    int32_t total_score;
    Time stopwatch;
    int32_t score_tail;
    int32_t startup_track_index;
    int32_t movement_flag_selector;
    uint8_t _pad_30c[0x4];
    int32_t score_buckets[0x6];
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
    float nuke_effect_progress;
    float nuke_effect_progress_step;
    float last_ring_spawn_z;
    int32_t player_slot;
    FollowState follow_state;
    DamageGuage damage_gauge;
    ProgressBar progress_bar;
    uint8_t _pad_3f1[0x3];
    Warning warning;
    int32_t lives;
    struct SubgameRuntime* game;
    int32_t movement_mode_selector;
    Vec3 velocity;
    uint8_t boost_one_tick;
    uint8_t attachment_exit_pending;
    uint8_t _pad_41e[0x6];
    float attachment_exit_anchor_z;
    uint8_t _pad_428[0x4];
    float post_follow_exit_roll;
    int32_t post_follow_heading_carryover;
    float attachment_exit_progress;
    float attachment_exit_progress_step;
    struct PlayerControlSource* control_source;
    uint8_t completion_handoff_active;
    uint8_t _pad_441[0x3];
    float completion_handoff_timer;
    float completion_handoff_timer_step;
    uint8_t attachment_exit_gate_a;
    uint8_t attachment_exit_gate_b;
    uint8_t completion_handoff_voice_gate;
    uint8_t _pad_44f[0x1];
    GolbShot golb_shots[0xc];
    float movement_fire_progress;
    float movement_fire_progress_step;
    float slide_extension_threshold_z;
    float track_z_offset;
    float track_z_anchor;
    float completion_handoff_cycle_progress;
    float completion_handoff_cycle_step;
    uint8_t _pad_274c[0x4];
    SubHover sub_hover;
    Vec3 cached_camera_target_world;
    int32_t steering_mode_selector;
    uint8_t _pad_2974[0xc];
    float interaction_max_z;
    Snail presentation;
    int32_t parcels_collected;
    uint8_t _pad_433c[0x4];
    int32_t visible_life_stock;
    Squidge squidge;
    float slow_commentary_timer;
    float slow_commentary_step;
} Player;

#endif
