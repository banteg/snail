#ifndef INPUT_STATE_H
#define INPUT_STATE_H

class InputState {
public:
    int initialize_input();
    void update_input();

    int controller_slot;          // +0x00
    int pressed_buttons;          // +0x04, current-frame down edges
    int released_buttons;         // +0x08, current-frame up edges
    int previous_buttons;         // +0x0c
    int inverse_current_buttons;  // +0x10
    float axis_x;                 // +0x14
    float axis_y;                 // +0x18
    int unknown_1c;               // +0x1c
    float pointer_x;              // +0x20
    float pointer_y;              // +0x24
    float authored_x;             // +0x28
    float authored_y;             // +0x2c
    float pointer_value;          // +0x30
    int current_buttons;          // +0x34
};

typedef char InputState_must_be_0x38[(sizeof(InputState) == 0x38) ? 1 : -1];

class GameInputOwner {
public:
    void update_game_input();

    char unknown_00[0x38];
    InputState input; // +0x38
};

typedef char GameInputOwner_must_be_0x70[(sizeof(GameInputOwner) == 0x70) ? 1 : -1];

#endif
