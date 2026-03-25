/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_repeating_text_input_key_code @ 0x4327e0 */
/* selector: read_repeating_text_input_key_code */

// Maps held keyboard scancodes into the same text-input byte codes as read_pressed_text_input_key_code, but with the native repeat delay/rate state so border_input_text can autorepeat held edits and cursor moves.
char sub_4327E0()
{
  char v0; // bl
  double v2; // st7
  char v3; // [esp+7h] [ebp-5h]
  char v4; // [esp+8h] [ebp-4h]

  v0 = 0;
  v4 = 0;
  if ( is_key_down(0x1Eu) )
  {
    v0 = 97;
    v4 = 97;
  }
  if ( is_key_down(0x30u) )
  {
    v0 = 98;
    v4 = 98;
  }
  if ( is_key_down(0x2Eu) )
  {
    v0 = 99;
    v4 = 99;
  }
  if ( is_key_down(0x20u) )
  {
    v0 = 100;
    v4 = 100;
  }
  if ( is_key_down(0x12u) )
  {
    v0 = 101;
    v4 = 101;
  }
  if ( is_key_down(0x21u) )
  {
    v0 = 102;
    v4 = 102;
  }
  if ( is_key_down(0x22u) )
  {
    v0 = 103;
    v4 = 103;
  }
  if ( is_key_down(0x23u) )
  {
    v0 = 104;
    v4 = 104;
  }
  if ( is_key_down(0x17u) )
  {
    v0 = 105;
    v4 = 105;
  }
  if ( is_key_down(0x24u) )
  {
    v0 = 106;
    v4 = 106;
  }
  if ( is_key_down(0x25u) )
  {
    v0 = 107;
    v4 = 107;
  }
  if ( is_key_down(0x26u) )
  {
    v0 = 108;
    v4 = 108;
  }
  if ( is_key_down(0x32u) )
  {
    v0 = 109;
    v4 = 109;
  }
  if ( is_key_down(0x31u) )
  {
    v0 = 110;
    v4 = 110;
  }
  if ( is_key_down(0x18u) )
  {
    v0 = 111;
    v4 = 111;
  }
  if ( is_key_down(0x19u) )
  {
    v0 = 112;
    v4 = 112;
  }
  if ( is_key_down(0x10u) )
  {
    v0 = 113;
    v4 = 113;
  }
  if ( is_key_down(0x13u) )
  {
    v0 = 114;
    v4 = 114;
  }
  if ( is_key_down(0x1Fu) )
  {
    v0 = 115;
    v4 = 115;
  }
  if ( is_key_down(0x14u) )
  {
    v0 = 116;
    v4 = 116;
  }
  if ( is_key_down(0x16u) )
  {
    v0 = 117;
    v4 = 117;
  }
  if ( is_key_down(0x2Fu) )
  {
    v0 = 118;
    v4 = 118;
  }
  if ( is_key_down(0x11u) )
  {
    v0 = 119;
    v4 = 119;
  }
  if ( is_key_down(0x2Du) )
  {
    v0 = 120;
    v4 = 120;
  }
  if ( is_key_down(0x15u) )
  {
    v0 = 121;
    v4 = 121;
  }
  if ( is_key_down(0x2Cu) )
  {
    v0 = 122;
    v4 = 122;
  }
  else if ( !v0 )
  {
    goto LABEL_57;
  }
  if ( is_key_down(0x2Au) || is_key_down(0x36u) )
  {
    v0 -= 32;
    v4 = v0;
  }
LABEL_57:
  if ( is_key_down(0x39u) )
  {
    v0 = 32;
    v4 = 32;
  }
  if ( is_key_down(0xBu) )
  {
    v0 = 48;
    v4 = 48;
  }
  if ( is_key_down(2u) )
  {
    v0 = 49;
    v4 = 49;
  }
  if ( is_key_down(3u) )
  {
    v0 = 50;
    v4 = 50;
  }
  if ( is_key_down(4u) )
  {
    v0 = 51;
    v4 = 51;
  }
  if ( is_key_down(5u) )
  {
    v0 = 52;
    v4 = 52;
  }
  if ( is_key_down(6u) )
  {
    v0 = 53;
    v4 = 53;
  }
  if ( is_key_down(7u) )
  {
    v0 = 54;
    v4 = 54;
  }
  if ( is_key_down(8u) )
  {
    v0 = 55;
    v4 = 55;
  }
  if ( is_key_down(9u) )
  {
    v0 = 56;
    v4 = 56;
  }
  if ( is_key_down(0xAu) )
  {
    v0 = 57;
    v4 = 57;
  }
  if ( is_key_down(0x34u) )
  {
    v0 = 46;
    v4 = 46;
  }
  if ( is_key_down(0x33u) )
  {
    v0 = 44;
    v4 = 44;
  }
  if ( is_key_down(0x28u) )
  {
    v0 = 39;
    v4 = 39;
  }
  if ( is_key_down(0x2Bu) )
  {
    v0 = 92;
    v4 = 92;
  }
  if ( is_key_down(0xEu) )
  {
    v0 = 1;
    v4 = 1;
  }
  if ( is_key_down(0xD3u) )
  {
    v0 = 2;
    v4 = 2;
  }
  if ( is_key_down(0xCBu) )
  {
    v0 = 3;
    v4 = 3;
  }
  if ( is_key_down(0xCDu) )
  {
    v0 = 4;
    v4 = 4;
  }
  if ( is_key_down(0xC8u) )
  {
    v0 = 7;
    v4 = 7;
  }
  if ( is_key_down(0xD0u) )
  {
    v0 = 8;
    v4 = 8;
  }
  if ( is_key_down(0xCFu) )
  {
    v0 = 9;
    v4 = 9;
  }
  if ( is_key_down(0xC7u) )
  {
    v0 = 10;
    v4 = 10;
  }
  if ( is_key_down(1u) )
  {
    v0 = 11;
    v4 = 11;
  }
  if ( is_key_down(0x3Bu) )
  {
    v0 = 12;
    v4 = 12;
  }
  if ( is_key_down(0x1Cu) )
  {
    v0 = is_key_down(0x1Du) + 5;
    v4 = v0;
  }
  else if ( !v0 )
  {
    MEMORY[0x5108B8] = 0;
    MEMORY[0x53C7F5] = 0;
    return 0;
  }
  if ( *(float *)&MEMORY[0x5108B8] == 0.0 )
  {
    MEMORY[0x53C7F5] = v0;
    MEMORY[0x50339C] = 1023969417;
    MEMORY[0x5108B8] = 1023969417;
    return v0;
  }
  v3 = ascii_upper_if_lowercase(v4);
  if ( v3 == ascii_upper_if_lowercase(MEMORY[0x53C7F5]) )
  {
    v2 = *(float *)&MEMORY[0x50339C] + *(float *)&MEMORY[0x5108B8];
    *(float *)&MEMORY[0x5108B8] = v2;
    if ( v2 > 1.0 )
    {
      MEMORY[0x50339C] = 1038323256;
      MEMORY[0x5108B8] = 1038323256;
      return v0;
    }
    return 0;
  }
  MEMORY[0x53C7F5] = v0;
  MEMORY[0x50339C] = 1010174817;
  MEMORY[0x5108B8] = 1010174817;
  return v0;
}

