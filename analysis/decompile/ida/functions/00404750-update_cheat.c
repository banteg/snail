/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_cheat @ 0x404750 */
/* selector: update_cheat */

void __thiscall update_cheat(CheatState *cheat)
{
  char pressed_text_input_key_code; // al
  char *recent_text_cursor; // ecx
  uint32_t flags; // eax
  uint32_t v5; // eax
  uint32_t v6; // eax

  pressed_text_input_key_code = read_pressed_text_input_key_code();
  if ( pressed_text_input_key_code >= 97 && pressed_text_input_key_code <= 122 )
    pressed_text_input_key_code -= 32;
  if ( pressed_text_input_key_code >= 65 && pressed_text_input_key_code <= 90 )
  {
    recent_text_cursor = &cheat->recent_text.bytes[7];
    do
    {
      *recent_text_cursor = *(recent_text_cursor - 1);
      --recent_text_cursor;
    }
    while ( (int)&recent_text_cursor[-8 - (_DWORD)cheat] > 0 );
    cheat->recent_text.bytes[0] = pressed_text_input_key_code;
    if ( match_cheat_text(cheat, aNewton) )
    {
      flags = cheat->flags;
      LOBYTE(flags) = cheat->flags | 1;
      cheat->flags = flags;
    }
    if ( match_cheat_text(cheat, aAutumn) )
    {
      v5 = cheat->flags;
      LOBYTE(v5) = cheat->flags | 2;
      cheat->flags = v5;
    }
    if ( match_cheat_text(cheat, aSheep) )
    {
      v6 = cheat->flags;
      LOBYTE(v6) = cheat->flags | 4;
      cheat->flags = v6;
    }
  }
}
