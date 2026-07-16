/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input_controller_slot_button_axes @ 0x431ff0 */
/* selector: update_input_controller_slot_button_axes */

// Updates one global input-controller slot from a button mask and two analog axes. Slot 0 merges button bits and only fills empty analog lanes, while nonzero slots overwrite their lane directly and derive the slot's centered authored-X value from the X axis with the native 0.15 deadzone.
void __cdecl update_input_controller_slot_button_axes(int a1, InputButtonFlag a2, float a3, float a4)
{
  int v4; // eax
  double axis_x; // st7
  double v6; // st7
  InputButtonFlag buttons; // eax

  if ( a1 )
  {
    v4 = 56 * a1;
    *(InputButtonFlag *)((char *)&g_input_controller_slot0.buttons + v4) = a2;
    *(float *)((char *)&g_input_controller_slot0.axis_x + v4) = a3;
    *(float *)((char *)&g_input_controller_slot0.axis_y + v4) = a4;
    axis_x = g_input_controller_slot0.axis_x;
    if ( g_input_controller_slot0.axis_x <= 0.15000001 )
    {
      if ( axis_x <= -0.15000001 )
        v6 = (-axis_x - 0.15000001) * -1.1764706;
      else
        v6 = 0.0;
    }
    else
    {
      v6 = (axis_x - 0.15000001) * 1.1764706;
    }
    buttons = g_input_controller_slot1.buttons;
    g_input_controller_slot1.authored_x = (v6 + 1.0) * 320.0;
    if ( (a2 & 0xF0) != 0 )
      BYTE1(buttons) = BYTE1(g_input_controller_slot1.buttons) | 0x40;
    else
      BYTE1(buttons) = BYTE1(g_input_controller_slot1.buttons) & 0xBF;
    g_input_controller_slot1.buttons = buttons;
  }
  else
  {
    g_input_controller_slot0.buttons |= a2;
    if ( g_input_controller_slot0.axis_x == 0.0 )
      g_input_controller_slot0.axis_x = a3;
    if ( g_input_controller_slot0.axis_y == 0.0 )
      g_input_controller_slot0.axis_y = a4;
  }
}
