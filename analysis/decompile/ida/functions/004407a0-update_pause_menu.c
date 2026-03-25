/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_pause_menu @ 0x4407a0 */
/* selector: update_pause_menu */

void *__thiscall sub_4407A0(_DWORD *this)
{
  int v1; // eax
  void *result; // eax
  int v3; // edx
  int v4; // eax
  int v5; // ecx

  v1 = *(_DWORD *)(*this + 416);
  if ( (v1 & 0x20) != 0 )
  {
    LOBYTE(v1) = v1 & 0xDF;
    *(_DWORD *)(*this + 416) = v1;
    *((_BYTE *)MEMORY[0x4DF904] + 324492) = 0;
    result = MEMORY[0x4DF904];
    *((_DWORD *)MEMORY[0x4DF904] + 81122) = *((_DWORD *)MEMORY[0x4DF904] + 110);
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 6;
  }
  else
  {
    v3 = *(this + 2);
    v4 = *(_DWORD *)(v3 + 416);
    if ( (v4 & 0x20) != 0 )
    {
      LOBYTE(v4) = v4 & 0xDF;
      *(_DWORD *)(v3 + 416) = v4;
      uninit_pause_menu((_DWORD **)this);
      result = MEMORY[0x4DF904];
      *((_DWORD *)MEMORY[0x4DF904] + 119189) = 2;
      *((_BYTE *)MEMORY[0x4DF904] + 476704) = 1;
    }
    else
    {
      v5 = *(this + 1);
      result = *(void **)(v5 + 416);
      if ( ((unsigned __int8)result & 0x20) != 0 )
      {
        LOBYTE(result) = (unsigned __int8)result & 0xDF;
        *(_DWORD *)(v5 + 416) = result;
        *((_DWORD *)MEMORY[0x4DF904] + 81133) = *((_DWORD *)MEMORY[0x4DF904] + 110);
        if ( *((_DWORD *)MEMORY[0x4DF904] + 119190) == 7 )
        {
          *((_DWORD *)MEMORY[0x4DF904] + 81131) = 7;
        }
        else if ( *((_BYTE *)MEMORY[0x4DF904] + 17198057) == 1 )
        {
          *((_DWORD *)MEMORY[0x4DF904] + 81131) = 3;
        }
        else
        {
          *((_DWORD *)MEMORY[0x4DF904] + 81131) = 2;
        }
        result = MEMORY[0x4DF904];
        *((_DWORD *)MEMORY[0x4DF904] + 4953464) = 2;
        *((_DWORD *)MEMORY[0x4DF904] + 110) = 8;
      }
    }
  }
  return result;
}

