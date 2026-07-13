#ifndef BN_SUBGAME_HAZARD_POOL_TYPES_H
#define BN_SUBGAME_HAZARD_POOL_TYPES_H

/*
 * Narrow Binary Ninja projection of the contiguous SubLazer/Salt runtime
 * pools embedded in FrameSubgameRuntime. Names are lane-local so replaying
 * this header cannot overwrite older standalone hazard-slot experiments.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct FrameHazardVec3 {
    float x;
    float y;
    float z;
} FrameHazardVec3;

typedef struct FrameHazardVec4 {
    float x;
    float y;
    float z;
    float w;
} FrameHazardVec4;

typedef struct FrameHazardColor4f {
    float r;
    float g;
    float b;
    float a;
} FrameHazardColor4f;

typedef struct FrameHazardBodNode FrameHazardBodNode;
struct FrameHazardBodNode {
    void* vtable;
    uint32_t list_flags;
    FrameHazardBodNode* list_prev;
    FrameHazardBodNode* list_next;
};

typedef struct FrameSubLazerSlot FrameSubLazerSlot;
struct FrameSubLazerSlot {
    void* vtable;
    uint32_t list_flags;
    FrameHazardBodNode* list_prev;
    FrameHazardBodNode* list_next;
    FrameHazardVec3 bod_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    FrameHazardColor4f color;
    FrameHazardVec4 basis_right;
    FrameHazardVec4 basis_up;
    FrameHazardVec4 basis_forward;
    FrameHazardVec4 world_position;
    uint8_t unknown_78[0x8];
    int32_t state;
    uint8_t unknown_84[0x4];
    void* owner_game;
    FrameHazardVec3 velocity;
    float sprite_bob_phase;
    float sprite_bob_phase_step;
    uint8_t unknown_a0[0x10];
};

typedef struct FrameSubLazerManager {
    FrameSubLazerSlot slots[20];
} FrameSubLazerManager;

typedef struct FrameSaltSlot FrameSaltSlot;
struct FrameSaltSlot {
    void* vtable;
    uint32_t list_flags;
    FrameHazardBodNode* list_prev;
    FrameHazardBodNode* list_next;
    FrameHazardVec3 bod_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    FrameHazardColor4f color;
    FrameHazardVec4 basis_right;
    FrameHazardVec4 basis_up;
    FrameHazardVec4 basis_forward;
    FrameHazardVec4 world_position;
    uint8_t unknown_78[0x8];
    int32_t state;
    uint8_t unknown_84[0x4];
    void* owner_game;
    float fade_alpha;
    float spawn_velocity_y;
    uint8_t collision_armed;
    uint8_t unknown_95[0x3];
};

typedef struct FrameSaltManager {
    FrameSaltSlot slots[40];
} FrameSaltManager;

#endif
