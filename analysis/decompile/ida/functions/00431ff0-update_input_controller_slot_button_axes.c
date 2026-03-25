/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input_controller_slot_button_axes @ 0x431ff0 */
/* selector: update_input_controller_slot_button_axes */

// Updates one global input-controller slot from a button mask and two analog axes. Slot 0 merges button bits and only fills empty analog lanes, while nonzero slots overwrite their lane directly and derive the slot's centered authored-X value from the X axis with the native 0.15 deadzone.
void __cdecl sub_431FF0(int a1, int a2, float a3, float a4)
{
  int v4; // eax
  double v5; // st7
  double v6; // st7
  int v7; // eax

  if ( a1 )
  {
    v4 = 14 * a1;
    MEMORY[0x503344][v4] = a2;
    MEMORY[0x50333C][v4] = a3;
    MEMORY[0x503340][v4] = a4;
    v5 = MEMORY[0x50333C][0];
    if ( MEMORY[0x50333C][0] <= 0.15000001 )
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
    v7 = MEMORY[0x50337C];
    MEMORY[0x503388] = (v6 + 1.0) * 320.0;
    if ( (a2 & 0xF0) != 0 )
      BYTE1(v7) = BYTE1(MEMORY[0x50337C]) | 0x40;
    else
      BYTE1(v7) = BYTE1(MEMORY[0x50337C]) & 0xBF;
    MEMORY[0x50337C] = v7;
  }
  else
  {
    MEMORY[0x503344][0] |= a2;
    if ( MEMORY[0x50333C][0] == 0.0 )
      MEMORY[0x50333C][0] = a3;
    if ( MEMORY[0x503340][0] == 0.0 )
      MEMORY[0x503340][0] = a4;
  }
}

