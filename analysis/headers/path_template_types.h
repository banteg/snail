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

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

typedef struct TwinkleManager {
    uint8_t twinkles[0xf0];
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

typedef struct BodBase {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    tColour color;
} BodBase;

typedef struct AnimManager AnimManager;

typedef struct RenderableBod {
    BodBase bod;
    uint8_t transform[0x40];
    /* Borrowed only when BodNode.list_flags has the render-sync bit 0x800. */
    AnimManager* render_animation_manager;
    uint8_t unknown_7c[0x4];
} RenderableBod;

typedef struct FringeObject {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    tColour color;
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

typedef union AuthoredFloatBits {
    int32_t bits;
    float value;
} AuthoredFloatBits;

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
    union {
        float selected_speed;
        int32_t selected_speed_bits;
    };
    float garbage_frequency;
    float salt_frequency;
    int32_t landscape_script_index;
    int32_t parcel_count;
    int32_t track_texture_set;
    int32_t parcel_quota;
} SubTracks;

/* Exact 0xb4-byte authored cRSubSpeedUp singleton. */
typedef struct SubSpeedUp {
    RenderableBod body;
    int32_t state;
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
    uint32_t widget_flags;
    uint32_t previous_widget_flags;
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
    uint8_t _pad_6fc[0x1c];
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
    RenderableBod body;
    uint32_t state;
    uint8_t _pad_84[0x4];
    SubgameRuntime* owner_game;
    float fade_alpha;
    float spawn_velocity_y;
    uint8_t collision_armed;
    uint8_t _pad_95[0x03];
} SaltHazardSlot;

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

typedef struct SubLazerSlot {
    RenderableBod body;
    uint32_t state;
    uint8_t _pad_84[0x4];
    SubgameRuntime* owner_game;
    Vec3 velocity;
    float sprite_bob_phase;
    float sprite_bob_phase_step;
    uint8_t _pad_a0[0x10];
} SubLazerSlot;

/* Exact 0x74-byte authored cRSubHealth pickup slot. */
typedef struct TrackHealthPickup {
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
} TrackHealthPickup;

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

typedef struct SlugHazardRuntime {
    RenderableBod bod;
    int32_t state;
    int32_t death_toss_direction;
    SubgameRuntime* owner_game;
    Vec3 velocity;
    float attachment_facing_angle;
    uint8_t _pad_9c[0xac - 0x9c];
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
} SlugHazardRuntime;

typedef struct SlugPool {
    SlugHazardRuntime slots[SUB_SLUG_SLOT_CAPACITY];
} SlugPool;

typedef struct SubLazerManager {
    SubLazerSlot slots[SUB_LAZER_SLOT_CAPACITY];
} SubLazerManager;

typedef struct SaltManager {
    SaltHazardSlot slots[40];
} SaltManager;

typedef struct GarbageHazardSlot GarbageHazardSlot;
struct GarbageHazardSlot {
    RenderableBod body;
    GarbageHazardSlot* next_active;
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

typedef struct GarbageHazardPool {
    GarbageHazardSlot* active_head;
    GarbageHazardSlot slots[50];
} GarbageHazardPool;

typedef struct RingOrSpecialEffectParent RingOrSpecialEffectParent;

typedef struct RingOrSpecialEffectParticle {
    Sprite* sprite;
    RingOrSpecialEffectParent* parent;
    Vec3 base_position;
    float phase;
    float phase_step;
    float radius;
} RingOrSpecialEffectParticle;

typedef struct RingEffectRateSource {
    uint8_t _pad_00[0x09];
    uint8_t subgame_pause_gate;
    uint8_t _pad_0a[0x38 - 0x0a];
    float subgame_rate;
} RingEffectRateSource;

struct RingOrSpecialEffectParent {
    RenderableBod body;
    int32_t state;
    Player* owner_player;
    int32_t kind;
    int32_t owner_lives_snapshot;
    RingOrSpecialEffectParticle particles[10];
    RingEffectRateSource* rate_source;
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

typedef struct RingOrSpecialEffectPool {
    RingOrSpecialEffectParent slots[2];
} RingOrSpecialEffectPool;

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

/* Exact FrameSequence extent; its internals are owned by the renderer lane. */
typedef struct FrameSequence {
    uint8_t _storage[0xf0];
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

typedef struct TrackAttachmentRuntimeRow {
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
} TrackAttachmentRuntimeRow;

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

typedef struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
} TransformMatrix;

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

typedef struct PresentationAnimationChannel {
    RenderableBod body;
    uint8_t _pad_80[0x104 - 0x80];
    int32_t selected_state;
    AnimManager anim_manager;
    PresentationAnimationSlot animation_slots[5];
    Vec3 release_step;
} PresentationAnimationChannel;

/* Authored cRSnailSkin, exact 0x20-byte material-selection owner. */
typedef struct SnailSkin {
    int32_t selected_slot;
    TextureRef* material_overrides[3];
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
} PresentationWobbleController;

/* Authored cRInvincible, exact 0xa4-byte spinning shell visual owner. */
typedef struct Invincible {
    RenderableBod body;
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
    RenderableBod body;
    TransformMatrix previous_live_matrix;
    TransformMatrix cached_cutscene_matrix;
    Player* owner_player;
    AnimManager anim_manager;
    PresentationAnimationSlot cutscene_animation_slots[10];
    PresentationAnimationChannel weapon_channels[3];
    PresentationAnimationChannel jetpack_channel;
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
    int32_t state;
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
    Vec3 widget_world;
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
    uint8_t _pad_a4[0x4];
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
    uint8_t _pad_3c[0x4];
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
    uint8_t _pad_00[0x09];
    uint8_t subgame_pause_gate;
    uint8_t _pad_0a[0x14 - 0x0a];
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
    uint32_t runtime_flags;
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
    TrackHealthPickup health_pickups[8];
    SlugPool slug_hazards;
    SubLazerManager sub_lazers;
    SaltManager salt_hazards;
    BannerPool banners;
    GarbageHazardPool garbage_hazards;
    RingOrSpecialEffectPool ring_effects;
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
    TrackAttachmentRuntimeRow runtime_rows[3200];
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
int32_t __fastcall finalize_path_template(Path* self);
int32_t __thiscall mirror_path_template_pair_x(Path* self, Path* source);
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
void __thiscall request_object_vertices(Object* object, int32_t vertex_count);
void __fastcall request_object_vertex_colours(Object* object);
void __thiscall request_object_facequads(Object* object, int32_t facequad_count);
tColour* __thiscall set_color_rgba(tColour* color, float r, float g, float b, float a);
void __thiscall set_color_alpha(tColour* color, float alpha);
void __thiscall set_color_grayscale(tColour* color, float intensity);
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
void __thiscall set_weapon_animation(PresentationAnimationChannel* channel, int32_t animation_id, uint8_t immediate, int32_t mode_flags);
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
int32_t __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags);
void __thiscall initialize_cutscene_ai(CutScene* cutscene);
void __thiscall update_cutscene(CutScene* cutscene);
void __thiscall update_progress_bar(ProgressBar* progress_bar);
void __thiscall initialize_nuke(Nuke* nuke);
void __thiscall update_nuke(Nuke* nuke);
void __thiscall uninit_nuke(Nuke* nuke);
TrackRowCell* __thiscall get_track_grid_cell_at_world_position(SubgameRuntime* game, Vec3* position);
TrackAttachmentRuntimeRow* __thiscall get_track_runtime_cell_at_world_z(SubgameRuntime* game, Vec3* position);
double __thiscall sample_track_floor_height_at_position(SubgameRuntime* game, Vec3* position);
int32_t __thiscall merge_track_tile_runs(SubgameRuntime* game);
void __thiscall mark_track_warning_zones(SubgameRuntime* game);
void __thiscall begin_track_attachment_follow_state(FollowState* follow_state, TrackRowCell* source_cell, const Vec3* world_position, Player* player);
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

char __cdecl cache_music_file(
    char* path,
    int32_t unused,
    char* unused_default_path
);

void* __thiscall noop_this_constructor(void* self);

void __thiscall populate_runtime_track_cells_from_segments(SubgameRuntime* game);

int32_t __thiscall rebuild_track_runtime_from_segments(
    SubgameRuntime* game,
    int32_t level_index
);

void __thiscall build_subgame_level(SubgameRuntime* game, int32_t level_index);

int32_t __thiscall place_parcels_on_track(SubgameRuntime* game);
int32_t __thiscall place_challenge_parcels_on_track(SubgameRuntime* game);

void* __thiscall initialize_track_render_cache_manager(SegmentCache* manager);

int32_t __thiscall build_track_render_caches(
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
