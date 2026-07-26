/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_input_controller_slot0_button_axes @ 0x431fd0 */
/* selector: set_input_controller_slot0_button_axes */

// Stores the keyboard-derived button mask and X/Y axis floats into input-controller slot 0, overwriting its shared digital and analog lanes before later pointer data is merged in.
void __cdecl set_input_controller_slot0_button_axes(InputButtonFlag buttons, float axis_x, float axis_y)
{
  g_input_controller_slot0.buttons = buttons;
  g_input_controller_slot0.axis_x = axis_x;
  g_input_controller_slot0.axis_y = axis_y;
}
