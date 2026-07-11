#ifndef FRAME_RENDERER_TYPES_H
#define FRAME_RENDERER_TYPES_H

/* Narrow IDA import slice for the root frame updater/renderer and sort workspace. */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct FrameColor4f {
    float r;
    float g;
    float b;
    float a;
} FrameColor4f;

typedef struct FrameVec3 {
    float x;
    float y;
    float z;
} FrameVec3;

typedef struct FrameVec4 {
    float x;
    float y;
    float z;
    float w;
} FrameVec4;

typedef struct FrameTransformMatrix {
    FrameVec4 basis_right;
    FrameVec4 basis_up;
    FrameVec4 basis_forward;
    FrameVec4 position;
} FrameTransformMatrix;

typedef struct FrontendFade {
    int32_t state;
    int32_t alpha_bits;
    float hold_progress;
    float hold_progress_step;
    int32_t hold_state;
} FrontendFade;

typedef struct MouseCursorState {
    uint8_t captured;
    uint8_t unknown_01[0x3];
    float live_x;
    float live_y;
    float saved_x;
    float saved_y;
    uint8_t suppress_next_draw;
    uint8_t unknown_15[0x3];
} MouseCursorState;

typedef struct FrontendOverlayColorLerp {
    int32_t state;
    FrameColor4f target;
    FrameColor4f current;
} FrontendOverlayColorLerp;

typedef struct GamePlayer {
    void* vtable;
    uint8_t unknown_004[0x16c - 0x004];
    MouseCursorState mouse_cursor;
    FrontendOverlayColorLerp frontend_overlay;
    uint8_t unknown_1a8[0x1f8 - 0x1a8];
} GamePlayer;

typedef struct FrameBodBase FrameBodBase;

typedef struct FrameBodNode {
    void** vtable;
    uint32_t list_flags;
    FrameBodBase* list_prev;
    FrameBodBase* list_next;
} FrameBodNode;

typedef struct FrameBodList {
    int32_t unknown_00;
    FrameBodBase* first;
    FrameBodBase* free_top;
} FrameBodList;

struct FrameBodBase {
    FrameBodNode bod;
    FrameVec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    FrameColor4f color;
};

typedef struct FrameRenderCamera {
    uint8_t unknown_00[0x38];
    FrameTransformMatrix transform;
    uint8_t unknown_78[0x08];
    FrameTransformMatrix view_matrix;
    float fov_degrees;
    uint32_t render_mask;
} FrameRenderCamera;

typedef struct FrameRenderCameraSlot {
    int32_t unknown_00;
    int32_t sort_key;
    uint32_t flags;
    float viewport_x;
    float viewport_y;
    float viewport_width;
    float viewport_height;
    float unknown_1c;
    FrameRenderCamera* source;
    uint8_t draw_world;
    uint8_t unknown_25[0x3];
} FrameRenderCameraSlot;

typedef struct FrameContactTargetRegistry {
    int32_t count;
    uint8_t entries[0x1800];
} FrameContactTargetRegistry;

typedef struct FrameSubgameRuntime {
    uint8_t unknown_000000[0x40];
    int32_t level_mode;
    uint8_t unknown_000044[0x1270fd4 - 0x44];
    FrameContactTargetRegistry contact_targets;
} FrameSubgameRuntime;

typedef struct GameRoot {
    uint8_t unknown_000000[0x24];
    FrontendFade fade;
    int32_t frontend_quit_requested;
    int32_t fixed_update_count;
    int32_t player_count;
    uint8_t unknown_000044[0x124 - 0x44];
    GamePlayer players[2];
    uint8_t unknown_000514[0x518 - 0x514];
    float fixed_update_accumulator;
    int32_t frame_counter;
    uint8_t input_sampling_gate;
    uint8_t unknown_000521[0x56c - 0x521];
    int32_t render_skip_count;
    FrameBodBase inactive_bod_sentinel;
    FrameBodList active_bod_list;
    FrameRenderCameraSlot render_camera_slots[5];
    uint8_t unknown_00067c[0x74618 - 0x67c];
    FrameSubgameRuntime subgame;
    uint8_t unknown_12e6df0[0x12e6ff4 - 0x12e6df0];
} GameRoot;

typedef struct FrameRendererVec3 {
    float x;
    float y;
    float z;
} FrameRendererVec3;

typedef struct SpriteDepthNode {
    struct SpriteDepthNode* next;
    FrameRendererVec3 position;
    float depth_key;
    void* sprite;
} SpriteDepthNode;

#endif
