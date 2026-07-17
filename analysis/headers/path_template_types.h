#ifndef PATH_TEMPLATE_TYPES_H
#define PATH_TEMPLATE_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef int int32_t;

typedef struct Object Object;
typedef struct ObjectFaceQuad ObjectFaceQuad;

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

typedef struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
} TransformMatrix;

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

typedef struct FrontendWidget FrontendWidget;
typedef struct FrontendWidgetTooltip FrontendWidgetTooltip;
typedef struct FrontendWidgetTextBuffer FrontendWidgetTextBuffer;

typedef struct Twinkle {
    int32_t state;
    int32_t unused_04;
    float delay_progress;
    float delay_step;
    float alpha;
    float target_alpha;
    float angle;
    float angle_step;
    float x;
    float y;
    float size;
    FrontendWidget* owner_widget;
} Twinkle;

typedef struct TwinkleManager {
    Twinkle twinkles[5];
    int32_t active_state;
    int32_t twinkle_count;
} TwinkleManager;

/* Authored packed-colour owner; Android proves the same BGRA byte order. */
typedef struct tColourSmall {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
} tColourSmall;

typedef struct BodNode {
    void* vtable;
    uint32_t list_flags;
    struct BodNode* list_prev;
    struct BodNode* list_next;
} BodNode;

/* Root-owned intrusive list header shared by active and free BOD chains. */
typedef struct BodList {
    int32_t unknown_00;
    BodNode* first;
    BodNode* free_top;
} BodList;

typedef struct BodBase {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    Object* object;
    tColour color;
} BodBase;

typedef struct AnimManager AnimManager;

typedef struct RenderableBod {
    BodBase bod;
    TransformMatrix transform;
    /* Borrowed only when BodNode.list_flags has the render-sync bit 0x800. */
    AnimManager* render_animation_manager;
    uint8_t unknown_7c[0x4];
} RenderableBod;

typedef struct FringeObject {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    Object* object;
    tColour color;
} FringeObject;

typedef struct Player Player;
typedef struct SubSegment SubSegment;
typedef struct SubgameRuntime SubgameRuntime;
typedef struct Snail Snail;
typedef struct Sprite Sprite;
typedef struct TrackRowCell TrackRowCell;
typedef struct TrackRowCell SubLoc;

typedef enum FrontendWidgetFlag {
    FRONTEND_WIDGET_FLAG_HIGHLIGHTED = 0x00000002,
    FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED = 0x00000004,
    FRONTEND_WIDGET_FLAG_HOVER_TEXT_EFFECT_ENABLED = 0x00000008,
    FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED = 0x00000010,
    FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED = 0x00000020,
    FRONTEND_WIDGET_FLAG_SECONDARY_INPUT_ENABLED = 0x00000040,
    FRONTEND_WIDGET_FLAG_SECONDARY_ACTION_TRIGGERED = 0x00000080,
    FRONTEND_WIDGET_FLAG_KILL_PENDING = 0x00000200,
    FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE = 0x00000400,
    FRONTEND_WIDGET_FLAG_SPRITE_MODE = 0x00000800,
    FRONTEND_WIDGET_FLAG_HIDDEN = 0x00001000,
    FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE = 0x00002000,
    FRONTEND_WIDGET_FLAG_TEXT_INPUT_COMPLETE = 0x00004000,
    FRONTEND_WIDGET_FLAG_DISABLED = 0x00008000,
    FRONTEND_WIDGET_FLAG_USE_AUTHORED_RECT = 0x00010000,
    FRONTEND_WIDGET_FLAG_POINTER_INSIDE = 0x00020000,
    FRONTEND_WIDGET_FLAG_SNAP_VISUAL_STATE = 0x00040000,
    FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED = 0x00080000,
    FRONTEND_WIDGET_FLAG_SLIDER = 0x00100000,
    FRONTEND_WIDGET_FLAG_FRAMELESS = 0x00400000,
    FRONTEND_WIDGET_FLAG_SUPPRESS_ACTION_SOUND = 0x00800000,
    FRONTEND_WIDGET_FLAG_IMMEDIATE_ACTION = 0x01000000,
    FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED = 0x08000000,
    FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN = 0x20000000,
    FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION = 0x40000000,
    FRONTEND_WIDGET_FLAG_DISABLED_BEFORE_DEACTIVATION = 0x80000000,
} FrontendWidgetFlag;

typedef enum TextureRefFlags {
    TEXTURE_REF_RETAIN_SOURCE_BYTES = 0x20,
    TEXTURE_REF_REGISTERED = 0x400,
    TEXTURE_REF_DISABLE_PATH_REUSE = 0x800,
    TEXTURE_REF_WRAP_ADDRESSING = 0x1000,
    TEXTURE_REF_ANIMATED = 0x2000,
    TEXTURE_REF_ANIMATION_PING_PONG = 0x4000,
    TEXTURE_REF_SKIP_RUNTIME_LOAD = 0x8000,
    TEXTURE_REF_HAS_ALPHA = 0x10000,
} TextureRefFlags;

typedef union AuthoredFloatBits {
    int32_t bits;
    float value;
} AuthoredFloatBits;

/* Writable level-definition text storage at 0x74ec78. The next independently
 * referenced global begins at 0x751478, and no interior address is referenced. */
typedef char LevelFileTextBuffer[0x2800];

typedef enum AuthoredSegmentRowFlag {
    AUTHORED_SEGMENT_ROW_FLAG_PARCEL = 0x0001,
    AUTHORED_SEGMENT_ROW_FLAG_3D_MODEL = 0x0002,
    AUTHORED_SEGMENT_ROW_FLAG_STAR_MARKER = 0x0004,
    AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY = 0x0008,
    AUTHORED_SEGMENT_ROW_FLAG_NO_FALL = 0x0100,
    AUTHORED_SEGMENT_ROW_FLAG_RING_NONE = 0x0200,
    AUTHORED_SEGMENT_ROW_FLAG_RING_NORMAL = 0x0400,
    AUTHORED_SEGMENT_ROW_FLAG_RING_EXPLODE = 0x0800,
    AUTHORED_SEGMENT_ROW_FLAG_RING_SLOW = 0x1000,
    AUTHORED_SEGMENT_ROW_FLAG_RING_POWER_UP = 0x2000,
    AUTHORED_SEGMENT_ROW_FLAG_JETPACK_OFF = 0x8000,
} AuthoredSegmentRowFlag;

/* Game-wide cRSubGame::runtime_flags bits with proved Windows consumers. */
typedef enum SubgameRuntimeFlag {
    SUBGAME_RUNTIME_FLAG_PRESERVE_SPACE_GLYPH = 0x000001,
    SUBGAME_RUNTIME_FLAG_AMBIENT_GARBAGE = 0x000002,
    SUBGAME_RUNTIME_FLAG_PRESERVE_O_GLYPH = 0x000004,
    SUBGAME_RUNTIME_FLAG_DEFAULT_RAMP_RINGS = 0x000008,
    SUBGAME_RUNTIME_FLAG_RING_LIFE_REWARD = 0x000010,
    SUBGAME_RUNTIME_FLAG_PRESERVE_BRACE_ORIENTATION = 0x000020,
    SUBGAME_RUNTIME_FLAG_PRESERVE_UNDERSCORE_GLYPH = 0x000040,
    SUBGAME_RUNTIME_FLAG_SLUG_HAZARDS = 0x000080,
    SUBGAME_RUNTIME_FLAG_PRESERVE_EQUALS_BAR_GLYPHS = 0x000100,
    SUBGAME_RUNTIME_FLAG_PRESERVE_RAMP_GLYPHS = 0x000200,
    SUBGAME_RUNTIME_FLAG_ALLOW_FALLING = 0x000400,
    SUBGAME_RUNTIME_FLAG_HEALTH_PICKUPS = 0x000800,
    SUBGAME_RUNTIME_FLAG_PRESERVE_DASH_GLYPH = 0x004000,
    SUBGAME_RUNTIME_FLAG_AMBIENT_SALT = 0x010000,
    SUBGAME_RUNTIME_FLAG_MOVEMENT_FIRE_EMITTERS = 0x400000,
    SUBGAME_RUNTIME_FLAG_PARCEL_SPAWNS = 0x800000,
} SubgameRuntimeFlag;

/* Native composite words. Bits 0x040000, 0x100000, and 0x200000 remain
 * intentionally unnamed because no Windows consumer has established them. */
typedef enum SubgameRuntimeFlagPreset {
    SUBGAME_RUNTIME_FLAGS_SWITCH_SEED = 0x000484,
    SUBGAME_RUNTIME_FLAGS_ENGINE_DEFAULT = 0x600484,
    SUBGAME_RUNTIME_FLAGS_POSTAL_CHALLENGE = 0xf5cfff,
    SUBGAME_RUNTIME_FLAGS_TIME_TRIAL = 0x75cfff,
    SUBGAME_RUNTIME_FLAGS_TUTORIAL = 0xe4cfff,
    SUBGAME_RUNTIME_FLAGS_TUTORIAL_INIT_OR_MASK = 0x600000,
} SubgameRuntimeFlagPreset;

typedef struct AuthoredSegmentRow {
    int32_t flags;
    int32_t parcel_set_id;
    Vec3 local_position;
    int32_t object_id;
    Vec3 object_position;
    Vec3 object_velocity;
    int32_t path_template_index;
    AuthoredFloatBits ring_speed;
} AuthoredSegmentRow;

/* Exact 0x4220-byte authored cRSubSegment value. */
struct SubSegment {
    int32_t row_base;
    int32_t row_count;
    uint8_t visited;
    uint8_t unknown_09[0x0c - 0x09];
    int32_t path_index;
    char* source_name;
    char glyph_rows[8][0x100];
    AuthoredSegmentRow rows[256];
    AuthoredFloatBits angle_radians;
    char message_text[0x4218 - 0x4018];
    AuthoredFloatBits message_duration;
    int32_t message_sample_id;
};

/* The runtime-cell builder advances an ESI cursor by one 0x38-byte authored
 * row while retaining the enclosing SubSegment base. Only row at +0x814 is
 * consumed through this overlapping analysis view. */
typedef struct SubSegmentRowStrideAnchor {
    uint8_t segment_prefix[0x814];
    AuthoredSegmentRow row;
} SubSegmentRowStrideAnchor;

/* Exact 0x1a5978-byte authored cRSubTracks level-definition owner. */
typedef struct SubTracks {
    int32_t segment_count;
    SubSegment segment_slots[100];
    SubSegment first_segment;
    SubSegment last_segment;
    int32_t random_length;
    uint8_t random_enabled;
    uint8_t unknown_1a58c9[0x1a58cc - 0x1a58c9];
    tColour fringe_color;
    char level_display_name[0x80];
    AuthoredFloatBits selected_speed;
    float garbage_frequency;
    float salt_frequency;
    int32_t landscape_script_index;
    int32_t parcel_count;
    int32_t track_texture_set;
    int32_t parcel_quota;
} SubTracks;

typedef enum TrackPickupState {
    TRACK_PICKUP_STATE_INACTIVE = 0,
    TRACK_PICKUP_STATE_ACTIVE = 1,
    TRACK_PICKUP_STATE_TEARDOWN_PENDING = 2,
} TrackPickupState;

/* Exact 0xb4-byte authored cRSubSpeedUp singleton. */
typedef struct SubSpeedUp {
    RenderableBod body;
    TrackPickupState state;
    Player* owner;
    uint8_t unknown_88[0x8c - 0x88];
    SubgameRuntime* owner_game;
    uint8_t unknown_90[0xac - 0x90];
    Sprite* sprite;
    uint8_t unknown_b0[0xb4 - 0xb0];
} SubSpeedUp;

/* Two authored cRBanner actors are embedded at SubgameRuntime +0x359080. */
typedef struct Banner {
    BodBase bod;
    int32_t visibility_mode;
    uint8_t _pad_3c[0x48 - 0x3c];
    SubgameRuntime* owner_game;
    uint8_t _pad_4c[0x54 - 0x4c];
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
    TrackPickupState state;
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

typedef enum ParcelState {
    PARCEL_STATE_INACTIVE = 0,
    PARCEL_STATE_TRACK_ACTIVE = 1,
    /* The updater preserves values 2 and 3, but no live Windows writer is known. */
    PARCEL_STATE_UNKNOWN_2 = 2,
    PARCEL_STATE_UNKNOWN_3 = 3,
    PARCEL_STATE_COLLECT_PENDING = 4,
    PARCEL_STATE_COLLECTING = 5,
    PARCEL_STATE_DELIVERY_PENDING = 6,
    PARCEL_STATE_DELIVERING = 7,
} ParcelState;

typedef struct Parcel {
    BodBase bod;
    ParcelState state;
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

/* Exact 0x28-byte authored cRGUI front-end controller. */
typedef struct GUI {
    SubgameRuntime* game;
    FrontendWidget* next_level_button;
    FrontendWidget* previous_level_button;
    FrontendWidget* level_name_widget;
    FrontendWidget* play_button;
    uint8_t _pad_14[0x18 - 0x14];
    FrontendWidget* back_button;
    FrontendWidget* speed_slider;
    FrontendWidget* difficulty_slider;
    FrontendWidget* replay_button;
} GUI;

/* Exact four-byte authored cRHelp front-end controller. */
typedef struct Help {
    FrontendWidget* back_button;
} Help;

/* Exact 0x24-byte authored cROptions front-end controller. */
typedef struct Options {
    int32_t previous_frontend_state;
    uint8_t active;
    uint8_t _pad_05[0x0b];
    FrontendWidget* back_widget;
    FrontendWidget* fullscreen_widget;
    FrontendWidget* sound_volume_widget;
    FrontendWidget* music_volume_widget;
    float previous_sample_volume;
} Options;

/* Exact 0x0c-byte global cRLoadingBar lifecycle owner. */
typedef struct LoadingBar {
    int32_t active;
    int32_t previous_percent;
    int32_t last_loading_budget;
} LoadingBar;

/* Exact 0x14-byte thanks-for-playing controller. */
typedef struct ThanksScreen {
    SubgameRuntime* game;
    FrontendWidget* message_widget;
    int32_t message_state;
    float message_progress;
    float message_progress_step;
} ThanksScreen;

typedef struct GalaxyRouteRecord {
    int32_t route_name_index;
    uint8_t _pad_04[0x08 - 0x04];
    float map_x;
    float map_y;
    float map_z;
    float route_tint_alpha;
    float highlight_target;
    char detail_text[0x80];
    char description_text[0x29c - 0x9c];
} GalaxyRouteRecord;

typedef struct GalaxyPoint {
    union {
        int32_t x_bits;
        float x;
    };
    union {
        int32_t y_bits;
        float y;
    };
} GalaxyPoint;

typedef struct GalaxyRouteSlot {
    int32_t unknown_000;
    GalaxyRouteRecord record;
} GalaxyRouteSlot;

typedef struct GalaxyRouteNameRecord {
    char name[0x80];
    int32_t star_count;
    tColour color;
    float map_x;
    float map_y;
    float map_z;
} GalaxyRouteNameRecord;

/* Exact 0x10fa8-byte authored cRGalaxy route-map controller. */
typedef struct Galaxy {
    uint8_t active;
    uint8_t _pad_01[0x04 - 0x01];
    int32_t route_mode;
    int32_t route_state;
    int32_t record_count;
    GalaxyRouteSlot route_slots[101];
    GalaxyRouteNameRecord route_names[10];
    SubgameRuntime* level_progress_base;
    FrontendWidget* exit_or_back_widget;
    FrontendWidget* route_title_widget;
    FrontendWidget* route_icon_widget;
    int32_t selected_index;
    int32_t hover_state;
    uint8_t _pad_10f88[0x10f8c - 0x10f88];
    FrontendWidget* bounds_frame_widget;
    FrontendWidget* selected_title_widget;
    FrontendWidget* selected_detail_widget;
    FrontendWidget* selected_description_widget;
    FrontendWidget* play_or_deliver_widget;
    FrontendWidget* replay_widget;
    int32_t unknown_10fa4;
} Galaxy;

typedef struct ContactTargetObject {
    void* vtable;
    int32_t list_flags;
} ContactTargetObject;

typedef struct ContactTargetEntry {
    int32_t kind;
    Vec3 position;
    float radius;
    ContactTargetObject* object;
} ContactTargetEntry;

/* Fixed-capacity per-frame contact registry. */
typedef struct EnemyManager {
    int32_t count;
    ContactTargetEntry entries[256];
} EnemyManager;

typedef struct FrontendWidgetTextBuffer {
    uint8_t raw[0x420];
} FrontendWidgetTextBuffer;

/* cRInputOK reuses the final 0x24 bytes of the tooltip interaction block. */
typedef struct InputOkState {
    uint8_t _pad_00[0x1c];
    FrontendWidget* source_widget;
    FrontendWidget* ok_widget;
} InputOkState;

typedef struct FrontendWidgetTooltip {
    uint8_t _pad_00[0x4];
    int32_t state;
    uint32_t mode_flags;
    FrontendWidget* owner_widget;
    float delay_progress;
    float delay_step;
    FrontendWidget* tooltip_widget;
    InputOkState input_ok_state;
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
    uint8_t sprite_wobble_positive;
    uint8_t _pad_5e[0x2];
    int32_t background_texture_id;
    int32_t texture_hit_test_sprite;
    int32_t sprite_extend_texture_c;
    uint8_t _pad_6c[0x10];
    int32_t widget_type;
    TwinkleManager twinkle_manager;
    float sprite_shadow_offset;
    float slider_position_target;
    float slider_position_current;
    float slider_hit_left;
    float slider_hit_right;
    float slider_hit_top;
    float slider_hit_bottom;
    int32_t shortcut_key_code;
    uint8_t _pad_198[0x8];
    FrontendWidgetFlag widget_flags;
    FrontendWidgetFlag previous_widget_flags;
    uint8_t _pad_1a8[0x4];
    tColour current_fill_color;
    tColour idle_fill_color;
    tColour hot_fill_color;
    tColour current_text_color;
    tColour idle_text_color;
    tColour hot_text_color;
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
    int32_t input_cursor;
    int32_t input_cursor_visible;
    float input_cursor_blink_progress;
    float input_cursor_blink_step;
    uint32_t input_flags;
    int32_t input_length;
    int32_t input_capacity;
    FrontendWidget* slider_less_widget;
    FrontendWidget* slider_more_widget;
    FrontendWidget* slider_value_widget;
} FrontendWidget;

/* Authored cRSubPause owner embedded in SubgameRuntime at +0x14. */
typedef struct SubPause {
    FrontendWidget* options_widget;
    FrontendWidget* end_game_widget;
    FrontendWidget* resume_widget;
} SubPause;

typedef struct TextureRef {
    TextureRefFlags flags;
    int32_t loaded_width;
    int32_t loaded_height;
    char name[0x8c - 0x0c];
    int32_t slot_index;
    int32_t frame_count;
    float frame_progress_step;
    void* texture_ref;
    uint8_t _pad_9c[0x4];
    int32_t mip_levels;
} TextureRef;

/* Authored empty cRProgressBar at Player +0x3f0. */
typedef struct ProgressBar {
    uint8_t _empty;
} ProgressBar;

typedef enum WarningState {
    WARNING_STATE_INACTIVE = 0,
    WARNING_STATE_OPAQUE = 1,
    WARNING_STATE_FADING = 2,
} WarningState;

/*
 * Authored cRWarning, exact 0x10-byte Windows owner at Player +0x3f4.
 * Native functions: initialize_warning @ 0x446e80, uninit_warning @ 0x446f10,
 * start_warning @ 0x446f30, stop_warning @ 0x446f50,
 * stop_warning_sample @ 0x446f60, and update_warning @ 0x446f80.
 * Mobile variants retain the owner and lifecycle but add fields before border.
 */
typedef struct Warning {
    WarningState state;
    float phase;
    float phase_step;
    FrontendWidget* border;
} Warning;

/*
 * Authored cRTimesUp countdown actor at SubgameRuntime +0x1272828. Native
 * functions: update_times_up @ 0x445e20, uninit_times_up @ 0x445e70.
 */
typedef enum TimesUpState {
    TIMES_UP_STATE_INACTIVE = 0,
    TIMES_UP_STATE_DISPLAYING = 1,
    TIMES_UP_STATE_EXPIRED = 2,
} TimesUpState;

typedef struct TimesUp {
    TimesUpState state;
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
typedef struct Salt {
    RenderableBod body;
    uint32_t state;
    uint8_t _pad_84[0x4];
    SubgameRuntime* owner_game;
    float fade_alpha;
    float spawn_velocity_y;
    uint8_t collision_armed;
    uint8_t _pad_95[0x03];
} Salt;

typedef Salt SaltHazardSlot;

/*
 * SubLazer projectile runtime slot. Pool lives at `SubgameRuntime +0x356b00`
 * with 20 owned slots and stride 0xb0. Each slot borrows its containing
 * subgame and is fired by Wall2 tile emitters through cRSubLazerManager::Shoot.
 * Native functions: initialize_sub_lazer_pool
 * @ 0x441650, spawn_sub_lazer_projectile @ 0x441670,
 * deactivate_sub_lazer_projectile @ 0x441740, update_sub_lazer_projectile
 * @ 0x4417d0.
 */
enum SubLazerState {
    SUB_LAZER_STATE_INACTIVE = 0,
    SUB_LAZER_STATE_ACTIVE = 1,
    SUB_LAZER_STATE_RECYCLE_PENDING = 2,
};

enum {
    SUB_LAZER_SLOT_CAPACITY = 20,
};

typedef struct SubLazer {
    RenderableBod body;
    uint32_t state;
    uint8_t _pad_84[0x4];
    SubgameRuntime* owner_game;
    Vec3 velocity;
    float sprite_bob_phase;
    float sprite_bob_phase_step;
    uint8_t _pad_a0[0x10];
} SubLazer;

typedef SubLazer SubLazerSlot;

/* Exact 0x74-byte authored cRSubHealth pickup slot. */
typedef struct SubHealth {
    BodNode bod;
    Vec3 world_position;
    uint8_t _pad_1c[0x38 - 0x1c];
    TrackPickupState state;
    Player* owner;
    uint8_t _pad_40[0x44 - 0x40];
    SubgameRuntime* owner_game;
    uint8_t _pad_48[0x64 - 0x48];
    Sprite* sprite;
    TrackRowCell* source_cell;
    float bob_phase;
    float bob_phase_step;
} SubHealth;

typedef SubHealth TrackHealthPickup;

/* Exact 0xec-byte authored cRSlug hazard slot. */
enum SubSlugState {
    SUB_SLUG_STATE_INACTIVE = 0,
    SUB_SLUG_STATE_ACTIVE = 1,
    SUB_SLUG_STATE_DEATH_TOSS_PENDING = 2,
    SUB_SLUG_STATE_TEARDOWN_PENDING = 3,
    SUB_SLUG_STATE_LATERAL_ACTIVE = 4,
};

enum SubSlugDeathTossDirection {
    SUB_SLUG_DEATH_TOSS_RIGHT = 1,
    SUB_SLUG_DEATH_TOSS_LEFT = 2,
};

enum {
    SUB_SLUG_SLOT_CAPACITY = 8,
};

typedef struct Slug {
    RenderableBod body;
    int32_t state;
    int32_t death_toss_direction;
    SubgameRuntime* owner_game;
    Vec3 velocity;
    float attachment_facing_angle;
    uint8_t unknown_9c[0xac - 0x9c];
    Sprite* sprite;
    TrackRowCell* source_cell;
    uint8_t passed_player;
    uint8_t _pad_b5[0xb8 - 0xb5];
    float lateral_phase;
    float lateral_phase_step;
    Player* owner_player;
    int32_t engagement_voice_gate;
    int32_t hit_points;
    uint8_t hit_flash_pending;
    uint8_t _pad_cd[0xd0 - 0xcd];
    float hit_flash_progress;
    float hit_flash_progress_step;
    uint8_t voice_active;
    uint8_t player_encounter_latched;
    uint8_t _pad_da[0xdc - 0xda];
    float voice_progress;
    float voice_progress_step;
    float blink_progress;
    float blink_step;
} Slug;

typedef struct SlugPool {
    Slug slots[SUB_SLUG_SLOT_CAPACITY];
} SlugPool;

typedef struct SubLazerManager {
    SubLazer slots[SUB_LAZER_SLOT_CAPACITY];
} SubLazerManager;

typedef struct SaltManager {
    Salt slots[40];
} SaltManager;

typedef struct SubGarbage SubGarbage;
struct SubGarbage {
    RenderableBod body;
    SubGarbage* next_active;
    int32_t state;
    int32_t collision_side;
    SubgameRuntime* owner_game;
    Vec3 velocity;
    float radius;
    float attachment_facing_angle;
    int32_t unknown_a4;
    float burst_rate_step;
    float smoke_timer;
    float smoke_timer_step;
    Sprite* sprite;
    TrackRowCell* source_cell;
    uint8_t hidden;
    uint8_t _pad_bd[0xc0 - 0xbd];
    Player* owner_player;
};

typedef SubGarbage GarbageHazardSlot;

typedef struct SubGarbagePool {
    SubGarbage* active_head;
    SubGarbage slots[50];
} SubGarbagePool;

typedef SubGarbagePool GarbageHazardPool;

typedef enum SubRingState {
    SUB_RING_STATE_INACTIVE = 0,
    SUB_RING_STATE_ACTIVE = 1,
    SUB_RING_STATE_COLLECT_PENDING = 2,
    SUB_RING_STATE_COLLECTING = 3,
    SUB_RING_STATE_EXPAND_PENDING = 4,
    SUB_RING_STATE_EXPANDING = 5,
} SubRingState;

typedef enum SubRingKind {
    /* No live Windows producer has been recovered for kinds 0 or 1 yet. */
    SUB_RING_KIND_UNKNOWN_0 = 0,
    SUB_RING_KIND_UNKNOWN_1 = 1,
    SUB_RING_KIND_EXPLODE_RAMP = 2,
    SUB_RING_KIND_SLOW_DEFAULT = 3,
    SUB_RING_KIND_NORMAL_DEFAULT = 4,
    SUB_RING_KIND_NORMAL_AUTHORED = 5,
    SUB_RING_KIND_EXPLODE_AUTHORED = 6,
    SUB_RING_KIND_SLOW_AUTHORED = 7,
    SUB_RING_KIND_POWER_UP_AUTHORED = 8,
} SubRingKind;

typedef struct SubRing SubRing;

typedef struct SubRingStar {
    Sprite* sprite;
    SubRing* parent;
    Vec3 base_position;
    float phase;
    float phase_step;
    float radius;
} SubRingStar;

struct SubRing {
    RenderableBod body;
    SubRingState state;
    Player* owner_player;
    SubRingKind kind;
    int32_t owner_lives_snapshot;
    SubRingStar particles[10];
    SubgameRuntime* rate_source;
    float transition_progress;
    float transition_step;
    uint8_t oscillate_x;
    uint8_t _pad_1dd[0x1e0 - 0x1dd];
    float active_phase;
    float active_phase_step;
    int32_t star_shower_counter;
    int32_t star_sprite_id;
    uint8_t _pad_1f0[0x1f8 - 0x1f0];
};

typedef SubRingStar RingOrSpecialEffectParticle;
typedef SubRing RingOrSpecialEffectParent;

typedef struct SubRingPool {
    SubRing slots[2];
} SubRingPool;

typedef SubRingPool RingOrSpecialEffectPool;

/*
 * Analysis-only manager-relative view used while VC6 retains
 * `SubgameRuntime + slot_index * sizeof(SubRing)` instead of materializing a
 * direct SubRing pointer. The prefix is not separately owned storage: `ring`
 * aliases one of SubgameRuntime::ring_effects.slots.
 */
typedef struct SubRingSlotCursor {
    uint8_t subgame_prefix[0x35b78c];
    SubRing ring;
} SubRingSlotCursor;

/*
 * Analysis-only manager-relative views for the byte-strided pool sweeps in
 * Player::handle_subgoldy_collisions. Each prefix aliases the enclosing
 * SubgameRuntime; the final field is one embedded slot, not separately owned
 * storage. The views preserve native `subgame + slot_offset` cursor lifetimes
 * without misrepresenting them as additional SubgameRuntime instances.
 */
typedef struct SubHealthSlotCursor {
    uint8_t subgame_prefix[0x356000];
    SubHealth health;
} SubHealthSlotCursor;

typedef struct SlugSlotCursor {
    uint8_t subgame_prefix[0x3563a0];
    Slug slug;
} SlugSlotCursor;

typedef struct SubLazerSlotCursor {
    uint8_t subgame_prefix[0x356b00];
    SubLazer sub_lazer;
} SubLazerSlotCursor;

typedef struct SaltSlotCursor {
    uint8_t subgame_prefix[0x3578c0];
    Salt salt;
} SaltSlotCursor;

typedef struct ParcelSlotCursor {
    uint8_t subgame_prefix[0x125e480];
    Parcel parcel;
} ParcelSlotCursor;

typedef struct SlugVoiceManager {
    uint8_t active;
    uint8_t _pad_01[0x3];
    float progress;
    float step;
} SlugVoiceManager;

typedef struct FringeManager {
    FringeObject objects[7000];
    int32_t count;
} FringeManager;

/* Exact 0x330-byte authored cRTimeTrial owner. */
typedef struct TimeTrial {
    uint8_t _storage[0x330];
} TimeTrial;

/* Exact 0x3c-byte authored cRBarrier tutorial actor. */
typedef struct BarrierActor {
    BodBase bod;
    Player* owner_player;
} BarrierActor;

typedef struct ActiveLandscapeEntry {
    RenderableBod bod;
    int32_t state;
    uint8_t _pad_84[0x88 - 0x84];
    float repeat_z_span;
    RenderableBod* reference_bod;
} ActiveLandscapeEntry;

typedef struct LandscapeScriptRecord {
    int32_t id;
    char name[0x84 - 0x04];
    int32_t backdrop_texture_id;
    uint8_t split_backdrop_texture_pair;
    char backdrop_texture_path[0x10c - 0x89];
    int32_t object_index;
    tColour fog_color;
    float distort;
} LandscapeScriptRecord;

typedef struct LandscapeManager {
    ActiveLandscapeEntry active_entries[10];
    int32_t script_count;
    LandscapeScriptRecord scripts[128];
} LandscapeManager;

/*
 * Bounded view of the Object prefix inherited by FrameSequence. The renderer
 * lane owns the complete Object declaration; this path/subgame lane only needs
 * the independently consumed face array and count.
 */
typedef struct FrameSequenceObjectView {
    uint8_t _pad_00[0x54];
    int32_t facequad_count;
    int32_t facequad_capacity;
    ObjectFaceQuad* facequads;
    uint8_t _pad_60[0xdc - 0x60];
} FrameSequenceObjectView;

typedef enum FrameSequenceFlag {
    FRAME_SEQUENCE_COMPLETE = 0x01,
    FRAME_SEQUENCE_LOOP = 0x02,
    FRAME_SEQUENCE_PING_PONG = 0x04,
    FRAME_SEQUENCE_REVERSE = 0x08,
    FRAME_SEQUENCE_PAUSED = 0x10,
} FrameSequenceFlag;

/* Exact 0xf0-byte Object-derived animated texture sequence. */
typedef struct FrameSequence {
    FrameSequenceObjectView object;
    int32_t sequence_flags;
    int32_t current_frame_index;
    float phase;
    float phase_step;
    TextureRef* current_texture_ref;
} FrameSequence;

typedef struct SmtrackHeightfieldAnimator {
    BodBase bod;
    FrameSequence frame_sequence;
} SmtrackHeightfieldAnimator;

typedef struct SegmentCatalogEntry {
    char display_name[0x40];
    char filename[0x40];
    int32_t id;
    int32_t row_count;
    char glyph_columns[0x100][8];
    AuthoredSegmentRow rows[256];
} SegmentCatalogEntry;

/* Native selected-entry cursor anchored four bytes before the entry while
 * indexing 0x4088-byte records from the SMTracks base. */
typedef struct SegmentCatalogEntryAnchor {
    int32_t stride_prefix_word;
    SegmentCatalogEntry entry;
} SegmentCatalogEntryAnchor;

/* Overlapping analysis view for the importer's flattened 0x38-byte row
 * induction. Only row at +0x88c is consumed through this cursor. */
typedef struct SegmentCatalogRowStrideAnchor {
    uint8_t catalog_prefix[0x88c];
    AuthoredSegmentRow row;
} SegmentCatalogRowStrideAnchor;

typedef struct SMTracks {
    int32_t count;
    SegmentCatalogEntry entries[150];
} SMTracks;

typedef struct TextureRefList {
    int32_t count;
    int32_t capacity;
    TextureRef entries[1];
} TextureRefList;

typedef enum SubLocOpenEdgeFlag {
    SUBLOC_OPEN_PREVIOUS_ROW = 0x01,
    SUBLOC_OPEN_NEXT_ROW = 0x02,
    SUBLOC_OPEN_NEXT_LANE = 0x04,
    SUBLOC_OPEN_PREVIOUS_LANE = 0x08,
    SUBLOC_OPEN_EDGE_MASK = 0x0f,
} SubLocOpenEdgeFlag;

typedef enum SubLocFlag {
    SUBLOC_LANE_INDEX_MASK = 0x0007,
    SUBLOC_FLAG_SUPPRESS_SALT_SPAWN = 0x0008,
    SUBLOC_FLAG_SUPPRESS_GARBAGE_SPAWN = 0x0010,
    SUBLOC_FLAG_RANDOM_HAZARD_BLOCKED = 0x0018,
    SUBLOC_FLAG_WARNING_CACHE_FAMILY = 0x0020,
    SUBLOC_FLAG_CACHE_FAMILY_SWAPPED = 0x0040,
    SUBLOC_MERGED_RUN_WIDTH_ONE = 0x0100,
    SUBLOC_MERGED_RUN_WIDTH_REMAINDER_MASK = 0x0e00,
    SUBLOC_MERGED_RUN_WIDTH_MASK = 0x0f00,
    SUBLOC_MERGED_RUN_WIDTH_SHIFT = 8,
    SUBLOC_MERGED_RUN_WIDTH_VALUE_MASK = 0x000f,
    SUBLOC_FLAG_AI_ENABLED = 0x2000,
    SUBLOC_FLAG_UNCACHED_BODY = 0x4000,
    SUBLOC_FLAG_CORNER_OBJECT = 0x8000,
} SubLocFlag;

typedef struct TrackRowCell {
    BodNode bod;
    Vec3 anchor_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    tColour color;
    struct Path* attachment_template_record;
    uint8_t tile_id;
    uint8_t open_edge_mask;
    uint8_t _pad_3e[0x2];
    uint32_t lane_and_flags;
    FringeObject* fringe_front;
    FringeObject* fringe_right;
    FringeObject* fringe_left;
    FringeObject* fringe_back;
} TrackRowCell;

typedef enum SubRowFlag {
    SUBROW_FLAG_PARCEL_CANDIDATE = 0x0001,
    SUBROW_FLAG_ROW_MODEL_PRESENT = 0x0002,
    SUBROW_FLAG_SUPPRESS_TRACK_RENDER = 0x0004,
    SUBROW_FLAG_PATH_OR_MODEL_VELOCITY = 0x0008,
    SUBROW_FLAG_PARCEL_SPAWN_REQUESTED = 0x0010,
    SUBROW_FLAG_MIRRORED = 0x0020,
    SUBROW_FLAG_PRIMARY_ATTACHMENT = 0x0040,
    SUBROW_FLAG_SECONDARY_ATTACHMENT = 0x0080,
    SUBROW_ATTACHMENT_MASK = 0x00c0,
    SUBROW_FLAG_NO_FALL = 0x0100,
    SUBROW_FLAG_RING_NONE = 0x0200,
    SUBROW_FLAG_RING_NORMAL = 0x0400,
    SUBROW_FLAG_RING_EXPLODE = 0x0800,
    SUBROW_FLAG_RING_SLOW = 0x1000,
    SUBROW_FLAG_RING_POWER_UP = 0x2000,
    SUBROW_FLAG_PARCEL_Z_IS_LOCAL = 0x4000,
    SUBROW_FLAG_JETPACK_OFF = 0x8000,
} SubRowFlag;

typedef struct SubRow {
    uint32_t flags;
    RenderableBod primary_body;
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
} SubRow;

/* Native retains the enclosing SubgameRuntime base while advancing one
 * 0xf4-byte runtime-row lane. Only row at +0x5ccac8 is consumed here. */
typedef struct RuntimeRowStrideAnchor {
    uint8_t runtime_prefix[0x5ccac8];
    SubRow row;
} RuntimeRowStrideAnchor;

/* Native likewise carries a SubgameRuntime-relative 0x54-byte cell cursor.
 * The immediate lane neighbors are one cell stride away, the same-lane row
 * neighbors are one eight-cell row stride (0x2a0) away, and update_subgame's
 * projected ring cell is six rows (0xfc0) ahead of the current cell at
 * +0x3bfac8. */
typedef struct RuntimeCellStrideAnchor {
    uint8_t runtime_prefix_before_previous_row_same_lane[0x3bf828];
    TrackRowCell previous_row_same_lane;
    uint8_t runtime_gap_previous_row_to_previous_lane[0x1f8];
    TrackRowCell previous_lane_same_row;
    TrackRowCell cell;
    TrackRowCell next_lane_same_row;
    uint8_t runtime_gap_next_lane_to_next_row[0x1f8];
    TrackRowCell next_row_same_lane;
    uint8_t runtime_gap_next_row_to_projected_row[0xccc];
    TrackRowCell projected_row_six_ahead_same_lane;
} RuntimeCellStrideAnchor;

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

typedef enum ObjectFaceQuadFlag {
    OBJECT_FACEQUAD_FLAG_TRIANGLE = 0x80,
} ObjectFaceQuadFlag;

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

/* Authored four-float Windows AxisAngle value; Android calls it tAxis. */
typedef struct AxisAngle {
    float x;
    float y;
    float z;
    float angle;
} AxisAngle;

/* Authored four-float tQuaternian value retained by the Android symbols. */
typedef struct Quaternion {
    float x;
    float y;
    float z;
    float w;
} Quaternion;

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
    tColourSmall skirt_color_bgra;
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
    tColourSmall white_color;
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
    uint8_t force_camera_update;
    uint8_t _pad_cd[0x3];
    float attachment_lift_envelope;
    float smoothed_attachment_lift_envelope;
} Cameraman;

typedef enum DamageGuageState {
    DAMAGE_GUAGE_STATE_MONITORING = 0,
    DAMAGE_GUAGE_STATE_WARNING_TRANSITION = 1,
    DAMAGE_GUAGE_STATE_DRAINING = 2,
} DamageGuageState;

/* Authored cRDamageGuage, exact 0x2c contact-damage owner. */
typedef struct DamageGuage {
    DamageGuageState state;
    float pulse_progress;
    float pulse_step;
    /* Cleared by Init on Windows and Android; no live consumer is proved. */
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

typedef enum SubHoverState {
    SUB_HOVER_STATE_INACTIVE = 0,
    SUB_HOVER_STATE_ACTIVE = 1,
} SubHoverState;

/* Authored cRSubHover, exact 0x214-byte hover and jet-VFX owner. */
typedef struct SubHover {
    float progress;
    float progress_step;
    uint8_t _pad_08[0x4];
    SubHoverState state;
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

typedef enum CutSceneState {
    CUT_SCENE_STATE_INACTIVE = 0,
    CUT_SCENE_STATE_INTRO_PENDING = 1,
    CUT_SCENE_STATE_INTRO_ACTIVE = 2,
    CUT_SCENE_STATE_COMPLETION_PENDING = 5,
    CUT_SCENE_STATE_COMPLETION_BLEND = 6,
    CUT_SCENE_STATE_COMPLETION_HOLD = 7,
    CUT_SCENE_STATE_INTRO_RETURN_BLEND = 8,
    CUT_SCENE_STATE_INTRO_FINISH = 9,
    CUT_SCENE_STATE_DEATH_PENDING = 10,
    CUT_SCENE_STATE_DEATH_BLEND = 11,
    CUT_SCENE_STATE_DEATH_HOLD = 12,
} CutSceneState;

/* Authored cRCutScene, exact 0x5c-byte camera state-machine owner. */
typedef struct CutScene {
    Snail* presentation;
    Player* player;
    int32_t camera_mode;
    CutSceneState state;
    TransformMatrix live_matrix;
    float progress;
    float progress_step;
    uint8_t force_camera_update;
    uint8_t _pad_59[0x3];
} CutScene;

typedef enum ObjectAnimationFlag {
    OBJECT_ANIMATION_MODE_LOOP = 1,
    OBJECT_ANIMATION_MODE_PING_PONG = 2,
    OBJECT_ANIMATION_MODE_ONCE = 4,
    OBJECT_ANIMATION_MODE_ONCE_REVERSE = 8,
} ObjectAnimationFlag;

typedef enum ObjectAnimationModeOverride {
    OBJECT_ANIMATION_MODE_UNCHANGED = -1,
} ObjectAnimationModeOverride;

typedef uint16_t ObjectAnimationFlags;

typedef struct ObjectAnimationFrame {
    Vec3* vertices;
    Vec3* facequad_normals;
} ObjectAnimationFrame;

typedef struct ObjectAnimation {
    ObjectAnimationFlags flags;
    uint8_t _pad_02[0x2];
    int32_t generated_frame_count;
    ObjectAnimationFrame** frames;
    float progress;
    float progress_step;
} ObjectAnimation;

/* One owned 0x80-byte Windows presentation-animation donor slot. */
typedef struct PresentationAnimationSlot {
    RenderableBod body;
} PresentationAnimationSlot;

/* Authored cRAnimManager, exact 0x48-byte queued animation owner. */
struct AnimManager {
    int32_t state;
    float progress;
    float progress_step;
    ObjectAnimation* active_animation;
    uint8_t completed;
    uint8_t _pad_11[0x3];
    int32_t queued_animations[10];
    int32_t queue_count;
    RenderableBod* target_model;
    PresentationAnimationSlot* animation_slots;
};

/* Authored cRWeapon, exact 0x3dc-byte animation-channel owner. */
typedef struct Weapon {
    RenderableBod body;
    uint8_t _pad_80[0x104 - 0x80];
    int32_t selected_state;
    AnimManager anim_manager;
    PresentationAnimationSlot animation_slots[5];
    Vec3 release_step;
} Weapon;

/* Authored cRSnailSkin, exact 0x20-byte material-selection owner. */
typedef struct SnailSkin {
    int32_t selected_slot;
    TextureRef* material_overrides[3];
    Snail* owner_snail;
    int32_t active;
    float progress;
    float progress_step;
} SnailSkin;

/*
 * Exact 0x10-byte view over four adjacent cRSnail wobble lanes. The grouping
 * is analytical; no cross-port symbol proves a separate authored C++ child.
 */
typedef struct PresentationWobbleController {
    float roll_phase;
    float roll_phase_step;
    float lift_phase;
    float lift_phase_step;
} PresentationWobbleController;

typedef enum InvincibleState {
    INVINCIBLE_STATE_INACTIVE = 0,
    INVINCIBLE_STATE_FADING_IN = 1,
    INVINCIBLE_STATE_ACTIVE = 2,
    INVINCIBLE_STATE_FADING_OUT = 3,
} InvincibleState;

/* Authored cRInvincible, exact 0xa4-byte spinning shell visual owner. */
typedef struct Invincible {
    RenderableBod body;
    InvincibleState state;
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
    RenderableBod body;
    TransformMatrix previous_live_matrix;
    TransformMatrix cached_cutscene_matrix;
    Player* owner_player;
    AnimManager anim_manager;
    PresentationAnimationSlot cutscene_animation_slots[10];
    Weapon weapon_channels[3];
    Weapon jetpack_channel;
    PresentationWobbleController wobble;
    RenderableBod snail_hotspot_source_body;
    RenderableBod snail_hotspot_body;
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

typedef enum NukeState {
    NUKE_STATE_INACTIVE = 0,
    NUKE_STATE_ACTIVE = 1,
} NukeState;

/* Authored cRNuke, exact 0x7c-byte collision-ring effect owner. */
typedef struct Nuke {
    NukeState state;
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

typedef enum ClickStartState {
    CLICK_START_STATE_INACTIVE = 0,
    CLICK_START_STATE_UNKNOWN_1 = 1,
    CLICK_START_STATE_WAITING_FOR_START = 2,
    CLICK_START_STATE_START_PENDING = 3,
    CLICK_START_STATE_TEARDOWN = 4,
} ClickStartState;

/* Authored cRClickStart, exact 0xac-byte RenderableBod child. */
typedef struct ClickStart {
    RenderableBod bod;
    ClickStartState state;
    FrontendWidget* prompt;
    float teardown_progress;
    float teardown_progress_step;
    uint8_t _pad_90[0x8];
    Player* owner_player;
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

/* Authored root cRHighScore owner. The proved 0xf4-byte widget bank is
 * followed by a separate 0x14-byte root gap before TipManager. */
typedef struct HighScore {
    int32_t field_00;
    int32_t mode;
    int32_t selected_bank;
    uint8_t _pad_0c[0x10 - 0x0c];
    uint8_t entering_name;
    uint8_t _pad_11[0x14 - 0x11];
    int32_t selected_rank;
    FrontendWidget* title_widget;
    FrontendWidget* back_button;
    FrontendWidget* bank_toggle_button;
    FrontendWidget* cancel_name_button;
    FrontendWidget* submit_name_button;
    FrontendWidget* row_background_widgets[10];
    FrontendWidget* rank_row_widgets[10];
    FrontendWidget* name_row_widgets[10];
    FrontendWidget* score_row_widgets[10];
    FrontendWidget* replay_row_widgets[10];
} HighScore;

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
    SubgameRuntime* game;
    uint8_t _pad_10[0xc];
} Tutorial;

typedef enum CompletionState {
    COMPLETION_STATE_INACTIVE = 0,
    COMPLETION_STATE_STAGING_PARCELS = 1,
    COMPLETION_STATE_WAITING_FOR_DELIVERIES = 2,
    COMPLETION_STATE_SUMMARY_PENDING = 3,
    COMPLETION_STATE_SUMMARY_ACTIVE = 4,
    COMPLETION_STATE_CONTINUE_ACCEPTED = 5,
    COMPLETION_STATE_EMPTY_DELIVERY_DELAY = 6,
} CompletionState;

typedef struct Completion {
    void* widget_a;
    void* delivered_count_widget;
    void* bonus_widget;
    void* widget_d;
    void* continue_widget;
    CompletionState state;
    uint8_t gate_18;
    uint8_t _pad_19[0x3];
    int32_t parcel_target_count;
    int32_t bonus_enabled;
    int32_t staged_parcel_count;
    int32_t delivered_parcel_count;
    float progress;
    float progress_step;
    Vec3 widget_world;
    float bonus_blink_progress;
    float bonus_blink_step;
    int32_t bonus_score;
    int32_t display_token;
} Completion;

typedef struct ReplayRunRecord {
    int16_t lateral_x;
    int16_t delta_z;
    uint16_t flags;
} ReplayRunRecord;

typedef union SubSolutionScoreOrTime {
    float total_seconds;
    int32_t score_buckets[6];
    Time timer;
} SubSolutionScoreOrTime;

typedef union SubSolutionScalar {
    int32_t bits;
    float value;
} SubSolutionScalar;

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
    SubSolutionScalar challenge_difficulty_scalar;
    uint32_t runtime_build_flags;
    int32_t high_score_mode_tag;
    int32_t route_or_rank_index;
    int32_t replay_cursor;
    SubSolutionScalar replay_speed_scalar;
    int32_t challenge_speed_value;
    int32_t challenge_difficulty_value;
    char player_name[0x14];
    int32_t runtime_build_seed;
    int32_t replay_sample_count;
    ReplayRunRecord run_records[21600];
    SubSolutionScalar garbage_frequency;
    SubSolutionScalar salt_frequency;
    int32_t unknown_1fab8;
    int32_t unknown_1fabc;
} SubSolution;

/* Analysis-only SubgameRuntime-relative view for update_subgame's native
 * `game + route_index * sizeof(SubSolution)` cursor. The prefix aliases the
 * enclosing runtime and the terminal field aliases one record owned by
 * SubHighScore::time_trial_route_records; this is not additional storage. */
typedef struct TimeTrialRouteRecordCursor {
    uint8_t subgame_prefix[0x944150];
    SubSolution record;
} TimeTrialRouteRecordCursor;

/* Stable prefix of the variable cRSubSolutionHeader record: byte_count is
 * 0x88 + replay_sample_count * 5 for two int16 lanes and one byte lane. */
typedef struct CompactHighScoreRecord {
    int32_t byte_count;
    int32_t score;
    SubSolutionScoreOrTime score_or_time;
    int32_t score_tail;
    int32_t source_tail;
    int32_t checksum;
    int32_t replay_level_index;
    int32_t replay_mode_id;
    uint8_t reserved_34[0x4];
    uint32_t runtime_build_flags;
    int32_t bank_selector;
    int32_t entry_index;
    int32_t replay_cursor;
    SubSolutionScalar replay_speed_scalar;
    int32_t challenge_speed_value;
    int32_t challenge_difficulty_value;
    SubSolutionScalar challenge_difficulty_scalar;
    uint8_t reserved_58[0x4];
    char player_name[0x14];
    int32_t runtime_build_seed;
    int32_t replay_sample_count;
    SubSolutionScalar garbage_frequency;
    SubSolutionScalar salt_frequency;
    int32_t unknown_80;
    int32_t unknown_84;
    uint8_t replay_payload[1];
} CompactHighScoreRecord;

/* Exact 0x947648-byte authored cRSubHighScore bank embedded in cRSubGame. */
typedef struct SubHighScore {
    SubSolution* active_record_bank;
    int32_t active_record_count;
    SubSolution postal_records[11];
    SubSolution survival_records[11];
    SubSolution time_trial_route_records[51];
    SubSolution current_result_record;
    SubSolution survival_pending_record;
} SubHighScore;

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
    /* Cross/dot-derived lateral source, mirrored and clamped by
     * finalize_path_template. */
    float lateral_source;
} PathTemplateSample;

/* Authored cRPath, exact 0xa8 bytes. Windows stores 126 instances as 63
 * adjacent primary/secondary PathPair records in SubgameRuntime. */
typedef struct Path {
    BodBase bod;
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
    BodBase fringe_mesh_bod;
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
    Vec3 orientation_up;
    Vec3 output_position;
    Player* player;
    /* Cleared while rebuilding runtime cells and consumed by update_subgoldy.
     * No nonzero producer has been recovered, so retain the neutral name. */
    uint8_t flag_3c;
    uint8_t _pad_3d[0x3];
} FollowState;

typedef struct GolbPathFollowState {
    uint8_t active;
    uint8_t _pad_01[0x3];
    Path* template_record;
    TrackRowCell* source_cell;
    int32_t sample_index;
    float progress;
    float vertical_offset;
    Vec3 output_position;
    struct GolbShot* shot;
} GolbPathFollowState;

typedef struct GolbShot {
    union {
        struct {
            RenderableBod primary_body;
            RenderableBod secondary_body;
            uint8_t _pad_100[0x114 - 0x100];
            struct GolbShot* vapour_owner_shot;
            RenderableBod tertiary_body;
        };
        struct {
            uint8_t _pad_000[0x080];
            Vapour vapour;
            uint8_t _pad_114[0x150 - 0x114];
            TransformMatrix live_matrix;
        };
    };
    ContactTargetObject* homing_target_object;
    Vec3 homing_target;
    struct GolbShot* rocket_owner_shot;
    float homing_blend;
    float homing_blend_step;
    float spin;
    float spin_step;
    uint8_t skip_one_tick;
    uint8_t slug_bounce_armed;
    uint8_t _pad_1be[0x2];
    int32_t kind;
    TransformMatrix flight_transform;
    TransformMatrix previous_flight_transform;
    int32_t state;
    void* render_body_owner;
    Vec3 velocity;
    Vec3 direction;
    float path_factor;
    float lifetime;
    float lifetime_step;
    SubgameRuntime* game;
    void* object_ref;
    Player* owner_player;
    TransformMatrix source_matrix;
    GolbPathFollowState path_follow;
    float path_entry_z_latch;
} GolbShot;

typedef struct Player {
    RenderableBod body;
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
    int32_t timer_360_state;
    int32_t unknown_364;
    float timer_360_progress;
    float timer_360_step;
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
    int32_t unused_274c;
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

typedef union RuntimeRateOrLevelArg {
    float base_rate;
    int32_t level_arg_tail;
} RuntimeRateOrLevelArg;

/*
 * Authored cRSubGame owner embedded in the root runtime. This campaign keeps
 * the broad object sparse, but the complete Player child at +0x3bb764 is now
 * represented as ownership rather than flattened score/presentation aliases.
 */
typedef struct SubgameRuntime {
    uint8_t scan_reset;
    uint8_t camera_snap_requested;
    uint8_t track_mirror_enabled;
    uint8_t unknown_000003;
    int32_t track_mirror_repeat_count;
    uint8_t resume_requested;
    uint8_t subgame_pause_gate;
    uint8_t unknown_00000a[0x0c - 0x0a];
    float pause_fade;
    float pause_fade_step;
    SubPause sub_pause;
    int32_t runtime_row_scan_begin;
    int32_t runtime_row_scan_end;
    int32_t completion_bonus_x_source;
    int32_t completion_bonus_y_source;
    RuntimeRateOrLevelArg rate_or_level_arg;
    float challenge_difficulty_scalar;
    float subgame_rate;
    int32_t subgame_state;
    int32_t level_mode;
    int32_t level_mode_arg;
    float base_subgame_rate;
    uint32_t runtime_flags; /* SubgameRuntimeFlag bits/full preset word. */
    int32_t first_block_row_count;
    int32_t runtime_row_count;
    int32_t completion_row_start;
    SegmentCache segment_cache;
    uint8_t track_state_latch;
    uint8_t _pad_a855[0x3];
    Tutorial tutorial;
    SubTracks level_definition;
    SubTracks level_definition_scratch;
    BodBase fringe_attachment_list_head;
    BodBase track_body_list_head;
    BodBase barrier_sub_lazer_list_head;
    BodBase salt_hazard_list_head;
    BodBase landscape_slice_list_head;
    BodBase unknown_bod_355c7c;
    BodBase special_track_cell_list_head;
    BodBase unknown_bod_355cec;
    BodBase golb_vapour_list_head;
    BodBase unknown_bod_355d5c;
    int32_t active_level_score;
    Time active_level_timer;
    SubSpeedUp speedup_pickup;
    JetPack jetpack_pickup;
    SubHealth health_pickups[8];
    SlugPool slug_hazards;
    SubLazerManager sub_lazers;
    SaltManager salt_hazards;
    BannerPool banners;
    SubGarbagePool garbage_hazards;
    SubRingPool ring_effects;
    SlugVoiceManager slug_voice_manager;
    FrontendWidget* top_score_widget;
    FrontendWidget* bottom_score_widget;
    FrontendWidget* lives_icon_widget;
    FrontendWidget* lives_text_widget;
    FrontendWidget* life_stock_widgets[9];
    FringeManager fringe_manager;
    int32_t blink_random_index;
    float blink_random_samples[24];
    Player player;
    TrackRowCell runtime_cells[3200][8];
    SubRow runtime_rows[3200];
    SubHighScore sub_high_score;
    SubSolution current_high_score_record;
    uint8_t selected_level_record_active;
    uint8_t selected_level_record_persistent;
    uint8_t _pad_ff25d2[0x2];
    SubSolution* selected_level_record;
    int32_t selected_level_record_cursor;
    int32_t replay_update_cursor;
    TimeTrial time_trial;
    PathManager path_manager;
    uint8_t _pad_ff2911[0xff2914 - 0xff2911];
    PathPair path_pairs[63];
    BarrierActor barrier;
    LandscapeManager landscape_manager;
    SmtrackHeightfieldAnimator smtrack_heightfield;
    SMTracks sm_tracks;
    ParcelManager parcel_manager;
    float garbage_frequency;
    float salt_frequency;
    GUI gui;
    Help help;
    ThanksScreen thanks_screen;
    Galaxy galaxy;
    int32_t subgame_rebuild_selector;
    float next_slug_voice_trigger_z;
    float slug_voice_trigger_spacing_z;
    EnemyManager enemy_manager;
    Completion completion;
    TimesUp times_up;
} SubgameRuntime;

TextureRef* __thiscall get_or_create_texture_ref(TextureRefList* texture_list, char* texture_path, int32_t arg3, int16_t arg4);
void __fastcall allocate_path_template_samples(Path* self);
void __fastcall finalize_path_template(Path* self);
void __thiscall mirror_path_template_pair_x(Path* self, Path* source);
void __thiscall set_matrix_identity(TransformMatrix* transform);
void __thiscall set_matrix_rotation_identity(TransformMatrix* transform);
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
void __thiscall rotate_matrix_local_x(TransformMatrix* transform, float angle);
void __thiscall rotate_matrix_local_y(TransformMatrix* transform, float angle);
void __thiscall rotate_matrix_local_z(TransformMatrix* transform, float angle);
void __cdecl initialize_global_identity_matrix_thunk();
void __cdecl initialize_global_identity_matrix();
TransformMatrix* __thiscall initialize_uniform_scale_matrix(
    TransformMatrix* transform,
    float scale
);
Vec3* __thiscall multiply_vector_by_matrix_copy(
    const Vec3* vector,
    Vec3* out,
    const TransformMatrix* matrix
);
void __thiscall multiply_vector_by_matrix(
    Vec3* vector,
    TransformMatrix matrix
);
Vec3* __thiscall rotate_vector_by_matrix(
    Vec3* vector,
    const TransformMatrix* matrix
);
double __stdcall dot_vectors(const Vec3* lhs, const Vec3* rhs);
float __thiscall dot_vector(const Vec3* vector, const Vec3* rhs);
float __thiscall normalize_vector(Vec3* vector);
float __thiscall vector_magnitude(const Vec3* vector);
float __thiscall normalize_vector_from_source(Vec3* out, const Vec3* src);
void __thiscall cross_vectors(Vec3* out, const Vec3* lhs, const Vec3* rhs);
void __thiscall orthogonalize_matrix(TransformMatrix* transform);
void __thiscall invert_matrix_in_place(TransformMatrix* transform);
void __thiscall invert_matrix_from_source(
    TransformMatrix* out,
    const TransformMatrix* source
);
void __thiscall multiply_matrices(
    TransformMatrix* out,
    const TransformMatrix* lhs,
    const TransformMatrix* rhs
);
void __thiscall multiply_matrix(
    TransformMatrix* matrix,
    const TransformMatrix* rhs
);
void __thiscall multiply_matrix_in_place_forward_thunk(
    TransformMatrix* matrix,
    const TransformMatrix* rhs
);
void __thiscall premultiply_matrix_in_place(
    TransformMatrix* matrix,
    const TransformMatrix* lhs
);
void __thiscall set_matrix_z_direction(TransformMatrix* transform, const Vec3* direction);
void __thiscall look_at_point(TransformMatrix* transform, const Vec3* target);
void __thiscall initialize_quaternion_from_axis(
    Quaternion* out,
    const AxisAngle* axis
);
void __thiscall initialize_axis_from_quaternion(
    AxisAngle* out,
    const Quaternion* quaternion
);
Quaternion* __thiscall initialize_quaternion_from_matrix(
    Quaternion* out,
    const TransformMatrix* matrix
);
TransformMatrix* __thiscall initialize_matrix_from_quaternion(
    TransformMatrix* out,
    const Quaternion* quaternion
);
void __thiscall interpolate_matrix_rotation(TransformMatrix* transform, float alpha);
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
void __thiscall uninit_pause_menu(SubPause* pause);
void __thiscall initialize_pause_menu(SubPause* pause);
void __thiscall update_pause_menu(SubPause* pause);
int32_t __thiscall set_bod_object(BodBase* bod, Object* object);
BodBase* __thiscall initialize_bod_base(BodBase* bod);
Object* __thiscall apply_bod_position(
    BodBase* bod,
    TransformMatrix* matrix
);
void __thiscall request_object_vertices(Object* object, int32_t vertex_count);
void __fastcall request_object_vertex_colours(Object* object);
void __thiscall request_object_facequads(Object* object, int32_t facequad_count);
void __thiscall build_track_fringe_mesh(
    Path* self,
    char* texture_path,
    float clamp_side
);
void __thiscall build_track_fringe_supertramp_mesh(
    Path* self,
    char* texture_path
);
tColour* __thiscall set_color_rgba(tColour* color, float r, float g, float b, float a);
void __thiscall set_color_alpha(tColour* color, float alpha);
void __thiscall set_color_grayscale(tColour* color, float intensity);
void __thiscall initialize_score_stats(Squidge* squidge);
void __thiscall start_squidge_y(Squidge* squidge, float value);
void __thiscall start_squidge_z(Squidge* squidge, float value);
void __thiscall update_squidge(Squidge* squidge);
void __thiscall firework_shoot(FireWork* firework, Vec3* position, int32_t owner, int32_t texture_id, int32_t count);
void __thiscall update_banner(Banner* banner);
SubSpeedUp* __thiscall initialize_track_speedup_runtime(SubSpeedUp* speedup);
void __thiscall update_track_speedup(SubSpeedUp* speedup);
JetPack* __thiscall initialize_track_jetpack_pickup_runtime(JetPack* jetpack);
void __thiscall update_track_jetpack_pickup(JetPack* jetpack);
SubHealth* __thiscall initialize_track_health_pickup_runtime(SubHealth* pickup);
void __thiscall update_track_health_pickup(SubHealth* pickup);
void __thiscall initialize_vapour(Vapour* vapour, Object* unused, float half_width);
void __thiscall reset_vapour(Vapour* vapour, float* z_floor);
void __thiscall add_vapour_point(Vapour* vapour, const TransformMatrix* point);
void __thiscall update_vapour(Vapour* vapour);
SubRing* __thiscall initialize_track_ring_or_special_effect_runtime(SubRing* ring);
void __thiscall spawn_track_ring_or_special_effect(
    SubgameRuntime* game,
    TrackRowCell* cell,
    int32_t requested_kind,
    Player* player,
    float ring_speed);
int32_t __thiscall initialize_ring_or_special_effect_particles(
    SubRing* ring,
    int32_t unused_lives_snapshot);
void __thiscall emit_ring_star_shower(SubRingStar* particle, Player* owner);
void __thiscall update_ring_or_special_effect_particle(SubRingStar* particle);
void __thiscall update_ring_or_special_effect_parent(SubRing* ring);
void __thiscall initialize_invincible_shell(Invincible* invincible);
void __thiscall start_invincible_shell(Invincible* invincible);
void __thiscall update_invincible_shell(Invincible* invincible);
void __thiscall initialize_snail_skin(SnailSkin* snail_skin);
void __thiscall update_snail_skin(Snail* snail);
void __thiscall initialize_anim_manager(AnimManager* manager);
void __thiscall update_anim_manager(AnimManager* manager);
void __thiscall advance_frame_sequence(FrameSequence* sequence);
void __thiscall update_smtracks(SmtrackHeightfieldAnimator* animator);
void __cdecl sample_smtrack_heightmap(
    Object* source,
    float base,
    float scale,
    TextureRef* replacement,
    char cubic);
uint8_t __thiscall deserialize_compact_high_score_record(
    SubSolution* record,
    CompactHighScoreRecord* compact);
int32_t __thiscall serialize_compact_high_score_record(
    SubSolution* record,
    CompactHighScoreRecord* compact);
void __thiscall set_weapon_animation(Weapon* weapon, int32_t animation_id, uint8_t immediate, int32_t mode_flags);
void __thiscall update_snail_skin_transition(SnailSkin* snail_skin);
void __thiscall change_snail_skin(SnailSkin* snail_skin, int32_t slot_id, float duration_seconds);
void __thiscall store_color4f(tColour* color, float r, float g, float b, float a);
tColourSmall* __thiscall pack_color_rgba_u8(tColourSmall* out, tColour* color);
void __thiscall kill_tip_widgets(Tip* tip);
void __thiscall initialize_tip(Tip* tip, TipData* definition, int32_t hide_disable_button);
void __thiscall update_tip(Tip* tip);
void __thiscall initialize_tip_manager(TipManager* manager);
void __thiscall uninit_tips(TipManager* manager);
Tip* __thiscall enqueue_tip_message(TipManager* manager, TipData* definition, int32_t hide_disable_button);
void __thiscall update_tip_manager(TipManager* manager);
void __thiscall initialize_tutorial(Tutorial* tutorial);
void __thiscall uninit_tutorial(Tutorial* tutorial);
void __thiscall update_tutorial(Tutorial* tutorial);
void __thiscall update_barrier_ai(BarrierActor* barrier);
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
void __thiscall show_subgoldy_lives(Player* player);
void __thiscall initialize_subgoldy_ghost(Player* player, int32_t owner);
void __thiscall update_subgoldy(Player* player);
void __thiscall play_movement_state_sound(Player* player);
void __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z);
void __thiscall add_subgoldy_score(
    Player* player,
    int32_t score_kind,
    int32_t bonus_score
);
void __thiscall clear_subgoldy_score_buckets(Player* player);
void __thiscall display_score_stats(Player* player);
void __thiscall initialize_subgoldy_resurrect(Player* player, int32_t final_loss);
void __thiscall update_subgoldy_resurrect(Player* player);
void __thiscall handle_subgoldy_collisions(Player* player);
void __thiscall kill_subgoldy(Player* player);
void __thiscall initialize_subgoldy_death(Player* player);
void __thiscall set_snail_weapon(Snail* snail, int32_t movement_flags);
void __thiscall set_snail_jetpack(Snail* snail, int32_t state);
void __thiscall initialize_cutscene(Snail* snail);
int32_t __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags);
void __thiscall initialize_cutscene_ai(CutScene* cutscene);
void __thiscall update_cutscene(CutScene* cutscene);
void __thiscall update_progress_bar(ProgressBar* progress_bar);
void __thiscall initialize_nuke(Nuke* nuke);
void __thiscall update_nuke(Nuke* nuke);
void __thiscall uninit_nuke(Nuke* nuke);
TrackRowCell* __thiscall get_track_grid_cell_at_world_position(SubgameRuntime* game, Vec3* position);
SubRow* __thiscall get_track_runtime_cell_at_world_z(SubgameRuntime* game, Vec3* position);
double __thiscall sample_track_floor_height_at_position(SubgameRuntime* game, Vec3* position);
void __thiscall spawn_track_health_pickup(SubgameRuntime* game, TrackRowCell* cell, Player* player);
void __thiscall spawn_track_jetpack_pickup(SubgameRuntime* game, TrackRowCell* cell, Player* player);
int32_t __thiscall merge_track_tile_runs(SubgameRuntime* game);
void __thiscall mark_track_warning_zones(SubgameRuntime* game);
void __thiscall try_enter_track_attachment_from_swept_motion(
    Path* self,
    float world_x,
    float world_y,
    float world_z,
    float sweep_dx,
    float sweep_dy,
    float sweep_dz,
    TrackRowCell* source_cell
);
void __thiscall begin_track_attachment_follow_state(FollowState* follow_state, TrackRowCell* source_cell, const Vec3* world_position, Player* player);
int32_t __thiscall update_track_attachment_follow_state(FollowState* follow_state, float path_factor, Vec3* out_position, Vec3* motion);

void __thiscall initialize_looptheloop_path_template_pair(
    Path* self,
    float curve_source,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_loopout_path_template_pair(
    Path* self,
    float curve_source,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_cage2_path_template_pair(
    Path* self,
    int32_t width_cells_,
    char* texture_a,
    char* texture_b,
    char* vertical_texture
);

int32_t __thiscall initialize_supertramp_path_template_pair(
    Path* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b,
    char* texture_c
);

void __thiscall initialize_halfpipe_path_template_pair(
    Path* self,
    float scale,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* vertical_texture
);

void __thiscall initialize_hump_path_template_pair(
    Path* self,
    float curve_source,
    float height_scale,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_looptheloopw_path_template_pair(
    Path* self,
    float curve_source,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_dump_path_template_pair(
    Path* self,
    float curve_source,
    float height_scale,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_dip_path_template_pair(
    Path* self,
    float curve_source,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_screw_path_template_pair(
    Path* self,
    int32_t curve_source,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_slalom_path_template_pair(
    Path* self,
    int32_t curve_source,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_worm_path_template_pair(
    Path* self,
    char* texture_path
);

void __thiscall initialize_slalombig_path_template_pair(
    Path* self,
    int32_t curve_segments,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_sweep_path_template_pair(
    Path* self,
    float scale_arg,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_snake_path_template_pair(
    Path* self,
    float scale_arg,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_slalomdouble_path_template_pair(
    Path* self,
    int32_t curve_segments,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
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

void __thiscall initialize_start_path_template_pair(
    Path* self,
    float length,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_turnover_path_template_pair(
    Path* self,
    float length,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_turnoverdouble_path_template_pair(
    Path* self,
    float length,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* cap_texture
);

void __thiscall initialize_turnunder_path_template_pair(
    Path* self,
    float turns,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* vertical_texture
);

void __thiscall initialize_wibble_path_template_pair(
    Path* self,
    float radius,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* vertical_texture
);

void __thiscall initialize_invert_path_template_pair(
    Path* self,
    float radius,
    int32_t width_cells_,
    int32_t side_exit,
    char* texture_a,
    char* texture_b,
    char* vertical_texture
);

void __thiscall initialize_twister_path_template_pair(
    Path* self,
    float height,
    int32_t width_cells_,
    char handedness,
    char* texture_a,
    char* texture_b,
    char* vertical_texture
);

void __thiscall initialize_twister2_path_template_pair(
    Path* self,
    float height,
    int32_t width_cells_,
    char handedness,
    char* texture_a,
    char* texture_b,
    char* vertical_texture
);

int32_t __thiscall initialize_loopbow_path_template_pair(
    Path* self,
    float arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

void __thiscall initialize_toad_path_template_pair(
    Path* self,
    char turn_left,
    char* texture_a,
    char* texture_b,
    char* vertical_texture
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

/* D3DX 8 texture helpers use callee cleanup; exact arity is required for IDA. */
int32_t __stdcall d3dx_create_texture_from_file_in_memory_ex(
    void* device,
    void* source_data,
    uint32_t source_size,
    uint32_t width,
    uint32_t height,
    uint32_t mip_levels,
    uint32_t usage,
    uint32_t format,
    uint32_t pool,
    uint32_t filter,
    uint32_t mip_filter,
    uint32_t color_key,
    void* source_info,
    void* palette,
    void** texture
);

int32_t __stdcall d3dx_create_texture_from_file_ex(
    void* device,
    char* path,
    uint32_t width,
    uint32_t height,
    uint32_t mip_levels,
    uint32_t usage,
    uint32_t format,
    uint32_t pool,
    uint32_t filter,
    uint32_t mip_filter,
    uint32_t color_key,
    void* source_info,
    void* palette,
    void** texture
);

int32_t __stdcall d3dx_create_texture_from_file(
    void* device,
    char* path,
    void** texture
);

void __thiscall destroy_help_screen(Help* help);

void __thiscall initialize_loading_screen(LoadingBar* loading_bar);

void __thiscall destroy_loading_screen(LoadingBar* loading_bar);

void __thiscall update_loading_screen(LoadingBar* loading_bar);

void __thiscall destroy_options_menu(Options* options);

void __thiscall initialize_subgame(SubgameRuntime* game);

void __thiscall destroy_subgame(SubgameRuntime* game);

void __thiscall update_subgame(SubgameRuntime* game);

void __thiscall remove_subgame_bods(SubgameRuntime* game);

void __thiscall populate_runtime_track_cells_from_segments(SubgameRuntime* game);

void __thiscall rebuild_track_runtime_from_segments(
    SubgameRuntime* game,
    int32_t level_index
);

void __thiscall build_subgame_level(SubgameRuntime* game, int32_t level_index);

void __thiscall place_parcels_on_track(SubgameRuntime* game);
void __thiscall place_challenge_parcels_on_track(SubgameRuntime* game);

void __thiscall initialize_track_render_cache_manager(SegmentCache* manager);

void __thiscall build_track_render_caches(
    SegmentCache* manager,
    tColour skirt_color
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
