/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input_controller_slot_button_axes @ 0x431ff0 */
/* selector: update_input_controller_slot_button_axes */

// Updates one global input-controller slot from a button mask and two analog axes. Slot 0 merges button bits and only fills empty analog lanes, while nonzero slots overwrite their lane directly and derive the slot's centered authored-X value from the X axis with the native 0.15 deadzone.
void __cdecl update_input_controller_slot_button_axes(int slot, InputButtonFlag buttons, float axis_x, float axis_y)
{
  int v4; // eax
  double v5; // st7
  double v6; // st7
  InputButtonFlag v7; // eax

  if ( slot != 0 )
  {
    v4 = 56 * slot;
    *(InputButtonFlag *)((char *)&g_input_controller_slot0.buttons + v4) = buttons;
    *(float *)((char *)&g_input_controller_slot0.axis_x + v4) = axis_x;
    *(float *)((char *)&g_input_controller_slot0.axis_y + v4) = axis_y;
    v5 = g_input_controller_slot0.axis_x;
    if ( g_input_controller_slot0.axis_x <= 0.15000001 )
    {
      if ( v5 <= -0.15000001 )
        v6 = (-v5 - 0.15000001) * -1.1764706;
      else
        v6 = 0.0;
    }
    else
    {
      v6 = (v5 - 0.15000001) * 1.1764706;
    }
    v7 = g_input_controller_slot1.buttons;
    g_input_controller_slot1.authored_x = (v6 + 1.0) * 320.0;
    if ( (buttons & 0xF0) != 0 )
      BYTE1(v7) = BYTE1(g_input_controller_slot1.buttons) | 0x40;
    else
      BYTE1(v7) = BYTE1(g_input_controller_slot1.buttons) & 0xBF;
    g_input_controller_slot1.buttons = v7;
  }
  else
  {
    g_input_controller_slot0.buttons |= buttons;
    if ( g_input_controller_slot0.axis_x == 0.0 )
      g_input_controller_slot0.axis_x = axis_x;
    if ( g_input_controller_slot0.axis_y == 0.0 )
      g_input_controller_slot0.axis_y = axis_y;
  }
}
