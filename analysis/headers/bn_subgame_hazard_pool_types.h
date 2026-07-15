#ifndef BN_SUBGAME_HAZARD_POOL_TYPES_H
#define BN_SUBGAME_HAZARD_POOL_TYPES_H

/*
 * Canonical narrow Binary Ninja projection of the authored cRSubLazer and
 * cRSalt owners. The dedicated sync replaces the obsolete sparse slot
 * experiments while preserving complete shared types from other lanes.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct SubgameRuntime SubgameRuntime;

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
    tColour color;
} BodBase;

typedef struct RenderableBod {
    BodBase bod;
    TransformMatrix transform;
    void* render_animation_manager;
    uint8_t unknown_7c[0x4];
} RenderableBod;

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
    int32_t state;
    uint8_t unknown_84[0x4];
    SubgameRuntime* owner_game;
    Vec3 velocity;
    float sprite_bob_phase;
    float sprite_bob_phase_step;
    uint8_t unknown_a0[0x10];
} SubLazer;

typedef SubLazer SubLazerSlot;

typedef struct SubLazerManager {
    SubLazer slots[SUB_LAZER_SLOT_CAPACITY];
} SubLazerManager;

typedef struct Salt {
    RenderableBod body;
    int32_t state;
    uint8_t unknown_84[0x4];
    SubgameRuntime* owner_game;
    float fade_alpha;
    float spawn_velocity_y;
    uint8_t collision_armed;
    uint8_t unknown_95[0x3];
} Salt;

typedef Salt SaltHazardSlot;

typedef struct SaltManager {
    Salt slots[40];
} SaltManager;

#endif
