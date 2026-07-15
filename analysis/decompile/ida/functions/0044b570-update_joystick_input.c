/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_joystick_input @ 0x44b570 */
/* selector: update_joystick_input */

// Polls each enumerated DirectInput joystick device, reacquires on transient loss, normalizes its primary X/Y axes into the shared [-1000, 1000] range, packs the sampled buttons into the game's bitmask format, and publishes the result through the input-controller slot writer.
int __cdecl update_joystick_input()
{
  int v0; // ebx
  IDirectInputDevice8A **v1; // esi
  int result; // eax
  double v3; // st7
  double v4; // st7
  int v5; // esi
  float v6; // [esp+10h] [ebp-11Ch]
  float v7; // [esp+14h] [ebp-118h]
  IDirectInputDevice8A **v8; // [esp+18h] [ebp-114h]
  struct DIJOYSTATE2 state; // [esp+1Ch] [ebp-110h] BYREF

  v0 = 0;
  if ( g_joystick_count > 0 )
  {
    v1 = g_joystick_devices;
    v8 = g_joystick_devices;
    while ( *v1 )
    {
      if ( (*v1)->lpVtbl->Poll(*v1) < 0 )
      {
        while ( g_joystick_devices[v0]->lpVtbl->Acquire(g_joystick_devices[v0]) == -2147024866 )
          ;
        return 0;
      }
      result = (*v1)->lpVtbl->GetDeviceState(*v1, 272, &state);
      if ( result < 0 )
        return result;
      v3 = (double)state.lX * 0.001;
      v6 = v3;
      if ( v3 <= 1000.0 )
      {
        if ( v6 <= -1000.0 )
          v6 = -1000.0;
      }
      else
      {
        v6 = 1000.0;
      }
      v4 = (double)state.lY * 0.001;
      v7 = v4;
      if ( v4 <= 1000.0 )
      {
        if ( v7 <= -1000.0 )
          v7 = -1000.0;
      }
      else
      {
        v7 = 1000.0;
      }
      v5 = (state.rgbButtons[12] & 0x80u) != 0;
      if ( (state.rgbButtons[14] & 0x80u) != 0 )
        v5 |= 2u;
      if ( (state.rgbButtons[15] & 0x80u) != 0 )
        v5 |= 4u;
      if ( (state.rgbButtons[13] & 0x80u) != 0 )
        v5 |= 8u;
      if ( (state.rgbButtons[2] & 0x80u) != 0 )
        v5 |= 0x10u;
      if ( (state.rgbButtons[3] & 0x80u) != 0 )
        v5 |= 0x20u;
      if ( (state.rgbButtons[1] & 0x80u) != 0 )
        v5 |= 0x40u;
      if ( (state.rgbButtons[0] & 0x80u) != 0 )
        v5 |= 0x80u;
      if ( (state.rgbButtons[6] & 0x80u) != 0 )
        v5 |= 0x100u;
      if ( (state.rgbButtons[7] & 0x80u) != 0 )
        v5 |= 0x200u;
      if ( (state.rgbButtons[4] & 0x80u) != 0 )
        v5 |= 0x1000u;
      if ( (state.rgbButtons[5] & 0x80u) != 0 )
        v5 |= 0x2000u;
      if ( (state.rgbButtons[11] & 0x80u) != 0 )
        v5 |= 0x400u;
      if ( (state.rgbButtons[8] & 0x80u) != 0 )
        v5 |= 0x800u;
      update_input_controller_slot_button_axes(v0, v5, v6, v7);
      update_input_controller_slot_button_axes(1, v5, v6, v7);
      ++v0;
      ++v8;
      if ( v0 >= g_joystick_count )
        return 0;
      v1 = v8;
    }
  }
  return 0;
}
