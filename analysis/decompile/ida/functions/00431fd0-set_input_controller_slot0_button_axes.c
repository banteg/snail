/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_input_controller_slot0_button_axes @ 0x431fd0 */
/* selector: set_input_controller_slot0_button_axes */

// Stores the keyboard-derived button mask and X/Y axis floats into input-controller slot 0, overwriting its shared digital and analog lanes before later pointer data is merged in.
InputButtonFlag __cdecl set_input_controller_slot0_button_axes(InputButtonFlag a1, float a2, float a3)
{
  g_input_controller_slot0.buttons = a1;
  g_input_controller_slot0.axis_x = a2;
  g_input_controller_slot0.axis_y = a3;
  return a1;
}
