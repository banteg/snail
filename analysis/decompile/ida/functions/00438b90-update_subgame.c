/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgame @ 0x438b90 */
/* selector: update_subgame */

// Runs the main gameplay subgame state machine, including the continuation-controlled galaxy or challenge-setup handoff, replay-backed level start or restart, pause and quit flow, HUD timing, camera updates, and the active gameplay tick. Cross-port Android and iOS symbols match this helper to `cRSubGame::AI()`.
void __thiscall sub_438B90(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // edx
  int v9; // eax
  double v10; // st7
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // ebp
  int v17; // edi
  char *v18; // ecx
  char *v19; // eax
  int v20; // edx
  int v21; // edx
  int v22; // eax
  int v23; // edi
  char v24; // al
  int v25; // eax
  int v26; // ecx
  int v27; // eax
  int v28; // ecx
  _DWORD *v29; // eax
  int v30; // ecx
  int v31; // ecx
  _DWORD *v32; // ebx
  _DWORD *v33; // ebx
  _DWORD *v34; // eax
  int v35; // ecx
  int v36; // ecx
  _DWORD *v37; // eax
  _DWORD *v38; // edx
  char v39; // al
  char v40; // al
  char v41; // al
  char v42; // al
  int v43; // edx
  char v44; // cl
  int v45; // edx
  char v46; // al
  int v47; // eax
  char *v48; // eax
  int v49; // eax
  char *v50; // eax
  int v51; // eax
  int v52; // ecx
  int *v53; // [esp-1Ch] [ebp-68h]
  int *v54; // [esp-1Ch] [ebp-68h]
  int v55; // [esp+10h] [ebp-3Ch]
  int v56; // [esp+14h] [ebp-38h]
  int v57; // [esp+18h] [ebp-34h]
  int v58[4]; // [esp+1Ch] [ebp-30h] BYREF
  int v59[4]; // [esp+2Ch] [ebp-20h] BYREF
  int v60[4]; // [esp+3Ch] [ebp-10h] BYREF

  calc_subgame_rate(this);
  switch ( *(_DWORD *)(this + 60) )
  {
    case 0:
      v2 = *(_DWORD *)(this + 19337160);
      *(_DWORD *)(this + 60) = 1;
      if ( v2 == 1 )
        goto LABEL_214;
      if ( !v2 || v2 == 3 )
      {
LABEL_21:
        build_subgame_level(this, *(_DWORD *)(this + 68));
      }
      else
      {
        if ( *(_BYTE *)(this + 16721361) != 1 )
        {
          *(_BYTE *)(this + 16721360) = 0;
          hide_star_field((int *)MEMORY[0x4DF904] + 81103);
          goto LABEL_14;
        }
        v3 = *(_DWORD *)(this + 16721364);
        *(_BYTE *)(this + 16721360) = 1;
        build_subgame_level(this, *(_DWORD *)(v3 + 40));
      }
      return;
    case 1:
LABEL_14:
      random_float_below(1.0);
      v4 = *(_DWORD *)(this + 64);
      *(_DWORD *)(this + 40) = unk_4DF958;
      *(_DWORD *)(this + 44) = unk_4DF960;
      switch ( v4 )
      {
        case 0:
          v5 = update_galaxy(this + 19267616);
          if ( v5 == 1 )
          {
            v6 = *(_DWORD *)(this + 68);
            *(_DWORD *)(this + 19337160) = 3;
            unk_4DF9BC = v6;
            build_subgame_level(this, *(_DWORD *)(this + 68));
            return;
          }
          if ( v5 == 2 )
          {
            v7 = *(_DWORD *)(this + 68);
            *(_DWORD *)(this + 19337160) = 1;
            unk_4DF9BC = v7;
            build_subgame_level(this, *(_DWORD *)(this + 68));
            return;
          }
LABEL_22:
          if ( v5 != 3 )
            goto LABEL_214;
LABEL_23:
          destroy_subgame(this);
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 2;
          break;
        case 1:
          v9 = update_challenge_setup_screen((_DWORD **)(this + 19267552));
          if ( v9 == 1 )
            goto LABEL_25;
          if ( v9 == 3 )
            goto LABEL_23;
          goto LABEL_214;
        case 4:
          v5 = update_galaxy(this + 19267616);
          if ( v5 != 1 )
            goto LABEL_22;
          v8 = *(_DWORD *)(this + 68);
          *(_DWORD *)(this + 19337160) = 2;
          unk_4DF9BC = v8;
          goto LABEL_21;
        case 7:
LABEL_25:
          *(_DWORD *)(this + 19337160) = 2;
          build_subgame_level(this, 0);
          return;
        default:
          goto LABEL_214;
      }
      return;
    case 2:
      if ( *(_BYTE *)(this + 16721360) == 1 && !*((_BYTE *)MEMORY[0x4DF904] + 324320) )
      {
        if ( *(_DWORD *)(this + 64) == 3 )
        {
          v53 = set_color_rgba(v58, 1065353216, 1065353216, 1065353216, 1053609165);
          queue_axis_aligned_textured_quad_uv(
            27,
            1141964800,
            1086324736,
            1115684864,
            1115684864,
            0x1000000,
            v53,
            0,
            0,
            1065353216,
            1065353216,
            1,
            0);
        }
        else
        {
          v54 = set_color_rgba(v59, 1065353216, 1065353216, 1065353216, 1053609165);
          queue_axis_aligned_textured_quad_uv(
            27,
            1133510656,
            1092616192,
            1115684864,
            1115684864,
            0x1000000,
            v54,
            0,
            0,
            1065353216,
            1065353216,
            1,
            0);
        }
      }
      if ( !*(_BYTE *)(this + 3914660) && *(_DWORD *)(this + 3913860) != 2 )
        advance_timer_counters((float *)(this + 3914316), 1.0);
      if ( *(_DWORD *)(this + 64) == 7 )
        update_tutorial((char **)(this + 43096));
      update_slug_voice_manager((float *)(this + 3521404));
      if ( *(_BYTE *)(this + 8) == 1 )
      {
        *(_BYTE *)(this + 9) = 0;
        *(_BYTE *)(this + 8) = 0;
        set_sprite_manager_paused(unk_790F30, 0);
      }
      if ( *(_BYTE *)(this + 16721360)
        && *(float *)(this + 12) == 0.0
        && (*(_DWORD *)(*(_DWORD *)(this + 3914656) + 4) & 0x4000) != 0
        || *((_BYTE *)MEMORY[0x4DF904] + 324320) )
      {
        if ( *(_BYTE *)(this + 16721361) )
        {
          *((_DWORD *)MEMORY[0x4DF904] + 111) = *((_DWORD *)MEMORY[0x4DF904] + 110);
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
        }
        else
        {
          *((_DWORD *)MEMORY[0x4DF904] + 111) = *((_DWORD *)MEMORY[0x4DF904] + 110);
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 27;
        }
        if ( *((float *)MEMORY[0x4DF904] + 81081) <= 1.0 )
          *((_BYTE *)MEMORY[0x4DF904] + 324320) = 0;
        return;
      }
      if ( (read_pressed_text_input_key_code() == 11 || unk_4B7654 == 1) && !*((_DWORD *)MEMORY[0x4DF904] + 9) )
      {
        *(_BYTE *)(this + 9) = 1;
        *(_DWORD *)(this + 60) = 3;
        set_sprite_manager_paused(unk_790F30, 1);
        if ( *(_DWORD *)(this + 3913860) == 2 )
          hide_border_init(*(_DWORD **)(this + 3913864));
        return;
      }
      if ( *(float *)(this + 12) > 0.0 )
      {
        v10 = *(float *)(this + 16) + *(float *)(this + 12);
        *(float *)(this + 12) = v10;
        if ( v10 > 1.0 )
          *(_DWORD *)(this + 12) = 0;
        if ( *(_DWORD *)(this + 3913860) == 2 )
          unhide_border_init(*(_DWORD **)(this + 3913864));
      }
      if ( *(_BYTE *)this )
      {
        v11 = *(_DWORD *)(this + 64);
        *(_DWORD *)(this + 32) = 0;
        if ( v11 == 2 )
        {
          *(_DWORD *)(this + 36) = *(_DWORD *)(this + 84);
          goto LABEL_62;
        }
        v12 = (__int64)*(float *)(this + 3924196) + 46;
LABEL_61:
        *(_DWORD *)(this + 36) = v12;
        goto LABEL_62;
      }
      v13 = *(_DWORD *)(this + 64);
      v14 = *(_DWORD *)(this + 36);
      *(_DWORD *)(this + 32) = v14;
      if ( v13 == 2 )
      {
        *(_DWORD *)(this + 36) = *(_DWORD *)(this + 84);
        goto LABEL_62;
      }
      v12 = (__int64)*(float *)(this + 3924196) + 46;
      if ( v12 > v14 )
        goto LABEL_61;
LABEL_62:
      v15 = *(_DWORD *)(this + 88) + 20;
      if ( *(_DWORD *)(this + 36) > v15 )
        *(_DWORD *)(this + 36) = v15;
      v16 = *(_DWORD *)(this + 32);
      if ( v16 < *(_DWORD *)(this + 36) )
      {
LABEL_65:
        v17 = this + 244 * v16;
        v57 = v17;
        if ( (*((_BYTE *)byte_5CCAC8 + v17) & 2) != 0 )
        {
          v18 = (char *)&unk_5CCACC + v17;
          if ( (*(int *)((char *)&unk_5CCAD0 + v17) & 0x200) != 0 )
          {
            report_errorf(aListAdd);
          }
          else
          {
            v19 = (char *)MEMORY[0x4DF904] + 1452;
            v20 = *((_DWORD *)MEMORY[0x4DF904] + 363);
            if ( v20 )
            {
              *(_DWORD *)(v20 + 8) = v18;
              *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v19 + 8) + 12) = *(_DWORD *)v19;
              v21 = *(_DWORD *)(*(_DWORD *)v19 + 8);
              *(_DWORD *)v19 = v21;
              *(_DWORD *)(v21 + 8) = 0;
            }
            else
            {
              *(_DWORD *)v19 = v18;
              *((_DWORD *)v18 + 2) = 0;
              *(_DWORD *)(*(_DWORD *)v19 + 12) = 0;
            }
            v22 = *((_DWORD *)v18 + 1);
            BYTE1(v22) |= 2u;
            *((_DWORD *)v18 + 1) = v22;
          }
        }
        if ( (*((_BYTE *)byte_5CCAC8 + v17) & 0x10) != 0 && ((unsigned int)&unk_800000 & *(_DWORD *)(this + 76)) != 0 )
          spawn_track_parcel((int *)this, (float *)((char *)&unk_5CCB58 + v17), this + 3913572);
        v55 = 0;
        while ( 1 )
        {
          if ( v16 < 0 )
            goto LABEL_209;
          if ( v16 >= *(_DWORD *)(this + 84) )
            goto LABEL_209;
          v23 = this + 84 * (v55 + 8 * v16);
          if ( (*(_DWORD *)(v23 + 3930828) & 0x200) != 0 )
            goto LABEL_209;
          if ( (*(_DWORD *)(v23 + 3930888) & 0x4000) != 0 )
          {
            v24 = *(_BYTE *)(v23 + 3930884);
            if ( v24 == 29 || v24 == 30 )
            {
              if ( *(_DWORD *)(v23 + 3930860) )
              {
                v27 = v23 + 3930824;
                if ( (*(_DWORD *)(v23 + 3930828) & 0x200) != 0 )
                {
                  report_errorf(aListAddafter);
                }
                else
                {
                  *(_DWORD *)(v23 + 3930832) = this + 3497140;
                  *(_DWORD *)(v23 + 3930836) = *(_DWORD *)(this + 3497152);
                  *(_DWORD *)(this + 3497152) = v27;
                  v28 = *(_DWORD *)(v23 + 3930836);
                  if ( v28 )
                    *(_DWORD *)(v28 + 8) = v27;
                  *(_DWORD *)(v23 + 3930828) |= 0x200u;
                }
                v29 = (_DWORD *)((char *)&unk_5CCB78 + v57);
                *(float *)(v23 + 3930856) = (double)(v16 & 7) * 0.125;
                if ( (*(_DWORD *)((_BYTE *)&unk_5CCB78 + v57 + 4) & 0x200) != 0 )
                {
                  report_errorf(aListAddafter);
                }
                else
                {
                  v29[2] = this + 3496804;
                  v29[3] = *(_DWORD *)(this + 3496816);
                  *(_DWORD *)(this + 3496816) = v29;
                  v30 = v29[3];
                  if ( v30 )
                    *(_DWORD *)(v30 + 8) = v29;
                  v31 = v29[1];
                  BYTE1(v31) |= 2u;
                  v29[1] = v31;
                }
                v32 = (int *)((char *)&unk_5CCB88 + v57);
                *v32 = *(_DWORD *)(v23 + 3930840);
                v32[1] = *(_DWORD *)(v23 + 3930844);
                v32[2] = *(_DWORD *)(v23 + 3930848);
              }
            }
            else
            {
              v25 = v23 + 3930824;
              if ( (*(_DWORD *)(v23 + 3930828) & 0x200) != 0 )
              {
                report_errorf(aListAddafter);
              }
              else
              {
                *(_DWORD *)(v23 + 3930832) = this + 3496860;
                *(_DWORD *)(v23 + 3930836) = *(_DWORD *)(this + 3496872);
                *(_DWORD *)(this + 3496872) = v25;
                v26 = *(_DWORD *)(v23 + 3930836);
                if ( v26 )
                  *(_DWORD *)(v26 + 8) = v25;
                *(_DWORD *)(v23 + 3930828) |= 0x200u;
              }
            }
            (**(void (__thiscall ***)(int))(v23 + 3930824))(v23 + 3930824);
          }
          v33 = (_DWORD *)(v23 + 3930892);
          v56 = 4;
          do
          {
            v34 = (_DWORD *)*v33;
            if ( *v33 )
            {
              if ( (v34[1] & 0x200) != 0 )
              {
                report_errorf(aListAddafter);
              }
              else
              {
                v34[2] = this + 3496804;
                v34[3] = *(_DWORD *)(this + 3496816);
                *(_DWORD *)(this + 3496816) = v34;
                v35 = v34[3];
                if ( v35 )
                  *(_DWORD *)(v35 + 8) = v34;
                v36 = v34[1];
                BYTE1(v36) |= 2u;
                v34[1] = v36;
              }
              v37 = get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v60);
              v38 = (_DWORD *)(*v33 + 40);
              *v38 = *v37;
              v38[1] = v37[1];
              v38[2] = v37[2];
              v38[3] = v37[3];
            }
            ++v33;
            --v56;
          }
          while ( v56 );
          if ( *(_BYTE *)(v23 + 3930884) == 23
            && (*(_DWORD *)(this + 76) & 0x800) != 0
            && v16 >= *(_DWORD *)(this + 80)
            && v16 < *(_DWORD *)(this + 88) )
          {
            spawn_track_health_pickup(this, v23 + 3930824, v23 + 3930824, this + 3913572);
          }
          if ( *(_BYTE *)(v23 + 3930884) == 24 && v16 >= *(_DWORD *)(this + 80) && v16 < *(_DWORD *)(this + 88) )
            spawn_track_speedup(v23 + 3930824, this + 3913572);
          if ( *(_BYTE *)(v23 + 3930884) == 25 && v16 >= *(_DWORD *)(this + 80) && v16 < *(_DWORD *)(this + 88) )
            spawn_track_jetpack_pickup((char *)this, v23 + 3930824, this + 3913572);
          v39 = *(_BYTE *)(v23 + 3930884);
          if ( v39 == 33
            || (*(_BYTE *)(v23 + 3930888) & 0x10) == 0
            && (v39 == 1 || v39 == 21)
            && (*(_BYTE *)(this + 76) & 2) != 0
            && (1.0 - *(float *)(this + 19267544)) * 0.2 + 0.80000001 < random_float_below(1.0)
            && (!v55 || (v40 = *(_BYTE *)(v23 + 3930800), v40 == 1) || v40 == 20 || v40 == 21 || v40 == 32)
            && (v55 == 7 || (v41 = *(_BYTE *)(v23 + 3930968), v41 == 1) || v41 == 20 || v41 == 21 || v41 == 32)
            && v16 >= *(_DWORD *)(this + 80)
            && v16 < *(_DWORD *)(this + 88)
            && *(_DWORD *)(this + 3913860) != 2
            && (*(_DWORD *)(this + 64) != 4 || *(float *)(this + 72) * 0.30000001 + 0.69999999 >= random_float_below(1.0))
            && (*(_DWORD *)(this + 64) || *(float *)(this + 72) * 0.60000002 + 0.40000001 >= random_float_below(1.0)) )
          {
            spawn_track_garbage_hazard((_DWORD *)this, v23 + 3930824, this + 3913572);
          }
          v42 = *(_BYTE *)(v23 + 3930884);
          if ( v42 == 34 )
          {
            if ( v16 >= *(_DWORD *)(this + 80) && v16 < *(_DWORD *)(this + 88) )
              goto LABEL_158;
          }
          else if ( (*(_BYTE *)(v23 + 3930888) & 8) == 0
                 && (v42 == 1 || v42 == 15)
                 && *(_DWORD *)(this + 3913860) != 2
                 && (*(_DWORD *)(this + 76) & 0x10000) != 0
                 && (1.0 - *(float *)(this + 19267548)) * 0.02 + 0.98000002 < random_float_below(1.0)
                 && v16 >= *(_DWORD *)(this + 80)
                 && v16 < *(_DWORD *)(this + 88) )
          {
LABEL_158:
            spawn_salt_hazard((_DWORD *)(this + 3504320), (_DWORD *)(v23 + 3930840));
          }
          if ( *(char *)(this + 76) < 0
            && *(_BYTE *)(v23 + 3930884) == 18
            && v16 >= *(_DWORD *)(this + 80)
            && v16 < *(_DWORD *)(this + 88) )
          {
            spawn_slug_hazard(this, v23 + 3930824, this + 3913572);
          }
          v43 = *(int *)((char *)byte_5CCAC8 + v57);
          if ( (v43 & 0x200) != 0 )
            goto LABEL_209;
          v44 = *(_BYTE *)(v23 + 3930884);
          if ( v44 == 35 )
          {
            if ( (v43 & 0x400) != 0 )
            {
              spawn_track_ring_or_special_effect(
                this,
                v23 + 3930824,
                5,
                this + 3913572,
                *(float *)(this + 4 * (v16 + 20 * (3 * v16 + 74772) + 24924)));
              goto LABEL_207;
            }
            if ( (v43 & 0x2000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                this,
                v23 + 3930824,
                8,
                this + 3913572,
                *(float *)(this + 4 * (v16 + 20 * (3 * v16 + 74772) + 24924)));
              goto LABEL_207;
            }
            if ( (v43 & 0x800) != 0 )
            {
              spawn_track_ring_or_special_effect(
                this,
                v23 + 3930824,
                6,
                this + 3913572,
                *(float *)(this + 4 * (v16 + 20 * (3 * v16 + 74772) + 24924)));
              goto LABEL_207;
            }
            if ( (v43 & 0x1000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                this,
                v23 + 3930824,
                7,
                this + 3913572,
                *(float *)(this + 4 * (v16 + 20 * (3 * v16 + 74772) + 24924)));
              goto LABEL_207;
            }
          }
          else
          {
            if ( v44 != 2 && v44 != 3 && v44 != 4 && v44 != 5 && v44 != 6 && v44 != 7
              || *(float *)(this + 3914464) + 10.0 >= *(float *)(v23 + 3930848)
              || v16 >= *(_DWORD *)(this + 88) )
            {
              if ( v44 != 8 && v44 != 9 && v44 != 10
                || *(float *)(this + 3914464) + 10.0 >= *(float *)(v23 + 3930848)
                || v16 >= *(_DWORD *)(this + 88) )
              {
                goto LABEL_209;
              }
              if ( (v43 & 0x800) != 0 )
              {
                spawn_track_ring_or_special_effect(
                  this,
                  v23 + 3930824,
                  2,
                  this + 3913572,
                  *(float *)(this + 4 * (v16 + 20 * (3 * v16 + 74772) + 24924)));
              }
              else
              {
                if ( random_float_below(1.0) <= 0.69999999
                  && *(_DWORD *)(this + 64) != 7
                  && (*(int *)((char *)byte_5CCAC8 + v57) & 0x800) == 0 )
                {
                  goto LABEL_209;
                }
                spawn_track_ring_or_special_effect(this, v23 + 3930824, 2, this + 3913572, 0.0);
              }
LABEL_207:
              v45 = *(_DWORD *)(v23 + 3930848);
LABEL_208:
              *(_DWORD *)(this + 3914464) = v45;
              goto LABEL_209;
            }
            if ( (v43 & 0x2000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                this,
                v23 + 3934856,
                8,
                this + 3913572,
                *(float *)(this + 4 * (v16 + 20 * (3 * v16 + 74772) + 24924)));
              v45 = *(_DWORD *)(v23 + 3934880);
              goto LABEL_208;
            }
            if ( (v43 & 0x800) != 0 )
            {
              spawn_track_ring_or_special_effect(
                this,
                v23 + 3934856,
                6,
                this + 3913572,
                *(float *)(this + 4 * (v16 + 20 * (3 * v16 + 74772) + 24924)));
              v45 = *(_DWORD *)(v23 + 3934880);
              goto LABEL_208;
            }
            if ( (v43 & 0x1000) != 0 )
            {
              spawn_track_ring_or_special_effect(
                this,
                v23 + 3934856,
                7,
                this + 3913572,
                *(float *)(this + 4 * (v16 + 20 * (3 * v16 + 74772) + 24924)));
              v45 = *(_DWORD *)(v23 + 3934880);
              goto LABEL_208;
            }
            if ( (*(_BYTE *)(this + 76) & 8) == 0
              || random_float_below(1.0) <= 0.69999999 && *(_DWORD *)(this + 64) != 7 )
            {
              goto LABEL_209;
            }
            v46 = *(_BYTE *)(v23 + 3930884);
            if ( v46 == 5 || v46 == 6 || v46 == 7 )
              goto LABEL_209;
            spawn_track_ring_or_special_effect(this, v23 + 3930824, 4, this + 3913572, 0.0);
            if ( *(int *)(this + 3914600) < 10 )
              goto LABEL_207;
            *(float *)(this + 3914464) = *(float *)(v23 + 3930848) + 35.0;
          }
LABEL_209:
          if ( ++v55 >= 8 )
          {
            v47 = *(_DWORD *)(this + 36);
            ++v16;
            *(_BYTE *)this = 0;
            if ( v16 >= v47 )
              break;
            goto LABEL_65;
          }
        }
      }
      sub_433B30(this + 92);
      if ( *(_DWORD *)(this + 64) == 4 )
      {
        v48 = format_time_trial_string(this + 3914316);
        rstrcpy_checked_ascii((char *)(*(_DWORD *)(this + 3521416) + 716), v48);
        v49 = this + 129728 * *(_DWORD *)(this + 68);
        if ( *(_DWORD *)(v49 + 9716048) == 1 )
        {
          v50 = format_time_trial_string(v49 + 9716056);
          rstrcpy_checked_ascii((char *)(*(_DWORD *)(this + 3521420) + 716), v50);
          goto LABEL_214;
        }
        hide_border_init(*(_DWORD **)(this + 3521420));
        update_subgame_camera(this);
      }
      else
      {
        *(_BYTE *)(*(_DWORD *)(this + 3521416) + 716) = 0;
        border_add_text_number(*(_BYTE **)(this + 3521416), *(_DWORD *)(this + 3914312));
        v51 = *(_DWORD *)(this + 3914312);
        if ( v51 <= *(_DWORD *)(this + 3497364) )
          goto LABEL_214;
        v52 = *(_DWORD *)(this + 3521420);
        *(_DWORD *)(this + 3497364) = v51;
        *(_BYTE *)(v52 + 716) = 0;
        border_add_text_number(*(_BYTE **)(this + 3521420), *(_DWORD *)(this + 3497364));
        update_subgame_camera(this);
      }
      return;
    case 3:
      *(_DWORD *)(this + 60) = 4;
      *(_BYTE *)(this + 9) = 1;
      *(_DWORD *)(this + 12) = *(_DWORD *)(this + 16);
      initialize_pause_menu((int *)(this + 20));
      goto LABEL_3;
    case 4:
LABEL_3:
      update_pause_menu((_DWORD *)(this + 20));
      return;
    case 7:
      *(_BYTE *)(this + 16721360) = *(_BYTE *)(this + 16721361) == 1;
      build_subgame_level(this, 0);
      *(_DWORD *)(this + 60) = 2;
      *((_DWORD *)MEMORY[0x4DF904] + 347) = 1;
      return;
    default:
LABEL_214:
      update_subgame_camera(this);
      return;
  }
}

