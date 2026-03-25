/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_new_game_menu @ 0x417eb0 */
/* selector: update_new_game_menu */

// Runs the New Game menu controller, dispatching Tutorial, Postal Mode, Time Trial, Challenge Mode, Help, and Back through the shared front-end state machine. It also advances the menu-owned random replay-attract lane: rotates cursor `0..4`, probes replay banks `0/1/3` only, gives up after `1000` attempts, seeds app replay scratch `+0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0` plus return state `2`, sets the menu hide latch, and resets the secondary timer lane to `1/3600` after either launch or miss.
void __thiscall sub_417EB0(_BYTE *this)
{
  char v2; // al
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  double v15; // st7
  int v16; // edi
  _DWORD *v17; // eax
  _DWORD *v18; // eax
  _DWORD *v19; // eax
  int v20; // eax

  if ( read_pressed_text_input_key_code() || (*(_DWORD *)(*((_DWORD *)MEMORY[0x4DF904] + 163) + 60) & 0x4000) != 0 )
  {
    v2 = *(this + 4);
    *((_DWORD *)this + 4) = 0;
    if ( v2 == 1 )
    {
      unhide_border_init(*((_DWORD **)this + 12));
      unhide_border_init(*((_DWORD **)this + 15));
      unhide_border_init(*((_DWORD **)this + 13));
      unhide_border_init(*((_DWORD **)this + 14));
      unhide_border_init(*((_DWORD **)this + 16));
      unhide_border_init(*((_DWORD **)this + 17));
      capture_mouse_cursor((float *)MEMORY[0x4DF904] + 164);
      *(this + 4) = 0;
    }
  }
  v3 = *((_DWORD *)this + 12);
  v4 = *(_DWORD *)(v3 + 416);
  if ( (v4 & 0x20) != 0 )
  {
    LOBYTE(v4) = v4 & 0xDF;
    *(_DWORD *)(v3 + 416) = v4;
    destroy_main_menu();
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
    *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
    *((_DWORD *)MEMORY[0x4DF904] + 119190) = 0;
    *((_DWORD *)MEMORY[0x4DF904] + 4953464) = 2;
  }
  else
  {
    v5 = *((_DWORD *)this + 13);
    v6 = *(_DWORD *)(v5 + 416);
    if ( (v6 & 0x20) != 0 )
    {
      LOBYTE(v6) = v6 & 0xDF;
      *(_DWORD *)(v5 + 416) = v6;
      destroy_main_menu();
      *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
      *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
      *((_DWORD *)MEMORY[0x4DF904] + 119190) = 4;
    }
    else
    {
      v7 = *((_DWORD *)this + 15);
      v8 = *(_DWORD *)(v7 + 416);
      if ( (v8 & 0x20) != 0 )
      {
        LOBYTE(v8) = v8 & 0xDF;
        *(_DWORD *)(v7 + 416) = v8;
        destroy_main_menu();
        *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
        *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
        *((_DWORD *)MEMORY[0x4DF904] + 119190) = 7;
        initialize_tutorial((_DWORD *)MEMORY[0x4DF904] + 129948);
        unk_4DF9D8 = 1;
      }
      else
      {
        v9 = *((_DWORD *)this + 14);
        v10 = *(_DWORD *)(v9 + 416);
        if ( (v10 & 0x20) != 0 )
        {
          LOBYTE(v10) = v10 & 0xDF;
          *(_DWORD *)(v9 + 416) = v10;
          destroy_main_menu();
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
          *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
          *((_DWORD *)MEMORY[0x4DF904] + 119190) = 1;
        }
        else
        {
          v11 = *((_DWORD *)this + 17);
          v12 = *(_DWORD *)(v11 + 416);
          if ( (v12 & 0x20) != 0 )
          {
            LOBYTE(v12) = v12 & 0xDF;
            *(_DWORD *)(v11 + 416) = v12;
            destroy_main_menu();
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 4;
            *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
          }
          else
          {
            v13 = *((_DWORD *)this + 16);
            v14 = *(_DWORD *)(v13 + 416);
            if ( (v14 & 0x20) != 0 )
            {
              LOBYTE(v14) = v14 & 0xDF;
              *(_DWORD *)(v13 + 416) = v14;
              destroy_main_menu();
              *((_DWORD *)MEMORY[0x4DF904] + 110) = 31;
              *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
            }
          }
          v15 = *((float *)this + 5) + *((float *)this + 4);
          *((float *)this + 4) = v15;
          if ( v15 > 1.0 )
          {
            *((_DWORD *)this + 4) = 0;
            v16 = 0;
            *((_DWORD *)MEMORY[0x4DF904] + 4299515) = 0;
            while ( 1 )
            {
              ++v16;
              if ( *(_DWORD *)this )
              {
                if ( *(_DWORD *)this == 1 )
                {
                  v18 = (char *)MEMORY[0x4DF904]
                      + 129728 * (__int64)((double)next_math_random_value() * 0.00012207031)
                      + 8765736;
                  if ( *v18 == 1 )
                  {
                    *((_DWORD *)MEMORY[0x4DF904] + 4299515) = v18;
                    *((_DWORD *)MEMORY[0x4DF904] + 119190) = 1;
                  }
                }
                else if ( *(_DWORD *)this == 3 )
                {
                  v17 = (char *)MEMORY[0x4DF904]
                      + 129728 * (__int64)((double)next_math_random_value() * 0.0015563965)
                      + 10192744;
                  if ( *v17 == 1 )
                  {
                    *((_DWORD *)MEMORY[0x4DF904] + 4299515) = v17;
                    *((_DWORD *)MEMORY[0x4DF904] + 119190) = 4;
                  }
                }
              }
              else
              {
                v19 = (int *)((char *)&unk_6FFAE8
                            + (_DWORD)MEMORY[0x4DF904]
                            + 129728 * (__int64)((double)next_math_random_value() * 0.00012207031));
                if ( *v19 == 1 )
                {
                  *((_DWORD *)MEMORY[0x4DF904] + 4299515) = v19;
                  *((_DWORD *)MEMORY[0x4DF904] + 119190) = 0;
                }
              }
              v20 = *(_DWORD *)this + 1;
              *(_DWORD *)this = v20;
              if ( v20 == 5 )
                *(_DWORD *)this = 0;
              if ( *((_DWORD *)MEMORY[0x4DF904] + 4299515) )
                break;
              if ( v16 >= 1000 )
                goto LABEL_32;
            }
            if ( v16 >= 1000 )
            {
LABEL_32:
              *((_DWORD *)this + 2) = 0;
              *((_DWORD *)this + 3) = 965845684;
              return;
            }
            *(this + 4) = 1;
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
            *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
            *((_BYTE *)MEMORY[0x4DF904] + 17198056) = 1;
            *((_DWORD *)MEMORY[0x4DF904] + 4299516) = 2;
            *((_BYTE *)MEMORY[0x4DF904] + 17198057) = 1;
            *((_DWORD *)this + 2) = 0;
            *((_DWORD *)this + 3) = 965845684;
            destroy_main_menu();
          }
        }
      }
    }
  }
}

