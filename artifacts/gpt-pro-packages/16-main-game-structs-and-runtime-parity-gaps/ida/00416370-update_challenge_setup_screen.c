/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_challenge_setup_screen @ 0x416370 */
/* selector: update_challenge_setup_screen */

// Runs the mode-1 front-end setup screen, including difficulty and speed changes, replay launch, Play, and Back handoff into `update_subgame` state 1.
int __thiscall sub_416370(_DWORD **this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  char *v6; // eax
  int v7; // ecx
  int v8; // eax
  char *v9; // eax
  int v10; // eax
  int v11; // edi
  unsigned int v12; // edi
  int v13; // eax
  _DWORD *v14; // ecx
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v22; // ecx
  int v23; // eax
  int v24; // ecx
  int v25; // eax
  int v26; // ecx
  int v27; // eax
  int v28; // eax
  int v29; // edi
  unsigned int v30; // edi
  int v31; // eax

  hide_gameplay_scores(*this);
  v2 = (*this)[16];
  if ( v2 )
  {
    v3 = v2 - 1;
    if ( v3 )
    {
      if ( v3 == 3 )
      {
        v4 = (int)*(this + 1);
        v5 = *(_DWORD *)(v4 + 416);
        if ( (v5 & 0x20) != 0 )
        {
          LOBYTE(v5) = v5 & 0xDF;
          *(_DWORD *)(v4 + 416) = v5;
          load_frontend_level_by_mode_and_index((char *)*this + 43124, (*this)[16], ++(*this)[17]);
          sub_44E5B0((char *)*(this + 3) + 716, (char *)*this + 1769808);
          layout_frontend_widget((int)*(this + 3));
          v6 = format_time_trial_string((int)&(*this)[32432 * (*this)[17] + 2429014]);
          sub_44E5B0((char *)((*this)[880355] + 716), v6);
        }
        v7 = (int)*(this + 2);
        v8 = *(_DWORD *)(v7 + 416);
        if ( (v8 & 0x20) != 0 )
        {
          LOBYTE(v8) = v8 & 0xDF;
          *(_DWORD *)(v7 + 416) = v8;
          load_frontend_level_by_mode_and_index((char *)*this + 43124, (*this)[16], --(*this)[17]);
          sub_44E5B0((char *)*(this + 3) + 716, (char *)*this + 1769808);
          layout_frontend_widget((int)*(this + 3));
          v9 = format_time_trial_string((int)&(*this)[32432 * (*this)[17] + 2429014]);
          sub_44E5B0((char *)((*this)[880355] + 716), v9);
        }
        v10 = (int)*(this + 2);
        v11 = *(_DWORD *)(v10 + 416);
        if ( (*this)[17] )
          v12 = v11 & 0xFFFF7FFF;
        else
          v12 = v11 | 0x8000;
        *(_DWORD *)(v10 + 416) = v12;
        v13 = (int)*(this + 1);
        if ( (*this)[17] == dword_4DF9B8 )
          *(_DWORD *)(v13 + 416) |= 0x8000u;
        else
          *(_DWORD *)(v13 + 416) &= ~0x8000u;
        v14 = *(this + 9);
        if ( (*this)[32432 * (*this)[17] + 2429012] == 1 )
        {
          unhide_border_init(v14);
          stack_widget_below((int)*(this + 6), (int)*(this + 9));
        }
        else
        {
          hide_border_init(v14);
          stack_widget_below((int)*(this + 6), (int)*(this + 4));
        }
        v15 = (int)*(this + 6);
        v16 = *(_DWORD *)(v15 + 416);
        if ( (v16 & 0x20) != 0 )
          goto LABEL_38;
        v17 = (int)*(this + 4);
        v18 = *(_DWORD *)(v17 + 416);
        if ( (v18 & 0x20) != 0 )
          goto LABEL_40;
        v19 = (int)*(this + 9);
        v20 = *(_DWORD *)(v19 + 416);
        if ( (v20 & 0x20) != 0 )
        {
          LOBYTE(v20) = v20 & 0xDF;
          *(_DWORD *)(v19 + 416) = v20;
          destroy_challenge_setup_screen(this);
          *((_BYTE *)*this + 16721360) = 1;
          (*this)[4180341] = &(*this)[32432 * (*this)[17] + 2429012];
          return 1;
        }
      }
    }
    else
    {
      v15 = (int)*(this + 6);
      v16 = *(_DWORD *)(v15 + 416);
      if ( (v16 & 0x20) != 0 )
      {
LABEL_38:
        LOBYTE(v16) = v16 & 0xDF;
        *(_DWORD *)(v15 + 416) = v16;
        destroy_challenge_setup_screen(this);
        return 3;
      }
      v17 = (int)*(this + 4);
      v18 = *(_DWORD *)(v17 + 416);
      if ( (v18 & 0x20) != 0 )
        goto LABEL_40;
      unk_4DF958 = (__int64)(*((float *)*(this + 7) + 95) * 100.0 + 0.1);
      unk_4DF960 = (__int64)(*((float *)*(this + 8) + 95) * 100.0 + 0.1);
      v22 = (int)*(this + 9);
      v23 = *(_DWORD *)(v22 + 416);
      if ( (v23 & 0x20) != 0 )
      {
        LOBYTE(v23) = v23 & 0xDF;
        *(_DWORD *)(v22 + 416) = v23;
        destroy_challenge_setup_screen(this);
        *((_BYTE *)*this + 16721360) = 1;
        (*this)[4180341] = *this + 4115476;
        return 1;
      }
    }
  }
  else
  {
    v24 = (int)*(this + 1);
    v25 = *(_DWORD *)(v24 + 416);
    if ( (v25 & 0x20) != 0 )
    {
      LOBYTE(v25) = v25 & 0xDF;
      *(_DWORD *)(v24 + 416) = v25;
      load_frontend_level_by_mode_and_index((char *)*this + 43124, (*this)[16], ++(*this)[17]);
      sub_44E5B0((char *)*(this + 3) + 716, (char *)*this + 1769808);
      layout_frontend_widget((int)*(this + 3));
    }
    v26 = (int)*(this + 2);
    v27 = *(_DWORD *)(v26 + 416);
    if ( (v27 & 0x20) != 0 )
    {
      LOBYTE(v27) = v27 & 0xDF;
      *(_DWORD *)(v26 + 416) = v27;
      load_frontend_level_by_mode_and_index((char *)*this + 43124, (*this)[16], --(*this)[17]);
      sub_44E5B0((char *)*(this + 3) + 716, (char *)*this + 1769808);
      layout_frontend_widget((int)*(this + 3));
    }
    v28 = (int)*(this + 2);
    v29 = *(_DWORD *)(v28 + 416);
    if ( (*this)[17] )
      v30 = v29 & 0xFFFF7FFF;
    else
      v30 = v29 | 0x8000;
    *(_DWORD *)(v28 + 416) = v30;
    v31 = (int)*(this + 1);
    if ( (*this)[17] == dword_4DF9B8 )
      *(_DWORD *)(v31 + 416) |= 0x8000u;
    else
      *(_DWORD *)(v31 + 416) &= ~0x8000u;
    v15 = (int)*(this + 6);
    v16 = *(_DWORD *)(v15 + 416);
    if ( (v16 & 0x20) != 0 )
      goto LABEL_38;
    v17 = (int)*(this + 4);
    v18 = *(_DWORD *)(v17 + 416);
    if ( (v18 & 0x20) != 0 )
    {
LABEL_40:
      LOBYTE(v18) = v18 & 0xDF;
      *(_DWORD *)(v17 + 416) = v18;
      destroy_challenge_setup_screen(this);
      return 1;
    }
  }
  return 0;
}

