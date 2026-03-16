/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgoldy @ 0x43b120 */
/* selector: update_subgoldy */

// Main per-frame player or Goldy actor step. Updates attachment-follow state, samples current track cells, drives row events, dispatches pickups and completion handoff, emits movement flags and sounds, and advances the runtime track index. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::AI()`.
void __thiscall sub_43B120(int this)
{
  int v2; // esi
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  float *v10; // ebx
  int v11; // eax
  double v12; // st7
  double v13; // st7
  double v14; // st7
  char v16; // c0
  double v17; // st7
  __int16 v18; // ax
  int v19; // esi
  int v20; // esi
  double v21; // st7
  int v22; // eax
  int v23; // eax
  int v24; // eax
  char *v25; // eax
  int v26; // edi
  int v27; // eax
  char *v28; // esi
  int v29; // eax
  int v30; // esi
  int v31; // edx
  char v32; // al
  double v33; // st7
  int v34; // ecx
  float *v35; // esi
  double v36; // st7
  char *v37; // eax
  double v38; // st6
  double v39; // st7
  double v40; // st7
  char *v41; // esi
  int v42; // edi
  int v43; // eax
  int v44; // eax
  char v45; // al
  char v46; // al
  double v47; // st7
  double v48; // st6
  int v49; // ecx
  double v50; // st7
  double v51; // st7
  double v52; // st7
  char *v53; // eax
  char *v54; // esi
  float v55; // eax
  char *v56; // ecx
  double v57; // st7
  double v58; // st7
  int v59; // ecx
  int v60; // ecx
  double v61; // st7
  int v62; // ecx
  double v63; // st7
  double v64; // st7
  int v65; // ecx
  int v66; // eax
  int v67; // ecx
  int v68; // eax
  int v69; // eax
  int v70; // ecx
  int v71; // ebp
  bool v72; // zf
  double v73; // st7
  double v74; // st7
  int v75; // edx
  double v76; // st7
  double v77; // st6
  double v78; // st6
  double v79; // st5
  double v80; // st5
  int v81; // eax
  double v82; // st7
  double v83; // st7
  double v84; // st7
  double v85; // st7
  double v86; // st7
  int v87; // ecx
  int v88; // eax
  int v89; // ecx
  int v90; // edx
  int v91; // ecx
  double v92; // st7
  double v93; // st7
  double v94; // st7
  int v95; // eax
  double v96; // st7
  double v97; // st6
  double v98; // st7
  char v99; // al
  double v100; // st7
  int v101; // eax
  double v102; // st7
  double v103; // st7
  int v104; // ecx
  int v105; // eax
  double v106; // st7
  int v107; // eax
  float v108; // [esp-14h] [ebp-6Ch]
  float v109; // [esp-14h] [ebp-6Ch]
  float v110; // [esp-10h] [ebp-68h]
  float v111; // [esp-10h] [ebp-68h]
  float v112; // [esp-Ch] [ebp-64h]
  float v113; // [esp-Ch] [ebp-64h]
  float v114; // [esp+0h] [ebp-58h]
  int v115; // [esp+4h] [ebp-54h]
  int v116; // [esp+4h] [ebp-54h]
  float v117; // [esp+4h] [ebp-54h]
  float v118; // [esp+4h] [ebp-54h]
  int v119; // [esp+4h] [ebp-54h]
  float v120; // [esp+18h] [ebp-40h]
  int v121; // [esp+18h] [ebp-40h]
  float v122; // [esp+18h] [ebp-40h]
  float v123; // [esp+18h] [ebp-40h]
  int v124; // [esp+18h] [ebp-40h]
  float v125; // [esp+18h] [ebp-40h]
  float v126; // [esp+1Ch] [ebp-3Ch]
  float v127; // [esp+1Ch] [ebp-3Ch]
  float v128; // [esp+1Ch] [ebp-3Ch]
  float v129; // [esp+20h] [ebp-38h]
  float v130; // [esp+20h] [ebp-38h]
  float v131; // [esp+20h] [ebp-38h]
  float v132; // [esp+24h] [ebp-34h]
  float v133; // [esp+24h] [ebp-34h]
  float v134; // [esp+24h] [ebp-34h]
  float v135; // [esp+28h] [ebp-30h] BYREF
  float v136; // [esp+2Ch] [ebp-2Ch]
  float v137; // [esp+30h] [ebp-28h]
  float v138; // [esp+34h] [ebp-24h]
  float v139; // [esp+38h] [ebp-20h]
  float v140; // [esp+40h] [ebp-18h]
  float v141; // [esp+44h] [ebp-14h]
  float v142; // [esp+4Ch] [ebp-Ch]
  int v143; // [esp+50h] [ebp-8h]
  int v144; // [esp+54h] [ebp-4h]

  if ( *(_BYTE *)(*(_DWORD *)(this + 1032) + 9) )
  {
    if ( *((_DWORD *)MEMORY[0x4DF904] + 110) != 9 )
    {
      update_damage_gauge(this + 964);
      sub_437C40();
      sub_446F80((float *)(this + 1012));
      update_row_event_display((_DWORD **)(*(_DWORD *)(this + 1032) + 19343320));
    }
    return;
  }
  if ( *(_BYTE *)(this + 900) == 1 )
  {
    v2 = *(_DWORD *)(this + 904);
    v3 = *(_DWORD *)(this + 912) + 3;
    v4 = *(_DWORD *)(v2 + 68);
    if ( v3 >= v4 )
      v3 = v4 - 1;
    *(float *)(*(_DWORD *)(this + 10664) + 128) = (*(float *)(*(_DWORD *)(v2 + 88) + 168 * v3 + 164) * -3.0
                                                 - *(float *)(*(_DWORD *)(this + 10664) + 128))
                                                * 0.1
                                                + *(float *)(*(_DWORD *)(this + 10664) + 128);
  }
  else
  {
    *(float *)(*(_DWORD *)(this + 10664) + 128) = -*(float *)(*(_DWORD *)(this + 10664) + 128) * 0.1
                                                + *(float *)(*(_DWORD *)(this + 10664) + 128);
  }
  sub_4449C0((float *)(this + 17220));
  *(_DWORD *)(*(_DWORD *)(this + 10664) + 132) = *(_DWORD *)(this + 17220);
  *(_DWORD *)(*(_DWORD *)(this + 10664) + 136) = *(_DWORD *)(this + 17232);
  if ( !*(_DWORD *)(*(_DWORD *)(this + 1032) + 64) )
    show_subgoldy_lives((_DWORD *)this);
  v5 = *(_DWORD *)(this + 1036);
  if ( v5 && v5 != 2 )
  {
    v6 = *(_DWORD *)(this + 1032);
    if ( *(int *)(v6 + 16721372) > 20 && !*(_BYTE *)(v6 + 43092) )
      *(_BYTE *)(v6 + 43092) = 1;
    v7 = *(_DWORD *)(this + 1032);
    if ( *(_BYTE *)(v7 + 16721360) )
    {
      v8 = *(_DWORD *)(v7 + 16721364);
      v9 = *(_DWORD *)(v7 + 16721372);
      if ( v9 < *(_DWORD *)(v8 + 108) && *(_DWORD *)(this + 288) != 2 )
      {
        v10 = (float *)(this + 104);
        *(float *)(this + 104) = sub_44C8B0(*(_WORD *)(v8 + 6 * v9 + 112), 16.0);
        v11 = *(_DWORD *)(this + 1032);
        *(_BYTE *)(v11 + 43092) = (*(_BYTE *)(*(_DWORD *)(v11 + 16721364) + 6 * *(_DWORD *)(v11 + 16721372) + 116) & 4) != 0;
        if ( (*(_BYTE *)(*(_DWORD *)(*(_DWORD *)(this + 1032) + 16721364)
                       + 6 * *(_DWORD *)(*(_DWORD *)(this + 1032) + 16721372)
                       + 116)
            & 8) != 0 )
        {
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
          *((_DWORD *)MEMORY[0x4DF904] + 111) = 10;
          *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
          begin_frontend_fade_in((_DWORD *)MEMORY[0x4DF904] + 9);
          return;
        }
LABEL_60:
        if ( *v10 < -4.0 )
        {
          *v10 = -4.0;
          *(_DWORD *)(this + 1040) = 0;
        }
        if ( *v10 > 4.0 )
        {
          *v10 = 4.0;
          *(_DWORD *)(this + 1040) = 0;
        }
        if ( *(_BYTE *)(this + 132) )
          update_subgoldy_resurrect(this);
        v25 = get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10);
        v26 = *(_DWORD *)(this + 1032);
        v121 = (int)v25;
        v27 = 61 * get_track_cell_row_index(v25);
        v28 = (char *)&unk_5CCAC8[v27] + v26;
        v29 = *(int *)((char *)&unk_5CCBB8[v27] + v26);
        if ( v29 > 0 && v29 != *(_DWORD *)(this + 488) && v29 < *(_DWORD *)(v26 + 43124) + 1 )
        {
          *(_DWORD *)(this + 488) = v29;
          if ( *(_BYTE *)(16928 * *((_DWORD *)v28 + 60) + *(_DWORD *)(this + 1032) + 42608) )
          {
            *(_DWORD *)(this + 492) = 2;
            *(_DWORD *)(this + 508) = 16928 * *((_DWORD *)v28 + 60) + *(_DWORD *)(this + 1032) + 42608;
            *(_DWORD *)(this + 496) = 0;
            *(_DWORD *)(this + 500) = 1106247680;
            *(_DWORD *)(this + 504) = *(_DWORD *)(16928 * *((_DWORD *)v28 + 60) + *(_DWORD *)(this + 1032) + 43120);
            if ( !*(_BYTE *)(this + 332) )
            {
              *(_BYTE *)(this + 332) = 1;
              if ( *v10 <= 0.0 )
                dispatch_cutscene_animation(this + 10628, 3, 1, -1);
              else
                dispatch_cutscene_animation(this + 10628, 4, 1, -1);
              dispatch_cutscene_animation(this + 10628, 1, 0, -1);
            }
            v30 = *((_DWORD *)v28 + 60);
            v31 = *(_DWORD *)(this + 1032);
            if ( *(_DWORD *)(16928 * v30 + v31 + 43124) != -1 )
              sub_4492D0((int)unk_751498, 13, 2u, *(_DWORD *)(16928 * v30 + v31 + 43124));
            enqueue_tip_message((_DWORD *)MEMORY[0x4DF904] + 4955094, this + 492, 1);
          }
        }
        if ( !*(_BYTE *)(this + 1053) )
        {
          v32 = *(_BYTE *)(v121 + 60);
          if ( (v32 == 29 || v32 == 30) && !*(_BYTE *)(this + 900) )
          {
            begin_track_attachment_follow_state((float *)(this + 900), v121, (int)v10, this);
            if ( *(_DWORD *)(*(_DWORD *)(this + 904) + 56) == 24 )
              sub_4492D0((int)unk_751498, 12, 0, -1);
          }
        }
        if ( *(_BYTE *)(this + 728) )
        {
          if ( *(float *)(this + 1048) < 0.0 )
          {
            v33 = *(float *)(*(_DWORD *)(this + 1032) + 56);
            *(float *)(this + 1048) = v33 * v33 * 0.0040000002 * 0.25 + *(float *)(this + 1048);
          }
          if ( *(float *)(this + 1048) > 0.0 )
LABEL_94:
            *(_DWORD *)(this + 1048) = 0;
        }
        else
        {
          v34 = *(_DWORD *)(this + 1032);
          if ( (double)*(int *)(v34 + 80) > *(float *)(this + 112) )
            *(float *)(this + 1048) = *(float *)(v34 + 56) * *(float *)(v34 + 56) * 0.0040000002
                                    + *(float *)(this + 1048);
          if ( *(float *)(this + 1048) > 1.0 )
            *(_DWORD *)(this + 1048) = 1065353216;
          if ( *(_DWORD *)(this + 288) == 2 )
            goto LABEL_94;
        }
        if ( *(_BYTE *)(this + 900) == 1 )
        {
          v35 = (float *)(this + 1040);
          switch ( update_track_attachment_follow_state((char *)(this + 900), *(float *)(this + 1048), v10, this + 1040) )
          {
            case 0:
              if ( *(_DWORD *)(*(_DWORD *)(this + 904) + 56) != 15 )
              {
                v36 = *(float *)(*(_DWORD *)(this + 1032) + 56);
                *(float *)(this + 1048) = v36 * v36 * 0.0040000002 + v36 * v36 * 0.0040000002 + *(float *)(this + 1048);
              }
              goto LABEL_101;
            case 1:
            case 3:
              if ( *(_BYTE *)(this + 900) == 1 )
                goto LABEL_98;
              break;
            case 2:
LABEL_101:
              *v10 = *v10 + *v35;
              v10[1] = *(float *)(this + 1044) + v10[1];
              v10[2] = *(float *)(this + 1048) + v10[2];
              *(float *)(this + 1048) = (1.0 - *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.003)
                                      * *(float *)(this + 1048);
              *(float *)(this + 1044) = (1.0 - *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.003)
                                      * *(float *)(this + 1044);
              *v35 = (1.0 - *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.1) * *v35;
              *(float *)(this + 1044) = *(float *)(*(_DWORD *)(this + 1032) + 56)
                                      * *(float *)(*(_DWORD *)(this + 1032) + 56)
                                      * -0.0099999998
                                      + *(float *)(this + 1044);
              if ( *v10 < -4.0 )
              {
                *v10 = -4.0;
                *v35 = 0.0;
              }
              if ( *v10 > 4.0 )
              {
                *v10 = 4.0;
                *v35 = 0.0;
              }
              break;
            default:
              break;
          }
        }
        else
        {
          *v10 = *(float *)(this + 1040) + *v10;
          v10[1] = *(float *)(this + 1044) + v10[1];
          v10[2] = *(float *)(this + 1048) + v10[2];
          if ( *v10 < -4.0 )
          {
            *v10 = -4.0;
            *(_DWORD *)(this + 1040) = 0;
          }
          if ( *v10 > 4.0 )
          {
            *v10 = 4.0;
            *(_DWORD *)(this + 1040) = 0;
          }
          if ( !*(_BYTE *)(this + 1088) )
          {
            if ( get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 15
              || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 16
              || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 18
              || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 19
              || *(_DWORD *)(this + 964) == 2
              && (v37 = get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10),
                  is_slide_cache_tile_family(v37)) )
            {
              v38 = *(float *)(*(_DWORD *)(this + 1032) + 56) * *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.0040000002;
              *(float *)(this + 1048) = v38 + v38 + *(float *)(this + 1048);
              if ( (double)*(int *)(*(_DWORD *)(this + 1032) + 80) <= *(float *)(this + 112)
                && *(float *)(this + 112) > (double)*(float *)(this + 10040) )
              {
                *(float *)(this + 10040) = *(float *)(this + 112) + 1.0;
              }
            }
          }
          if ( *(_DWORD *)(this + 10076) == 1 )
          {
            v39 = *(float *)(*(_DWORD *)(this + 1032) + 56);
            *(float *)(this + 1048) = v39 * v39 * 0.0040000002 + v39 * v39 * 0.0040000002 + *(float *)(this + 1048);
          }
          if ( !*(_BYTE *)(this + 484) )
            *(float *)(this + 1048) = (1.0 - *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.003)
                                    * *(float *)(this + 1048);
          *(float *)(this + 1044) = (1.0 - *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.003) * *(float *)(this + 1044);
          *(float *)(this + 1040) = (1.0 - *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.1) * *(float *)(this + 1040);
          if ( *(_BYTE *)(this + 1052) )
          {
            v40 = *(float *)(*(_DWORD *)(this + 1032) + 56);
            *(float *)(this + 1048) = v40 * v40 * 0.0040000002 + v40 * v40 * 0.0040000002 + *(float *)(this + 1048);
            *(_BYTE *)(this + 1053) = 0;
          }
          else
          {
            v41 = get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10);
            if ( *(_BYTE *)(this + 1053) )
            {
              v42 = *(_DWORD *)(this + 1032);
              if ( (*(int *)((char *)&unk_5CCAC8[61 * get_track_cell_row_index(v41)] + v42) & 0x100) == 0
                && !*(_DWORD *)(this + 10076)
                && !*(_BYTE *)(this + 728) )
              {
                *(float *)(this + 1048) = (1.0 - *(float *)(v42 + 56) * 0.2) * *(float *)(this + 1048);
              }
              if ( (*((_BYTE *)&unk_5CCAC8[61 * get_track_cell_row_index(v41)] + *(_DWORD *)(this + 1032)) & 0x40) != 0 )
              {
                v126 = *(float *)(this + 1040) * 1.05;
                v129 = *(float *)(this + 1044) * 1.05;
                v132 = *(float *)(this + 1048) * 1.05;
                v115 = *(int *)((char *)&unk_5CCB6C[61 * get_track_cell_row_index(v41)] + *(_DWORD *)(this + 1032));
                v108 = *v10;
                v110 = v10[1];
                v112 = v10[2];
                v43 = get_track_cell_row_index(v41);
                try_enter_track_attachment_from_swept_motion(
                  *(_DWORD **)(*(int *)((char *)&unk_5CCB6C[61 * v43] + *(_DWORD *)(this + 1032)) + 56),
                  v108,
                  v110,
                  v112,
                  v126,
                  v129,
                  v132,
                  v115);
              }
              if ( *(_BYTE *)(this + 1053)
                && *((char *)&unk_5CCAC8[61 * get_track_cell_row_index(v41)] + *(_DWORD *)(this + 1032)) < 0 )
              {
                v127 = *(float *)(this + 1040) * 1.05;
                v130 = *(float *)(this + 1044) * 1.05;
                v133 = *(float *)(this + 1048) * 1.05;
                v116 = *(int *)((char *)&unk_5CCB70[61 * get_track_cell_row_index(v41)] + *(_DWORD *)(this + 1032));
                v109 = *v10;
                v111 = v10[1];
                v113 = v10[2];
                v44 = get_track_cell_row_index(v41);
                try_enter_track_attachment_from_swept_motion(
                  *(_DWORD **)(*(int *)((char *)&unk_5CCB70[61 * v44] + *(_DWORD *)(this + 1032)) + 56),
                  v109,
                  v111,
                  v113,
                  v127,
                  v130,
                  v133,
                  v116);
              }
            }
            if ( !*(_BYTE *)(this + 900) )
            {
              if ( *(float *)(this + 108) < 0.49000001
                && *(float *)(this + 108) > -0.16333334
                && !is_open_neighbor_tile_family(v41)
                && v41[60] != 22 )
              {
                set_matrix_identity((_DWORD *)(this + 56));
                *(_BYTE *)(this + 484) = 0;
                if ( *(float *)(this + 1044) < -0.029999999 )
                {
                  v117 = *(float *)(this + 1044) - 0.029999999;
                  sub_444980(this + 17220, v117);
                }
                if ( *(float *)(this + 1044) <= 0.0 )
                {
                  *(_DWORD *)(this + 108) = 1056629064;
                  *(_DWORD *)(this + 1044) = 0;
                }
                *(_BYTE *)(this + 1053) = 0;
              }
              v45 = v41[60];
              if ( (!v45 || v45 == 35) && *(float *)(this + 108) < 0.49000001 && *(float *)(this + 1044) <= 0.0 )
              {
                v46 = v41[61];
                v47 = *(float *)(this + 112) - (double)(int)(__int64)*(float *)(this + 112);
                if ( (v46 & 2) != 0 )
                  v48 = 0.80000001;
                else
                  v48 = 1.0;
                v122 = 0.0;
                if ( (v46 & 1) != 0 )
                  v122 = 0.2;
                if ( v47 < v48 && v47 > v122 && !*(_BYTE *)(this + 1053) )
                  initialize_subgoldy_fall_state(this);
              }
              v49 = *(_DWORD *)(this + 1032);
              if ( *(_DWORD *)(v49 + 64) == 3 )
                get_track_grid_cell_at_world_position((char *)v49, v10);
              if ( ((*(_DWORD *)(*(_DWORD *)(this + 1032) + 76) & 0x400) == 0 || (byte_4B2F40 & 2) != 0)
                && *(float *)(this + 108) < 0.49000001 )
              {
                sub_444980(this + 17220, *(float *)(this + 1044));
                *(_BYTE *)(this + 484) = 0;
                *(_DWORD *)(this + 1044) = 0;
                *(_BYTE *)(this + 1053) = 0;
                *(_DWORD *)(this + 108) = 1056629064;
              }
              if ( *(float *)(this + 108) < -7.0 && !*(_BYTE *)(this + 132) )
                initialize_subgoldy_death((_DWORD *)this);
            }
          }
          if ( *(float *)(this + 476) != 0.0 )
          {
            v50 = *(float *)(this + 480) + *(float *)(this + 476);
            *(float *)(this + 476) = v50;
            if ( v50 > 1.0 )
              *(_DWORD *)(this + 476) = 0;
          }
          if ( *(_BYTE *)(this + 1053) )
          {
            *(float *)(this + 1044) = *(float *)(*(_DWORD *)(this + 1032) + 56)
                                    * *(float *)(*(_DWORD *)(this + 1032) + 56)
                                    * -0.0099999998
                                    + *(float *)(this + 1044);
            v53 = get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10);
            v54 = v53;
            if ( v53[60] == 22
              && *((float *)v53 + 5) + 0.49000001 > *(float *)(this + 108)
              && *((float *)v53 + 5) - 0.49000001 < *(float *)(this + 108) )
            {
              sub_444980(this + 17220, *(float *)(this + 1044));
              *(float *)(this + 1044) = *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.30000001;
              *(float *)(this + 108) = *((float *)v54 + 5) + 0.49000001;
              *(_BYTE *)(this + 1053) = 0;
              *(_BYTE *)(this + 484) = 1;
              play_sound_effect(41);
            }
          }
          else
          {
            v51 = sample_track_floor_height_at_position((char *)*(_DWORD *)(this + 1032), v10) + 0.49000001;
            if ( v51 <= *(float *)(this + 108) )
            {
              v52 = *(float *)(*(_DWORD *)(this + 1032) + 56);
              *(float *)(this + 1044) = v52 * v52 * -0.0099999998 + *(float *)(this + 1044);
            }
            else
            {
              if ( *(float *)(this + 1044) <= 0.0 )
                *(float *)(this + 108) = v51;
              if ( get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 8
                || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 9
                || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 10
                || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 11
                || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 12
                || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 13 )
              {
                *(float *)(this + 1044) = *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.30000001;
              }
              else if ( get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 2
                     || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 3
                     || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 4
                     || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 5
                     || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 6
                     || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 7 )
              {
                if ( *(float *)(this + 476) == 0.0 )
                  *(_DWORD *)(this + 476) = *(_DWORD *)(this + 480);
                *(float *)(this + 1044) = *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.2;
                if ( !*(_BYTE *)(this + 728) )
                {
                  if ( *v10 <= 0.0 )
                    dispatch_cutscene_animation(this + 10628, 3, 1, -1);
                  else
                    dispatch_cutscene_animation(this + 10628, 4, 1, -1);
                  dispatch_cutscene_animation(this + 10628, 1, 0, -1);
                }
              }
              else if ( get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60]
                     && get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] != 35
                     && get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] != 22 )
              {
                *(_BYTE *)(this + 484) = 0;
                *(_DWORD *)(this + 1044) = 0;
              }
            }
            if ( *(float *)(this + 108) < 0.0 && *(float *)(this + 1044) <= 0.0 )
LABEL_98:
              initialize_subgoldy_fall_state(this);
          }
        }
        sub_446F80((float *)(this + 1012));
        if ( *(_BYTE *)(this + 1052)
          || *(_BYTE *)(this + 900)
          || (v55 = v10[1],
              v134 = v10[2] + 0.49000001,
              v135 = *v10,
              v137 = v134,
              v56 = *(char **)(this + 1032),
              v136 = v55,
              get_track_grid_cell_at_world_position(v56, &v135)[60] != 14)
          || *(float *)(this + 108) >= 6.5 )
        {
          *(_DWORD *)(this + 808) = 0;
        }
        else
        {
          *(_DWORD *)(this + 1048) = 0;
          *(float *)(this + 112) = (double)(int)(__int64)(*(float *)(this + 112) + 0.49000001) - 0.5;
          if ( *(float *)(this + 17232) == 0.0 )
            play_sound_effect(47);
          sub_4449A0((float *)(this + 17220), -0.33000001);
          v57 = *(float *)(this + 812) + *(float *)(this + 808);
          *(float *)(this + 808) = v57;
          if ( v57 > 1.0 )
          {
            *(_DWORD *)(this + 808) = 0;
            if ( !*(_BYTE *)(this + 1053) )
              initialize_subgoldy_fall_state(this);
          }
        }
        if ( !*(_DWORD *)(this + 848)
          && (get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 2
           || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 4
           || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 5
           || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 7
           || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 10
           || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 8
           || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 10
           || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 11
           || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 13)
          && !*(_BYTE *)(this + 1053)
          && *(float *)(this + 108) <= 0.98000002 )
        {
          *(float *)(this + 860) = *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.037037037;
          if ( get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 2
            || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 5
            || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 8
            || get_track_grid_cell_at_world_position(*(char **)(this + 1032), v10)[60] == 11 )
          {
            *(_DWORD *)(this + 848) = 1;
            *(_DWORD *)(this + 852) = 1065353216;
          }
          else
          {
            *(_DWORD *)(this + 848) = 2;
            *(_DWORD *)(this + 852) = -1082130432;
          }
        }
        if ( *(float *)(this + 468) != 0.0 )
        {
          v58 = *(float *)(this + 472) + *(float *)(this + 468);
          *(float *)(this + 468) = v58;
          if ( v58 > 1.0 )
            *(_DWORD *)(this + 468) = 0;
        }
        v59 = *(_DWORD *)(this + 1032);
        v123 = (float)*(int *)(v59 + 88);
        if ( *(float *)(this + 112) < (double)v123 || *(_BYTE *)(this + 1053) )
        {
          if ( !*(_BYTE *)(this + 1052) && !*(_BYTE *)(this + 728) )
          {
            v73 = *(float *)(v59 + 56) * 0.17;
            if ( *(float *)(this + 1048) >= v73 )
            {
              v73 = *(float *)(v59 + 56) * 0.5;
              if ( *(float *)(this + 1048) <= v73 )
                v73 = *(float *)(this + 1048);
            }
            *(float *)(this + 1048) = v73;
          }
        }
        else
        {
          if ( !*(_BYTE *)(this + 1088) )
          {
            if ( *(_DWORD *)(v59 + 64) == 4 )
            {
              v118 = (1.0 - (*(float *)(this + 112) - v123) / *(float *)(this + 1048)) * 0.016666668;
              advance_timer_counters((float *)(this + 744), v118);
            }
            v60 = *(_DWORD *)(this + 1032);
            *(_DWORD *)(this + 1092) = 0;
            *(_DWORD *)(this + 1096) = 1015580809;
            *(_BYTE *)(this + 1102) = 0;
            v61 = *(float *)(v60 + 56) * 0.17;
            if ( *(float *)(this + 1048) >= v61 )
            {
              v61 = *(float *)(v60 + 56) * 0.5;
              if ( *(float *)(this + 1048) <= v61 )
                v61 = *(float *)(this + 1048);
            }
            *(float *)(this + 1048) = v61;
            sub_448EC0(unk_751498);
            sub_43A370((float *)(this + 10064));
            *(_DWORD *)(this + 17128) = 5;
            play_sound_effect(0);
            *(_BYTE *)(this + 1052) = 0;
          }
          *(_BYTE *)(this + 1088) = 1;
          v62 = *(_DWORD *)(this + 1032);
          if ( (double)*(int *)(v62 + 88) + 2.5 < *(float *)(this + 112) )
          {
            v63 = *(float *)(this + 1048)
                - (*(float *)(v62 + 56) * *(float *)(v62 + 56) * 0.0040000002
                 + *(float *)(v62 + 56) * *(float *)(v62 + 56) * 0.0040000002);
            *(float *)(this + 1048) = v63;
            if ( v63 < 0.0 )
              *(_DWORD *)(this + 1048) = 0;
          }
          v64 = *(float *)(this + 10056) + *(float *)(this + 10052);
          *(float *)(this + 10052) = v64;
          if ( v64 > 1.0 )
            *(_DWORD *)(this + 10052) = 0;
          v65 = *(_DWORD *)(this + 1032);
          *(float *)(this + 1092) = *(float *)(this + 1092) + *(float *)(this + 1096);
          *(_DWORD *)(v65 + 19337160) = 2;
          if ( *(float *)(this + 1092) > 2.0 && !*(_BYTE *)(this + 1102) )
          {
            *(_BYTE *)(this + 1102) = 1;
            sub_4492D0((int)unk_751498, 8, 2u, -1);
          }
          if ( *(float *)(this + 1092) > 2.0 )
          {
            v66 = *(_DWORD *)(this + 1032);
            if ( *(_DWORD *)(v66 + 64) <= 1u )
            {
              if ( *(_BYTE *)(v66 + 19343344) == 1 && (*(_BYTE *)(*(_DWORD *)(this + 1084) + 5) & 0x40) != 0 )
                *(_DWORD *)(this + 1092) = 1084437299;
              if ( *(_DWORD *)(v66 + 19343340) == 5 )
                *(_DWORD *)(this + 1092) = 1084437299;
            }
          }
          if ( *(float *)(this + 1092) > 5.0 )
          {
            v67 = *(_DWORD *)(this + 1032);
            if ( *(_DWORD *)(v67 + 64) <= 1u && *(_DWORD *)(v67 + 19343340) != 5 )
              *(float *)(this + 1092) = *(float *)(this + 1092) - *(float *)(this + 1096);
          }
          if ( *(float *)(this + 1092) > 5.0 )
          {
            v68 = *((_DWORD *)MEMORY[0x4DF904] + 9);
            if ( !v68 )
            {
              begin_frontend_fade_out((_DWORD *)MEMORY[0x4DF904] + 9, 0);
              goto LABEL_287;
            }
            if ( v68 == 4 )
            {
              v69 = *(_DWORD *)(this + 1032);
              if ( *(_DWORD *)(v69 + 19343340) )
                flush_row_event_display((_DWORD *)(v69 + 19343320));
              v70 = *(_DWORD *)(this + 1032);
              if ( *(_DWORD *)(v70 + 64) )
              {
                complete_subgame(v70, 1);
              }
              else
              {
                if ( *(_DWORD *)(v70 + 68) == *((_DWORD *)MEMORY[0x4DF904] + 4936081) - 1 )
                {
                  complete_subgame(v70, 1);
                  *((_DWORD *)MEMORY[0x4DF904] + 111) = 29;
                  *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
                  return;
                }
                complete_subgame(v70, 0);
                *(_DWORD *)(*(_DWORD *)(this + 1032) + 19337160) = 1;
              }
              v71 = *(_DWORD *)(this + 1032);
              if ( *(_DWORD *)(v71 + 64) == 7 )
              {
                *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
                *((_DWORD *)MEMORY[0x4DF904] + 111) = 2;
              }
              else
              {
                v72 = *(_BYTE *)(v71 + 16721361) == 0;
                *((_DWORD *)MEMORY[0x4DF904] + 111) = *((_DWORD *)MEMORY[0x4DF904] + 110);
                if ( v72 )
                  *((_DWORD *)MEMORY[0x4DF904] + 110) = 27;
                else
                  *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
              }
              return;
            }
          }
        }
LABEL_287:
        v142 = *v10;
        v143 = *((_DWORD *)v10 + 1);
        v144 = *((_DWORD *)v10 + 2);
        if ( *(_BYTE *)(this + 900) == 1 )
        {
          *v10 = *(float *)(this + 944);
          v10[1] = *(float *)(this + 948);
          v10[2] = *(float *)(this + 952);
        }
        update_jetpack_gauge(this + 10064);
        if ( *(_BYTE *)(this + 1088) )
        {
          qmemcpy((char *)MEMORY[0x4DF904] + 716, (char *)MEMORY[0x4DF904] + 348, 0x40u);
          *((float *)MEMORY[0x4DF904] + 192) = *((float *)MEMORY[0x4DF904] + 192) - 1.0;
        }
        update_damage_gauge(this + 964);
        sub_437C40();
        v74 = *(float *)(this + 10092);
        *(float *)(this + 10596) = *v10;
        v75 = *((_DWORD *)v10 + 2);
        *(float *)(this + 10600) = v10[1];
        *(_DWORD *)(this + 10604) = v75;
        v140 = v74 * *(float *)(this + 88);
        v141 = v74 * *(float *)(this + 92);
        v76 = v74 * *(float *)(this + 96);
        v77 = *(float *)(this + 10088);
        v128 = v77 * *(float *)(this + 72);
        v131 = v77 * *(float *)(this + 76);
        v78 = v77 * *(float *)(this + 80);
        v79 = *(float *)(this + 10084);
        v135 = v79 * *(float *)(this + 56);
        v136 = v79 * *(float *)(this + 60);
        v80 = v79 * *(float *)(this + 64);
        v138 = v135 + v128;
        v139 = v136 + v131;
        v135 = v138 + v140;
        v136 = v139 + v141;
        *(float *)(this + 10596) = v135 + *(float *)(this + 10596);
        *(float *)(this + 10600) = v136 + *(float *)(this + 10600);
        *(float *)(this + 10604) = v76 + v78 + v80 + *(float *)(this + 10604);
        v81 = *(_DWORD *)(this + 988);
        if ( v81 > 0 )
          *(_DWORD *)(this + 988) = v81 - 1;
        if ( *(_BYTE *)(this + 900) == 1 )
          *v10 = v142;
        v82 = *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.037037037;
        *(float *)(this + 860) = v82;
        if ( *(_DWORD *)(this + 848) )
        {
          v83 = v82 + *(float *)(this + 856);
          *(float *)(this + 856) = v83;
          if ( v83 > 1.0 )
          {
            *(_DWORD *)(this + 856) = 0;
            *(_DWORD *)(this + 848) = 0;
          }
        }
        if ( *(_DWORD *)(this + 864) )
        {
          v84 = *(float *)(this + 876) + *(float *)(this + 872);
          *(float *)(this + 872) = v84;
          if ( v84 > 1.0 )
          {
            *(_DWORD *)(this + 872) = 0;
            *(_DWORD *)(this + 864) = 0;
          }
        }
        v85 = *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.022222223;
        *(float *)(this + 888) = v85;
        if ( *(float *)(this + 884) > 0.0 )
        {
          v86 = v85 + *(float *)(this + 884);
          *(float *)(this + 884) = v86;
          if ( v86 <= 1.0 )
          {
            sub_4471E0((float *)(this + 336));
          }
          else
          {
            *(_DWORD *)(this + 884) = 0;
            sub_4470E0((int *)(this + 336));
          }
        }
        v87 = *(_DWORD *)(this + 1032);
        if ( *(_DWORD *)(v87 + 64) == 4 )
        {
          v88 = v87 + 129728 * *(_DWORD *)(v87 + 68);
          if ( *(_DWORD *)(v88 + 9716048) == 1 && !*(_BYTE *)(v87 + 16721360) )
          {
            v89 = *(_DWORD *)(v87 + 16721372);
            if ( v89 >= *(_DWORD *)(v88 + 9716156) )
              v89 = *(_DWORD *)(v88 + 9716156);
            v90 = *(_DWORD *)(this + 772);
            if ( v90 && (v91 = *(_DWORD *)(v88 + 9716084) - v90 + v89) != 0 )
              v92 = sub_44C8B0(*(_WORD *)(v88 + 6 * v91 + 9716162), 32.0) + unk_643190;
            else
              v92 = sub_44C8B0(*(_WORD *)(v88 + 9716162), 32.0);
            unk_643190 = v92;
            if ( *(_BYTE *)(*(_DWORD *)(this + 1032) + 16721360) )
              unk_643190 = *(float *)(this + 112);
            v93 = *(float *)(this + 112) + 20.0;
            if ( unk_643190 >= v93 )
            {
              *(float *)&v124 = v93;
              mark_current_track_pair_with_payload((_DWORD *)this, v124);
            }
            else
            {
              mark_current_track_pair_with_payload((_DWORD *)this, SLODWORD(unk_643190));
            }
          }
        }
        *(float *)&v119 = *(float *)(this + 112) / (double)*(int *)(*(_DWORD *)(this + 1032) + 84);
        set_backdrop_progress_fraction((_DWORD *)MEMORY[0x4DF904] + 80644, v119);
        v94 = (double)*(int *)(*(_DWORD *)(this + 1032) + 88) - 30.0;
        v125 = *(float *)(this + 112) - 8.0;
        if ( v94 >= v125 )
          v94 = v125;
        v95 = *(_DWORD *)(this + 10076);
        *(float *)(this + 10624) = v94;
        if ( v95 == 1 )
        {
          if ( *(float *)(this + 108) < 1.0 )
          {
            v96 = *(float *)(this + 1044) * 0.89999998;
            *(float *)(this + 1044) = v96;
            v97 = *(float *)(*(_DWORD *)(this + 1032) + 56);
            *(float *)(this + 1044) = v96 - v97 * v97 * -0.0099999998;
          }
          *(_BYTE *)(this + 1053) = 0;
        }
        if ( *(_BYTE *)(this + 1053) )
        {
          v98 = *(float *)(this + 1080) + *(float *)(this + 1076);
          *(float *)(this + 1076) = v98;
          if ( v98 > 0.69999999 && !*(_BYTE *)(this + 1100) )
          {
            sub_4492D0((int)unk_751498, 3, 0, -1);
            v99 = *(_BYTE *)(this + 728);
            *(_BYTE *)(this + 1100) = 1;
            if ( !v99 && *(float *)(this + 108) < -6.0 )
              dispatch_cutscene_animation(this + 10628, 5, 1, -1);
          }
          if ( *(float *)(this + 108) < -7.0 && !*(_BYTE *)(this + 1101) )
          {
            sub_4492D0((int)unk_751498, 1, 2u, -1);
            *(_BYTE *)(this + 1101) = 1;
            *(_BYTE *)(this + 1100) = 1;
          }
        }
        if ( *(float *)(this + 816) > 0.0 )
        {
          v100 = *(float *)(this + 820) + *(float *)(this + 816);
          *(float *)(this + 816) = v100;
          if ( v100 > 1.0 )
          {
            sub_4492D0((int)unk_751498, 7, 2u, -1);
            *(_DWORD *)(this + 816) = 0;
          }
        }
        v101 = *(_DWORD *)(this + 1032);
        v102 = *(float *)(v101 + 56) * 0.17;
        if ( (*(float *)(v101 + 56) * 0.5 - v102) * 0.1 + v102 <= *(float *)(this + 1048)
          || v102 >= *(float *)(this + 1048)
          || *(_BYTE *)(this + 1053)
          || *(_DWORD *)(this + 288) == 2 )
        {
          *(_DWORD *)(this + 17244) = 0;
        }
        else
        {
          v103 = *(float *)(this + 17248) + *(float *)(this + 17244);
          *(float *)(this + 17244) = v103;
          if ( v103 > 1.0 )
          {
            *(_DWORD *)(this + 17244) = 0;
            sub_4492D0((int)unk_751498, 6, 1u, -1);
          }
        }
        handle_subgoldy_collisions(this);
        update_cutscene_animation_slot((char *)(this + 10888));
        update_cutscene_animation_slot((char *)(this + 15468));
        update_cutscene_animation_slot((char *)(this + 12504));
        update_cutscene_animation_slot((char *)(this + 13492));
        update_cutscene_animation_slot((char *)(this + 14480));
        sub_443130((_DWORD *)(*(_DWORD *)(this + 1032) + 19260544));
        initialize_cutscene(this + 10628);
        update_player_movement_flags((int *)this);
        if ( *((int *)MEMORY[0x4DF904] + 4299517) < 10 )
          *(_DWORD *)(this + 10032) = *(_DWORD *)(this + 10036);
        v104 = *(_DWORD *)(this + 1032);
        if ( (*(_DWORD *)(v104 + 76) & 0x400000) == 0 )
          goto LABEL_365;
        if ( *(_BYTE *)(this + 1088) )
          goto LABEL_365;
        if ( *(_BYTE *)(this + 728) )
          goto LABEL_365;
        v105 = *(_DWORD *)(this + 288);
        if ( v105 )
        {
          if ( v105 != 4 )
            goto LABEL_365;
        }
        if ( *(float *)(this + 10032) > 0.0 )
        {
          v106 = *(float *)(this + 10036) + *(float *)(this + 10032);
          *(float *)(this + 10032) = v106;
          if ( v106 > 1.0 )
            *(_DWORD *)(this + 10032) = 0;
          goto LABEL_365;
        }
        if ( *(_BYTE *)(v104 + 43092) )
        {
          if ( *(_BYTE *)(v104 + 16721360) )
          {
            if ( (*(_BYTE *)(*(_DWORD *)(v104 + 16721364) + 6 * *(_DWORD *)(v104 + 16721372) + 116) & 1) == 0 )
            {
              if ( (*(_BYTE *)(*(_DWORD *)(v104 + 16721364) + 6 * *(_DWORD *)(v104 + 16721372) + 116) & 2) == 0 )
                goto LABEL_365;
              goto LABEL_364;
            }
            goto LABEL_359;
          }
          if ( (*(_DWORD *)(*(_DWORD *)(this + 1084) + 4) & 0x4000) != 0 )
          {
LABEL_359:
            play_movement_state_sound(this);
            update_movement_flag_emitters((char *)this, this);
            *(float *)(this + 10032) = *(float *)(this + 10036) + 0.30000001;
            goto LABEL_365;
          }
          if ( (*(_DWORD *)(*(_DWORD *)(this + 1084) + 12) & 0x4000) != 0 )
          {
LABEL_364:
            *(_DWORD *)(this + 10032) = *(_DWORD *)(this + 10036);
            play_movement_state_sound(this);
            update_movement_flag_emitters((char *)this, this);
          }
        }
LABEL_365:
        update_row_event_display((_DWORD **)(*(_DWORD *)(this + 1032) + 19343320));
        ++*(_DWORD *)(*(_DWORD *)(this + 1032) + 16591740);
        ++*(_DWORD *)(*(_DWORD *)(this + 1032) + 16721372);
        v107 = *(_DWORD *)(this + 1032);
        if ( *(_DWORD *)(v107 + 16721372) == 21000 )
          show_times_up_message((int *)(v107 + 19343400));
        sub_445E20(*(_DWORD *)(this + 1032) + 19343400);
        return;
      }
    }
    if ( *(_BYTE *)(this + 960) && *(_BYTE *)(this + 1088) )
    {
      *(_DWORD *)(this + 10044) = 1134559232;
      *(_DWORD *)(this + 10048) = 1134559232;
    }
    else
    {
      if ( *(_BYTE *)(this + 728) )
      {
        v12 = *(float *)(this + 10044) - (*(float *)(this + 10700) + *(float *)(this + 10700));
        *(float *)(this + 10044) = v12;
        *(float *)(this + 10048) = v12;
        if ( *(float *)(this + 10044) >= 0.0 )
        {
          if ( *(float *)(this + 10044) <= 639.0 )
            v13 = *(float *)(this + 10044);
          else
            v13 = 639.0;
        }
        else
        {
          v13 = 0.0;
        }
      }
      else
      {
        sub_44BC20(*(&unk_4DF950 + *(_DWORD *)(this + 10608)));
        v14 = *(float *)(*(_DWORD *)(this + 1084) + 40) - *(float *)(this + 10048) + *(float *)(this + 10044);
        *(float *)(this + 10044) = v14;
        if ( v16 )
        {
          v14 = 0.0;
        }
        else if ( v14 > 639.0 )
        {
          v14 = 639.0;
        }
        *(float *)(this + 10044) = v14;
        *(_DWORD *)(this + 10048) = *(_DWORD *)(*(_DWORD *)(this + 1084) + 40);
        if ( *(_DWORD *)(this + 10608) != 1 )
          goto LABEL_40;
        v13 = *(float *)(*(_DWORD *)(this + 1084) + 40);
      }
      *(float *)(this + 10044) = v13;
    }
LABEL_40:
    if ( !*(_BYTE *)(this + 1088) )
    {
      v17 = (320.0 - *(float *)(this + 10044)) * 0.0125;
      if ( v17 >= -3.7 )
      {
        if ( v17 > 3.7 )
          v17 = 3.7;
      }
      else
      {
        v17 = -3.7;
      }
      if ( *(_DWORD *)(this + 288) != 2 )
        *(float *)(this + 104) = *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.2 * (v17 - *(float *)(this + 104))
                               + *(float *)(this + 104);
    }
    v10 = (float *)(this + 104);
    v18 = sub_44C890(*(float *)(this + 104), 16.0);
    v120 = sub_44C8B0(v18, 16.0);
    *(float *)(this + 104) = v120;
    v19 = *(_DWORD *)(this + 1032);
    *(_WORD *)(v19 + 6 * *(_DWORD *)(v19 + 16721372) + 16591744) = sub_44C890(v120, 16.0);
    v20 = *(_DWORD *)(this + 1032);
    if ( *(_DWORD *)(v20 + 16721372) )
    {
      v114 = *(float *)(this + 112) - unk_643194;
      *(_WORD *)(v20 + 6 * (*(_DWORD *)(v20 + 16721372) + 2765291)) = sub_44C890(v114, 32.0);
      v21 = sub_44C8B0(
              *(_WORD *)(*(_DWORD *)(this + 1032) + 6 * (*(_DWORD *)(*(_DWORD *)(this + 1032) + 16721372) + 2765291)),
              32.0)
          + unk_643194;
    }
    else
    {
      *(_WORD *)(v20 + 6 * (*(_DWORD *)(v20 + 16721372) + 2765291)) = sub_44C890(*(float *)(this + 112), 32.0);
      v21 = sub_44C8B0(
              *(_WORD *)(*(_DWORD *)(this + 1032) + 6 * (*(_DWORD *)(*(_DWORD *)(this + 1032) + 16721372) + 2765291)),
              32.0);
    }
    unk_643194 = v21;
    v22 = *(_DWORD *)(this + 1032);
    if ( *(_BYTE *)(v22 + 43092) )
    {
      if ( (*(_DWORD *)(*(_DWORD *)(this + 1084) + 4) & 0x4000) != 0 )
        *(_BYTE *)(v22 + 6 * *(_DWORD *)(v22 + 16721372) + 16591748) |= 1u;
      if ( (*(_DWORD *)(*(_DWORD *)(this + 1084) + 12) & 0x4000) != 0 )
        *(_BYTE *)(*(_DWORD *)(this + 1032) + 6 * *(_DWORD *)(*(_DWORD *)(this + 1032) + 16721372) + 16591748) |= 2u;
    }
    v23 = *(_DWORD *)(this + 1084);
    if ( (*(_DWORD *)(v23 + 12) & 0x4000) == 0 && (*(_DWORD *)(v23 + 4) & 0x4000) == 0 )
      *(_BYTE *)(*(_DWORD *)(this + 1032) + 43092) = 1;
    v24 = *(_DWORD *)(this + 1032);
    if ( *(_BYTE *)(v24 + 43092) )
      *(_BYTE *)(v24 + 6 * *(_DWORD *)(v24 + 16721372) + 16591748) |= 4u;
    goto LABEL_60;
  }
}

