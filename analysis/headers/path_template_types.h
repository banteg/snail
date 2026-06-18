#ifndef PATH_TEMPLATE_TYPES_H
#define PATH_TEMPLATE_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef int int32_t;

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

typedef struct Color4f {
    float r;
    float g;
    float b;
    float a;
} Color4f;

typedef struct ColorBGRA8 {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
} ColorBGRA8;

typedef struct BodNode {
    void* vtable;
    uint32_t list_flags;
    struct BodNode* list_prev;
    struct BodNode* list_next;
} BodNode;

typedef struct BodBase {
    BodNode bod;
    Vec3 position;
    int32_t render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
} BodBase;

typedef struct FringeObject {
    BodNode bod;
    Vec3 position;
    int32_t render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
} FringeObject;

typedef struct Sprite Sprite;
typedef struct Player Player;
typedef struct Game Game;
typedef struct PlayerPresentationController PlayerPresentationController;
typedef struct FrontendWidget FrontendWidget;
typedef struct FrontendWidgetTooltip FrontendWidgetTooltip;
typedef struct FrontendWidgetTextBuffer FrontendWidgetTextBuffer;

typedef struct FrontendWidgetTextBuffer {
    uint8_t raw[0x420];
} FrontendWidgetTextBuffer;

typedef struct FrontendWidgetTooltip {
    uint8_t _pad_00[0x4];
    int32_t state;
    uint32_t mode_flags;
    FrontendWidget* owner_widget;
    float delay_progress;
    float delay_step;
    FrontendWidget* tooltip_widget;
    uint8_t _pad_1c[0x1c];
    FrontendWidget* owner_widget_38;
    uint8_t _pad_3c[0x4];
} FrontendWidgetTooltip;

typedef struct FrontendWidget {
    uint8_t _pad_00[0x4];
    uint32_t list_flags;
    FrontendWidget* list_prev;
    FrontendWidget* list_next;
    uint8_t _pad_10[0x3c];
    float authored_left;
    float authored_top;
    float authored_width;
    float authored_height;
    uint8_t state_5c;
    uint8_t _pad_5d[0x3];
    int32_t background_texture_id;
    uint8_t _pad_64[0x18];
    int32_t widget_type;
    uint8_t _pad_80[0xfc];
    float slider_position_target;
    float slider_position_current;
    float slider_hit_left;
    float slider_hit_right;
    float slider_hit_top;
    float slider_hit_bottom;
    int32_t shortcut_key_code;
    uint8_t _pad_198[0x8];
    uint32_t widget_flags;
    uint32_t previous_widget_flags;
    uint8_t _pad_1a8[0x4];
    Color4f current_fill_color;
    Color4f idle_fill_color;
    Color4f hot_fill_color;
    Color4f current_text_color;
    Color4f idle_text_color;
    Color4f hot_text_color;
    float hover_blend_target;
    float hover_blend_current;
    float idle_padding;
    float hot_padding;
    float target_padding;
    float current_padding;
    float text_effect_target;
    float text_effect_current;
    float render_inset_delta;
    float render_inset_base;
    uint8_t render_inset_dynamic;
    uint8_t _pad_235[0x3];
    float layout_left;
    float layout_top;
    float clamped_left;
    float clamped_top;
    float layout_width;
    float layout_height;
    uint8_t _pad_250[0x8];
    float border_edge;
    int32_t text_alignment;
    float anchor_x;
    float aux_progress;
    float aux_step;
    float stack_gap;
    int32_t texture_id_270;
    uint8_t _pad_274[0x4];
    int32_t mouse_settle_frames;
    float previous_mouse_x;
    float previous_mouse_y;
    uint8_t _pad_284[0x8];
    FrontendWidgetTooltip tooltip;
    FrontendWidgetTextBuffer text_buffer;
    int32_t font_id;
    float font_scale;
    float layout_anchor_x;
    float layout_anchor_y;
    uint8_t _pad_6fc[0x1c];
    FrontendWidget* slider_less_widget;
    FrontendWidget* slider_more_widget;
    FrontendWidget* slider_value_widget;
} FrontendWidget;

typedef struct TextureRef {
    uint32_t flags;
    uint8_t _pad_04[0x8];
    char name[0x8c - 0x0c];
    int32_t slot_index;
    int32_t frame_count;
    float frame_progress_step;
    void* texture_ref;
    uint8_t _pad_9c[0x4];
    int32_t unknown_a0;
} TextureRef;

/*
 * Warning actor controller. Native functions: initialize_warning @ 0x446e80,
 * start_warning @ 0x446f30, stop_warning @ 0x446f50, update_warning @ 0x446f80,
 * uninit_warning @ 0x446f10. State machine: 0 = idle, 1 = solid (phase=1s), 2 = fade.
 */
typedef struct WarningActor {
    int32_t state;
    float progress;
    float progress_step;
    FrontendWidget* border;
} WarningActor;

/*
 * TimesUp countdown actor, lives on the Game struct at +0x1272828. Native
 * functions: update_times_up @ 0x445e20, uninit_times_up @ 0x445e70.
 */
typedef struct TimesUpController {
    int32_t state;
    FrontendWidget* border;
    float progress;
    float progress_step;
} TimesUpController;

/*
 * Stopwatch tick counter. Native advance_timer_counters @ 0x441b90 increments
 * total_seconds and second_fraction by `delta_ticks * (1/60)`, rolling frames
 * into minutes and publishing hundredths / thousandths for the HUD.
 */
typedef struct Stopwatch {
    float total_seconds;
    int32_t minutes;
    int32_t frames_into_second;
    int32_t display_hundredths;
    int32_t display_thousandths;
    float second_fraction;
} Stopwatch;

/*
 * Voice manager bank. Holds 16 `cRVoiceSet` playlists (Damage, Dying, Enemies,
 * Fall, Misc, PowerUp, Slow, Start, Victory, Ouch, Package, Slugged, WormTunnel,
 * Tutorial, Postal, SuperTramp). Shared instance is the global at 0x751498.
 * Native functions: initialize_voice_manager @ 0x448ee0, play_voice_manager
 * @ 0x4492d0, initialize_voice_set @ 0x448df0, play_voice_set @ 0x449260.
 */
typedef struct VoiceSet {
    uint32_t sample_count;
    uint32_t next_index;
    int32_t* playlist;
    int32_t* bites;
    float cooldown;
    float cooldown_step;
} VoiceSet;

typedef struct VoiceManager {
    VoiceSet sets[16];
    float global_progress;
    float global_frequency_seconds;
} VoiceManager;

/*
 * Salt hazard runtime slot. Pool lives at `game + 0x3578c0` with 40 slots and
 * stride 0x98. The real updater uses the owner-game pointer plus an in-slot
 * fade alpha; spawn still seeds the y velocity lane and low armed byte.
 * Native functions: initialize_salt_hazard_pool @ 0x441540, spawn_salt_hazard
 * @ 0x441560, update_salt_hazard @ 0x441c10.
 */
typedef struct SaltHazardSlot {
    uint8_t _pad_00[0x68];
    Vec3 world_position;
    uint8_t _pad_74[0xc];
    uint32_t active;
    uint8_t _pad_84[0x4];
    struct Game* owner_game;
    float fade_alpha;
    float spawn_velocity_y;
    uint32_t armed_substate;
} SaltHazardSlot;

/*
 * SubLazer projectile runtime slot. Pool lives at `game + 0x356b00` with 20
 * slots and stride 0xb0. Each slot is a live projectile fired by Wall2 tile
 * emitters via `shoot_subgoldy`. Native functions: initialize_sub_lazer_pool
 * @ 0x441650, spawn_sub_lazer_projectile @ 0x441670,
 * deactivate_sub_lazer_projectile @ 0x441740, update_sub_lazer_projectile
 * @ 0x4417d0.
 */
typedef struct SubLazerSlot {
    uint8_t _pad_00[0x14];
    float sprite_bob_base_y;
    uint8_t _pad_18[0x20];
    uint8_t live_matrix_basis[0x2c];
    void* sprite;
    Vec3 live_position;
    uint8_t _pad_74[0xc];
    uint32_t state;
    uint8_t _pad_84[0x4];
    struct Game* owner_game;
    Vec3 velocity;
    float sprite_bob_phase;
    float sprite_bob_phase_step;
    uint8_t _pad_a0[0x10];
} SubLazerSlot;

typedef struct TextureRefList {
    int32_t count;
    int32_t capacity;
    TextureRef entries[1];
} TextureRefList;

typedef struct TrackRowCell {
    BodNode bod;
    Vec3 anchor_position;
    uint8_t _pad_1c[0x1c];
    struct PathTemplate* attachment_template_record;
    uint8_t tile_id;
    uint8_t tile_flags_3d;
    uint8_t _pad_3e[0x2];
    uint32_t lane_and_flags;
    FringeObject* fringe_front;
    FringeObject* fringe_right;
    FringeObject* fringe_left;
    FringeObject* fringe_back;
} TrackRowCell;

typedef struct TrackAttachmentRuntimeRow {
    uint32_t flags;
    uint8_t _pad_04[0x8c];
    Vec3 projection_payload;
    int32_t parcel_set_id;
    int32_t attachment_template_index;
    TrackRowCell* primary_attachment_cell;
    TrackRowCell* secondary_attachment_cell;
    uint8_t _pad_ac[0x4];
    BodBase aux_body;
    uint8_t _pad_e8[0x8];
    int32_t row_event_id;
} TrackAttachmentRuntimeRow;

typedef enum PathTemplateStripMeshFlags {
    PATH_TEMPLATE_STRIP_MESH_FLAG_HAS_VERTEX_COLOURS = 0x10000,
    PATH_TEMPLATE_STRIP_MESH_FLAG_IMPORTED_X_MESH = 0x100000,
} PathTemplateStripMeshFlags;

typedef enum PathTemplateKind {
    PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY = 0x00,
    PATH_TEMPLATE_KIND_LOOPTHELOOPW = 0x06,
    PATH_TEMPLATE_KIND_DETOUR = 0x0f,
    PATH_TEMPLATE_KIND_FAMILY_10 = 0x10,
    PATH_TEMPLATE_KIND_FAMILY_11 = 0x11,
    PATH_TEMPLATE_KIND_CAGE2 = 0x14,
    PATH_TEMPLATE_KIND_SCREW = 0x15,
    PATH_TEMPLATE_KIND_SLALOM = 0x16,
    PATH_TEMPLATE_KIND_SLALOMBIG = 0x17,
    PATH_TEMPLATE_KIND_WORM = 0x18,
    PATH_TEMPLATE_KIND_LOOPOUT = 0x19,
    PATH_TEMPLATE_KIND_SWEEP = 0x1c,
    PATH_TEMPLATE_KIND_SNAKE = 0x1d,
    PATH_TEMPLATE_KIND_SUPERTRAMP = 0x1f,
    PATH_TEMPLATE_KIND_DIP = 0x20,
    PATH_TEMPLATE_KIND_START = 0x24,
    PATH_TEMPLATE_KIND_TURNOVER = 0x25,
    PATH_TEMPLATE_KIND_TURNOVERDOUBLE = 0x26,
    PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY = 0x27,
    PATH_TEMPLATE_KIND_WIBBLE = 0x28,
    PATH_TEMPLATE_KIND_INVERT = 0x29,
    PATH_TEMPLATE_KIND_NONLINEAR_42 = 0x2a,
    PATH_TEMPLATE_KIND_TWISTER = 0x2b,
    PATH_TEMPLATE_KIND_TWISTER2 = 0x2d,
} PathTemplateKind;

typedef enum ObjectFaceQuadFlags {
    OBJECT_FACEQUAD_FLAG_NON_QUAD = 0x80,
} ObjectFaceQuadFlags;

typedef struct ObjectUv {
    float u;
    float v;
} ObjectUv;

typedef struct ObjectFaceQuad {
    uint8_t flags;
    uint8_t unknown_01;
    uint16_t vertex_0;
    uint16_t vertex_1;
    uint16_t vertex_2;
    uint16_t vertex_3;
    uint8_t _pad_0a[0x0c - 0x0a];
    TextureRef* texture_ref;
    ObjectUv uv[4];
} ObjectFaceQuad;

typedef struct PathTemplateStripMesh {
    uint8_t _pad_00[0x10];
    PathTemplateStripMeshFlags flags;
    uint8_t _pad_14[0x18];
    uint32_t vertex_count;
    uint8_t _pad_30[0x8];
    Vec3* vertices;
    uint8_t _pad_3c[0xc];
    Color4f* vertex_colours;
    uint8_t _pad_4c[0x8];
    uint32_t facequad_count;
    uint32_t facequad_capacity;
    ObjectFaceQuad* facequads;
} PathTemplateStripMesh;

typedef struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
} TransformMatrix;

typedef struct RenderObjectTextureGroups {
    uint8_t _pad_00[0xc0];
    void* vertex_buffer;
    int32_t vertex_count;
    void* index_buffer;
    int32_t* texture_group_ids;
    TextureRef** texture_group_texture_refs;
    int32_t* texture_group_primcounts;
} RenderObjectTextureGroups;

typedef struct TrackRenderGrid {
    uint8_t _pad_00[0x54];
    int32_t cell_count;
    uint8_t _pad_58[0x3bfa70];
    TrackRowCell cells[8];
} TrackRenderGrid;

typedef struct TrackRenderCacheSlot {
    uint8_t _pad_00[0x24];
    RenderObjectTextureGroups* render_object;
    int32_t vertex_count;
    uint8_t _pad_2c[0x10];
} TrackRenderCacheSlot;

typedef struct TrackRenderCacheManager {
    ColorBGRA8 clear_color;
    int32_t max_vertex_counts[5];
    int32_t max_index_counts[5];
    void* shared_vertex_buffers[5];
    void* shared_index_buffers[5];
    TrackRenderGrid* track_render_grid;
    TrackRenderCacheSlot slots[0x2cb];
    uint8_t _pad_a7bc[0x30];
    float build_cache_row_base;
    float next_cache_row_z;
    int32_t next_cache_row_index;
} TrackRenderCacheManager;

typedef struct CameramanState {
    TransformMatrix live_matrix;
    TransformMatrix desired_matrix;
    TransformMatrix previous_desired_matrix;
    Player* player;
    Game* game;
    float fov_degrees;
    uint8_t unresolved_cc;
    uint8_t _pad_cd[0x3];
    float attachment_lift_envelope;
    float smoothed_attachment_lift_envelope;
} CameramanState;

typedef struct DamageGaugeController {
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
} DamageGaugeController;

typedef struct JetParticleSlot {
    Sprite* sprite;
    float wobble_x;
    float wobble_y;
    float wobble_alpha;
} JetParticleSlot;

typedef struct JetpackGaugeController {
    float progress;
    float progress_step;
    uint8_t _pad_08[0x4];
    int32_t state;
    struct Player* player;
    float wobble_x;
    float wobble_y;
    float wobble_alpha;
    JetParticleSlot particle_slots[30];
    Game* game;
    uint8_t _pad_204[0x8];
    float warning_intensity_latch;
    float warning_intensity;
} JetpackGaugeController;

typedef struct SnailVisual {
    uint8_t _pad_00[0x10];
    uint32_t flags;
    uint8_t _pad_14[0x6c];
    float follow_lateral_response;
    float squidge_primary;
    float squidge_secondary;
} SnailVisual;

typedef struct CutsceneAI {
    PlayerPresentationController* presentation;
    Player* player;
    int32_t unresolved_08;
    int32_t state;
    TransformMatrix live_matrix;
    float progress;
    float progress_step;
    uint8_t unresolved_58;
    uint8_t _pad_59[0xb];
} CutsceneAI;

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
    SnailVisual* visual_root;
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

typedef struct PlayerPresentationController {
    uint8_t _pad_00[0x4];
    uint32_t visual_flags;
    uint8_t _pad_08[0x1c];
    SnailVisual* visual_root;
    uint8_t _pad_28[0x10];
    TransformMatrix live_matrix;
    uint8_t _pad_78[0x8];
    TransformMatrix previous_live_matrix;
    TransformMatrix cached_cutscene_matrix;
    Player* owner_player;
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

typedef struct GlobalJetpackPresentationController {
    uint8_t _pad_00[0x11e0];
    PresentationAnimationChannel jetpack_channel;
} GlobalJetpackPresentationController;

enum {
    PLAYER_CONTROL_FLAG_CONFIRM = 0x4000,
};

typedef struct PlayerControlSource {
    uint8_t _pad_00[0x4];
    uint32_t control_flags_a;
    uint8_t _pad_08[0x4];
    uint32_t control_flags_b;
    uint8_t _pad_10[0x18];
    float steering_x;
} PlayerControlSource;

typedef struct SquidgeState {
    float y_output;
    float y_velocity;
    float y_phase;
    float z_output;
    float z_velocity;
    float z_phase;
} SquidgeState;

typedef struct NukeController {
    int32_t state;
    Player* owner_player;
    float orbit_axis_step;
    float orbit_axis;
    float phase;
    float phase_step;
    void* sprite_slots[25];
} NukeController;

typedef struct TipMessageDefinition {
    uint32_t flags;
    float layout_y;
    float text_scale;
    float dismiss_seconds;
    char* text;
} TipMessageDefinition;

typedef struct TipSlot {
    int32_t active;
    int32_t previous_outer_owner;
    TipMessageDefinition* definition;
    void* widget_main;
    void* widget_ok;
    void* widget_disable;
    float dismiss_progress;
    float dismiss_step;
} TipSlot;

typedef struct TipManager {
    uint8_t _pad_00[0x38];
    TipSlot slots[3];
} TipManager;

typedef struct PlayerRowEventState {
    int32_t id;
    TipMessageDefinition tip_definition;
} PlayerRowEventState;

typedef struct TutorialController {
    int32_t state;
    int32_t _pad_04;
    int32_t _pad_08;
    void* game;
} TutorialController;

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
    uint8_t _pad_30[0x08];
    uint32_t runtime_build_flags;
    uint8_t _pad_3c[0x0c];
    float replay_speed_scalar;
    uint32_t challenge_speed_value;
    uint32_t challenge_difficulty_value;
    char name[0x14];
    uint32_t runtime_build_seed;
    uint32_t replay_sample_count;
    SelectedLevelReplaySample replay_samples[1];
} SelectedLevelRecord;

typedef struct Game {
    uint8_t _pad_00[0x34];
    float challenge_difficulty_scalar;
    float subgame_rate;
    int32_t subgame_state;
    int32_t level_mode;
    int32_t level_mode_arg;
    float base_subgame_rate;
    uint32_t runtime_flags;
    int32_t first_block_row_count;
    int32_t runtime_row_count;
    int32_t completion_row_start;
    uint8_t _pad_5c[0xa7f8];
    uint8_t track_state_latch;
    uint8_t _pad_a855[0x3];
    TutorialController tutorial;
    uint8_t _pad_a868[0xc];
    int32_t level_segment_count;
    uint8_t _pad_a878[0x69da9];
    uint8_t pause_gate;
    uint8_t _pad_74622[0xf7dfae];
    uint8_t selected_level_record_active;
    uint8_t selected_level_record_persistent;
    uint8_t _pad_ff25d2[0x2];
    SelectedLevelRecord* selected_level_record;
    int32_t selected_level_record_saved_return_owner;
    int32_t replay_update_cursor;
    uint8_t _pad_ff25e0[0x4];
    int32_t runtime_track_index;
    uint8_t _pad_ff25e8[0x2801f0];
    RowEventDisplayController row_event_display;
} Game;

typedef TransformMatrix PathTemplateTransform;

typedef struct PathTemplateSample {
    TransformMatrix transform;
    uint8_t _pad_40[0x40];
    Vec3 delta_dir_to_next;
    float delta_length;
    float center_x;
    float rotation_scalar_94;
    float rotation_scalar_98;
    float lateral_scale;
    float special_scalar;
    uint8_t _pad_a4[0x4];
} PathTemplateSample;

typedef struct PathTemplate {
    uint8_t _pad_00[0x24];
    PathTemplateStripMesh* strip_mesh;
    uint8_t _pad_28[0x8];
    float header_30;
    float header_34;
    PathTemplateKind kind;
    uint8_t is_mirrored_x;
    uint8_t _pad_3d[0x3];
    uint32_t side_exit_mode;
    uint32_t segment_count;
    uint32_t row_span_count;
    float segment_count_f;
    float width_or_scale;
    uint32_t width_cells;
    PathTemplateSample* primary_samples;
    PathTemplateSample* secondary_samples;
    uint8_t _pad_60[0x38];
    float installed_heading_delta;
    uint8_t special_runtime_flag_9c;
    uint8_t _pad_9d[0x3];
    float header_a0;
    float header_a4;
} PathTemplate;

typedef struct FollowState {
    uint8_t active;
    uint8_t _pad_01[0x3];
    PathTemplate* template_record;
    TrackRowCell* source_cell;
    uint32_t sample_index;
    float progress;
    float vertical_offset;
    float orientation_a;
    float orientation_b;
    float orientation_c;
    float orientation_d;
    float orientation_e;
    Vec3 output_position;
    Player* player;
    uint8_t _pad_3c[0x4];
} FollowState;

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
    uint8_t _pad_a0[0x80];
    int32_t movement_state;
    uint8_t unresolved_pre_row_event[0x28];
    uint8_t row_event_cutscene_started;
    uint8_t _pad_14d[0x3];
    NukeController nuke;
    int32_t movement_sound_variant_sample;
    uint8_t _pad_1d0[0x4];
    float damage_retrigger_timer;
    float damage_retrigger_step;
    float surface_reaction_timer;
    float surface_reaction_step;
    uint8_t _pad_1e4[0x4];
    PlayerRowEventState row_event;
    uint8_t _pad_200[0xd8];
    uint8_t control_override_active;
    uint8_t _pad_2d9[0x3];
    float cutscene_pitch_cycle;
    float cutscene_pitch_cycle_step;
    uint8_t _pad_2e4[0x24];
    int32_t movement_flag_selector;
    uint8_t _pad_30c[0x2c];
    uint32_t movement_flags;
    uint32_t previous_movement_flags;
    float barrier_hold_progress;
    float barrier_hold_step;
    float startup_voice_timer;
    float startup_voice_step;
    int32_t lane_lean_state;
    float lane_lean_amplitude;
    float lane_lean_progress;
    float lane_lean_progress_step;
    uint8_t _pad_360[0x10];
    float heading_roll;
    float nuke_effect_progress;
    float nuke_effect_progress_step;
    uint8_t _pad_37c[0x4];
    int32_t player_slot;
    FollowState follow_state;
    DamageGaugeController damage_gauge;
    uint8_t _pad_3f0[0x18];
    Game* game;
    int32_t movement_mode_selector;
    Vec3 velocity;
    uint8_t _pad_41c[0x1];
    uint8_t attachment_exit_pending;
    uint8_t _pad_41e[0x6];
    float attachment_exit_anchor_z;
    uint8_t _pad_428[0x4];
    float post_follow_exit_roll;
    int32_t post_follow_heading_carryover;
    float attachment_exit_progress;
    float attachment_exit_progress_step;
    PlayerControlSource* control_source;
    int32_t completion_handoff_active;
    float completion_handoff_timer;
    float completion_handoff_timer_step;
    uint8_t attachment_exit_gate_a;
    uint8_t attachment_exit_gate_b;
    uint8_t completion_handoff_voice_gate;
    uint8_t _pad_44f[0x22e1];
    float movement_fire_progress;
    float movement_fire_progress_step;
    uint8_t _pad_2738[0x4];
    float track_z_offset;
    float track_z_anchor;
    float completion_handoff_cycle_progress;
    float completion_handoff_cycle_step;
    uint8_t _pad_274c[0x4];
    JetpackGaugeController jetpack_gauge;
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

TextureRef* __thiscall get_or_create_texture_ref(TextureRefList* texture_list, char* texture_path, int32_t arg3, int16_t arg4);
void __fastcall allocate_path_template_samples(PathTemplate* self);
int32_t __fastcall finalize_path_template(PathTemplate* self);
int32_t __thiscall mirror_path_template_pair_x(PathTemplate* self, PathTemplate* source);
void __fastcall set_matrix_identity(TransformMatrix* transform);
void __fastcall set_matrix_rotation_identity(TransformMatrix* transform);
TransformMatrix* __thiscall initialize_matrix_from_values(
    TransformMatrix* transform,
    float m00,
    float m01,
    float m02,
    float m03,
    float m10,
    float m11,
    float m12,
    float m13,
    float m20,
    float m21,
    float m22,
    float m23,
    float m30,
    float m31,
    float m32,
    float m33
);
void __thiscall rotate_matrix_world_x(TransformMatrix* transform, float angle);
void __thiscall rotate_matrix_world_y(TransformMatrix* transform, float angle);
void __thiscall rotate_matrix_world_z(TransformMatrix* transform, float angle);
double __fastcall normalize_vector(Vec3* vector);
float __thiscall normalize_vector_from_source(Vec3* out, const Vec3* src);
int32_t __thiscall cross_vectors(Vec3* out, Vec3* lhs, Vec3* rhs);
int32_t __fastcall orthogonalize_matrix(TransformMatrix* transform);
TransformMatrix* __fastcall invert_matrix_from_source(TransformMatrix* out, TransformMatrix* source);
TransformMatrix* __thiscall multiply_matrix_in_place(TransformMatrix* lhs, TransformMatrix* rhs);
TransformMatrix* __thiscall premultiply_matrix_in_place(TransformMatrix* lhs, TransformMatrix* rhs);
void __thiscall set_matrix_z_direction(TransformMatrix* transform, const Vec3* direction);
void __thiscall look_at_point(TransformMatrix* transform, const Vec3* target);
TransformMatrix* __thiscall interpolate_matrix_rotation(TransformMatrix* transform, float alpha);
void __thiscall linear_interpolate_matrix(
    TransformMatrix* out,
    const TransformMatrix* from,
    const TransformMatrix* to,
    float alpha
);
void __thiscall compute_kind42_attachment_transform(
    PathTemplate* self,
    float radius,
    float x,
    float y,
    TransformMatrix* transform,
    float* out_angle
);
int32_t __stdcall load_x_mesh(char* mesh_path, PathTemplateStripMesh* mesh, uint8_t options_flags);
void __thiscall request_object_vertices(PathTemplateStripMesh* mesh, int32_t vertex_count);
void __fastcall request_object_vertex_colours(PathTemplateStripMesh* mesh);
void __thiscall request_object_facequads(PathTemplateStripMesh* mesh, int32_t facequad_count);
Color4f* __thiscall set_color_rgba(Color4f* color, float r, float g, float b, float a);
float __thiscall set_color_alpha(Color4f* color, float alpha);
float __thiscall set_color_grayscale(Color4f* color, float intensity);
void __thiscall start_squidge_y(SquidgeState* squidge, float value);
void __thiscall start_squidge_z(SquidgeState* squidge, float value);
void __thiscall update_squidge(SquidgeState* squidge);
void __thiscall initialize_invincible_shell(InvincibleShellController* shell);
void __thiscall start_invincible_shell(InvincibleShellController* shell);
void __thiscall update_invincible_shell(InvincibleShellController* shell);
void __thiscall initialize_snail_skin(SnailSkinTransitionState* state);
void __thiscall update_snail_skin(PlayerPresentationController* presentation);
void __thiscall initialize_anim_manager(AnimationDispatchState* manager);
void __thiscall update_anim_manager(AnimationDispatchState* manager);
int32_t __thiscall set_weapon_animation(PresentationAnimationChannel* channel, int32_t animation_id, uint8_t immediate, int32_t initial_frame);
void __thiscall update_snail_skin_transition(SnailSkinTransitionState* state);
float __thiscall store_color4f(Color4f* color, float r, float g, float b, float a);
ColorBGRA8* __thiscall pack_color_rgba_u8(ColorBGRA8* out, Color4f* color);
TipSlot* __thiscall enqueue_tip_message(TipManager* manager, TipMessageDefinition* definition, int32_t show_disable_button);
void __thiscall initialize_tip(TipSlot* slot, TipMessageDefinition* definition, int32_t show_disable_button);
void* __fastcall update_tip(TipSlot* slot);
void __fastcall update_tip_manager(TipManager* manager);
void __fastcall initialize_tutorial(TutorialController* controller);
TrackRowCell* __fastcall update_tutorial(TutorialController* controller);
int32_t __fastcall flush_row_event_display(RowEventDisplayController* controller);
int32_t __fastcall register_parcel_delivery(RowEventDisplayController* controller);
void __fastcall update_row_event_display(RowEventDisplayController* controller);
int32_t __thiscall initialize_cameraman(CameramanState* cameraman);
int32_t __thiscall update_cameraman(CameramanState* cameraman);
int32_t __thiscall initialize_subgoldy(Player* player, int32_t player_slot);
int32_t __thiscall update_subgoldy(Player* player);
int32_t __thiscall handle_subgoldy_collisions(Player* player);
void __thiscall set_snail_weapon(PlayerPresentationController* presentation, int32_t movement_flags);
void __thiscall set_snail_jetpack(GlobalJetpackPresentationController* controller, int32_t state);
int32_t __thiscall initialize_cutscene(PlayerPresentationController* presentation);
int32_t __thiscall dispatch_cutscene_animation(PlayerPresentationController* presentation, int32_t animation_id, uint8_t immediate, int32_t initial_frame);
int32_t __fastcall initialize_cutscene_ai(CutsceneAI* cutscene_ai);
int32_t __thiscall update_cutscene(CutsceneAI* cutscene_ai);
int32_t __thiscall initialize_nuke(NukeController* nuke);
int32_t __thiscall update_nuke(NukeController* nuke);
void __thiscall uninit_nuke(NukeController* nuke);
TrackRowCell* __thiscall get_track_grid_cell_at_world_position(Game* game, Vec3* position);
TrackAttachmentRuntimeRow* __thiscall get_track_runtime_cell_at_world_z(Game* game, Vec3* position);
double __thiscall sample_track_floor_height_at_position(Game* game, Vec3* position);
PathTemplate* __thiscall begin_track_attachment_follow_state(FollowState* follow_state, TrackRowCell* source_cell, Vec3* world_position, Player* player);
int32_t __thiscall update_track_attachment_follow_state(FollowState* follow_state, float path_factor, Vec3* out_position, Vec3* motion);

int32_t __thiscall initialize_looptheloop_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_loopout_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_cage2_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_supertramp_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b,
    char* texture_c
);

int32_t __thiscall initialize_kind42_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_hump_path_template_pair(
    PathTemplate* self,
    float arg2,
    float arg3,
    int32_t arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_looptheloopw_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_dump_path_template_pair(
    PathTemplate* self,
    float arg2,
    float arg3,
    int32_t arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_dip_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_screw_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_slalom_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_worm_path_template_pair(
    PathTemplate* self,
    char* texture_path
);

int32_t __thiscall initialize_slalombig_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_sweep_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_snake_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_slalomdouble_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_p_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    uint32_t arg3,
    float arg4,
    float arg5,
    int32_t arg6,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_start_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_path
);

int32_t __thiscall initialize_turnover_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_turnoverdouble_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_turnunder_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_wibble_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_invert_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_twister_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_twister2_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_loopbow_path_template_pair(
    PathTemplate* self,
    float arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_toad_path_template_pair(
    PathTemplate* self,
    char arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_hill_valley_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    float arg3,
    float arg4,
    char arg5,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_sbend_path_template_pair(
    PathTemplate* self,
    uint32_t arg2,
    float arg3,
    float arg4,
    char arg5,
    char* texture_a,
    char* texture_b
);

int32_t __cdecl parse_next_int32(char** cursor);

char** __cdecl parse_next_space_delimited_token(char** cursor, char* out);

double __cdecl parse_next_float32(char** cursor);

void* __fastcall initialize_track_render_cache_manager(TrackRenderCacheManager* manager);

int32_t __fastcall build_track_render_caches(TrackRenderCacheManager* manager);

void __fastcall update_track_render_cache_rows(TrackRenderCacheManager* manager);

void __fastcall remove_track_render_cache_bods(TrackRenderCacheManager* manager);

int32_t __fastcall is_slide_cache_tile_family(TrackRowCell* cell);

int32_t __fastcall is_floor_cache_tile_family(TrackRowCell* cell);

int32_t __fastcall is_ramp_cache_tile_family(TrackRowCell* cell);

#endif
