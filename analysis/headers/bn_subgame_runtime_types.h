#ifndef BN_SUBGAME_RUNTIME_TYPES_H
#define BN_SUBGAME_RUNTIME_TYPES_H

typedef int int32_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

typedef struct Object Object;
typedef struct Player Player;
typedef struct Sprite Sprite;
typedef struct FrontendWidget FrontendWidget;
typedef struct SubgameRuntime SubgameRuntime;
typedef struct TrackRowCell TrackRowCell;
typedef struct TransformMatrix TransformMatrix;
typedef struct BodNode BodNode;

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

typedef enum SubgameRuntimeFlagPreset {
    SUBGAME_RUNTIME_FLAGS_SWITCH_SEED = 0x000484,
    SUBGAME_RUNTIME_FLAGS_ENGINE_DEFAULT = 0x600484,
    SUBGAME_RUNTIME_FLAGS_POSTAL_CHALLENGE = 0xf5cfff,
    SUBGAME_RUNTIME_FLAGS_TIME_TRIAL = 0x75cfff,
    SUBGAME_RUNTIME_FLAGS_TUTORIAL = 0xe4cfff,
    SUBGAME_RUNTIME_FLAGS_TUTORIAL_INIT_OR_MASK = 0x600000,
} SubgameRuntimeFlagPreset;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

/* Keep the narrow Binary Ninja import independently declarable. */
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

typedef struct EnemyManager {
    int32_t count;
    ContactTargetEntry entries[256];
} EnemyManager;

/* Exact 0x8c-byte Windows cRParcel, flattened across its BodBase prefix. */
typedef struct Parcel {
    void* vtable;
    uint32_t list_flags;
    BodNode* list_prev;
    BodNode* list_next;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    Object* object;
    float color_r;
    float color_g;
    float color_b;
    float color_a;
    int32_t state;
    SubgameRuntime* owner_subgame;
    uint8_t unknown_40[0x54 - 0x40];
    Sprite* sprite;
    uint8_t unknown_58[0x5c - 0x58];
    float bob_phase;
    float bob_phase_step;
    Player* owner_player;
    float progress;
    float progress_step;
    float target_distance;
    Vec3 travel_dir;
    Vec3 delivery_offset;
} Parcel;

/* Exact 0x1b58-byte Windows cRParcelManager embedded in SubgameRuntime. */
typedef struct ParcelManager {
    Parcel slots[50];
} ParcelManager;

/* Exact 0x50-byte Windows cRCompletion embedded in SubgameRuntime. */
typedef struct Completion {
    FrontendWidget* widget_a;
    FrontendWidget* delivered_count_widget;
    FrontendWidget* bonus_widget;
    FrontendWidget* widget_d;
    FrontendWidget* continue_widget;
    int32_t state;
    uint8_t gate_18;
    uint8_t unknown_19[0x1c - 0x19];
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

/* Exact 0x10-byte Windows cRTimesUp tail owner. */
typedef struct TimesUp {
    int32_t state;
    FrontendWidget* border;
    float progress;
    float progress_step;
} TimesUp;

/* Exact 0x94-byte Windows cRVapour owner. */
typedef struct Vapour {
    void* vtable;
    int32_t flags;
    uint8_t unknown_08[0x24 - 0x08];
    Object* owner;
    uint8_t unknown_28[0x80 - 0x28];
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
    void* vtable;
    uint32_t list_flags;
    struct JetPack* list_prev;
    struct JetPack* list_next;
    float world_position_x;
    float world_position_y;
    float world_position_z;
    uint8_t unknown_1c[0x38 - 0x1c];
    int32_t state;
    Player* owner;
    uint8_t unknown_40[0x44 - 0x40];
    SubgameRuntime* owner_game;
    uint8_t unknown_48[0x64 - 0x48];
    Sprite* sprite;
    TrackRowCell* source_cell;
    float bob_phase;
    float bob_phase_step;
    Vapour vapour_a;
    Vapour vapour_b;
} JetPack;

/* Flattened exact Windows cRBanner layout; inherited BodBase occupies +0x00. */
typedef struct Banner {
    void* vtable;
    uint32_t list_flags;
    void* list_prev;
    void* list_next;
    float position_x;
    float position_y;
    float position_z;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    float color_r;
    float color_g;
    float color_b;
    float color_a;
    int32_t visibility_mode;
    uint8_t unknown_3c[0x54 - 0x3c];
    Player* owner_player;
    float phase;
    float phase_step;
} Banner;

typedef struct BannerPool {
    Banner slots[2];
} BannerPool;

#define SUB_SOLUTION_STRIDE 0x1fac0
#define SUB_SOLUTION_PLAYER_NAME_SIZE 0x14
#define SUB_SOLUTION_RUN_RECORD_COUNT 21600
#define SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT 11
#define SUB_HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT 51

typedef struct ScoreBucketBlock {
    int32_t values[6];
} ScoreBucketBlock;

typedef struct Time {
    float total_seconds;
    int32_t minutes;
    int32_t seconds;
    int32_t display_hundredths;
    int32_t display_thousandths;
    float second_fraction;
} Time;

typedef union ScoreOrTime {
    float total_seconds;
    ScoreBucketBlock stats;
    Time timer;
} ScoreOrTime;

typedef struct ReplayRunRecord {
    int16_t lateral_x;
    int16_t delta_z;
    uint8_t flags;
    uint8_t reserved_05;
} ReplayRunRecord;

typedef struct SubSolution {
    int32_t active;
    int32_t score;
    ScoreOrTime score_or_time;
    int32_t score_tail;
    int32_t source_tail;
    int32_t replay_level_index;
    int32_t replay_mode_id;
    int32_t unknown_30;
    int32_t challenge_difficulty_scalar_bits;
    uint32_t runtime_build_flags;
    int32_t high_score_mode_tag;
    int32_t route_or_rank_index;
    int32_t replay_cursor;
    int32_t replay_speed_scalar_bits;
    int32_t challenge_speed_value;
    int32_t challenge_difficulty_value;
    char player_name[SUB_SOLUTION_PLAYER_NAME_SIZE];
    int32_t runtime_build_seed;
    int32_t replay_sample_count;
    ReplayRunRecord run_records[SUB_SOLUTION_RUN_RECORD_COUNT];
    float garbage_frequency;
    float salt_frequency;
    int32_t unknown_1fab8;
    int32_t unknown_1fabc;
} SubSolution;

typedef struct SubHighScore {
    SubSolution* active_record_bank;
    int32_t active_record_count;
    SubSolution postal_records[SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    SubSolution survival_records[SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    SubSolution time_trial_route_records[SUB_HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT];
    SubSolution current_result_record;
    SubSolution survival_pending_record;
} SubHighScore;

typedef struct TimeTrial {
    uint8_t unknown_000[0x330];
} TimeTrial;

typedef struct GUI {
    void* game;
    void* next_level_button;
    void* previous_level_button;
    void* level_name_widget;
    void* play_button;
    uint8_t unknown_14[0x18 - 0x14];
    void* back_button;
    void* speed_slider;
    void* difficulty_slider;
    void* replay_button;
} GUI;

typedef struct Help {
    FrontendWidget* back_button;
} Help;

typedef struct ThanksScreen {
    SubgameRuntime* game;
    FrontendWidget* message_widget;
    int32_t message_state;
    float message_progress;
    float message_progress_step;
} ThanksScreen;

typedef struct GalaxyRouteRecord {
    int32_t route_name_index;
    uint8_t unknown_004[0x08 - 0x04];
    float map_x;
    float map_y;
    float map_z;
    float route_tint_alpha;
    float highlight_target;
    char detail_text[0x80];
    char description_text[0x29c - 0x9c];
} GalaxyRouteRecord;

typedef struct GalaxyRouteSlot {
    int32_t unknown_000;
    GalaxyRouteRecord record;
} GalaxyRouteSlot;

typedef struct GalaxyRouteNameRecord {
    char name[0x80];
    int32_t star_count;
    float color_r;
    float color_g;
    float color_b;
    float color_a;
    float map_x;
    float map_y;
    float map_z;
} GalaxyRouteNameRecord;

typedef struct Galaxy {
    uint8_t active;
    uint8_t unknown_001[0x04 - 0x01];
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
    uint8_t unknown_10f88[0x10f8c - 0x10f88];
    FrontendWidget* bounds_frame_widget;
    FrontendWidget* selected_title_widget;
    FrontendWidget* selected_detail_widget;
    FrontendWidget* selected_description_widget;
    FrontendWidget* play_or_deliver_widget;
    FrontendWidget* replay_widget;
    int32_t unknown_10fa4;
} Galaxy;

typedef union RuntimeRateOrLevelArg {
    float base_rate;
    int32_t level_arg_tail;
} RuntimeRateOrLevelArg;

typedef union ChallengeDifficultyOrBits {
    float challenge_difficulty_scalar;
    int32_t difficulty_scalar_bits;
} ChallengeDifficultyOrBits;

typedef struct SubgameRuntime {
    uint8_t unknown_000000[0x02];
    uint8_t track_mirror_enabled;
    uint8_t unknown_000003;
    int32_t track_mirror_repeat_count;
    uint8_t unknown_000008;
    uint8_t subgame_pause_gate;
    uint8_t unknown_00000a[0x28 - 0x0a];
    int32_t completion_bonus_x_source;
    int32_t completion_bonus_y_source;
    RuntimeRateOrLevelArg rate_or_level_arg;
    ChallengeDifficultyOrBits challenge_difficulty;
    float subgame_rate;
    int32_t subgame_state;
    int32_t level_mode;
    int32_t level_mode_arg;
    float base_subgame_rate;
    uint32_t runtime_flags; /* SubgameRuntimeFlag bits/full preset word. */
    int32_t first_block_row_count;
    int32_t runtime_row_count;
    int32_t completion_row_start;
    uint8_t unknown_00005c[0xa874 - 0x5c];
    int32_t level_segment_count;
    uint8_t unknown_00a878[0x1b0140 - 0xa878];
    float track_skirt_r;
    float track_skirt_g;
    float track_skirt_b;
    uint8_t unknown_1b014c[0x355e64 - 0x1b014c];
    JetPack jetpack_pickup;
    uint8_t unknown_356000[0x359080 - 0x356000];
    BannerPool banners;
    uint8_t unknown_359140[0x3bb700 - 0x359140];
    int32_t blink_random_index;
    float blink_random_samples[24];
    uint8_t score_stats_anchor;
    uint8_t unknown_3bb765[0x3bb7d4 - 0x3bb765];
    float completion_progress_z;
    uint8_t unknown_3bb7d8[0x3bba48 - 0x3bb7d8];
    int32_t source_score;
    ScoreBucketBlock source_stats;
    int32_t source_score_tail;
    int32_t source_tail;
    uint8_t unknown_3bba6c[0x3bbae4 - 0x3bba6c];
    int32_t parcel_sprite_owner;
    uint8_t unknown_3bbae8[0x3bbb28 - 0x3bbae8];
    int32_t bonus_rate_state;
    uint8_t unknown_3bbb2c[0x3bbb48 - 0x3bbb2c];
    float bonus_rate_phase;
    uint8_t unknown_3bbb4c[0x3bbba4 - 0x3bbb4c];
    uint8_t time_trial_route_active;
    uint8_t unknown_3bbba5[0x3bdec0 - 0x3bbba5];
    int32_t nuke_rate_state;
    uint8_t unknown_3bdec4[0x3be0c0 - 0x3bdec4];
    float nuke_rate_progress;
    uint8_t unknown_3be0c4[0x68b4c8 - 0x3be0c4];
    SubHighScore sub_high_score;
    SubSolution current_high_score_record;
    uint8_t selected_level_record_active;
    uint8_t selected_level_record_persistent;
    uint8_t unknown_ff25d2[0xff25d4 - 0xff25d2];
    void* selected_level_record;
    int32_t selected_level_record_cursor;
    int32_t replay_update_cursor;
    TimeTrial time_trial;
    uint8_t unknown_ff2910[0x125e480 - 0xff2910];
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

#endif
