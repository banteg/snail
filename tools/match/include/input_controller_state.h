// Shared input-controller slot state, partial.
#ifndef INPUT_CONTROLLER_STATE_H
#define INPUT_CONTROLLER_STATE_H

struct InputControllerSlot {
    float axis_x;            // +0x00
    float axis_y;            // +0x04
    int buttons;             // +0x08
    float pointer_x;         // +0x0c
    float pointer_y;         // +0x10
    float authored_x;        // +0x14, 640-wide authored coordinate
    float authored_y;        // +0x18, 480-high authored coordinate
    float pointer_value;     // +0x1c, copied from pointer-region arg8
    char unknown_20[0x38 - 0x20];
};

typedef char InputControllerSlot_must_be_0x38[
    (sizeof(InputControllerSlot) == 0x38) ? 1 : -1];

// The globals are lane arrays: slot 1 is 14 dwords/floats after slot 0.
extern float g_input_slot0_axis_x[];       // data_50333c
extern float g_input_slot0_axis_y[];       // data_503340
extern int g_input_slot0_buttons[];        // data_503344
extern float g_input_slot0_pointer_x[];    // data_503348
extern float g_input_slot0_pointer_y[];    // data_50334c
extern float g_input_slot0_authored_x[];   // data_503350
extern float g_input_slot0_authored_y[];   // data_503354
extern float g_input_slot0_pointer_value[]; // data_503358

extern int g_input_region_top[2];          // data_508890
extern int g_input_region_bottom[2];       // data_508898
extern int g_input_region_left[2];         // data_5088a0
extern int g_input_region_right[2];        // data_5088a8

#endif
