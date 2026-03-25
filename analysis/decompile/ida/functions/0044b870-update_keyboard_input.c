/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_keyboard_input @ 0x44b870 */
/* selector: update_keyboard_input */

// Polls the DirectInput keyboard device into the current and previous 0x100-byte key-state tables, retries reacquisition on transient failures, and publishes the derived digital input flags and directional axes into the shared input-controller lanes.
int sub_44B870()
{
  int i; // eax
  int v2; // esi
  float v3; // [esp+Ch] [ebp-8h]
  float v4; // [esp+10h] [ebp-4h]

  if ( MEMORY[0x777D50] )
  {
    qmemcpy(MEMORY[0x777B4C], MEMORY[0x777C4C], sizeof(MEMORY[0x777B4C]));
    memset(MEMORY[0x777C4C], 0, sizeof(MEMORY[0x777C4C]));
    if ( (*(int (__stdcall **)(int, int, char *))(*(_DWORD *)MEMORY[0x777D50] + 36))(
           MEMORY[0x777D50],
           256,
           MEMORY[0x777C4C]) >= 0 )
    {
      v2 = 0;
      v4 = 0.0;
      v3 = 0.0;
      if ( is_key_down(0xC8u) )
      {
        v2 = 1;
        v3 = -1.0;
      }
      if ( is_key_down(0xD0u) )
      {
        v2 |= 2u;
        v3 = 1.0;
      }
      if ( is_key_down(0xCBu) )
      {
        v2 |= 4u;
        v4 = -1.0;
      }
      if ( is_key_down(0xCDu) )
      {
        v2 |= 8u;
        v4 = 1.0;
      }
      if ( is_key_down(0x1Du) )
        v2 |= 0x10u;
      if ( is_key_down(0x2Cu) )
        v2 |= 0x100u;
      if ( is_key_down(0x2Eu) )
        v2 |= 0x200u;
      if ( is_key_down(0x1Fu) )
        v2 |= 0x80u;
      if ( is_key_down(0x2Du) )
        v2 |= 0x40u;
      if ( is_key_down(0x38u) )
        v2 |= 0x4000000u;
      if ( is_key_down(0x38u) )
        v2 |= 0x20u;
      if ( is_key_down(0x2Cu) )
        v2 |= 0x20000u;
      if ( is_key_down(0x2Eu) )
        v2 |= 0x1000000u;
      if ( is_key_down(0x39u) )
        v2 |= 0x80000u;
      if ( is_key_down(0x3Cu) )
        v2 |= 0x400u;
      if ( is_key_down(0x39u) )
        v2 |= 0x2000u;
      if ( is_key_down(0x11u) )
        v2 |= 0x400000u;
      if ( is_key_down(0x2Du) )
        v2 |= 0x40000u;
      if ( is_key_down(0x1Fu) )
        v2 |= 0x200000u;
      if ( is_key_down(0x12u) )
        v2 |= (unsigned int)&unk_800000;
      if ( is_key_down(0x1Du) )
        v2 |= 0x10000u;
      if ( is_key_down(0x2Au) )
        v2 |= 0x2000000u;
      set_input_controller_slot0_button_axes(v2, v4, v3);
    }
    else
    {
      for ( i = (*(int (__stdcall **)(int))(*(_DWORD *)MEMORY[0x777D50] + 28))(MEMORY[0x777D50]);
            i == -2147024866;
            i = (*(int (__stdcall **)(int))(*(_DWORD *)MEMORY[0x777D50] + 28))(MEMORY[0x777D50]) )
      {
        ;
      }
      if ( i == -2147024891 || i == -2147024884 )
      {
        memset(MEMORY[0x777C4C], 0, sizeof(MEMORY[0x777C4C]));
        memset(MEMORY[0x777B4C], 0, sizeof(MEMORY[0x777B4C]));
        return 0;
      }
    }
  }
  return 0;
}

