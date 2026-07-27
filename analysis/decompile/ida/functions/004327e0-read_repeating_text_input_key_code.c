/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_repeating_text_input_key_code @ 0x4327e0 */
/* selector: read_repeating_text_input_key_code */

// Maps held keyboard scancodes into the same text-input byte codes as read_pressed_text_input_key_code, but with the native repeat delay/rate state so border_input_text can autorepeat held edits and cursor moves.
char __cdecl read_repeating_text_input_key_code()
{
  char v0; // bl
  double v2; // st7
  char v3; // [esp+7h] [ebp-5h]
  char value; // [esp+8h] [ebp-4h]

  v0 = 0;
  value = 0;
  if ( is_key_down(0x1Eu) != 0 )
  {
    v0 = 97;
    value = 97;
  }
  if ( is_key_down(0x30u) != 0 )
  {
    v0 = 98;
    value = 98;
  }
  if ( is_key_down(0x2Eu) != 0 )
  {
    v0 = 99;
    value = 99;
  }
  if ( is_key_down(0x20u) != 0 )
  {
    v0 = 100;
    value = 100;
  }
  if ( is_key_down(0x12u) != 0 )
  {
    v0 = 101;
    value = 101;
  }
  if ( is_key_down(0x21u) != 0 )
  {
    v0 = 102;
    value = 102;
  }
  if ( is_key_down(0x22u) != 0 )
  {
    v0 = 103;
    value = 103;
  }
  if ( is_key_down(0x23u) != 0 )
  {
    v0 = 104;
    value = 104;
  }
  if ( is_key_down(0x17u) != 0 )
  {
    v0 = 105;
    value = 105;
  }
  if ( is_key_down(0x24u) != 0 )
  {
    v0 = 106;
    value = 106;
  }
  if ( is_key_down(0x25u) != 0 )
  {
    v0 = 107;
    value = 107;
  }
  if ( is_key_down(0x26u) != 0 )
  {
    v0 = 108;
    value = 108;
  }
  if ( is_key_down(0x32u) != 0 )
  {
    v0 = 109;
    value = 109;
  }
  if ( is_key_down(0x31u) != 0 )
  {
    v0 = 110;
    value = 110;
  }
  if ( is_key_down(0x18u) != 0 )
  {
    v0 = 111;
    value = 111;
  }
  if ( is_key_down(0x19u) != 0 )
  {
    v0 = 112;
    value = 112;
  }
  if ( is_key_down(0x10u) != 0 )
  {
    v0 = 113;
    value = 113;
  }
  if ( is_key_down(0x13u) != 0 )
  {
    v0 = 114;
    value = 114;
  }
  if ( is_key_down(0x1Fu) != 0 )
  {
    v0 = 115;
    value = 115;
  }
  if ( is_key_down(0x14u) != 0 )
  {
    v0 = 116;
    value = 116;
  }
  if ( is_key_down(0x16u) != 0 )
  {
    v0 = 117;
    value = 117;
  }
  if ( is_key_down(0x2Fu) != 0 )
  {
    v0 = 118;
    value = 118;
  }
  if ( is_key_down(0x11u) != 0 )
  {
    v0 = 119;
    value = 119;
  }
  if ( is_key_down(0x2Du) != 0 )
  {
    v0 = 120;
    value = 120;
  }
  if ( is_key_down(0x15u) != 0 )
  {
    v0 = 121;
    value = 121;
  }
  if ( is_key_down(0x2Cu) != 0 )
  {
    v0 = 122;
    value = 122;
  }
  else if ( v0 == 0 )
  {
    goto LABEL_57;
  }
  if ( is_key_down(0x2Au) != 0 || is_key_down(0x36u) != 0 )
  {
    v0 -= 32;
    value = v0;
  }
LABEL_57:
  if ( is_key_down(0x39u) != 0 )
  {
    v0 = 32;
    value = 32;
  }
  if ( is_key_down(0xBu) != 0 )
  {
    v0 = 48;
    value = 48;
  }
  if ( is_key_down(2u) != 0 )
  {
    v0 = 49;
    value = 49;
  }
  if ( is_key_down(3u) != 0 )
  {
    v0 = 50;
    value = 50;
  }
  if ( is_key_down(4u) != 0 )
  {
    v0 = 51;
    value = 51;
  }
  if ( is_key_down(5u) != 0 )
  {
    v0 = 52;
    value = 52;
  }
  if ( is_key_down(6u) != 0 )
  {
    v0 = 53;
    value = 53;
  }
  if ( is_key_down(7u) != 0 )
  {
    v0 = 54;
    value = 54;
  }
  if ( is_key_down(8u) != 0 )
  {
    v0 = 55;
    value = 55;
  }
  if ( is_key_down(9u) != 0 )
  {
    v0 = 56;
    value = 56;
  }
  if ( is_key_down(0xAu) != 0 )
  {
    v0 = 57;
    value = 57;
  }
  if ( is_key_down(0x34u) != 0 )
  {
    v0 = 46;
    value = 46;
  }
  if ( is_key_down(0x33u) != 0 )
  {
    v0 = 44;
    value = 44;
  }
  if ( is_key_down(0x28u) != 0 )
  {
    v0 = 39;
    value = 39;
  }
  if ( is_key_down(0x2Bu) != 0 )
  {
    v0 = 92;
    value = 92;
  }
  if ( is_key_down(0xEu) != 0 )
  {
    v0 = 1;
    value = 1;
  }
  if ( is_key_down(0xD3u) != 0 )
  {
    v0 = 2;
    value = 2;
  }
  if ( is_key_down(0xCBu) != 0 )
  {
    v0 = 3;
    value = 3;
  }
  if ( is_key_down(0xCDu) != 0 )
  {
    v0 = 4;
    value = 4;
  }
  if ( is_key_down(0xC8u) != 0 )
  {
    v0 = 7;
    value = 7;
  }
  if ( is_key_down(0xD0u) != 0 )
  {
    v0 = 8;
    value = 8;
  }
  if ( is_key_down(0xCFu) != 0 )
  {
    v0 = 9;
    value = 9;
  }
  if ( is_key_down(0xC7u) != 0 )
  {
    v0 = 10;
    value = 10;
  }
  if ( is_key_down(1u) != 0 )
  {
    v0 = 11;
    value = 11;
  }
  if ( is_key_down(0x3Bu) != 0 )
  {
    v0 = 12;
    value = 12;
  }
  if ( is_key_down(0x1Cu) != 0 )
  {
    v0 = (is_key_down(0x1Du) != 0) + 5;
    value = v0;
  }
  else if ( v0 == 0 )
  {
    g_text_input_repeat_accumulator = 0.0;
    g_text_input_last_repeat_code = 0;
    return 0;
  }
  if ( g_text_input_repeat_accumulator == 0.0 )
  {
    g_text_input_last_repeat_code = v0;
    g_text_input_repeat_step = 0.033333335;
    g_text_input_repeat_accumulator = 0.033333335;
    return v0;
  }
  v3 = ascii_upper_if_lowercase(value);
  if ( v3 == ascii_upper_if_lowercase(g_text_input_last_repeat_code) )
  {
    v2 = g_text_input_repeat_step + g_text_input_repeat_accumulator;
    g_text_input_repeat_accumulator = v2;
    if ( v2 > 1.0 )
    {
      g_text_input_repeat_step = 0.1111111;
      g_text_input_repeat_accumulator = 0.1111111;
      return v0;
    }
    return 0;
  }
  g_text_input_last_repeat_code = v0;
  g_text_input_repeat_step = 0.011111111;
  g_text_input_repeat_accumulator = 0.011111111;
  return v0;
}
