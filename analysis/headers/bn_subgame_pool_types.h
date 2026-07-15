#ifndef BN_SUBGAME_POOL_TYPES_H
#define BN_SUBGAME_POOL_TYPES_H

/*
 * Narrow Binary Ninja type-import slice for the contiguous subgame pickup and
 * hazard pool band recovered from reset/collision/spawn paths.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Object Object;
typedef struct BodNode BodNode;
typedef struct Player Player;
typedef struct Sprite Sprite;
typedef struct SubgameRuntime SubgameRuntime;
typedef struct TrackRowCell TrackRowCell;
typedef struct TransformMatrix TransformMatrix;
typedef struct AnimManager AnimManager;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

struct BodNode {
    void* vtable;
    uint32_t list_flags;
    BodNode* list_prev;
    BodNode* list_next;
};

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
};

typedef struct BodBase {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    Object* object;
    tColour color;
} BodBase;

typedef struct RenderableBod {
    BodBase bod;
    TransformMatrix transform;
    AnimManager* render_animation_manager;
    uint8_t unknown_7c[0x04];
} RenderableBod;

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

typedef enum TrackPickupState {
    TRACK_PICKUP_STATE_INACTIVE = 0,
    TRACK_PICKUP_STATE_ACTIVE = 1,
    TRACK_PICKUP_STATE_TEARDOWN_PENDING = 2,
} TrackPickupState;

typedef struct SubSpeedUp {
    void* vtable;
    uint32_t list_flags;
    struct SubSpeedUp* list_prev;
    struct SubSpeedUp* list_next;
    Vec3 bod_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    tColour color;
    Vec3 basis_right;
    float basis_right_w;
    Vec3 basis_up;
    float basis_up_w;
    Vec3 basis_forward;
    float basis_forward_w;
    Vec3 world_position;
    float world_position_w;
    void* render_animation_manager;
    uint8_t unknown_7c[0x04];
    TrackPickupState state;
    struct Player* owner;
    uint8_t unknown_88[0x04];
    SubgameRuntime* owner_game;
    uint8_t unknown_90[0x1c];
    struct Sprite* sprite;
    uint8_t unknown_b0[0x04];
} SubSpeedUp;

typedef SubSpeedUp TrackSpeedupRuntime;

typedef struct JetPack {
    void* vtable;
    uint32_t list_flags;
    struct JetPack* list_prev;
    struct JetPack* list_next;
    Vec3 world_position;
    uint8_t unknown_1c[0x1c];
    TrackPickupState state;
    struct Player* owner;
    uint8_t unknown_40[0x04];
    SubgameRuntime* owner_game;
    uint8_t unknown_48[0x1c];
    struct Sprite* sprite;
    struct TrackRowCell* source_cell;
    float bob_phase;
    float bob_phase_step;
    Vapour vapour_a;
    Vapour vapour_b;
} JetPack;

typedef struct SubHealth {
    void* vtable;
    uint32_t list_flags;
    struct SubHealth* list_prev;
    struct SubHealth* list_next;
    Vec3 world_position;
    uint8_t unknown_1c[0x1c];
    TrackPickupState state;
    struct Player* owner;
    uint8_t unknown_40[0x04];
    SubgameRuntime* owner_game;
    uint8_t unknown_48[0x1c];
    struct Sprite* sprite;
    struct TrackRowCell* source_cell;
    float bob_phase;
    float bob_phase_step;
} SubHealth;

typedef SubHealth TrackHealthPickup;

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

/* Exact 0xec-byte authored cRSlug owner. */
typedef struct Slug {
    RenderableBod body;
    int32_t state;
    int32_t death_toss_direction;
    SubgameRuntime* owner_game;
    Vec3 velocity;
    float attachment_facing_angle;
    uint8_t unknown_9c[0xac - 0x9c];
    struct Sprite* sprite;
    struct TrackRowCell* source_cell;
    uint8_t passed_player;
    uint8_t unknown_b5[0x03];
    float lateral_phase;
    float lateral_phase_step;
    struct Player* owner_player;
    int32_t engagement_voice_gate;
    int32_t hit_points;
    uint8_t hit_flash_pending;
    uint8_t unknown_cd[0x03];
    float hit_flash_progress;
    float hit_flash_progress_step;
    uint8_t voice_active;
    uint8_t player_encounter_latched;
    uint8_t unknown_da[0x02];
    float voice_progress;
    float voice_progress_step;
    float blink_progress;
    float blink_step;
} Slug;

typedef struct SlugPool {
    Slug slots[SUB_SLUG_SLOT_CAPACITY];
} SlugPool;

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

typedef SubRingStar RingOrSpecialEffectParticle;

struct SubRing {
    BodNode bod;
    Vec3 bod_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    tColour color;
    Vec3 basis_right;
    float basis_right_w;
    Vec3 basis_up;
    float basis_up_w;
    Vec3 basis_forward;
    float basis_forward_w;
    Vec3 world_position;
    float world_position_w;
    void* render_animation_manager;
    uint8_t unknown_7c[0x04];
    SubRingState state;
    Player* owner_player;
    SubRingKind kind;
    int32_t owner_lives_snapshot;
    SubRingStar particles[10];
    SubgameRuntime* rate_source;
    float transition_progress;
    float transition_step;
    uint8_t oscillate_x;
    uint8_t unknown_1dd[0x03];
    float active_phase;
    float active_phase_step;
    int32_t star_shower_counter;
    int32_t star_sprite_id;
    uint8_t unknown_1f0[0x08];
};

typedef SubRing RingOrSpecialEffectParent;

typedef struct SubRingPool {
    SubRing slots[2];
} SubRingPool;

typedef SubRingPool RingOrSpecialEffectPool;

SubRing* __thiscall initialize_track_ring_or_special_effect_runtime(SubRing* ring);
void __thiscall spawn_track_ring_or_special_effect(
    SubgameRuntime* game,
    TrackRowCell* cell,
    SubRingKind requested_kind,
    Player* player,
    float ring_speed);
int32_t __thiscall initialize_ring_or_special_effect_particles(
    SubRing* ring,
    int32_t unused_lives_snapshot);
void __thiscall emit_ring_star_shower(SubRingStar* particle, Player* owner);
void __thiscall update_ring_or_special_effect_particle(SubRingStar* particle);
void __thiscall update_ring_or_special_effect_parent(SubRing* ring);
void __thiscall initialize_vapour(Vapour* vapour, Object* unused, float half_width);
void __thiscall reset_vapour(Vapour* vapour, float* z_floor);
void __thiscall add_vapour_point(Vapour* vapour, const TransformMatrix* point);
void __thiscall update_vapour(Vapour* vapour);
SubSpeedUp* __thiscall initialize_track_speedup_runtime(SubSpeedUp* speedup);
void __thiscall update_track_speedup(SubSpeedUp* speedup);
JetPack* __thiscall initialize_track_jetpack_pickup_runtime(JetPack* jetpack);
void __thiscall update_track_jetpack_pickup(JetPack* jetpack);
SubHealth* __thiscall initialize_track_health_pickup_runtime(SubHealth* pickup);
void __thiscall update_track_health_pickup(SubHealth* pickup);
Slug* __thiscall initialize_slug_hazard_runtime(Slug* slug);
void __thiscall update_slug_voice_ai(Slug* slug);
void __thiscall play_slug_voice(Slug* slug, int32_t sample_index);
void __thiscall hit_slug_hazard(Slug* slug, int32_t damage);
void __thiscall explode_slug_hazard(Slug* slug);
void __thiscall kill_slug_hazard(Slug* slug);
void __thiscall update_slug_hazard_ai(Slug* slug);

#endif
