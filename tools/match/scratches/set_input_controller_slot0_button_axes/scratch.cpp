// set_input_controller_slot0_button_axes @ 0x431fd0 (cdecl, ret)

extern float g_input_slot0_axis_x; // data_50333c
extern float g_input_slot0_axis_y; // data_503340
extern int g_input_slot0_buttons;  // data_503344

int set_input_controller_slot0_button_axes(int buttons, float axis_x, float axis_y)
{
    g_input_slot0_buttons = buttons;
    g_input_slot0_axis_x = axis_x;
    g_input_slot0_axis_y = axis_y;
    return buttons;
}
