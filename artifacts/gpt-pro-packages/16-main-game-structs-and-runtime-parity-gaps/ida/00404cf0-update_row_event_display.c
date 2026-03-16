/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_row_event_display @ 0x404cf0 */
/* selector: update_row_event_display */

// Runs the gameplay row-event display state machine, including staged score payout, widget show or hide transitions, and the final handoff into `flush_row_event_display`.
void __thiscall sub_404CF0(_DWORD **this)
{
  _DWORD *v2; // ecx
  double v3; // st7
  int v4; // eax
  char *v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  double v9; // st7
  int v10; // eax
  float *v11; // eax
  double v12; // st7
  _DWORD *v13; // ecx
  int v14; // ecx
  float v15; // [esp+8h] [ebp-3Ch]
  float v16; // [esp+Ch] [ebp-38h]
  float v17; // [esp+Ch] [ebp-38h]
  float v18; // [esp+10h] [ebp-34h]
  float v19; // [esp+10h] [ebp-34h]
  float v20; // [esp+18h] [ebp-2Ch]
  float v21; // [esp+1Ch] [ebp-28h]
  float v22; // [esp+24h] [ebp-20h]
  float v23; // [esp+28h] [ebp-1Ch]
  float v24; // [esp+30h] [ebp-14h]
  float v25; // [esp+34h] [ebp-10h]
  float v26; // [esp+3Ch] [ebp-8h]
  float v27; // [esp+40h] [ebp-4h]

  if ( *(this + 5) )
  {
    v2 = *(this + 1);
    if ( *((_BYTE *)MEMORY[0x4DF904] + 476705) )
    {
      hide_border_init(v2);
      hide_border_init(*this);
      hide_border_init(*(this + 3));
      hide_border_init(*(this + 2));
      hide_border_init(*(this + 4));
    }
    else
    {
      unhide_border_init(v2);
      unhide_border_init(*this);
      unhide_border_init(*(this + 3));
      unhide_border_init(*(this + 4));
      switch ( (unsigned int)*(this + 5) )
      {
        case 0u:
          return;
        case 1u:
          v3 = *((float *)this + 12) + *((float *)this + 11);
          *((float *)this + 11) = v3;
          if ( v3 > 1.0 )
          {
            v4 = (int)*(this + 9);
            if ( v4 < (int)*(this + 7) )
            {
              *(this + 9) = (_DWORD *)(v4 + 1);
              v5 = spawn_track_parcel(
                     (int *)MEMORY[0x4DF904] + 119174,
                     (float *)MEMORY[0x4DF904] + 1101773,
                     (int)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]);
              v6 = *((_DWORD *)v5 + 21);
              *((_DWORD *)v5 + 14) = 6;
              *(_DWORD *)(v6 + 100) = 0;
              *(_DWORD *)(*((_DWORD *)v5 + 21) + 96) = 0;
            }
            v7 = (int)*(this + 7);
            v8 = (int)*(this + 9);
            *(this + 11) = nullptr;
            if ( v8 == v7 )
            {
              if ( v7 )
              {
                *(this + 5) = (_DWORD *)2;
              }
              else
              {
                *(this + 5) = (_DWORD *)6;
                *(this + 11) = nullptr;
                *(this + 12) = (_DWORD *)1007192201;
              }
            }
          }
          goto LABEL_27;
        case 3u:
          unhide_border_init(*(this + 4));
          v10 = (int)*(this + 8);
          *((_BYTE *)this + 24) = 0;
          *(this + 5) = (_DWORD *)4;
          if ( !v10 )
            goto LABEL_18;
          unhide_border_init(*(this + 2));
          if ( *(this + 7) )
            goto LABEL_18;
          v11 = (float *)MEMORY[0x4DF904];
          if ( *((_DWORD *)MEMORY[0x4DF904] + 119190) == 1 )
          {
            add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), 5, (int)*(this + 18));
            play_sound_effect(49);
LABEL_18:
            v11 = (float *)MEMORY[0x4DF904];
          }
          if ( *(this + 8) )
          {
            v12 = *((float *)this + 17) + *((float *)this + 16);
            *((float *)this + 16) = v12;
            if ( v12 > 1.0 )
            {
              v13 = *(this + 2);
              *(this + 16) = nullptr;
              if ( (v13[104] & 0x1000) != 0 )
                unhide_border_init(v13);
              else
                hide_border_init(v13);
            }
            v11 = (float *)MEMORY[0x4DF904];
          }
          if ( (*(_DWORD *)(*((_DWORD *)v11 + 163) + 60) & 0x4000) != 0 )
          {
            *(this + 5) = (_DWORD *)5;
            play_sound_effect(8);
LABEL_27:
            v11 = (float *)MEMORY[0x4DF904];
          }
          v26 = v11[96] * 6.0;
          v27 = v11[97] * 6.0;
          v22 = v11[92] + v11[92];
          v23 = v11[93] + v11[93];
          v16 = v11[88] * 7.3000002;
          v18 = v11[89] * 7.3000002;
          v20 = v16 + v11[100];
          v21 = v18 + v11[101];
          v24 = v20 + v22;
          v25 = v21 + v23;
          v15 = v11[91] + v11[91] + v11[87] * 7.3000002 + v11[99] + v11[95] * 6.0;
          *((float *)this + 13) = v15;
          v17 = v24 + v26;
          *((float *)this + 14) = v17;
          v19 = v25 + v27;
          *((float *)this + 15) = v19;
          v14 = (int)*(this + 10);
          if ( v14 >= 10 )
            *((_BYTE *)*(this + 1) + 716) = v14 / 10 + 48;
          else
            *((_BYTE *)*(this + 1) + 716) = 32;
          *((_BYTE *)*(this + 1) + 717) = (int)*(this + 10) % 10 + 48;
          break;
        case 4u:
          goto LABEL_18;
        case 6u:
          v9 = *((float *)this + 12) + *((float *)this + 11);
          *((float *)this + 11) = v9;
          if ( v9 > 1.0 )
            *(this + 5) = (_DWORD *)3;
          goto LABEL_27;
        default:
          goto LABEL_27;
      }
    }
  }
}

