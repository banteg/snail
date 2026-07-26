/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_keyboard_input @ 0x44b870 */
/* selector: update_keyboard_input */

// Polls the DirectInput keyboard device into the current and previous 0x100-byte key-state tables, retries reacquisition on transient failures, and publishes the derived digital input flags and directional axes into the shared input-controller lanes.
int update_keyboard_input()
{
  int32_t i; // eax
  InputButtonFlag v2; // esi
  float axis_y; // [esp+Ch] [ebp-8h]
  float axis_x; // [esp+10h] [ebp-4h]

  if ( g_keyboard_device != nullptr )
  {
    qmemcpy(g_keyboard_previous_state, g_keyboard_current_state, sizeof(g_keyboard_previous_state));
    memset(g_keyboard_current_state, 0, sizeof(g_keyboard_current_state));
    if ( g_keyboard_device->lpVtbl->GetDeviceState(g_keyboard_device, 256, g_keyboard_current_state) >= 0 )
    {
      v2 = 0;
      axis_x = 0.0;
      axis_y = 0.0;
      if ( is_key_down(0xC8u) != 0 )
      {
        v2 = 1;
        axis_y = -1.0;
      }
      if ( is_key_down(0xD0u) != 0 )
      {
        v2 |= 2u;
        axis_y = 1.0;
      }
      if ( is_key_down(0xCBu) != 0 )
      {
        v2 |= 4u;
        axis_x = -1.0;
      }
      if ( is_key_down(0xCDu) != 0 )
      {
        v2 |= 8u;
        axis_x = 1.0;
      }
      if ( is_key_down(0x1Du) != 0 )
        v2 |= 0x10u;
      if ( is_key_down(0x2Cu) != 0 )
        v2 |= 0x100u;
      if ( is_key_down(0x2Eu) != 0 )
        v2 |= 0x200u;
      if ( is_key_down(0x1Fu) != 0 )
        v2 |= 0x80u;
      if ( is_key_down(0x2Du) != 0 )
        v2 |= 0x40u;
      if ( is_key_down(0x38u) != 0 )
        v2 |= 0x4000000u;
      if ( is_key_down(0x38u) != 0 )
        v2 |= 0x20u;
      if ( is_key_down(0x2Cu) != 0 )
        v2 |= 0x20000u;
      if ( is_key_down(0x2Eu) != 0 )
        v2 |= 0x1000000u;
      if ( is_key_down(0x39u) != 0 )
        v2 |= 0x80000u;
      if ( is_key_down(0x3Cu) != 0 )
        v2 |= 0x400u;
      if ( is_key_down(0x39u) != 0 )
        v2 |= 0x2000u;
      if ( is_key_down(0x11u) != 0 )
        v2 |= 0x400000u;
      if ( is_key_down(0x2Du) != 0 )
        v2 |= 0x40000u;
      if ( is_key_down(0x1Fu) != 0 )
        v2 |= 0x200000u;
      if ( is_key_down(0x12u) != 0 )
        v2 |= 0x800000u;
      if ( is_key_down(0x1Du) != 0 )
        v2 |= 0x10000u;
      if ( is_key_down(0x2Au) != 0 )
        v2 |= 0x2000000u;
      set_input_controller_slot0_button_axes(v2, axis_x, axis_y);
    }
    else
    {
      for ( i = g_keyboard_device->lpVtbl->Acquire(g_keyboard_device);
            i == -2147024866;
            i = g_keyboard_device->lpVtbl->Acquire(g_keyboard_device) )
      {
        ;
      }
      if ( i == -2147024891 || i == -2147024884 )
      {
        memset(g_keyboard_current_state, 0, sizeof(g_keyboard_current_state));
        memset(g_keyboard_previous_state, 0, sizeof(g_keyboard_previous_state));
        return 0;
      }
    }
  }
  return 0;
}
