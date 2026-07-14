/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_slug_hazard_ai @ 0x43f930 */
/* selector: update_slug_hazard_ai */

// Runs one live `Slug` through active, lateral, death-toss, and teardown states. The exact Windows constructor table at 0x497324 points directly here, while Android and iOS retain `cRSlug::AI()`.
void __thiscall update_slug_hazard_ai(int this)
{
  int v2; // ecx
  double v3; // st7
  int v4; // edx
  __int64 v5; // rax
  int v6; // ecx
  _DWORD *v7; // eax
  int v8; // ecx
  int v9; // eax
  char *v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  double v14; // st7
  unsigned __int8 v16; // c0
  unsigned __int8 v17; // c3
  double v18; // st7
  int v19; // ecx
  _DWORD *v20; // edx
  int v21; // ecx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  double v25; // st7
  float *v26; // ecx
  int v27; // eax
  double v29; // st7
  char v30; // c0
  double v32; // st7
  char v33; // c0
  int v34; // eax
  double v35; // st7
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // ecx
  float v41; // [esp+Ch] [ebp-14h]
  int v42; // [esp+Ch] [ebp-14h]
  float v43; // [esp+10h] [ebp-10h]
  float v44; // [esp+14h] [ebp-Ch]

  if ( !*(_BYTE *)(*(_DWORD *)(this + 136) + 9) )
  {
    switch ( *(_DWORD *)(this + 128) )
    {
      case 0:
        return;
      case 1:
        if ( *(_BYTE *)(this + 204) && g_render_queue_active )
        {
          v2 = *(_DWORD *)(this + 212);
          *(_BYTE *)(this + 204) = 0;
          *(_DWORD *)(this + 208) = v2;
        }
        if ( *(float *)(this + 208) == 0.0 )
        {
          *(float *)(this + 228) = *(float *)(this + 232) + *(float *)(this + 228);
          if ( *(float *)(this + 232) <= 0.0 )
            set_sprite_texture_ref(*(_DWORD **)(this + 172), 119, 0);
          else
            set_sprite_texture_ref(*(_DWORD **)(this + 172), 118, 0);
          *(_DWORD *)(*(_DWORD *)(this + 172) + 40) = 0;
          store_color4f((tColour *)(*(_DWORD *)(this + 172) + 44), 1.0, 1.0, 1.0, 1.0);
          if ( *(float *)(this + 228) >= 0.0 )
          {
            if ( *(float *)(this + 228) > 1.0 )
            {
              *(_DWORD *)(this + 228) = 1065353216;
              *(_DWORD *)(this + 232) = -1104500053;
            }
          }
          else
          {
            *(_DWORD *)(this + 228) = 0;
            *(float *)(this + 232) = advance_blink_random((float *)g_game_base + 119174);
          }
        }
        else
        {
          v3 = *(float *)(this + 212) + *(float *)(this + 208);
          *(float *)(this + 208) = v3;
          if ( v3 <= 1.0 )
          {
            *(_DWORD *)(*(_DWORD *)(this + 172) + 40) = 5;
            set_sprite_texture_ref(*(_DWORD **)(this + 172), 120, 0);
            store_color4f((tColour *)(*(_DWORD *)(this + 172) + 44), 1.0, 0.0, 0.0, 0.99000001);
          }
          else
          {
            v4 = *(_DWORD *)(this + 172);
            *(_DWORD *)(this + 208) = 0;
            *(_DWORD *)(this + 228) = 1065353216;
            *(_DWORD *)(this + 232) = -1104500053;
            *(_DWORD *)(v4 + 40) = 0;
            store_color4f((tColour *)(*(_DWORD *)(this + 172) + 44), 1.0, 1.0, 1.0, 1.0);
            set_sprite_texture_ref(*(_DWORD **)(this + 172), 119, 0);
          }
        }
        if ( *(float *)(*(_DWORD *)(this + 192) + 112) + 1.0 > *(float *)(this + 112) && !*(_BYTE *)(this + 217) )
        {
          *(_BYTE *)(this + 217) = 1;
          if ( (double)next_math_random_value() * 0.000030517578 > 0.60000002 )
          {
            v5 = (__int64)((double)next_math_random_value() * -0.00012207031);
            play_slug_voice(this, 30 - v5);
          }
        }
        v6 = *(_DWORD *)(this + 192);
        if ( *(float *)(this + 112) < (double)*(float *)(v6 + 112) && !*(_BYTE *)(this + 180) )
          *(_BYTE *)(this + 180) = 1;
        if ( *(_DWORD *)(this + 196) == 1 && *(float *)(v6 + 112) + 16.0 > *(float *)(this + 112) )
        {
          *(_DWORD *)(this + 196) = 0;
          play_voice_manager((int)g_voice_manager, 2, 1u, -1);
        }
        v7 = (_DWORD *)(*(_DWORD *)(this + 172) + 72);
        *v7 = *(_DWORD *)(this + 104);
        v7[1] = *(_DWORD *)(this + 108);
        v7[2] = *(_DWORD *)(this + 112);
        v8 = *(_DWORD *)(this + 192);
        if ( *(float *)(this + 112) >= (double)*(float *)(v8 + 10624) )
        {
          if ( *(float *)(v8 + 884) > 0.0 )
            kill_slug_hazard(this);
          append_subgame_contact_target(
            (ContactTargetRegistry *)(*(_DWORD *)(this + 136) + 19337172),
            (const Vec3 *)(this + 104),
            2.0,
            1,
            (ContactTargetObject *)this);
          goto LABEL_39;
        }
        v9 = *(_DWORD *)(this + 4);
        *(_DWORD *)(this + 128) = 0;
        v10 = (char *)g_game_base + 1448;
        if ( (v9 & 0x200) == 0 )
          goto LABEL_70;
        if ( (v9 & 0x40) != 0 )
          goto LABEL_72;
        v11 = *(_DWORD *)(this + 12);
        if ( v11 )
          *(_DWORD *)(v11 + 8) = *(_DWORD *)(this + 8);
        v12 = *(_DWORD *)(this + 8);
        if ( v12 )
        {
          *(_DWORD *)(v12 + 12) = *(_DWORD *)(this + 12);
          goto LABEL_78;
        }
        goto LABEL_77;
      case 2:
        *(_DWORD *)(this + 128) = 3;
        v43 = random_float_below(0.30000001);
        v41 = random_float_below(0.2) + 0.1;
        v25 = random_signed_float_below(0.1);
        v26 = (float *)(this + 140);
        v44 = v25;
        *(float *)(this + 140) = v44;
        *(float *)(this + 144) = v41;
        *(float *)(this + 148) = v43;
        v27 = *(_DWORD *)(this + 132);
        if ( v27 == 1 )
        {
          v29 = *v26;
          if ( v30 )
            v29 = -v29;
        }
        else
        {
          if ( v27 != 2 )
            goto LABEL_65;
          v32 = *v26;
          if ( v33 )
            v32 = -v32;
          v29 = -v32;
        }
        *v26 = v29;
LABEL_65:
        if ( *v26 >= 0.0 )
          v42 = *v26 != 0.0;
        else
          v42 = -1;
        v34 = *(_DWORD *)(this + 136);
        *(_DWORD *)(this + 156) = 0;
        *v26 = (double)v42 * 0.2 + *v26;
        v35 = *(float *)(v34 + 56) * 0.0083333338;
        *(_DWORD *)(this + 164) = 0;
        *(float *)(this + 160) = v35;
        *(float *)(this + 168) = *(float *)(v34 + 56) * 0.16666667;
LABEL_69:
        v36 = *(_DWORD *)(this + 4);
        *(_DWORD *)(this + 128) = 0;
        v10 = (char *)g_game_base + 1448;
        if ( (v36 & 0x200) == 0 )
          goto LABEL_70;
        if ( (v36 & 0x40) != 0 )
          goto LABEL_72;
        v37 = *(_DWORD *)(this + 12);
        if ( v37 )
          *(_DWORD *)(v37 + 8) = *(_DWORD *)(this + 8);
        v38 = *(_DWORD *)(this + 8);
        if ( !v38 )
          goto LABEL_77;
        *(_DWORD *)(v38 + 12) = *(_DWORD *)(this + 12);
        goto LABEL_78;
      case 3:
        goto LABEL_69;
      case 4:
        v14 = *(float *)(this + 188) + *(float *)(this + 184);
        *(float *)(this + 184) = v14;
        if ( !(v16 | v17) )
          *(float *)(this + 184) = v14 - 6.2831855;
        v18 = sine(*(float *)(this + 184));
        v19 = *(_DWORD *)(this + 192);
        *(float *)(this + 104) = v18 * 3.0;
        if ( *(float *)(this + 112) < (double)*(float *)(v19 + 112) && !*(_BYTE *)(this + 180) )
          *(_BYTE *)(this + 180) = 1;
        v20 = (_DWORD *)(*(_DWORD *)(this + 172) + 72);
        *v20 = *(_DWORD *)(this + 104);
        v20[1] = *(_DWORD *)(this + 108);
        v20[2] = *(_DWORD *)(this + 112);
        v21 = *(_DWORD *)(this + 192);
        if ( *(float *)(this + 112) >= (double)*(float *)(v21 + 10624) )
        {
          if ( *(float *)(v21 + 884) > 0.0 )
            kill_slug_hazard(this);
LABEL_39:
          *(float *)(*(_DWORD *)(this + 172) + 124) = *(float *)(*(_DWORD *)(this + 192) + 880) + *(float *)(this + 152);
          v13 = *(_DWORD *)(this + 192);
          if ( *(_BYTE *)(v13 + 900) == 1 )
            *(float *)(*(_DWORD *)(this + 172) + 124) = *(float *)(v13 + 928)
                                                      + *(float *)(*(_DWORD *)(this + 172) + 124);
          update_slug_voice_ai(this);
        }
        else
        {
          v22 = *(_DWORD *)(this + 4);
          *(_DWORD *)(this + 128) = 0;
          v10 = (char *)g_game_base + 1448;
          if ( (v22 & 0x200) != 0 )
          {
            if ( (v22 & 0x40) != 0 )
            {
LABEL_72:
              report_errorf(aListRemoveNext);
              kill_sprite(*(_DWORD *)(this + 172));
            }
            else
            {
              v23 = *(_DWORD *)(this + 12);
              if ( v23 )
                *(_DWORD *)(v23 + 8) = *(_DWORD *)(this + 8);
              v24 = *(_DWORD *)(this + 8);
              if ( v24 )
                *(_DWORD *)(v24 + 12) = *(_DWORD *)(this + 12);
              else
LABEL_77:
                *((_DWORD *)v10 + 1) = *(_DWORD *)(this + 12);
LABEL_78:
              *(_DWORD *)(this + 12) = *((_DWORD *)v10 + 2);
              *((_DWORD *)v10 + 2) = this;
              v39 = *(_DWORD *)(this + 4);
              v40 = *(_DWORD *)(this + 172);
              BYTE1(v39) &= ~2u;
              *(_DWORD *)(this + 4) = v39;
              kill_sprite(v40);
            }
          }
          else
          {
LABEL_70:
            report_errorf(aListRemove);
            kill_sprite(*(_DWORD *)(this + 172));
          }
        }
        break;
      default:
        goto LABEL_39;
    }
  }
}

