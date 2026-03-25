/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_main_menu @ 0x419e00 */
/* selector: update_main_menu */

// Handles main-menu selection, front-end screen transitions, and the tutorial launch handoff. Cross-port Android and iOS symbols match this helper to `cRMainMenu::AI()`.
void *__thiscall sub_419E00(_DWORD *this)
{
  int v1; // eax
  void *result; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx

  v1 = *(_DWORD *)(*this + 416);
  if ( (v1 & 0x20) != 0 )
  {
    LOBYTE(v1) = v1 & 0xDF;
    *(_DWORD *)(*this + 416) = v1;
    destroy_main_menu();
    result = MEMORY[0x4DF904];
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 2;
    *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
  }
  else
  {
    v3 = *(this + 3);
    v4 = *(_DWORD *)(v3 + 416);
    if ( (v4 & 0x20) != 0 )
    {
      LOBYTE(v4) = v4 & 0xDF;
      *(_DWORD *)(v3 + 416) = v4;
      destroy_main_menu();
      *((_DWORD *)MEMORY[0x4DF904] + 110) = 14;
      result = MEMORY[0x4DF904];
      *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
    }
    else
    {
      v5 = *(this + 5);
      v6 = *(_DWORD *)(v5 + 416);
      if ( (v6 & 0x20) != 0 )
      {
        LOBYTE(v6) = v6 & 0xDF;
        *(_DWORD *)(v5 + 416) = v6;
        *((_DWORD *)MEMORY[0x4DF904] + 81133) = *((_DWORD *)MEMORY[0x4DF904] + 110);
        *((_DWORD *)MEMORY[0x4DF904] + 81134) = *(_DWORD *)(*(this + 5) + 572);
        result = MEMORY[0x4DF904];
        *((_DWORD *)MEMORY[0x4DF904] + 81131) = 10;
        *((_DWORD *)MEMORY[0x4DF904] + 110) = 8;
      }
      else
      {
        v7 = *(this + 2);
        v8 = *(_DWORD *)(v7 + 416);
        if ( (v8 & 0x20) != 0 )
        {
          LOBYTE(v8) = v8 & 0xDF;
          *(_DWORD *)(v7 + 416) = v8;
          *((_BYTE *)MEMORY[0x4DF904] + 324492) = 1;
          result = MEMORY[0x4DF904];
          *((_DWORD *)MEMORY[0x4DF904] + 81122) = *((_DWORD *)MEMORY[0x4DF904] + 110);
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 6;
        }
        else
        {
          v9 = *(this + 1);
          result = *(void **)(v9 + 416);
          if ( ((unsigned __int8)result & 0x20) != 0 )
          {
            LOBYTE(result) = (unsigned __int8)result & 0xDF;
            *(_DWORD *)(v9 + 416) = result;
            destroy_main_menu();
            result = MEMORY[0x4DF904];
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 18;
            *((_DWORD *)MEMORY[0x4DF904] + 4955029) = 0;
          }
        }
      }
    }
  }
  return result;
}

