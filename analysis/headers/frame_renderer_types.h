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

typedef struct InputState {
    int32_t controller_slot;
    int32_t pressed_buttons;
    int32_t released_buttons;
    int32_t previous_buttons;
    int32_t inverse_current_buttons;
    float axis_x;
    float axis_y;
    int32_t unknown_1c;
    float pointer_x;
    float pointer_y;
    float authored_x;
    float authored_y;
    float pointer_value;
    int32_t current_buttons;
} InputState;

typedef struct GameInputBodBase {
    void* vtable;
    uint32_t list_flags;
    struct GameInputBodBase* list_prev;
    struct GameInputBodBase* list_next;
    float position[3];
    float render_arg_1c;
    float render_arg_20;
    void* object;
    float color[4];
} GameInputBodBase;

typedef struct GameInput {
    GameInputBodBase bod;
    InputState input;
} GameInput;

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

typedef struct FrameRenderableBod {
    FrameBodBase bod;
    FrameTransformMatrix transform;
    void* render_animation_manager;
    uint8_t unknown_7c[0x04];
} FrameRenderableBod;

typedef struct FrameRenderCamera {
    uint8_t unknown_00[0x38];
    FrameTransformMatrix transform;
    void* render_animation_manager;
    uint8_t unknown_7c[0x04];
    FrameTransformMatrix view_matrix;
    float fov_degrees;
    uint32_t render_mask;
} FrameRenderCamera;

typedef struct FrameOverlay {
    FrameRenderableBod bod;
    FrameRenderCamera camera;
    float rotation_step;
} FrameOverlay;

typedef struct GamePlayer {
    void* vtable;
    uint8_t unknown_004[0x38 - 0x004];
    FrameTransformMatrix transform;
    void* render_animation_manager;
    uint8_t unknown_07c[0x04];
    char player_name[0x14];
    int32_t frontend_state;
    int32_t saved_frontend_state;
    uint8_t unknown_09c[0x04];
    FrameRenderCamera camera;
    GameInput* game_input;
    MouseCursorState mouse_cursor;
    FrontendOverlayColorLerp frontend_overlay;
    FrameTransformMatrix completion_handoff_transform;
    uint8_t redispatch_requested;
    uint8_t high_score_entry_pending;
    uint8_t unknown_1ea[0x02];
    int32_t selected_high_score_rank;
    int32_t selected_high_score_mode;
    uint8_t unknown_1f4[0x04];
} GamePlayer;

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

typedef struct TextureRef TextureRef;

typedef struct TextureSetSelector {
    TextureRef* primary_textures[4];
    TextureRef* secondary_textures[4];
    int32_t current_texture_set;
} TextureSetSelector;

/*
 * Sparse frame-owner view of the exact 0x435b4-byte cRBorderManager.  The
 * constructor lane only needs its final authored float; keeping the complete
 * pool opaque avoids creating a competing definition of BorderManager.
 */
typedef struct FrameBorderManager {
    void* vtable;
    uint32_t list_flags;
    void* list_prev;
    void* list_next;
    uint8_t unknown_000010[0x435b0 - 0x10];
    float justify_centre;
} FrameBorderManager;

void __thiscall kill_all_borders(FrameBorderManager* manager);
void __thiscall set_border_justify_centre(
    FrameBorderManager* manager, float justify_centre);

typedef struct FrameSubgameRuntime {
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
    uint8_t unknown_000014[0x3c - 0x14];
    int32_t subgame_state;
    int32_t level_mode;
    uint8_t unknown_000044[0x1270fd4 - 0x44];
    FrameContactTargetRegistry contact_targets;
    uint8_t unknown_12727d8[0x1272838 - 0x12727d8];
} FrameSubgameRuntime;

typedef struct GameRoot {
    uint8_t unknown_000000[0x24];
    FrontendFade fade;
    int32_t frontend_quit_requested;
    int32_t fixed_update_count;
    int32_t player_count;
    GameInput game_inputs[2];
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
    FrameOverlay overlay_0;
    FrameOverlay overlay_1;
    FrameOverlay overlay_2;
    uint8_t unknown_000a60[0xb24 - 0xa60];
    TextureSetSelector texture_set_selector;
    int32_t unknown_000b48;
    FrameBorderManager border_manager;
    uint8_t unknown_044100[0x74618 - 0x44100];
    FrameSubgameRuntime subgame;
    uint8_t unknown_12e6e50[0x12e6ff4 - 0x12e6e50];
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
