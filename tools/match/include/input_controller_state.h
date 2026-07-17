// Shared input-controller slot payload. Windows places the two proved 0x20-byte
// payloads 0x38 bytes apart, but the trailing bytes are not slot-owned: the
// second stride overlaps independently authored RShell repeat globals.
#ifndef INPUT_CONTROLLER_STATE_H
#define INPUT_CONTROLLER_STATE_H

#include "input_buttons.h"

struct InputControllerSlot {
    float axis_x;            // +0x00
    float axis_y;            // +0x04
    int buttons;             // +0x08, InputButtonFlag word plus gameplay lanes
    float pointer_x;         // +0x0c
    float pointer_y;         // +0x10
    float authored_x;        // +0x14, 640-wide authored coordinate
    float authored_y;        // +0x18, 480-high authored coordinate
    float pointer_value;     // +0x1c, copied from pointer-region arg8
};

typedef char InputControllerSlot_must_be_0x20[
    (sizeof(InputControllerSlot) == 0x20) ? 1 : -1];

enum {
    INPUT_CONTROLLER_SLOT_COUNT = 2,
    INPUT_CONTROLLER_SLOT_STRIDE = 0x38,
};

extern InputControllerSlot g_input_controller_slot0; // data_50333c
extern InputControllerSlot g_input_controller_slot1; // data_503374

__inline InputControllerSlot& input_controller_slot(int slot)
{
    return *(InputControllerSlot*)((char*)&g_input_controller_slot0
        + slot * INPUT_CONTROLLER_SLOT_STRIDE);
}

// Field-address views used by functions that operate on one lane directly;
// slot 1 is 14 dwords/floats after slot 0.
extern float g_input_slot0_axis_x[];       // data_50333c
extern float g_input_slot0_axis_y[];       // data_503340
extern int g_input_slot0_buttons[];        // data_503344
extern float g_input_slot0_pointer_x[];    // data_503348
extern float g_input_slot0_pointer_y[];    // data_50334c
extern float g_input_slot0_authored_x[];   // data_503350
extern float g_input_slot0_authored_y[];   // data_503354
extern float g_input_slot0_pointer_value[]; // data_503358

extern int g_input_region_top[INPUT_CONTROLLER_SLOT_COUNT];    // data_508890
extern int g_input_region_bottom[INPUT_CONTROLLER_SLOT_COUNT]; // data_508898
extern int g_input_region_left[INPUT_CONTROLLER_SLOT_COUNT];   // data_5088a0
extern int g_input_region_right[INPUT_CONTROLLER_SLOT_COUNT];  // data_5088a8

void update_input_controller_pointer_region(
    int slot,
    int left,
    int top,
    int right,
    int bottom,
    int x,
    int y,
    int pointer_value,
    char button_a,
    char button_b,
    char button_c,
    char capture_when_outside,
    char force_clamp); // @ 0x4321c0

#endif
