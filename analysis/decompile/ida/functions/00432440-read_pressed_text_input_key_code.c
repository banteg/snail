/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_pressed_text_input_key_code @ 0x432440 */
/* selector: read_pressed_text_input_key_code */

// Maps newly pressed keyboard scancodes into the shared text-input byte codes used by frontend widgets, cheat entry, intro skip, and subgame ESC handling: ASCII for letters/digits/punctuation plus the small control-code set for edit and navigation keys.
char sub_432440()
{
  char v0; // bl

  v0 = 0;
  if ( is_key_pressed_edge(0x1Eu) )
    v0 = 97;
  if ( is_key_pressed_edge(0x30u) )
    v0 = 98;
  if ( is_key_pressed_edge(0x2Eu) )
    v0 = 99;
  if ( is_key_pressed_edge(0x20u) )
    v0 = 100;
  if ( is_key_pressed_edge(0x12u) )
    v0 = 101;
  if ( is_key_pressed_edge(0x21u) )
    v0 = 102;
  if ( is_key_pressed_edge(0x22u) )
    v0 = 103;
  if ( is_key_pressed_edge(0x23u) )
    v0 = 104;
  if ( is_key_pressed_edge(0x17u) )
    v0 = 105;
  if ( is_key_pressed_edge(0x24u) )
    v0 = 106;
  if ( is_key_pressed_edge(0x25u) )
    v0 = 107;
  if ( is_key_pressed_edge(0x26u) )
    v0 = 108;
  if ( is_key_pressed_edge(0x32u) )
    v0 = 109;
  if ( is_key_pressed_edge(0x31u) )
    v0 = 110;
  if ( is_key_pressed_edge(0x18u) )
    v0 = 111;
  if ( is_key_pressed_edge(0x19u) )
    v0 = 112;
  if ( is_key_pressed_edge(0x10u) )
    v0 = 113;
  if ( is_key_pressed_edge(0x13u) )
    v0 = 114;
  if ( is_key_pressed_edge(0x1Fu) )
    v0 = 115;
  if ( is_key_pressed_edge(0x14u) )
    v0 = 116;
  if ( is_key_pressed_edge(0x16u) )
    v0 = 117;
  if ( is_key_pressed_edge(0x2Fu) )
    v0 = 118;
  if ( is_key_pressed_edge(0x11u) )
    v0 = 119;
  if ( is_key_pressed_edge(0x2Du) )
    v0 = 120;
  if ( is_key_pressed_edge(0x15u) )
    v0 = 121;
  if ( is_key_pressed_edge(0x2Cu) )
  {
    v0 = 122;
  }
  else if ( !v0 )
  {
    goto LABEL_57;
  }
  if ( is_key_down(0x2Au) || is_key_down(0x36u) )
    v0 -= 32;
LABEL_57:
  if ( is_key_pressed_edge(0x39u) )
    v0 = 32;
  if ( is_key_pressed_edge(0xBu) )
    v0 = 48;
  if ( is_key_pressed_edge(2u) )
    v0 = 49;
  if ( is_key_pressed_edge(3u) )
    v0 = 50;
  if ( is_key_pressed_edge(4u) )
    v0 = 51;
  if ( is_key_pressed_edge(5u) )
    v0 = 52;
  if ( is_key_pressed_edge(6u) )
    v0 = 53;
  if ( is_key_pressed_edge(7u) )
    v0 = 54;
  if ( is_key_pressed_edge(8u) )
    v0 = 55;
  if ( is_key_pressed_edge(9u) )
    v0 = 56;
  if ( is_key_pressed_edge(0xAu) )
    v0 = 57;
  if ( is_key_pressed_edge(0x34u) )
    v0 = 46;
  if ( is_key_pressed_edge(0x33u) )
    v0 = 44;
  if ( is_key_pressed_edge(0x28u) )
    v0 = 39;
  if ( is_key_pressed_edge(0x2Bu) )
    v0 = 92;
  if ( is_key_pressed_edge(0xEu) )
    v0 = 1;
  if ( is_key_pressed_edge(0xD3u) )
    v0 = 2;
  if ( is_key_pressed_edge(0xCBu) )
    v0 = 3;
  if ( is_key_pressed_edge(0xCDu) )
    v0 = 4;
  if ( is_key_pressed_edge(0xC8u) )
    v0 = 7;
  if ( is_key_pressed_edge(0xD0u) )
    v0 = 8;
  if ( is_key_pressed_edge(0xCFu) )
    v0 = 9;
  if ( is_key_pressed_edge(0xC7u) )
    v0 = 10;
  if ( is_key_pressed_edge(1u) )
    v0 = 11;
  if ( is_key_pressed_edge(0x3Bu) )
    v0 = 12;
  if ( is_key_pressed_edge(0x1Cu) )
    return is_key_down(0x1Du) + 5;
  else
    return v0;
}

