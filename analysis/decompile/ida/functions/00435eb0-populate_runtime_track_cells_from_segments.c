/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: populate_runtime_track_cells_from_segments @ 0x435eb0 */
/* selector: populate_runtime_track_cells_from_segments */

// Copies authored segment rows into the generated runtime grid, seeds Goldy's visible life stock to 3 before `initialize_subgoldy` runs, and seeds the course row bounds: non-random levels use the final `Last:` block boundary while the mode-1 random branch keeps the authored `Length:` lane scaled by the challenge scalar before subtracting the final `Last:` block rows.
char __thiscall sub_435EB0(int this)
{
  int v2; // esi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // esi
  int v10; // eax
  _DWORD *v11; // ecx
  _DWORD *v12; // edi
  int v13; // ebp
  _DWORD *v14; // esi
  int v15; // ecx
  int v16; // edx
  _DWORD *v17; // eax
  int v18; // ecx
  _DWORD *v19; // esi
  int v20; // eax
  _BYTE *v21; // ecx
  int v22; // eax
  int v23; // edi
  int v24; // ebp
  int v25; // esi
  double v26; // st7
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // ecx
  int v31; // eax
  int v32; // edx
  int v33; // eax
  int v34; // esi
  int v35; // ecx
  int v36; // eax
  _DWORD *v37; // esi
  int *v38; // eax
  int v39; // ecx
  int *v40; // eax
  int v41; // ecx
  float *v42; // ebx
  int v43; // eax
  _DWORD *v44; // edx
  int v45; // eax
  char *v46; // eax
  _DWORD *v47; // ecx
  int v48; // eax
  int v49; // eax
  int v50; // ebp
  int v51; // esi
  int v52; // eax
  int v53; // edi
  char *v54; // ebp
  char v55; // al
  int v56; // eax
  int v57; // eax
  int v58; // eax
  int v59; // eax
  int v60; // eax
  int v61; // eax
  int v62; // eax
  int v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // eax
  int v67; // eax
  int v68; // eax
  int v69; // eax
  int v70; // eax
  int v71; // eax
  int v72; // eax
  int v73; // ecx
  unsigned int v74; // ebp
  bool v75; // zf
  unsigned int v76; // eax
  int v77; // eax
  int v78; // eax
  int v79; // eax
  int v80; // eax
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // eax
  int v85; // ecx
  int v86; // ecx
  int v87; // edx
  int *v88; // ecx
  int v89; // eax
  int v90; // ecx
  int v91; // eax
  int v92; // eax
  float *v93; // edi
  char v94; // al
  char v95; // al
  double v96; // st7
  double v97; // st7
  _DWORD *v98; // eax
  _DWORD *v99; // ecx
  int v100; // eax
  char v101; // al
  _DWORD *v102; // ecx
  int v103; // edx
  _DWORD *v104; // eax
  _DWORD *v105; // eax
  bool v106; // cc
  float v108; // [esp+0h] [ebp-5Ch]
  char v109; // [esp+1Ah] [ebp-42h]
  char v110; // [esp+1Bh] [ebp-41h]
  int v111; // [esp+1Ch] [ebp-40h]
  int v112; // [esp+20h] [ebp-3Ch]
  int v114; // [esp+28h] [ebp-34h]
  int v115; // [esp+2Ch] [ebp-30h]
  int v116; // [esp+2Ch] [ebp-30h]
  int v117; // [esp+30h] [ebp-2Ch]
  int v118; // [esp+34h] [ebp-28h]
  float v119; // [esp+34h] [ebp-28h]
  int v120; // [esp+38h] [ebp-24h]
  int v121; // [esp+3Ch] [ebp-20h]
  int v122; // [esp+40h] [ebp-1Ch]
  char v123; // [esp+40h] [ebp-1Ch]
  int v124[4]; // [esp+4Ch] [ebp-10h] BYREF

  if ( *(_BYTE *)(this + 16721360) )
  {
    v2 = *(_DWORD *)(*(_DWORD *)(this + 16721364) + 104);
  }
  else
  {
    v3 = *(_DWORD *)(this + 64);
    if ( v3 == 4 || v3 == 7 )
      v2 = 0;
    else
      v2 = (__int64)random_float_below(32768.0);
  }
  v4 = *(_DWORD *)(this + 64);
  if ( v4 )
  {
    v5 = v4 - 1;
    if ( v5 )
    {
      if ( v5 == 3 )
        initialize_high_score_entry(
          (char *)(this + 16591632),
          v2,
          *(_DWORD *)(this + 68),
          *(_DWORD *)(this + 48),
          *(_DWORD *)(this + 76),
          2,
          *(_DWORD *)(this + 68));
    }
    else
    {
      initialize_high_score_entry(
        (char *)(this + 16591632),
        v2,
        *(_DWORD *)(this + 68),
        *(_DWORD *)(this + 48),
        *(_DWORD *)(this + 76),
        1,
        *(_DWORD *)(this + 68));
    }
  }
  else
  {
    initialize_high_score_entry(
      (char *)(this + 16591632),
      v2,
      *(_DWORD *)(this + 68),
      *(_DWORD *)(this + 48),
      *(_DWORD *)(this + 76),
      0,
      *(_DWORD *)(this + 68));
  }
  v6 = *(_DWORD *)(this + 19337160);
  *(_DWORD *)(this + 16721372) = 0;
  if ( v6 == 3 )
  {
    *(_DWORD *)(this + 19337160) = 1;
    *(_DWORD *)(this + 3914312) = 0;
    clear_subgoldy_score_buckets(this + 3913572);
    *(_DWORD *)(this + 3930788) = 3;
  }
  zero_timer_counters((_DWORD *)(this + 3914316));
  *(_DWORD *)(this + 3914340) = 0;
  *(_DWORD *)(this + 3914348) = 0;
  set_math_random_seed(v2);
  select_level_track_texture_set((int *)MEMORY[0x4DF904] + 713, *(_DWORD *)(this + 1769956));
  v7 = *(_DWORD *)(this + 64);
  if ( !v7 || v7 == 7 || v7 == 4 || v7 == 1 )
  {
    *(_DWORD *)(this + 80) = *(_DWORD *)(this + 1735932);
    v122 = *(_DWORD *)(this + 1769784);
    *(_DWORD *)(this + 84) = v122;
    if ( v7 == 1 )
      *(_DWORD *)(this + 84) = (__int64)((*(float *)(this + 52) * 0.64999998 + 0.34999999) * (double)v122);
    if ( !*(_BYTE *)(this + 1769788) )
    {
      v10 = 0;
      *(_DWORD *)(this + 84) = *(_DWORD *)(this + 1735932) + *(_DWORD *)(this + 1752860);
      if ( *(int *)(this + 43124) > 0 )
      {
        v11 = (_DWORD *)(this + 43132);
        do
        {
          ++v10;
          *(_DWORD *)(this + 84) += *v11;
          v11 += 4232;
        }
        while ( v10 < *(_DWORD *)(this + 43124) );
      }
      v120 = 0;
    }
    *(_DWORD *)(this + 88) = *(_DWORD *)(this + 84) - *(_DWORD *)(this + 1752860);
    if ( *(int *)(this + 84) >= 3100 )
      report_errorf("Track (%s) too long, Maximum Length %i", (const char *)(this + 1769808), 3100);
  }
  else if ( v7 == 3 )
  {
    *(_DWORD *)(this + 80) = *(_DWORD *)(this + 1735932);
    v8 = 16;
    *(_DWORD *)(this + 84) = *(_DWORD *)(this + 1735932) + *(_DWORD *)(this + 1752860);
    do
    {
      v9 = *(_DWORD *)(this + 43132) + *(_DWORD *)(this + 84);
      --v8;
      *(_DWORD *)(this + 84) = v9;
    }
    while ( v8 );
    v120 = 0;
    *(_DWORD *)(this + 88) = v9 - *(_DWORD *)(this + 1752860);
    *(_DWORD *)(this + 88) = v9 - *(_DWORD *)(this + 1752860);
  }
  *(_BYTE *)(this + 2) = 0;
  *(_DWORD *)(this + 4) = 0;
  v121 = 0;
  v109 = 0;
  v117 = 0;
  *(_BYTE *)(this + 3914532) = 0;
  v118 = this + 3930892;
  v12 = (int *)((char *)&unk_5CCB5C + this);
  v115 = 3200;
  do
  {
    v13 = 8;
    *(v12 - 37) = 0;
    v12[6] = 0;
    v12[3] = 0;
    v12[21] = 0;
    v12[4] = 0;
    v12[1] = 0;
    *v12 = 0;
    *(v12 - 1) = 0;
    v12[2] = 0;
    v12[22] = 0;
    v12[23] = 0;
    v14 = (_DWORD *)(v118 - 4);
    do
    {
      v15 = *v14;
      BYTE1(v15) = BYTE1(*v14) & 0x5F;
      *v14 = v15;
      *((_BYTE *)v14 - 3) = 0;
      *(_WORD *)v14 = 0;
      *v14 &= 0xFFFFAFA7;
      *(_WORD *)v14 = 0;
      v16 = *(v14 - 15);
      LOBYTE(v16) = v16 & 0x7F;
      *(v14 - 15) = v16;
      set_color_white(v14 - 6);
      v14 += 21;
      --v13;
    }
    while ( v13 );
    v17 = (_DWORD *)v118;
    v18 = 8;
    do
    {
      v19 = v17;
      v17 += 21;
      --v18;
      *v19 = 0;
      v19[1] = 0;
      v19[2] = 0;
      v19[3] = 0;
    }
    while ( v18 );
    v118 = (int)v17;
    v12 += 61;
    --v115;
  }
  while ( v115 );
  if ( *(_BYTE *)(this + 1769788) == 1 )
  {
    v20 = 0;
    if ( *(int *)(this + 43124) > 0 )
    {
      v21 = (_BYTE *)(this + 43136);
      do
      {
        *v21 = 0;
        ++v20;
        v21 += 16928;
      }
      while ( v20 < *(_DWORD *)(this + 43124) );
    }
  }
  v22 = *(_DWORD *)(this + 84);
  v111 = 0;
  if ( v22 > 0 )
  {
    v23 = 0;
    v24 = this;
    do
    {
      if ( v23 )
      {
        if ( v23 != *(_DWORD *)(v24 + 88) || *(_BYTE *)(v24 + 1769788) )
        {
          *(_DWORD *)(v24 + 72) = 1065353216;
          if ( *(_BYTE *)(v24 + 1769788) == 1 )
          {
            if ( *(_DWORD *)(v24 + 64) == 1 )
              v26 = (*(float *)(v24 + 52) * 0.89999998 + 0.1) * (double)*(int *)(v24 + 43124);
            else
              v26 = (double)*(int *)(v24 + 43124);
            v108 = v26;
            v25 = 16928 * (__int64)((double)(int)(__int64)random_float_below(v108) * *(float *)(v24 + 72)) + v24 + 43128;
            v112 = v25;
            *(_BYTE *)(v25 + 8) = 1;
          }
          else
          {
            v27 = v120;
            v28 = v120++;
            v25 = 32 * (v27 + 16 * (v27 + 32 * v28)) + v24 + 43128;
            v112 = v25;
          }
        }
        else
        {
          v25 = v24 + 1752856;
          v109 = 1;
          v112 = v24 + 1752856;
          *(_DWORD *)(v24 + 1752856) = v23;
        }
      }
      else
      {
        v25 = v24 + 1735928;
        v109 = 1;
        v112 = v24 + 1735928;
        *(_DWORD *)(v24 + 1735928) = 0;
      }
      switch_track_mirror(v24);
      v29 = *(_DWORD *)(v25 + 4);
      *(_DWORD *)v25 = v23;
      if ( v29 < 0 )
        report_errorf(aNegativeSegmen);
      v22 = *(_DWORD *)(v24 + 84);
      v114 = 0;
      if ( v23 < v22 )
      {
        do
        {
          LOBYTE(v22) = v112;
          if ( v114 >= *(_DWORD *)(v112 + 4) )
            break;
          v30 = *(_DWORD *)(v24 + 64);
          if ( v30 == 2 || (v31 = *(_DWORD *)(v24 + 88), v23 < v31) )
          {
            v32 = v112;
          }
          else
          {
            if ( !v30 || v30 == 4 || v30 == 1 || v30 == 7 || (v32 = v24 + 1786896, v30 == 3) )
              v32 = v24 + 1752856;
            v112 = v32;
            if ( v23 == v31 )
              v114 = 0;
          }
          if ( v30 != 2 )
          {
            v33 = *(_DWORD *)(v32 + 4);
            v34 = *(_DWORD *)(v24 + 88);
            if ( v23 + v33 - v114 <= v34 )
            {
              v32 = v112;
            }
            else
            {
              v32 = v112;
              if ( v112 != v24 + 1786896
                && v112 != v24 + 1820752
                && v112 != v24 + 1837680
                && (!v30 || v30 == 4 || v30 == 1 || v30 == 7 || v30 == 3)
                && v112 != v24 + 1752856 )
              {
                v35 = *(_DWORD *)(v24 + 84);
                v36 = v23 + v33 - v34 - v114;
                *(_DWORD *)(v24 + 88) = v36 + v34;
                *(_DWORD *)(v24 + 84) = v36 + v35;
              }
            }
          }
          if ( *(_BYTE *)(v24 + 2) )
            *(int *)((char *)&byte_5CCAC8[61 * v23] + v24) |= 0x20u;
          v37 = (_DWORD *)(v32 + 56 * v114);
          if ( (v37[517] & 0x100) != 0 )
          {
            v38 = (int *)((char *)&byte_5CCAC8[61 * v23] + v24);
            v39 = *v38;
            BYTE1(v39) = BYTE1(*v38) | 1;
            *v38 = v39;
          }
          if ( (BYTE1(v37[517]) & 0x80u) != 0 )
          {
            v40 = (int *)((char *)&byte_5CCAC8[61 * v23] + v24);
            v41 = *v40;
            BYTE1(v41) = BYTE1(*v40) | 0x80;
            *v40 = v41;
          }
          v42 = (float *)(v24 + 244 * v23);
          *(int *)((char *)&unk_5CCBB4 + (_DWORD)v42) = v32;
          *(int *)((char *)&unk_5CCBB8 + (_DWORD)v42) = v117;
          if ( (v37[517] & 2) != 0 )
          {
            v43 = *(int *)((char *)byte_5CCAC8 + (_DWORD)v42);
            LOBYTE(v43) = v43 | 2;
            *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) = v43;
            set_bod_object((char *)&unk_5CCACC + (_DWORD)v42, *((_DWORD *)MEMORY[0x4DF904] + 47 * v37[522] + 74635));
            set_matrix_identity((char *)&unk_5CCB04 + (_DWORD)v42);
            v44 = (_DWORD *)((char *)&unk_5CCB34 + (_DWORD)v42);
            *v44 = v37[523];
            v44[1] = v37[524];
            v44[2] = v37[525];
            v42[1520335] = (double)v111 + v42[1520335];
            if ( (v37[517] & 8) != 0 )
            {
              v45 = *(int *)((char *)byte_5CCAC8 + (_DWORD)v42);
              LOBYTE(v45) = v45 | 8;
              *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) = v45;
              v46 = (char *)&unk_5CCB4C + (_DWORD)v42;
              *(int *)((char *)&unk_5CCB4C + (_DWORD)v42) = v37[526];
              *((_DWORD *)v46 + 1) = v37[527];
              *((_DWORD *)v46 + 2) = v37[528];
            }
            else
            {
              *(int *)((char *)&unk_5CCB54 + (_DWORD)v42) = 0;
              *(int *)((char *)&unk_5CCB50 + (_DWORD)v42) = 0;
              *(int *)((char *)&unk_5CCB4C + (_DWORD)v42) = 0;
            }
            v32 = v112;
          }
          if ( (v37[517] & 1) != 0 )
          {
            *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) |= 0x4001u;
            v47 = (_DWORD *)((char *)&unk_5CCB58 + (_DWORD)v42);
            *(int *)((char *)&unk_5CCB64 + (_DWORD)v42) = *(_DWORD *)(v32 + 56 * (v114 + 37));
            *v47 = v37[519];
            v47[1] = v37[520];
            v47[2] = v37[521];
          }
          if ( (v37[517] & 8) != 0 )
          {
            v48 = *(int *)((char *)byte_5CCAC8 + (_DWORD)v42);
            LOBYTE(v48) = v48 | 8;
            *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) = v48;
            *(int *)((char *)&unk_5CCB68 + (_DWORD)v42) = v37[529];
          }
          if ( (v37[517] & 4) != 0 )
          {
            v49 = *(int *)((char *)byte_5CCAC8 + (_DWORD)v42);
            LOBYTE(v49) = v49 | 4;
            *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) = v49;
          }
          if ( (v37[517] & 0x200) != 0 )
            *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) |= 0x200u;
          if ( (v37[517] & 0x400) != 0 )
            *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) |= 0x400u;
          if ( (v37[517] & 0x2000) != 0 )
            *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) |= 0x2000u;
          if ( (v37[517] & 0x800) != 0 )
            *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) |= 0x800u;
          if ( (v37[517] & 0x1000) != 0 )
            *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) |= 0x1000u;
          v110 = 0;
          v116 = 0;
          *(_DWORD *)(v24 + 4 * (v23 + 20 * (3 * v23 + 74772) + 24924)) = v37[530];
          do
          {
            if ( *(_BYTE *)(this + 2) )
              v50 = 7 - v116;
            else
              v50 = v116;
            v51 = this + 84 * (v116 + 8 * v111);
            v52 = *(_DWORD *)(v51 + 3930888);
            LOBYTE(v52) = v52 & 0xE0;
            *(_DWORD *)(v51 + 3930888) = v116 & 7 ^ v52;
            *(_DWORD *)(v51 + 3930892) = 0;
            *(_DWORD *)(v51 + 3930896) = 0;
            *(_DWORD *)(v51 + 3930900) = 0;
            *(_DWORD *)(v51 + 3930904) = 0;
            if ( v111 < *(_DWORD *)(this + 80) || (v123 = 0, v111 >= *(_DWORD *)(this + 88)) )
              v123 = 1;
            v53 = v51 + 3930824;
            set_bod_object((_DWORD *)(v51 + 3930824), 0);
            v54 = (char *)(v112 + v114 + (v50 << 8) + 20);
            v55 = normalize_segment_glyph_for_track_flags(this, *v54, v111, v123);
            switch ( v55 )
            {
              case ' ':
                *(_BYTE *)(v51 + 3930884) = 0;
                v56 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v56) = v56 & 0xDF;
                *(_DWORD *)(v51 + 3930828) = v56;
                break;
              case '#':
                *(_BYTE *)(v51 + 3930884) = 32;
                v58 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v58) = v58 & 0xDF;
                *(_DWORD *)(v51 + 3930828) = v58;
                break;
              case '$':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70349));
                *(_BYTE *)(v51 + 3930884) = 23;
                v61 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v61) = v61 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v61;
                break;
              case '&':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70125));
                *(_BYTE *)(v51 + 3930884) = 34;
                v67 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v67) = v67 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v67;
                break;
              case '(':
                v73 = v121 + 1;
                v74 = *(_DWORD *)(v51 + 3930828) & 0xFFFFFFDF;
                v75 = v121++ == 14;
                *(_DWORD *)(v51 + 3930828) = v74;
                v76 = v74;
                if ( v75 )
                {
                  v121 = 0;
                  *(_BYTE *)(v51 + 3930884) = 22;
                }
                else
                {
                  if ( v73 == 8 )
                  {
                    set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 69943));
                    *(_DWORD *)(v51 + 3930828) |= 0x20u;
                    store_color4f(
                      (_DWORD *)(this + 84 * (v116 + 8 * v111 + 46796)),
                      1065353216,
                      1065353216,
                      1065353216,
                      1065336439);
                  }
                  else
                  {
                    LOBYTE(v76) = v74 & 0xDF;
                    *(_DWORD *)(v51 + 3930828) = v76;
                  }
                  *(_BYTE *)(v51 + 3930884) = 22;
                }
                break;
              case '+':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70349));
                *(_BYTE *)(v51 + 3930884) = 24;
                v69 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v69) = v69 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v69;
                break;
              case ',':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 69705));
                *(_BYTE *)(v51 + 3930884) = 28;
                v68 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v68) = v68 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v68;
                break;
              case '-':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70125));
                *(_BYTE *)(v51 + 3930884) = 21;
                v71 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v71) = v71 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v71;
                break;
              case '.':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70125));
                *(_BYTE *)(v51 + 3930884) = 1;
                v65 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v65) = v65 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v65;
                break;
              case '0':
                if ( *(_DWORD *)(this + 64) == 1 )
                {
                  v90 = *(int *)((char *)byte_5CCAC8 + (_DWORD)v42);
                  BYTE1(v90) &= ~0x40u;
                  *(int *)((char *)byte_5CCAC8 + (_DWORD)v42) = v90 | 1;
                  *(int *)((char *)&unk_5CCB64 + (_DWORD)v42) = 0;
                  v42[1520342] = (double)v116 - 4.0 + 0.5;
                  *(int *)((char *)&unk_5CCB5C + (_DWORD)v42) = *(_DWORD *)(v51 + 3930844);
                  v42[1520344] = (double)v111 + 0.5;
                  if ( *(_BYTE *)(this + 2) )
                    v42[1520342] = v42[1520342] * -1.0;
                }
                goto LABEL_173;
              case '1':
              case '2':
              case '3':
              case '4':
              case '5':
              case '6':
              case '7':
              case '8':
              case '9':
LABEL_173:
                if ( (*((_BYTE *)byte_5CCAC8 + (_DWORD)v42) & 0xC0) == 0 )
                  goto LABEL_174;
                v92 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v92) = v92 & 0xDF;
                *(_DWORD *)(v51 + 3930828) = v92;
                *(_BYTE *)(v51 + 3930884) = 0;
                break;
              case '<':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70475));
                *(_DWORD *)(v51 + 3930852) = 0;
                *(_DWORD *)(v51 + 3930856) = 0;
                *(_BYTE *)(v51 + 3930884) = 6;
                v83 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v83) = v83 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v83;
                break;
              case '=':
              case '|':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70013));
                *(_BYTE *)(v51 + 3930884) = 14;
                v72 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v72) = v72 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v72;
                break;
              case '>':
                if ( v111 > 0 && *(_BYTE *)(v51 + 3930212) == 3 )
                {
                  set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70475));
                  *(_DWORD *)(v51 + 3930852) = 0;
                  *(_DWORD *)(v51 + 3930856) = 0;
                  *(_BYTE *)(v51 + 3930884) = 9;
                  v77 = *(_DWORD *)(v51 + 3930828);
                  LOBYTE(v77) = v77 | 0x20;
                  *(_DWORD *)(v51 + 3930828) = v77;
                  *(_BYTE *)(v51 + 3930212) = 12;
                }
                else
                {
                  set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70475));
                  *(_DWORD *)(v51 + 3930852) = 0;
                  *(_DWORD *)(v51 + 3930856) = 0;
                  *(_BYTE *)(v51 + 3930884) = 3;
                  v78 = *(_DWORD *)(v51 + 3930828);
                  LOBYTE(v78) = v78 | 0x20;
                  *(_DWORD *)(v51 + 3930828) = v78;
                }
                break;
              case '@':
                *(_BYTE *)(v51 + 3930884) = 0;
                v59 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v59) = v59 & 0xDF;
                *(_DWORD *)(v51 + 3930828) = v59;
                switch_track_mirror(this);
                break;
              case 'F':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70349));
                *(_BYTE *)(v51 + 3930884) = 19;
                v64 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v64) = v64 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v64;
                break;
              case 'G':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70349));
                *(_BYTE *)(v51 + 3930884) = 17;
                v60 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v60) = v60 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v60;
                break;
              case 'J':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70349));
                *(_BYTE *)(v51 + 3930884) = 25;
                v70 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v70) = v70 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v70;
                break;
              case 'M':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70349));
                *(_BYTE *)(v51 + 3930884) = 18;
                v63 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v63) = v63 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v63;
                break;
              case 'P':
              case 'p':
                if ( v55 == 80 )
                {
                  *(_BYTE *)(v51 + 3930884) = 30;
                }
                else if ( v55 == 112 )
                {
                  *(_BYTE *)(v51 + 3930884) = 29;
                }
                v85 = *(int *)((char *)&unk_5CCB68 + (_DWORD)v42);
                if ( *(_BYTE *)(this + 2) )
                  v86 = 336 * v85 + this + 16722364;
                else
                  v86 = 336 * v85 + this + 16722196;
                *(_DWORD *)(v51 + 3930880) = v86;
                *(_DWORD *)(v51 + 3930828) &= ~0x20u;
                if ( !v110 )
                {
                  v110 = 1;
                  set_bod_object((_DWORD *)(v51 + 3930824), *(_DWORD *)(*(_DWORD *)(v51 + 3930880) + 36));
                  *(_DWORD *)(v51 + 3930828) |= 0x20u;
                  set_bod_object((char *)&unk_5CCB78 + (_DWORD)v42, *(_DWORD *)(*(_DWORD *)(v51 + 3930880) + 132));
                  *(int *)((char *)&unk_5CCB7C + (_DWORD)v42) |= 0x20u;
                  *(int *)((char *)&unk_5CCB74 + (_DWORD)v42) = *(_DWORD *)(v112 + 16404);
                  v87 = 0;
                  if ( *(int *)(*(_DWORD *)(v51 + 3930880) + 72) > 0 )
                  {
                    v88 = (int *)((char *)byte_5CCAC8 + (_DWORD)v42);
                    do
                    {
                      v89 = *v88;
                      if ( (*v88 & 0x40) != 0 )
                      {
                        LOBYTE(v89) = v89 | 0x80;
                        *v88 = v89;
                        v88[42] = v53;
                      }
                      else
                      {
                        LOBYTE(v89) = v89 | 0x40;
                        *v88 = v89;
                        v88[41] = v53;
                      }
                      ++v87;
                      v88 += 61;
                    }
                    while ( v87 < *(_DWORD *)(*(_DWORD *)(v51 + 3930880) + 72) );
                  }
                }
                break;
              case 'R':
                *(_BYTE *)(v51 + 3930884) = 35;
                v57 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v57) = v57 & 0xDF;
                *(_DWORD *)(v51 + 3930828) = v57;
                break;
              case '[':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70461));
                *(_DWORD *)(v51 + 3930852) = 0;
                *(_DWORD *)(v51 + 3930856) = 0;
                *(_BYTE *)(v51 + 3930884) = 5;
                v84 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v84) = v84 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v84;
                break;
              case '_':
LABEL_174:
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70349));
                *(_BYTE *)(v51 + 3930884) = 15;
                v91 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v91) = v91 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v91;
                break;
              case 'o':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70349));
                *(_BYTE *)(v51 + 3930884) = 16;
                v62 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v62) = v62 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v62;
                break;
              case 's':
                set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70125));
                *(_BYTE *)(v51 + 3930884) = 33;
                v66 = *(_DWORD *)(v51 + 3930828);
                LOBYTE(v66) = v66 | 0x20;
                *(_DWORD *)(v51 + 3930828) = v66;
                break;
              case '{':
                if ( v111 > 0 && *(_BYTE *)(v51 + 3930212) == 3 )
                {
                  set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70461));
                  *(_DWORD *)(v51 + 3930852) = 0;
                  *(_DWORD *)(v51 + 3930856) = 0;
                  *(_BYTE *)(v51 + 3930884) = 8;
                  v81 = *(_DWORD *)(v51 + 3930828);
                  LOBYTE(v81) = v81 | 0x20;
                  *(_DWORD *)(v51 + 3930828) = v81;
                  *(_BYTE *)(v51 + 3930212) = 11;
                }
                else
                {
                  set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70461));
                  *(_DWORD *)(v51 + 3930852) = 0;
                  *(_DWORD *)(v51 + 3930856) = 0;
                  *(_BYTE *)(v51 + 3930884) = 2;
                  v82 = *(_DWORD *)(v51 + 3930828);
                  LOBYTE(v82) = v82 | 0x20;
                  *(_DWORD *)(v51 + 3930828) = v82;
                }
                break;
              case '}':
                if ( v111 > 0 && *(_BYTE *)(v51 + 3930212) == 3 )
                {
                  set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70489));
                  *(_DWORD *)(v51 + 3930852) = 0;
                  *(_DWORD *)(v51 + 3930856) = 0;
                  *(_BYTE *)(v51 + 3930884) = 10;
                  v79 = *(_DWORD *)(v51 + 3930828);
                  LOBYTE(v79) = v79 | 0x20;
                  *(_DWORD *)(v51 + 3930828) = v79;
                  *(_BYTE *)(v51 + 3930212) = 13;
                }
                else
                {
                  set_bod_object((_DWORD *)(v51 + 3930824), *((_DWORD *)MEMORY[0x4DF904] + 70489));
                  *(_DWORD *)(v51 + 3930852) = 0;
                  *(_DWORD *)(v51 + 3930856) = 0;
                  *(_BYTE *)(v51 + 3930884) = 4;
                  v80 = *(_DWORD *)(v51 + 3930828);
                  LOBYTE(v80) = v80 | 0x20;
                  *(_DWORD *)(v51 + 3930828) = v80;
                }
                break;
              default:
                normalize_segment_glyph_for_track_flags(this, *v54, v111, 1);
                sub_449C00();
                break;
            }
            v93 = (float *)(v51 + 3930840);
            *(_DWORD *)(v51 + 3930848) = 0;
            *(_DWORD *)(v51 + 3930844) = 0;
            *(_DWORD *)(v51 + 3930840) = 0;
            *(int *)((char *)&unk_5CCB90 + (_DWORD)v42) = 0;
            *(int *)((char *)&unk_5CCB8C + (_DWORD)v42) = 0;
            *(int *)((char *)&unk_5CCB88 + (_DWORD)v42) = 0;
            v94 = *(_BYTE *)(v51 + 3930884);
            if ( v94 == 29 || v94 == 30 )
            {
              *v93 = 0.0;
              v96 = (double)v111 + 0.5;
              v119 = v96;
              v97 = v96 - 0.5;
              *(float *)(v51 + 3930848) = v97;
              if ( (byte_4DF934 & 0x20) != 0 )
              {
                *(int *)((char *)&unk_5CCB88 + (_DWORD)v42) = 0;
                v42[1520356] = v97;
                v98 = get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v124);
                v99 = (_DWORD *)((char *)&unk_5CCBA0 + (_DWORD)v42);
                *v99 = *v98;
                v99[1] = v98[1];
                v99[2] = v98[2];
                v99[3] = v98[3];
                set_object_color(*(_DWORD **)((char *)&unk_5CCB9C + (_DWORD)v42), *v98, v98[1], v98[2], v98[3]);
              }
              else
              {
                v100 = *(int *)((char *)&unk_5CCB7C + (_DWORD)v42);
                LOBYTE(v100) = v100 & 0xDF;
                *(int *)((char *)&unk_5CCB7C + (_DWORD)v42) = v100;
              }
            }
            else
            {
              *v93 = (double)v116 - 4.0 + 0.5;
              *(_DWORD *)(v51 + 3930844) = 0;
              v95 = *(_BYTE *)(v51 + 3930884);
              if ( v95 == 8 || v95 == 9 || v95 == 10 )
                *(_DWORD *)(v51 + 3930844) = 1056964608;
              v119 = (double)v111 + 0.5;
              *(float *)(v51 + 3930848) = v119;
            }
            if ( v111 < 4 && *(_DWORD *)(this + 64) != 2 )
              *(_DWORD *)(v51 + 3930844) = *(_DWORD *)(*(_DWORD *)(this + 16734380) + 52);
            if ( *(_BYTE *)(v51 + 3930884) == 28 )
              *(float *)(v51 + 3930844) = *(float *)(v51 + 3930844) - 0.029999999;
            v101 = *(_BYTE *)(v51 + 3930884);
            if ( v101 == 1
              || v101 == 21
              || v101 == 20
              || v101 == 33
              || v101 == 34
              || v101 == 15
              || v101 == 16
              || v101 == 23
              || v101 == 24
              || v101 == 25
              || v101 == 26
              || v101 == 27
              || v101 == 18
              || v101 == 19
              || v101 == 17 )
            {
              *(float *)(v51 + 3930852) = (double)(8 - v116) * 0.125;
              *(float *)(v51 + 3930856) = (double)(v111 % 8) * 0.125;
            }
            if ( *(_BYTE *)(v51 + 3930884) == 31 )
              *v93 = *v93 * 1.1;
            if ( *(_BYTE *)(v51 + 3930884) == 22 )
            {
              if ( *(_DWORD *)(this + 64) != 3 || (*(_DWORD *)(this + 76) & 0x400) != 0 )
                *(_DWORD *)(v51 + 3930844) = -1069547520;
              *(float *)(v51 + 3930848) = v119;
            }
            v102 = (_DWORD *)(v51 + 3930892);
            v103 = 4;
            do
            {
              v104 = (_DWORD *)*v102;
              if ( *v102 )
              {
                v104[6] = 0;
                v104[5] = 0;
                v104[4] = 0;
                v105 = (_DWORD *)(*v102 + 16);
                *v105 = *(_DWORD *)v93;
                v105[1] = *(_DWORD *)(v51 + 3930844);
                v105[2] = *(_DWORD *)(v51 + 3930848);
              }
              ++v102;
              --v103;
            }
            while ( v103 );
            ++v116;
          }
          while ( v116 < 8 );
          v22 = v111 + 1;
          ++v114;
          v106 = v111 + 1 < *(_DWORD *)(this + 84);
          v111 = v22;
          v23 = v22;
          v24 = this;
        }
        while ( v106 );
      }
      if ( *(_DWORD *)(v24 + 64) == 3 )
      {
        LOBYTE(v22) = v109;
        if ( v109 )
          continue;
      }
      ++v117;
    }
    while ( v23 < *(_DWORD *)(v24 + 84) );
  }
  return v22;
}

