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
typedef struct Player Player;
typedef struct SubgameRuntime SubgameRuntime;
typedef struct TransformMatrix TransformMatrix;

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

typedef struct TrackSpeedupRuntime {
    void* vtable;
    uint32_t list_flags;
    struct TrackSpeedupRuntime* list_prev;
    struct TrackSpeedupRuntime* list_next;
    Vec3 bod_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
    Vec3 basis_right;
    float basis_right_w;
    Vec3 basis_up;
    float basis_up_w;
    Vec3 basis_forward;
    float basis_forward_w;
    Vec3 world_position;
    float world_position_w;
    uint8_t unknown_78[0x08];
    int32_t state;
    struct Player* owner;
    uint8_t unknown_88[0x04];
    SubgameRuntime* owner_game;
    uint8_t unknown_90[0x1c];
    struct Sprite* sprite;
    uint8_t unknown_b0[0x04];
} TrackSpeedupRuntime;

typedef struct JetPack {
    void* vtable;
    uint32_t list_flags;
    struct JetPack* list_prev;
    struct JetPack* list_next;
    Vec3 world_position;
    uint8_t unknown_1c[0x1c];
    int32_t state;
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

typedef struct TrackHealthPickup {
    void* vtable;
    uint32_t list_flags;
    struct TrackHealthPickup* list_prev;
    struct TrackHealthPickup* list_next;
    Vec3 world_position;
    uint8_t unknown_1c[0x1c];
    int32_t state;
    struct Player* owner;
    uint8_t unknown_40[0x04];
    SubgameRuntime* owner_game;
    uint8_t unknown_48[0x1c];
    struct Sprite* sprite;
    struct TrackRowCell* source_cell;
    float bob_phase;
    float bob_phase_step;
} TrackHealthPickup;

typedef struct SlugHazardRuntime {
    uint8_t unknown_00[0x68];
    Vec3 world_position;
    uint8_t unknown_74[0x0c];
    int32_t state;
    int32_t death_toss_direction;
    SubgameRuntime* owner_game;
    Vec3 velocity;
    uint8_t unknown_98[0x14];
    struct Sprite* sprite;
    struct TrackRowCell* source_cell;
    uint8_t passed_player;
    uint8_t unknown_b5[0x03];
    float lateral_phase;
    float lateral_phase_step;
    struct Player* player;
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
} SlugHazardRuntime;

typedef struct SlugPool {
    SlugHazardRuntime slots[8];
} SlugPool;

typedef struct RingOrSpecialEffectParent RingOrSpecialEffectParent;

typedef struct RingOrSpecialEffectParticle {
    struct Sprite* sprite;
    RingOrSpecialEffectParent* parent;
    Vec3 base_position;
    float phase;
    float phase_step;
    float radius;
} RingOrSpecialEffectParticle;

typedef struct RingEffectRateSource {
    uint8_t unknown_00[0x09];
    uint8_t pause_gate;
    uint8_t unknown_0a[0x2e];
    float subgame_rate;
} RingEffectRateSource;

struct RingOrSpecialEffectParent {
    void* vtable;
    uint32_t list_flags;
    RingOrSpecialEffectParent* list_prev;
    RingOrSpecialEffectParent* list_next;
    Vec3 bod_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
    Vec3 basis_right;
    float basis_right_w;
    Vec3 basis_up;
    float basis_up_w;
    Vec3 basis_forward;
    float basis_forward_w;
    Vec3 world_position;
    float world_position_w;
    uint8_t unknown_78[0x08];
    int32_t state;
    struct Player* owner_player;
    int32_t kind;
    int32_t owner_lives_snapshot;
    RingOrSpecialEffectParticle particles[10];
    RingEffectRateSource* rate_source;
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

typedef struct RingOrSpecialEffectPool {
    RingOrSpecialEffectParent slots[2];
} RingOrSpecialEffectPool;

void __thiscall emit_ring_star_shower(RingOrSpecialEffectParticle* particle, Player* owner);
void __thiscall update_ring_or_special_effect_particle(RingOrSpecialEffectParticle* particle);
void __thiscall initialize_vapour(Vapour* vapour, Object* unused, float half_width);
void __thiscall reset_vapour(Vapour* vapour, float* z_floor);
void __thiscall add_vapour_point(Vapour* vapour, const TransformMatrix* point);
void __thiscall update_vapour(Vapour* vapour);
JetPack* __thiscall initialize_track_jetpack_pickup_runtime(JetPack* jetpack);
void __thiscall update_track_jetpack_pickup(JetPack* jetpack);

#endif
