#ifndef CLICK_START_TYPES_H
#define CLICK_START_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Object Object;
typedef struct cRAnimManager cRAnimManager;

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

typedef struct TransformMatrix {
    Vec3 basis_right;
    float basis_right_w;
    Vec3 basis_up;
    float basis_up_w;
    Vec3 basis_forward;
    float basis_forward_w;
    Vec3 position;
    float position_w;
} TransformMatrix;

typedef struct FrontendWidget FrontendWidget;
typedef struct Player Player;

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
    Object* object;
    tColour color;
} BodBase;

typedef struct RenderableBod {
    BodBase bod;
    TransformMatrix transform;
    cRAnimManager* render_animation_manager;
    int32_t frame_number;
} RenderableBod;

typedef enum ClickStartState {
    CLICK_START_STATE_INACTIVE = 0,
    CLICK_START_STATE_UNKNOWN_1 = 1,
    CLICK_START_STATE_WAITING_FOR_START = 2,
    CLICK_START_STATE_START_PENDING = 3,
    CLICK_START_STATE_TEARDOWN = 4,
} ClickStartState;

/* Exact Windows cRClickStart child embedded at Player +0xa0. */
typedef struct cRClickStart {
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
} cRClickStart;

typedef char cRClickStart_must_be_0xac[
    (sizeof(cRClickStart) == 0xac) ? 1 : -1];

#endif
