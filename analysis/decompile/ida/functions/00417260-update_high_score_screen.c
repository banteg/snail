/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_high_score_screen @ 0x417260 */
/* selector: update_high_score_screen */

// Runs the high-score screen state machine, including replay launch, bank toggling, inline name submission, and back or exit actions. Cross-port Android and iOS symbols match this helper to `cRHighScore::AI()`.
int __thiscall sub_417260(int this)
{
  int v2; // ecx
  int v3; // eax
  int result; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  void *v15; // edx
  int v16; // ebp
  int v17; // edi
  int v18; // ecx
  int v19; // eax
  int *v20; // [esp+Ch] [ebp-4h]

  if ( *(_BYTE *)(this + 16) )
  {
    v2 = *(_DWORD *)(this + 4 * *(_DWORD *)(this + 20) + 124);
    v3 = *(_DWORD *)(v2 + 416);
    if ( (v3 & 0x4000) != 0 )
    {
      BYTE1(v3) &= ~0x40u;
      *(_DWORD *)(v2 + 416) = v3;
      destroy_high_score_screen((_DWORD *)this);
      kill_game_sprites();
      sub_44E5B0(
        (char *)(*(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]) + 129728 * *(_DWORD *)(this + 20) + 84),
        (char *)(*(_DWORD *)(this + 4 * *(_DWORD *)(this + 20) + 124) + 716));
      sub_44E5B0((char *)MEMORY[0x4DF904] + 420, (char *)(*(_DWORD *)(this + 4 * *(_DWORD *)(this + 20) + 124) + 716));
      sub_44E5B0(&unk_4DF978, (char *)(*(_DWORD *)(this + 4 * *(_DWORD *)(this + 20) + 124) + 716));
      return (int)exit_high_score_screen();
    }
    else
    {
      v5 = *(_DWORD *)(this + 40);
      v6 = *(_DWORD *)(v5 + 416);
      if ( (v6 & 0x20) != 0 )
      {
        LOBYTE(v6) = v6 & 0xDF;
        *(_DWORD *)(v5 + 416) = v6;
        v7 = *(_DWORD *)(this + 4 * *(_DWORD *)(this + 20) + 124);
        *(_DWORD *)(v7 + 416) |= 0x8000000u;
      }
      v8 = *(_DWORD *)(this + 36);
      result = *(_DWORD *)(v8 + 416);
      if ( (result & 0x20) != 0 )
      {
        LOBYTE(result) = result & 0xDF;
        *(_DWORD *)(v8 + 416) = result;
        destroy_high_score_screen((_DWORD *)this);
        kill_game_sprites();
        commit_high_score_entry_into_top_ten(
          (int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]),
          *(_DWORD *)(this + 20));
        return (int)exit_high_score_screen();
      }
    }
  }
  else
  {
    v9 = *(_DWORD *)(this + 32);
    v10 = *(_DWORD *)(v9 + 416);
    if ( (v10 & 0x20) != 0 )
    {
      LOBYTE(v10) = v10 & 0xDF;
      *(_DWORD *)(v9 + 416) = v10;
      destroy_high_score_screen((_DWORD *)this);
      v11 = *(_DWORD *)(this + 8);
      if ( v11 )
      {
        if ( v11 == 1 )
          *(_DWORD *)(this + 8) = 0;
      }
      else
      {
        *(_DWORD *)(this + 8) = 1;
      }
      unk_4DF9C0 = *(_DWORD *)(this + 8);
      return (int)initialize_high_score_screen(this, *(_DWORD *)(this + 8), -1);
    }
    else
    {
      v12 = *(_DWORD *)(this + 28);
      v13 = *(_DWORD *)(v12 + 416);
      if ( (v13 & 0x20) != 0 )
      {
        LOBYTE(v13) = v13 & 0xDF;
        *(_DWORD *)(v12 + 416) = v13;
        v14 = *(_DWORD *)(this + 4);
        if ( v14 == 1 )
        {
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
          *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
          return destroy_high_score_screen((_DWORD *)this);
        }
        else
        {
          if ( !v14 )
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 4;
          return destroy_high_score_screen((_DWORD *)this);
        }
      }
      else
      {
        v15 = MEMORY[0x4DF904];
        v16 = 0;
        result = *(int *)((char *)&unk_6FFAE4 + (_DWORD)MEMORY[0x4DF904]);
        if ( result > 0 )
        {
          v17 = 0;
          v20 = (int *)(this + 204);
          do
          {
            if ( *(_DWORD *)(*(int *)((char *)&byte_6FFAE0 + (_DWORD)v15) + v17) == 1 )
            {
              v18 = *v20;
              if ( *v20 )
              {
                v19 = *(_DWORD *)(v18 + 416);
                if ( (v19 & 0x20) != 0 )
                {
                  LOBYTE(v19) = v19 & 0xDF;
                  *(_DWORD *)(v18 + 416) = v19;
                  *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
                  *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
                  destroy_high_score_screen((_DWORD *)this);
                  *((_DWORD *)MEMORY[0x4DF904] + 4299515) = v17
                                                          + *(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]);
                  *((_BYTE *)MEMORY[0x4DF904] + 17198056) = 1;
                  *((_BYTE *)MEMORY[0x4DF904] + 17198057) = 1;
                  *((_DWORD *)MEMORY[0x4DF904] + 4299516) = 18;
                  *((_DWORD *)MEMORY[0x4DF904] + 119190) = *(_DWORD *)(*((_DWORD *)MEMORY[0x4DF904] + 4299515) + 44);
                  v15 = MEMORY[0x4DF904];
                }
              }
            }
            ++v16;
            v17 += 129728;
            ++v20;
            result = *(int *)((char *)&unk_6FFAE4 + (_DWORD)v15);
          }
          while ( v16 < result );
        }
      }
    }
  }
  return result;
}

