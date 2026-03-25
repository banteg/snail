/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_warning @ 0x446f80 */
/* selector: update_warning */

void __thiscall sub_446F80(float *this)
{
  double v1; // st7
  double v2; // st7

  if ( !*((_BYTE *)MEMORY[0x4DF904] + 476705) && *(_DWORD *)this )
  {
    if ( *(_DWORD *)this == 1 )
    {
      *(_DWORD *)(*((_DWORD *)this + 3) + 520) = 1065336439;
      v2 = *(this + 2) + *(this + 1);
      *(this + 1) = v2;
      if ( v2 > 1.0 )
      {
        *(this + 1) = 0.0;
        *(_DWORD *)this = 2;
      }
    }
    else if ( *(_DWORD *)this == 2 )
    {
      if ( *(this + 1) >= 0.5 )
        *(_DWORD *)(*((_DWORD *)this + 3) + 520) = 0;
      else
        *(float *)(*((_DWORD *)this + 3) + 520) = 1.0 - (*(this + 1) + *(this + 1));
      v1 = *(this + 2) + *(this + 1);
      *(this + 1) = v1;
      if ( v1 > 1.0 )
      {
        *(this + 1) = 0.0;
        *(_DWORD *)this = 1;
        play_sound_effect(50);
      }
    }
  }
}

