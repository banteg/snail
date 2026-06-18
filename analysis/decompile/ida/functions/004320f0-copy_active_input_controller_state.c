/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_active_input_controller_state @ 0x4320f0 */
/* selector: copy_active_input_controller_state */

// Copies one of the two global input-controller slots into the caller-owned runtime buffer, including button flags, normalized pointer coordinates, and the per-slot authored cursor lanes used by gameplay input.
float *__cdecl copy_active_input_controller_state(
        int controller_slot,
        int *out_buttons,
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
    *out_buttons = unk_50337C;
    *out_axis_x = unk_503374;
    *out_axis_y = unk_503378;
    *out_authored_x = unk_503388;
    *out_authored_y = unk_50338C;
    *out_pointer_value = unk_503390;
    *out_pointer_x = unk_503380;
    *out_pointer_y = unk_503384;
    return out_pointer_value;
  }
  else
  {
    *out_buttons = g_input_slot0_buttons[0];
    *out_axis_x = g_input_slot0_axis_x[0];
    *out_axis_y = g_input_slot0_axis_y[0];
    *out_authored_x = *(float *)g_input_slot0_authored_x;
    *out_authored_y = *(float *)g_input_slot0_authored_y;
    *out_pointer_value = g_input_slot0_pointer_value;
    *out_pointer_x = g_input_slot0_pointer_x;
    *out_pointer_y = g_input_slot0_pointer_y;
    return out_pointer_value;
  }
}

