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

enum SubLazerState {
    SUB_LAZER_STATE_INACTIVE = 0,
    SUB_LAZER_STATE_ACTIVE = 1,
    SUB_LAZER_STATE_RECYCLE_PENDING = 2,
};

enum {
    SUB_LAZER_SLOT_CAPACITY = 20,
};

typedef struct SubLazer {
    BodNode bod;
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
    Vec3 position;
    float position_w;
    uint8_t unknown_78[0x8];
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
    BodNode bod;
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
    Vec3 position;
    float position_w;
    uint8_t unknown_78[0x8];
    int32_t state;
    uint8_t unknown_84[0x4];
    SubgameRuntime* owner_game;
    Vec3 velocity;
} Salt;

typedef Salt SaltHazardSlot;

typedef struct SaltManager {
    Salt slots[40];
} SaltManager;

#endif
