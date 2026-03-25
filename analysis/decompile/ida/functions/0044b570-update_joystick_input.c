/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_joystick_input @ 0x44b570 */
/* selector: update_joystick_input */

// Polls each enumerated DirectInput joystick device, reacquires on transient loss, normalizes its primary X/Y axes into the shared [-1000, 1000] range, packs the sampled buttons into the game's bitmask format, and publishes the result through the input-controller slot writer.
int sub_44B570()
{
  int v0; // ebx
  int *v1; // esi
  int result; // eax
  double v3; // st7
  double v4; // st7
  int v5; // esi
  float v6; // [esp+10h] [ebp-11Ch]
  float v7; // [esp+14h] [ebp-118h]
  int *v8; // [esp+18h] [ebp-114h]
  _DWORD v9[12]; // [esp+1Ch] [ebp-110h] BYREF
  char v10; // [esp+4Ch] [ebp-E0h]
  char v11; // [esp+4Dh] [ebp-DFh]
  char v12; // [esp+4Eh] [ebp-DEh]
  char v13; // [esp+4Fh] [ebp-DDh]
  char v14; // [esp+50h] [ebp-DCh]
  char v15; // [esp+51h] [ebp-DBh]
  char v16; // [esp+52h] [ebp-DAh]
  char v17; // [esp+53h] [ebp-D9h]
  char v18; // [esp+54h] [ebp-D8h]
  char v19; // [esp+57h] [ebp-D5h]
  char v20; // [esp+58h] [ebp-D4h]
  char v21; // [esp+59h] [ebp-D3h]
  char v22; // [esp+5Ah] [ebp-D2h]
  char v23; // [esp+5Bh] [ebp-D1h]

  v0 = 0;
  if ( dword_777B2C > 0 )
  {
    v1 = MEMORY[0x777B34];
    v8 = MEMORY[0x777B34];
    while ( *v1 )
    {
      if ( (*(int (__stdcall **)(int))(*(_DWORD *)*v1 + 100))(*v1) < 0 )
      {
        while ( (*(int (__stdcall **)(int))(*(_DWORD *)MEMORY[0x777B34][v0] + 28))(MEMORY[0x777B34][v0]) == -2147024866 )
          ;
        return 0;
      }
      result = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)*v1 + 36))(*v1, 272, v9);
      if ( result < 0 )
        return result;
      v3 = (double)v9[0] * 0.001;
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
      v4 = (double)v9[1] * 0.001;
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
      v5 = v20 < 0;
      if ( v22 < 0 )
        v5 |= 2u;
      if ( v23 < 0 )
        v5 |= 4u;
      if ( v21 < 0 )
        v5 |= 8u;
      if ( v12 < 0 )
        v5 |= 0x10u;
      if ( v13 < 0 )
        v5 |= 0x20u;
      if ( v11 < 0 )
        v5 |= 0x40u;
      if ( v10 < 0 )
        v5 |= 0x80u;
      if ( v16 < 0 )
        v5 |= 0x100u;
      if ( v17 < 0 )
        v5 |= 0x200u;
      if ( v14 < 0 )
        v5 |= 0x1000u;
      if ( v15 < 0 )
        v5 |= 0x2000u;
      if ( v19 < 0 )
        v5 |= 0x400u;
      if ( v18 < 0 )
        v5 |= 0x800u;
      update_input_controller_slot_button_axes(v0, v5, v6, v7);
      update_input_controller_slot_button_axes(1, v5, v6, v7);
      ++v0;
      ++v8;
      if ( v0 >= dword_777B2C )
        return 0;
      v1 = v8;
    }
  }
  return 0;
}

