/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_active_input_controller_state @ 0x4320f0 */
/* selector: copy_active_input_controller_state */

// Copies one of the two global input-controller slots into the caller-owned runtime buffer, including button flags, normalized pointer coordinates, and the per-slot authored cursor lanes used by gameplay input.
float *__cdecl copy_active_input_controller_state(
        int controller_slot,
        InputButtonFlag *out_buttons,
        float *out_axis_x,
        float *out_axis_y,
        float *out_authored_x,
        float *out_authored_y,
        float *out_pointer_value,
        float *out_pointer_x,
        float *out_pointer_y)
{
  if ( controller_slot )
  {
    *out_buttons = g_input_controller_slot1.buttons;
    *out_axis_x = g_input_controller_slot1.axis_x;
    *out_axis_y = g_input_controller_slot1.axis_y;
    *out_authored_x = g_input_controller_slot1.authored_x;
    *out_authored_y = g_input_controller_slot1.authored_y;
    *out_pointer_value = g_input_controller_slot1.pointer_value;
    *out_pointer_x = g_input_controller_slot1.pointer_x;
    *out_pointer_y = g_input_controller_slot1.pointer_y;
    return out_pointer_value;
  }
  else
  {
    *out_buttons = g_input_controller_slot0.buttons;
    *out_axis_x = g_input_controller_slot0.axis_x;
    *out_axis_y = g_input_controller_slot0.axis_y;
    *out_authored_x = g_input_controller_slot0.authored_x;
    *out_authored_y = g_input_controller_slot0.authored_y;
    *out_pointer_value = g_input_controller_slot0.pointer_value;
    *out_pointer_x = g_input_controller_slot0.pointer_x;
    *out_pointer_y = g_input_controller_slot0.pointer_y;
    return out_pointer_value;
  }
}
