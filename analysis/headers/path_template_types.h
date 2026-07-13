#ifndef PATH_TEMPLATE_TYPES_H
#define PATH_TEMPLATE_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef int int32_t;

/* Empty C++ cRPathManager occupies one byte in the Windows root layout. */
typedef struct PathManager {
    uint8_t _empty;
} PathManager;

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
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
} BodBase;

typedef struct RenderableBod {
    BodBase bod;
    uint8_t transform[0x40];
} RenderableBod;

typedef struct FringeObject {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
} FringeObject;

typedef struct Player Player;
typedef struct Object Object;
typedef struct SubSegment SubSegment;
typedef struct SubgameRuntime SubgameRuntime;
typedef struct Snail Snail;
typedef struct FrontendWidget FrontendWidget;
typedef struct FrontendWidgetTooltip FrontendWidgetTooltip;
typedef struct FrontendWidgetTextBuffer FrontendWidgetTextBuffer;
typedef struct Sprite Sprite;
typedef struct TrackRowCell TrackRowCell;
typedef struct TrackRowCell SubLoc;
typedef struct TransformMatrix TransformMatrix;

/* Two authored cRBanner actors are embedded at SubgameRuntime +0x359080. */
typedef struct Banner {
    BodBase bod;
    int32_t visibility_mode;
    uint8_t _pad_3c[0x54 - 0x3c];
    Player* owner_player;
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
    Object* owner;
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
    Player* owner;
    uint8_t _pad_40[0x44 - 0x40];
    SubgameRuntime* owner_game;
    uint8_t _pad_48[0x64 - 0x48];
    Sprite* sprite;
    TrackRowCell* source_cell;
    float bob_phase;
    float bob_phase_step;
    Vapour vapour_a;
    Vapour vapour_b;
} JetPack;

typedef struct Sprite {
    uint8_t _pad_00[0x04];
    uint32_t flags;
    uint8_t _pad_08[0x48 - 0x08];
    Vec3 position;
    uint8_t _pad_54[0xb4 - 0x54];
} Sprite;

typedef struct Parcel {
    BodBase bod;
    int32_t state;
    SubgameRuntime* owner_subgame;
    uint8_t _pad_40[0x54 - 0x40];
    Sprite* sprite;
    uint8_t _pad_58[0x5c - 0x58];
    float bob_phase;
    float bob_phase_step;
    Player* owner_player;
    float progress;
    float progress_step;
    float target_distance;
    Vec3 travel_dir;
    Vec3 delivery_offset;
} Parcel;

typedef struct ParcelManager {
    Parcel slots[50];
} ParcelManager;

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
    uint32_t list_kind;
    uint32_t list_flags;
    FrontendWidget* list_prev;
    FrontendWidget* list_next;
    uint8_t _pad_10[0x34];
    float hide_blend;
    int32_t border_texture_id;
    float authored_left;
    float authored_top;
    float authored_width;
    float authored_height;
    uint8_t texture_hit_test_enabled;
    uint8_t _pad_5d[0x3];
    int32_t background_texture_id;
    int32_t texture_hit_test_sprite;
    uint8_t _pad_68[0x14];
    int32_t widget_type;
    uint8_t _pad_80[0xf8];
    float sprite_shadow_offset;
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
    float texture_hit_x;
    float texture_hit_y;
    float layout_width;
    float layout_height;
    float texture_hit_width;
    float texture_hit_height;
    float border_edge;
    int32_t text_alignment;
    float anchor_x;
    float teardown_progress;
    float teardown_progress_step;
    float stack_gap;
    int32_t texture_id;
    int32_t texture_layer;
    int32_t mouse_history_warmup_frames;
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

/* Authored empty cRProgressBar at Player +0x3f0. */
typedef struct ProgressBar {
    uint8_t _empty;
} ProgressBar;

/*
 * Authored cRWarning, exact 0x10-byte Windows owner at Player +0x3f4.
 * Native functions: initialize_warning @ 0x446e80, uninit_warning @ 0x446f10,
 * start_warning @ 0x446f30, stop_warning @ 0x446f50,
 * stop_warning_sample @ 0x446f60, and update_warning @ 0x446f80.
 * Mobile variants retain the owner and lifecycle but add fields before border.
 */
typedef struct Warning {
    int32_t state;
    float phase;
    float phase_step;
    FrontendWidget* border;
} Warning;

/*
 * Authored cRTimesUp countdown actor at SubgameRuntime +0x1272828. Native
 * functions: update_times_up @ 0x445e20, uninit_times_up @ 0x445e70.
 */
typedef struct TimesUp {
    int32_t state;
    FrontendWidget* border;
    float progress;
    float progress_step;
} TimesUp;

/*
 * Authored cRTime value. Native cRTime::Zero @ 0x441b70 clears all six fields;
 * cRTime::Add(float) @ 0x441b90 increments total_seconds and second_fraction by
 * `delta_ticks * (1/60)`, rolling seconds into minutes and publishing
 * hundredths / thousandths for the HUD.
 */
typedef struct Time {
    float total_seconds;
    int32_t minutes;
    int32_t seconds;
    int32_t display_hundredths;
    int32_t display_thousandths;
    float second_fraction;
} Time;

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
 * fade alpha; spawn still seeds the y velocity lane and the collision latch.
 * Native functions: initialize_salt_hazard_pool @ 0x441540, spawn_salt_hazard
 * @ 0x441560, update_salt_hazard @ 0x441c10.
 */
typedef struct SaltHazardSlot {
    BodNode bod;
    Vec3 bod_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 world_position;
    uint8_t _pad_78[0x8];
    uint32_t state;
    uint8_t _pad_84[0x4];
    SubgameRuntime* owner_game;
    float fade_alpha;
    float spawn_velocity_y;
    uint8_t collision_armed;
    uint8_t _pad_95[0x03];
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
    BodNode bod;
    Vec3 bod_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 world_position;
    uint8_t _pad_78[0x8];
    uint32_t state;
    uint8_t _pad_84[0x4];
    SubgameRuntime* owner_game;
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
    SubSegment* source_segment;
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
    union {
        uint16_t header_word;
        struct {
            uint8_t flags;
            uint8_t secondary_flags;
        };
    };
    uint16_t vertex_0;
    uint16_t vertex_1;
    uint16_t vertex_2;
    uint16_t vertex_3;
    uint8_t _pad_0a[0x0c - 0x0a];
    TextureRef* texture_ref;
    ObjectUv uv[4];
} ObjectFaceQuad;

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

typedef struct ObjectRenderVertex {
    float x;
    float y;
    float z;
    uint32_t diffuse;
    float u;
    float v;
} ObjectRenderVertex;

typedef struct TrackRenderCacheSlot {
    BodBase bod;
    float cache_row_base;
} TrackRenderCacheSlot;

typedef struct SegmentCache {
    ColorBGRA8 skirt_color_bgra;
    int32_t max_vertex_counts[5];
    int32_t max_index_counts[5];
    ObjectRenderVertex* shared_vertex_buffers[5];
    uint16_t* shared_index_buffers[5];
    SubgameRuntime* owner_subgame;
    TrackRenderCacheSlot slots[0x8f][5];
    float build_cache_row_base;
    float next_cache_row_z;
    int32_t next_cache_row_index;
} SegmentCache;

/*
 * IDA-only aggregate view of build_track_render_caches' 0x34-byte overlapping
 * local range. The native source used individual locals and arrays; this view
 * prevents Hex-Rays from falsely propagating ObjectVertexBufferVtbl into the
 * coincidentally same-sized stack range.
 */
typedef struct TrackRenderCacheBuildLocals {
    ColorBGRA8 white_color;
    int32_t work_value;
    int32_t cache_row;
    int32_t cells_remaining_or_family_index;
    int32_t row_mod;
    void* locked_vertices;
    void* locked_indices;
    int32_t saved_cell_offset;
    int32_t vertex_counts[5];
} TrackRenderCacheBuildLocals;

/* Authored cRCameraman, exact 0xd8-byte follow-camera owner. */
typedef struct Cameraman {
    TransformMatrix live_matrix;
    TransformMatrix desired_matrix;
    TransformMatrix previous_desired_matrix;
    Player* player;
    SubgameRuntime* game;
    float fov_degrees;
    uint8_t unresolved_cc;
    uint8_t _pad_cd[0x3];
    float attachment_lift_envelope;
    float smoothed_attachment_lift_envelope;
} Cameraman;

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
    SubgameRuntime* game;
    uint8_t _pad_204[0x8];
    float warning_intensity_latch;
    float warning_intensity;
} SubHover;

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

/* Authored cRCutScene, exact 0x5c-byte camera state-machine owner. */
typedef struct CutScene {
    Snail* presentation;
    Player* player;
    int32_t camera_mode;
    int32_t state;
    TransformMatrix live_matrix;
    float progress;
    float progress_step;
    uint8_t force_camera_update;
    uint8_t _pad_59[0x3];
} CutScene;

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
    SnailVisual* visual_root;
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
    Snail* owner_snail;
    int32_t active;
    float progress;
    float progress_step;
} SnailSkin;

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

/* Authored cRSnail, exact 0x19b4-byte Player presentation owner. */
typedef struct Snail {
    void* vtable;
    uint32_t visual_flags;
    uint8_t _pad_08[0x1c];
    SnailVisual* visual_root;
    uint8_t _pad_28[0x10];
    TransformMatrix live_matrix;
    uint8_t _pad_78[0x8];
    TransformMatrix previous_live_matrix;
    TransformMatrix cached_cutscene_matrix;
    Player* owner_player;
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

/* Authored cRSquidge, exact 0x18-byte two-axis spring oscillator. */
typedef struct Squidge {
    float y_output;
    float y_velocity;
    float y_phase;
    float z_output;
    float z_velocity;
    float z_phase;
} Squidge;

/* Authored cRNuke, exact 0x7c-byte collision-ring effect owner. */
typedef struct Nuke {
    int32_t state;
    Player* owner_player;
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
    Player* player;
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

typedef struct ReplayRunRecord {
    int16_t lateral_x;
    int16_t delta_z;
    uint8_t flags;
    uint8_t reserved_05;
} ReplayRunRecord;

typedef union SubSolutionScoreOrTime {
    float total_seconds;
    int32_t score_buckets[6];
    Time timer;
} SubSolutionScoreOrTime;

/* Exact 0x1fac0-byte authored cRSubSolution replay/high-score record. */
typedef struct SubSolution {
    int32_t active;
    int32_t score;
    SubSolutionScoreOrTime score_or_time;
    int32_t score_tail;
    int32_t source_tail;
    int32_t replay_level_index;
    int32_t replay_mode_id;
    int32_t unknown_30;
    float challenge_difficulty_scalar;
    uint32_t runtime_build_flags;
    int32_t high_score_mode_tag;
    int32_t route_or_rank_index;
    int32_t replay_cursor;
    float replay_speed_scalar;
    int32_t challenge_speed_value;
    int32_t challenge_difficulty_value;
    char player_name[0x14];
    int32_t runtime_build_seed;
    int32_t replay_sample_count;
    ReplayRunRecord run_records[21600];
    float garbage_frequency;
    float salt_frequency;
    int32_t unknown_1fab8;
    int32_t unknown_1fabc;
} SubSolution;

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

/* Authored cRPath, exact 0xa8 bytes. Windows stores 126 instances as 63
 * adjacent primary/secondary PathPair records in SubgameRuntime. */
typedef struct Path {
    uint8_t _pad_00[0x24];
    Object* strip_mesh;
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
    uint8_t has_entry_mesh_transition;
    uint8_t _pad_9d[0x3];
    Object* entry_transition_strip_mesh;
    Object* entry_base_strip_mesh;
} Path;

typedef struct PathPair {
    Path primary;
    Path secondary;
} PathPair;

typedef struct FollowState {
    uint8_t active;
    uint8_t _pad_01[0x3];
    Path* template_record;
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
    SubgameRuntime* game;
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
    PlayerControlSource* control_source;
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

/*
 * Authored cRSubGame owner embedded in the root runtime. This campaign keeps
 * the broad object sparse, but the complete Player child at +0x3bb764 is now
 * represented as ownership rather than flattened score/presentation aliases.
 */
typedef struct SubgameRuntime {
    uint8_t _pad_00[0x09];
    uint8_t subgame_pause_gate;
    uint8_t _pad_0a[0x34 - 0x0a];
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
    SegmentCache segment_cache;
    uint8_t track_state_latch;
    uint8_t _pad_a855[0x3];
    Tutorial tutorial;
    int32_t level_segment_count;
    uint8_t _pad_a878[0x355e64 - 0xa878];
    JetPack jetpack_pickup;
    uint8_t _pad_356000[0x359080 - 0x356000];
    BannerPool banners;
    uint8_t _pad_359140[0x3bb764 - 0x359140];
    Player player;
    TrackRowCell runtime_cells[3200][8];
    TrackAttachmentRuntimeRow runtime_rows[3200];
    uint8_t _pad_68b4c8[0xfd2b10 - 0x68b4c8];
    SubSolution current_high_score_record;
    uint8_t selected_level_record_active;
    uint8_t selected_level_record_persistent;
    uint8_t _pad_ff25d2[0x2];
    SubSolution* selected_level_record;
    int32_t selected_level_record_cursor;
    int32_t replay_update_cursor;
    uint8_t _pad_ff25e0[0x4];
    int32_t runtime_track_index;
    uint8_t _pad_ff25e8[0xff2914 - 0xff25e8];
    PathPair path_pairs[63];
    uint8_t _pad_ff7bc4[0x125e480 - 0xff7bc4];
    ParcelManager parcel_manager;
    uint8_t _pad_125ffd8[0x12727d8 - 0x125ffd8];
    Completion completion;
    TimesUp times_up;
} SubgameRuntime;

TextureRef* __thiscall get_or_create_texture_ref(TextureRefList* texture_list, char* texture_path, int32_t arg3, int16_t arg4);
void __fastcall allocate_path_template_samples(Path* self);
int32_t __fastcall finalize_path_template(Path* self);
int32_t __thiscall mirror_path_template_pair_x(Path* self, Path* source);
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
    Path* self,
    float radius,
    float x,
    float y,
    TransformMatrix* transform,
    float* out_angle
);
void __thiscall request_object_vertices(Object* object, int32_t vertex_count);
void __fastcall request_object_vertex_colours(Object* object);
void __thiscall request_object_facequads(Object* object, int32_t facequad_count);
Color4f* __thiscall set_color_rgba(Color4f* color, float r, float g, float b, float a);
float __thiscall set_color_alpha(Color4f* color, float alpha);
float __thiscall set_color_grayscale(Color4f* color, float intensity);
void __thiscall initialize_score_stats(Squidge* squidge);
void __thiscall start_squidge_y(Squidge* squidge, float value);
void __thiscall start_squidge_z(Squidge* squidge, float value);
void __thiscall update_squidge(Squidge* squidge);
void __thiscall firework_shoot(FireWork* firework, Vec3* position, int32_t owner, int32_t texture_id, int32_t count);
void __thiscall update_banner(Banner* banner);
JetPack* __thiscall initialize_track_jetpack_pickup_runtime(JetPack* jetpack);
void __thiscall update_track_jetpack_pickup(JetPack* jetpack);
void __thiscall initialize_vapour(Vapour* vapour, Object* unused, float half_width);
void __thiscall reset_vapour(Vapour* vapour, float* z_floor);
void __thiscall add_vapour_point(Vapour* vapour, const TransformMatrix* point);
void __thiscall update_vapour(Vapour* vapour);
void __thiscall initialize_invincible_shell(Invincible* invincible);
void __thiscall start_invincible_shell(Invincible* invincible);
void __thiscall update_invincible_shell(Invincible* invincible);
void __thiscall initialize_snail_skin(SnailSkin* snail_skin);
void __thiscall update_snail_skin(Snail* snail);
void __thiscall initialize_anim_manager(AnimManager* manager);
void __thiscall update_anim_manager(AnimManager* manager);
int32_t __thiscall set_weapon_animation(PresentationAnimationChannel* channel, int32_t animation_id, uint8_t immediate, int32_t initial_frame);
void __thiscall update_snail_skin_transition(SnailSkin* snail_skin);
void __thiscall change_snail_skin(SnailSkin* snail_skin, int32_t slot_id, float duration_seconds);
float __thiscall store_color4f(Color4f* color, float r, float g, float b, float a);
ColorBGRA8* __thiscall pack_color_rgba_u8(ColorBGRA8* out, Color4f* color);
void __thiscall kill_tip_widgets(Tip* tip);
void __thiscall initialize_tip(Tip* tip, TipData* definition, int32_t hide_disable_button);
void __thiscall update_tip(Tip* tip);
void __thiscall initialize_tip_manager(TipManager* manager);
void __thiscall uninit_tips(TipManager* manager);
Tip* __thiscall enqueue_tip_message(TipManager* manager, TipData* definition, int32_t hide_disable_button);
void __thiscall update_tip_manager(TipManager* manager);
void __thiscall initialize_tutorial(Tutorial* tutorial);
void __thiscall uninit_tutorial(Tutorial* tutorial);
TrackRowCell* __thiscall update_tutorial(Tutorial* tutorial);
void __thiscall flush_row_event_display(Completion* completion);
void __thiscall initialize_completion_screen(
    Completion* completion,
    int32_t delivered_count,
    uint8_t perfect_delivery);
void __thiscall update_row_event_display(Completion* completion);
void __thiscall register_parcel_delivery(Completion* completion);
void __thiscall initialize_cameraman(Cameraman* cameraman);
void __thiscall update_cameraman(Cameraman* cameraman);
void __thiscall initialize_subgoldy(Player* player, int32_t player_slot);
void __thiscall end_jetpack_hover(SubHover* sub_hover);
void __thiscall update_jetpack_gauge(SubHover* sub_hover);
void __thiscall uninit_jet_particles(SubHover* sub_hover);
void __thiscall initialize_jet_particles(SubHover* sub_hover);
void __thiscall update_jet_particles(SubHover* sub_hover);
void __thiscall initialize_jetpack_gauge(SubHover* sub_hover, int32_t player_slot);
void __thiscall arm_jetpack_gauge(SubHover* sub_hover);
int32_t __thiscall update_subgoldy(Player* player);
Sprite* __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z);
int32_t __thiscall handle_subgoldy_collisions(Player* player);
void __thiscall set_snail_weapon(Snail* snail, int32_t movement_flags);
void __thiscall set_snail_jetpack(Snail* snail, int32_t state);
void __thiscall initialize_cutscene(Snail* snail);
int32_t __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t initial_frame);
void __thiscall initialize_cutscene_ai(CutScene* cutscene);
void __thiscall update_cutscene(CutScene* cutscene);
void __thiscall update_progress_bar(ProgressBar* progress_bar);
void __thiscall initialize_nuke(Nuke* nuke);
void __thiscall update_nuke(Nuke* nuke);
void __thiscall uninit_nuke(Nuke* nuke);
TrackRowCell* __thiscall get_track_grid_cell_at_world_position(SubgameRuntime* game, Vec3* position);
TrackAttachmentRuntimeRow* __thiscall get_track_runtime_cell_at_world_z(SubgameRuntime* game, Vec3* position);
double __thiscall sample_track_floor_height_at_position(SubgameRuntime* game, Vec3* position);
Path* __thiscall begin_track_attachment_follow_state(FollowState* follow_state, TrackRowCell* source_cell, Vec3* world_position, Player* player);
int32_t __thiscall update_track_attachment_follow_state(FollowState* follow_state, float path_factor, Vec3* out_position, Vec3* motion);

int32_t __thiscall initialize_looptheloop_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_loopout_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_cage2_path_template_pair(
    Path* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_supertramp_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b,
    char* texture_c
);

int32_t __thiscall initialize_halfpipe_path_template_pair(
    Path* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_hump_path_template_pair(
    Path* self,
    float arg2,
    float arg3,
    int32_t arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_looptheloopw_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_dump_path_template_pair(
    Path* self,
    float arg2,
    float arg3,
    int32_t arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_dip_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_screw_path_template_pair(
    Path* self,
    int32_t arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_slalom_path_template_pair(
    Path* self,
    int32_t arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_worm_path_template_pair(
    Path* self,
    char* texture_path
);

int32_t __thiscall initialize_slalombig_path_template_pair(
    Path* self,
    int32_t arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_sweep_path_template_pair(
    Path* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_snake_path_template_pair(
    Path* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_slalomdouble_path_template_pair(
    Path* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_p_path_template_pair(
    Path* self,
    int32_t arg2,
    uint32_t arg3,
    float arg4,
    float arg5,
    int32_t arg6,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_start_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_path
);

int32_t __thiscall initialize_turnover_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_turnoverdouble_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_turnunder_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_wibble_path_template_pair(
    Path* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_invert_path_template_pair(
    Path* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_twister_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_twister2_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_loopbow_path_template_pair(
    Path* self,
    float arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_toad_path_template_pair(
    Path* self,
    char arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_hill_valley_path_template_pair(
    Path* self,
    int32_t arg2,
    float arg3,
    float arg4,
    char arg5,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_sbend_path_template_pair(
    Path* self,
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

void* __thiscall noop_this_constructor(void* self);

void* __thiscall initialize_track_render_cache_manager(SegmentCache* manager);

int32_t __thiscall build_track_render_caches(
    SegmentCache* manager,
    Color4f skirt_color
);

int32_t __thiscall add_track_cache_vertex(
    SegmentCache* manager,
    Object* source,
    Vec3* position,
    int32_t source_index,
    float u,
    float v,
    ObjectRenderVertex* vertices,
    int32_t* vertex_count,
    int32_t max_vertices,
    int32_t max_indices,
    uint32_t color,
    uint8_t project_uv
);

int32_t __thiscall append_track_cache_object(
    SegmentCache* manager,
    int32_t row_index,
    Object* source,
    Vec3* position,
    ObjectRenderVertex* vertices,
    int32_t* vertex_count,
    uint16_t* indices,
    int32_t* index_count,
    int32_t max_vertices,
    int32_t max_indices,
    uint32_t color,
    uint8_t project_uv
);

void __thiscall update_track_render_cache_rows(SegmentCache* manager);

void __thiscall remove_track_render_cache_bods(SegmentCache* manager);

Parcel* __thiscall initialize_track_parcel_runtime(Parcel* parcel);

void __thiscall update_track_parcels(ParcelManager* manager);

void __thiscall initialize_track_parcel_slots(ParcelManager* manager);

Parcel* __thiscall allocate_track_parcel_slot(ParcelManager* manager);

void __thiscall update_track_parcel(Parcel* parcel);

Parcel* __thiscall spawn_track_parcel(
    SubgameRuntime* runtime,
    Vec3* world_position,
    Player* source_player
);

int32_t __fastcall is_sub_loc_floor(TrackRowCell* cell);

int32_t __fastcall is_sub_loc_slide(TrackRowCell* cell);

int32_t __fastcall is_sub_loc_ramp(TrackRowCell* cell);

int32_t __fastcall is_sub_loc_empty(TrackRowCell* cell);

#endif
