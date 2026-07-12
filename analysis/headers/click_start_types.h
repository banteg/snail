#ifndef CLICK_START_TYPES_H
#define CLICK_START_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

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

typedef struct ClickStart {
    void* vtable;
    int32_t list_flags;
    struct ClickStart* list_prev;
    struct ClickStart* list_next;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
    TransformMatrix transform;
    uint8_t _pad_78[0x8];
    int32_t state;
    FrontendWidget* prompt;
    float teardown_progress;
    float teardown_progress_step;
    uint8_t _pad_90[0x8];
    Player* player;
    uint8_t _pad_9c[0xc];
    uint8_t hide_prompt;
    uint8_t _pad_a9[0x3];
} ClickStart;

struct Player {
    uint8_t _pad_000[0xa0];
    ClickStart click_start;
    uint8_t _pad_14c[0x304 - 0x14c];
    int32_t startup_track_index;
};

#endif
