#ifndef IDA_INPUT_STATE_TYPES_H
#define IDA_INPUT_STATE_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

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

typedef struct MouseScreenRect {
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
} MouseScreenRect;

#endif
