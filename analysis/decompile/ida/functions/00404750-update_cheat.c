/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_cheat @ 0x404750 */
/* selector: update_cheat */

char __thiscall sub_404750(char *this)
{
  int v2; // eax
  _BYTE *v3; // ecx
  int v4; // eax
  int v5; // eax

  LOBYTE(v2) = read_pressed_text_input_key_code();
  if ( (char)v2 >= 97 && (char)v2 <= 122 )
    LOBYTE(v2) = v2 - 32;
  if ( (char)v2 >= 65 && (char)v2 <= 90 )
  {
    v3 = this + 15;
    do
    {
      *v3 = *(v3 - 1);
      --v3;
    }
    while ( (int)&v3[-8 - (_DWORD)this] > 0 );
    *(this + 8) = v2;
    if ( match_cheat_text(this, aNewton) )
    {
      v4 = *(_DWORD *)this;
      LOBYTE(v4) = *(_DWORD *)this | 1;
      *(_DWORD *)this = v4;
    }
    if ( match_cheat_text(this, aAutumn) )
    {
      v5 = *(_DWORD *)this;
      LOBYTE(v5) = *(_DWORD *)this | 2;
      *(_DWORD *)this = v5;
    }
    LOBYTE(v2) = match_cheat_text(this, aSheep);
    if ( (_BYTE)v2 )
    {
      v2 = *(_DWORD *)this;
      LOBYTE(v2) = *(_DWORD *)this | 4;
      *(_DWORD *)this = v2;
    }
  }
  return v2;
}

