#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include "bod_types.h"

class InputState {
public:
    void initialize_input();
    void update_input();

    int controller_slot;          // +0x00
    union {
        int pressed_buttons;          // +0x04, current-frame down edges
        unsigned int control_flags_a; // Goldy borrowed-control spelling
    };
    int released_buttons;         // +0x08, current-frame up edges
    union {
        int previous_buttons;         // +0x0c
        unsigned int control_flags_b; // Goldy borrowed-control spelling
    };
    int inverse_current_buttons;  // +0x10
    float axis_x;                 // +0x14
    float axis_y;                 // +0x18
    int unknown_1c;               // +0x1c
    float pointer_x;              // +0x20
    float pointer_y;              // +0x24
    union {
        float authored_x;             // +0x28
        float steering_x;             // Goldy borrowed-control spelling
    };
    float authored_y;             // +0x2c
    float pointer_value;          // +0x30
    int current_buttons;          // +0x34
};

typedef char InputState_must_be_0x38[(sizeof(InputState) == 0x38) ? 1 : -1];

// Windows owner corresponding to the portable cRGameInput class.
class GameInput : public BodBase {
public:
    void update_game_input();

    InputState input; // +0x38
};

typedef char GameInput_must_be_0x70[(sizeof(GameInput) == 0x70) ? 1 : -1];

#endif
