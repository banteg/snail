/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_intro_screen @ 0x4199e0 */
/* selector: update_intro_screen */

// Exact Windows cRLogo::AI(): advances the normalized intro or credits crawl, tears down its LogoLetters once scrolling completes, and exits early on skip input.
void __thiscall sub_4199E0(int this)
{
  int v2; // eax
  double v3; // st7
  double v4; // st7

  if ( !*((_DWORD *)MEMORY[0x4DF904] + 9)
    && ((*(_DWORD *)(*((_DWORD *)MEMORY[0x4DF904] + 163) + 60) & 0x4000) != 0 || read_pressed_text_input_key_code() == 11) )
  {
    begin_frontend_fade_out((_DWORD *)MEMORY[0x4DF904] + 9, 0);
  }
  if ( *((_DWORD *)MEMORY[0x4DF904] + 9) == 4 )
    destroy_intro_screen((int *)this);
  v2 = *(_DWORD *)(this + 8);
  if ( v2 )
  {
    if ( v2 == 1 )
    {
      v3 = *(float *)(this + 4) + *(float *)this;
      *(float *)this = v3;
      if ( v3 > 1.0 )
      {
        begin_frontend_fade_out((_DWORD *)MEMORY[0x4DF904] + 9, 0);
        ++*(_DWORD *)(this + 8);
      }
    }
  }
  else
  {
    v4 = *(float *)(this + 16) * 60.0;
    *(_DWORD *)this = 0;
    *(_DWORD *)(this + 8) = 1;
    *(float *)(this + 4) = 1.0 / v4;
  }
}
