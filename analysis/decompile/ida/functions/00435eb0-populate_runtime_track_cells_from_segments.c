/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: populate_runtime_track_cells_from_segments @ 0x435eb0 */
/* selector: populate_runtime_track_cells_from_segments */

// Copies authored segment rows into the generated runtime grid, seeds Goldy's visible life stock to 3 before `initialize_subgoldy` runs, and seeds the course row bounds: non-random levels use the final `Last:` block boundary while the mode-1 random branch keeps the authored `Length:` lane scaled by the challenge scalar before subtracting the final `Last:` block rows.
void __thiscall populate_runtime_track_cells_from_segments(Game *game)
{
  double v1; // st7
  int runtime_build_seed; // esi
  int32_t level_mode; // eax
  int32_t v5; // eax
  int v6; // eax
  int v7; // eax
  int32_t v8; // eax
  int v9; // ecx
  int v10; // esi
  int32_t v11; // eax
  uint8_t *v12; // ecx
  _DWORD *v13; // edi
  int v14; // ebp
  uint8_t *v15; // esi
  int v16; // ecx
  int v17; // edx
  uint8_t *v18; // eax
  int v19; // ecx
  uint8_t *v20; // esi
  int32_t v21; // eax
  uint8_t *v22; // ecx
  int32_t v23; // edi
  int v25; // esi
  double v26; // st7
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // ecx
  int32_t v31; // eax
  int v32; // edx
  int v33; // eax
  int v34; // esi
  int v35; // ecx
  int v36; // eax
  _DWORD *v37; // esi
  char *v38; // eax
  int v39; // ecx
  char *v40; // eax
  int v41; // ecx
  int v43; // eax
  _DWORD *v44; // edx
  int v46; // eax
  char *v47; // eax
  _DWORD *v48; // ecx
  int v49; // eax
  int v50; // eax
  int v51; // ebp
  int v53; // eax
  char *v54; // edi
  char *v55; // ebp
  char v56; // al
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
  int v73; // eax
  int v74; // ecx
  unsigned int v75; // ebp
  bool v76; // zf
  unsigned int v77; // eax
  int v78; // eax
  int v79; // eax
  int v80; // eax
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // eax
  int v85; // eax
  int v86; // ecx
  uint8_t *v87; // ecx
  int v88; // edx
  char *v89; // ecx
  int v90; // eax
  int v91; // ecx
  int v95; // eax
  int v96; // eax
  char v98; // al
  char v100; // al
  _DWORD *track_skirt_color; // eax
  _DWORD *v104; // ecx
  int v105; // eax
  char v107; // al
  _DWORD *v111; // ecx
  int v112; // edx
  _DWORD *v113; // eax
  _DWORD *v114; // eax
  bool v115; // cc
  float v116; // [esp+0h] [ebp-5Ch]
  char v117; // [esp+1Ah] [ebp-42h]
  char v118; // [esp+1Bh] [ebp-41h]
  int32_t v119; // [esp+1Ch] [ebp-40h]
  int v120; // [esp+20h] [ebp-3Ch]
  int v122; // [esp+28h] [ebp-34h]
  int v123; // [esp+2Ch] [ebp-30h]
  int v124; // [esp+2Ch] [ebp-30h]
  int v125; // [esp+30h] [ebp-2Ch]
  uint8_t *v126; // [esp+34h] [ebp-28h]
  int v127; // [esp+34h] [ebp-28h]
  float v128; // [esp+34h] [ebp-28h]
  int v129; // [esp+38h] [ebp-24h]
  int v130; // [esp+3Ch] [ebp-20h]
  int32_t v131; // [esp+40h] [ebp-1Ch]
  char v132; // [esp+40h] [ebp-1Ch]
  int v133; // [esp+44h] [ebp-18h]
  int v134; // [esp+44h] [ebp-18h]
  int v135[4]; // [esp+4Ch] [ebp-10h] BYREF

  _EBX = game;
  if ( game->selected_level_record_active )
  {
    runtime_build_seed = game->selected_level_record->runtime_build_seed;
  }
  else
  {
    level_mode = game->level_mode;
    if ( level_mode == 4 || level_mode == 7 )
    {
      runtime_build_seed = 0;
    }
    else
    {
      v1 = random_float_below(32768.0);
      runtime_build_seed = _ftol(v1);
    }
  }
  v5 = _EBX->level_mode;
  if ( v5 )
  {
    v6 = v5 - 1;
    if ( v6 )
    {
      if ( v6 == 3 )
        initialize_high_score_entry(
          (char *)&_EBX->_pad_74622[16114926],
          runtime_build_seed,
          _EBX->level_mode_arg,
          *(_DWORD *)&_EBX->_pad_00[48],
          _EBX->runtime_flags,
          2,
          _EBX->level_mode_arg);
    }
    else
    {
      initialize_high_score_entry(
        (char *)&_EBX->_pad_74622[16114926],
        runtime_build_seed,
        _EBX->level_mode_arg,
        *(_DWORD *)&_EBX->_pad_00[48],
        _EBX->runtime_flags,
        1,
        _EBX->level_mode_arg);
    }
  }
  else
  {
    initialize_high_score_entry(
      (char *)&_EBX->_pad_74622[16114926],
      runtime_build_seed,
      _EBX->level_mode_arg,
      *(_DWORD *)&_EBX->_pad_00[48],
      _EBX->runtime_flags,
      0,
      _EBX->level_mode_arg);
  }
  v7 = *(_DWORD *)&_EBX->_pad_ff25e8[2615776];
  _EBX->replay_update_cursor = 0;
  if ( v7 == 3 )
  {
    *(_DWORD *)&_EBX->_pad_ff25e8[2615776] = 1;
    *(_DWORD *)&_EBX->_pad_74622[3437606] = 0;
    clear_subgoldy_score_buckets((int)&_EBX->_pad_74622[3436866]);
    *(_DWORD *)&_EBX->_pad_74622[3454082] = 3;
  }
  zero_timer_counters(&_EBX->_pad_74622[3437610]);
  *(_DWORD *)&_EBX->_pad_74622[3437634] = 0;
  *(_DWORD *)&_EBX->_pad_74622[3437642] = 0;
  set_math_random_seed(runtime_build_seed);
  select_level_track_texture_set((int *)MEMORY[0x4DF904] + 713, *(_DWORD *)&_EBX->_pad_74622[1293250]);
  v8 = _EBX->level_mode;
  if ( !v8 || v8 == 7 || v8 == 4 || v8 == 1 )
  {
    _EBX->first_block_row_count = *(_DWORD *)&_EBX->_pad_74622[1259226];
    v131 = *(_DWORD *)&_EBX->_pad_74622[1293078];
    _EBX->runtime_row_count = v131;
    if ( v8 == 1 )
    {
      __asm
      {
        fld     dword ptr [ebx+34h]
        fmul    ds:flt_497550
        fadd    ds:flt_49754C
        fimul   [esp+54h+var_1C]
      }
      _EBX->runtime_row_count = _ftol(v1);
    }
    if ( !_EBX->_pad_74622[1293082] )
    {
      v11 = 0;
      _EBX->runtime_row_count = *(_DWORD *)&_EBX->_pad_74622[1259226] + *(_DWORD *)&_EBX->_pad_74622[1276154];
      if ( _EBX->level_segment_count > 0 )
      {
        v12 = &_EBX->_pad_a878[4];
        do
        {
          ++v11;
          _EBX->runtime_row_count += *(_DWORD *)v12;
          v12 += 16928;
        }
        while ( v11 < _EBX->level_segment_count );
      }
      v129 = 0;
    }
    _EBX->completion_row_start = _EBX->runtime_row_count - *(_DWORD *)&_EBX->_pad_74622[1276154];
    if ( _EBX->runtime_row_count >= 3100 )
      report_errorf("Track (%s) too long, Maximum Length %i", (const char *)&_EBX->_pad_74622[1293102], 3100);
  }
  else if ( v8 == 3 )
  {
    _EBX->first_block_row_count = *(_DWORD *)&_EBX->_pad_74622[1259226];
    v9 = 16;
    _EBX->runtime_row_count = *(_DWORD *)&_EBX->_pad_74622[1259226] + *(_DWORD *)&_EBX->_pad_74622[1276154];
    do
    {
      v10 = *(_DWORD *)&_EBX->_pad_a878[4] + _EBX->runtime_row_count;
      --v9;
      _EBX->runtime_row_count = v10;
    }
    while ( v9 );
    v129 = 0;
    _EBX->completion_row_start = v10 - *(_DWORD *)&_EBX->_pad_74622[1276154];
    _EBX->completion_row_start = v10 - *(_DWORD *)&_EBX->_pad_74622[1276154];
  }
  _EBX->_pad_00[2] = 0;
  *(_DWORD *)&_EBX->_pad_00[4] = 0;
  v130 = 0;
  v117 = 0;
  v125 = 0;
  _EBX->_pad_74622[3437826] = 0;
  v126 = &_EBX->_pad_74622[3454186];
  v13 = (_DWORD *)((char *)&unk_5CCB5C + (_DWORD)_EBX);
  v123 = 3200;
  do
  {
    v14 = 8;
    *(v13 - 37) = 0;
    v13[6] = 0;
    v13[3] = 0;
    v13[21] = 0;
    v13[4] = 0;
    v13[1] = 0;
    *v13 = 0;
    *(v13 - 1) = 0;
    v13[2] = 0;
    v13[22] = 0;
    v13[23] = 0;
    v15 = v126 - 4;
    do
    {
      v16 = *(_DWORD *)v15;
      BYTE1(v16) = BYTE1(*(_DWORD *)v15) & 0x5F;
      *(_DWORD *)v15 = v16;
      *(v15 - 3) = 0;
      *(_WORD *)v15 = 0;
      *(_DWORD *)v15 &= 0xFFFFAFA7;
      *(_WORD *)v15 = 0;
      v17 = *((_DWORD *)v15 - 15);
      LOBYTE(v17) = v17 & 0x7F;
      *((_DWORD *)v15 - 15) = v17;
      set_color_white((_DWORD *)v15 - 6);
      v15 += 84;
      --v14;
    }
    while ( v14 );
    v18 = v126;
    v19 = 8;
    do
    {
      v20 = v18;
      v18 += 84;
      --v19;
      *(_DWORD *)v20 = 0;
      *((_DWORD *)v20 + 1) = 0;
      *((_DWORD *)v20 + 2) = 0;
      *((_DWORD *)v20 + 3) = 0;
    }
    while ( v19 );
    v126 = v18;
    v13 += 61;
    --v123;
  }
  while ( v123 );
  if ( _EBX->_pad_74622[1293082] == 1 )
  {
    v21 = 0;
    if ( _EBX->level_segment_count > 0 )
    {
      v22 = &_EBX->_pad_a878[8];
      do
      {
        *v22 = 0;
        ++v21;
        v22 += 16928;
      }
      while ( v21 < _EBX->level_segment_count );
    }
  }
  v119 = 0;
  if ( _EBX->runtime_row_count > 0 )
  {
    v23 = 0;
    _EBP = (int)game;
    do
    {
      if ( v23 )
      {
        if ( v23 != *(_DWORD *)(_EBP + 88) || *(_BYTE *)(_EBP + 1769788) )
        {
          *(_DWORD *)(_EBP + 72) = 1065353216;
          if ( *(_BYTE *)(_EBP + 1769788) == 1 )
          {
            if ( *(_DWORD *)(_EBP + 64) == 1 )
            {
              __asm
              {
                fld     dword ptr [ebp+34h]
                fmul    ds:flt_49726C
              }
              __asm
              {
                fadd    ds:flt_497258
                fimul   dword ptr [ebp+0A874h]
              }
            }
            else
            {
              __asm { fild    dword ptr [ebp+0A874h] }
            }
            __asm { fstp    [esp+5Ch+var_5C]; float }
            v26 = random_float_below(v116);
            v127 = _ftol(v26);
            __asm
            {
              fild    [esp+54h+var_28]
              fmul    dword ptr [ebp+48h]
            }
            v25 = 16928 * _ftol(v26) + _EBP + 43128;
            v120 = v25;
            *(_BYTE *)(v25 + 8) = 1;
          }
          else
          {
            v27 = v129;
            v28 = v129++;
            v25 = 32 * (v27 + 16 * (v27 + 32 * v28)) + _EBP + 43128;
            v120 = v25;
          }
        }
        else
        {
          v25 = _EBP + 1752856;
          v117 = 1;
          v120 = _EBP + 1752856;
          *(_DWORD *)(_EBP + 1752856) = v23;
        }
      }
      else
      {
        v25 = _EBP + 1735928;
        v117 = 1;
        v120 = _EBP + 1735928;
        *(_DWORD *)(_EBP + 1735928) = 0;
      }
      switch_track_mirror(_EBP);
      v29 = *(_DWORD *)(v25 + 4);
      *(_DWORD *)v25 = v23;
      if ( v29 < 0 )
        report_errorf(aNegativeSegmen);
      v122 = 0;
      if ( v23 < *(_DWORD *)(_EBP + 84) )
      {
        do
        {
          if ( v122 >= *(_DWORD *)(v120 + 4) )
            break;
          v30 = *(_DWORD *)(_EBP + 64);
          if ( v30 == 2 || (v31 = *(_DWORD *)(_EBP + 88), v23 < v31) )
          {
            v32 = v120;
          }
          else
          {
            if ( !v30 || v30 == 4 || v30 == 1 || v30 == 7 || (v32 = _EBP + 1786896, v30 == 3) )
              v32 = _EBP + 1752856;
            v120 = v32;
            if ( v23 == v31 )
              v122 = 0;
          }
          if ( v30 != 2 )
          {
            v33 = *(_DWORD *)(v32 + 4);
            v34 = *(_DWORD *)(_EBP + 88);
            if ( v23 + v33 - v122 <= v34 )
            {
              v32 = v120;
            }
            else
            {
              v32 = v120;
              if ( v120 != _EBP + 1786896
                && v120 != _EBP + 1820752
                && v120 != _EBP + 1837680
                && (!v30 || v30 == 4 || v30 == 1 || v30 == 7 || v30 == 3)
                && v120 != _EBP + 1752856 )
              {
                v35 = *(_DWORD *)(_EBP + 84);
                v36 = v23 + v33 - v34 - v122;
                *(_DWORD *)(_EBP + 88) = v36 + v34;
                *(_DWORD *)(_EBP + 84) = v36 + v35;
              }
            }
          }
          if ( *(_BYTE *)(_EBP + 2) )
            *(_DWORD *)&byte_5CCAC8[244 * v23 + _EBP] |= 0x20u;
          v37 = (_DWORD *)(v32 + 56 * v122);
          if ( (v37[517] & 0x100) != 0 )
          {
            v38 = &byte_5CCAC8[244 * v23 + _EBP];
            v39 = *(_DWORD *)v38;
            BYTE1(v39) = BYTE1(*(_DWORD *)v38) | 1;
            *(_DWORD *)v38 = v39;
          }
          if ( (BYTE1(v37[517]) & 0x80u) != 0 )
          {
            v40 = &byte_5CCAC8[244 * v23 + _EBP];
            v41 = *(_DWORD *)v40;
            BYTE1(v41) = BYTE1(*(_DWORD *)v40) | 0x80;
            *(_DWORD *)v40 = v41;
          }
          _EBX = _EBP + 244 * v23;
          *(_DWORD *)((char *)&unk_5CCBB4 + _EBX) = v32;
          *(int *)((char *)unk_5CCBB8 + _EBX) = v125;
          if ( (v37[517] & 2) != 0 )
          {
            v43 = *(_DWORD *)&byte_5CCAC8[_EBX];
            LOBYTE(v43) = v43 | 2;
            *(_DWORD *)&byte_5CCAC8[_EBX] = v43;
            set_bod_object((char *)&unk_5CCACC + _EBX, *((_DWORD *)MEMORY[0x4DF904] + 47 * v37[522] + 74635));
            set_matrix_identity((TransformMatrix *)((char *)&unk_5CCB04 + _EBX));
            v44 = (_DWORD *)((char *)&unk_5CCB34 + _EBX);
            __asm { fild    [esp+54h+var_40] }
            *v44 = v37[523];
            v44[1] = v37[524];
            v44[2] = v37[525];
            __asm
            {
              fadd    dword ptr [ebx+5CCB3Ch]
              fstp    dword ptr [ebx+5CCB3Ch]
            }
            *(float *)(_EBX + 6081340) = _ET1;
            if ( (v37[517] & 8) != 0 )
            {
              v46 = *(_DWORD *)&byte_5CCAC8[_EBX];
              LOBYTE(v46) = v46 | 8;
              *(_DWORD *)&byte_5CCAC8[_EBX] = v46;
              v47 = (char *)&unk_5CCB4C + _EBX;
              *(_DWORD *)((char *)&unk_5CCB4C + _EBX) = v37[526];
              *((_DWORD *)v47 + 1) = v37[527];
              *((_DWORD *)v47 + 2) = v37[528];
            }
            else
            {
              *(_DWORD *)((char *)&unk_5CCB54 + _EBX) = 0;
              *(_DWORD *)((char *)&unk_5CCB50 + _EBX) = 0;
              *(_DWORD *)((char *)&unk_5CCB4C + _EBX) = 0;
            }
            v32 = v120;
          }
          if ( (v37[517] & 1) != 0 )
          {
            *(_DWORD *)&byte_5CCAC8[_EBX] |= 0x4001u;
            v48 = (_DWORD *)((char *)&unk_5CCB58 + _EBX);
            *(_DWORD *)((char *)&unk_5CCB64 + _EBX) = *(_DWORD *)(v32 + 56 * (v122 + 37));
            *v48 = v37[519];
            v48[1] = v37[520];
            v48[2] = v37[521];
          }
          if ( (v37[517] & 8) != 0 )
          {
            v49 = *(_DWORD *)&byte_5CCAC8[_EBX];
            LOBYTE(v49) = v49 | 8;
            *(_DWORD *)&byte_5CCAC8[_EBX] = v49;
            *(_DWORD *)((char *)&unk_5CCB68 + _EBX) = v37[529];
          }
          if ( (v37[517] & 4) != 0 )
          {
            v50 = *(_DWORD *)&byte_5CCAC8[_EBX];
            LOBYTE(v50) = v50 | 4;
            *(_DWORD *)&byte_5CCAC8[_EBX] = v50;
          }
          if ( (v37[517] & 0x200) != 0 )
            *(_DWORD *)&byte_5CCAC8[_EBX] |= 0x200u;
          if ( (v37[517] & 0x400) != 0 )
            *(_DWORD *)&byte_5CCAC8[_EBX] |= 0x400u;
          if ( (v37[517] & 0x2000) != 0 )
            *(_DWORD *)&byte_5CCAC8[_EBX] |= 0x2000u;
          if ( (v37[517] & 0x800) != 0 )
            *(_DWORD *)&byte_5CCAC8[_EBX] |= 0x800u;
          if ( (v37[517] & 0x1000) != 0 )
            *(_DWORD *)&byte_5CCAC8[_EBX] |= 0x1000u;
          v118 = 0;
          v124 = 0;
          *(_DWORD *)(_EBP + 4 * (v23 + 20 * (3 * v23 + 74772) + 24924)) = v37[530];
          do
          {
            if ( game->_pad_00[2] )
              v51 = 7 - v124;
            else
              v51 = v124;
            _ESI = (char *)game + 672 * v119 + 84 * v124;
            v53 = *((_DWORD *)_ESI + 982722);
            LOBYTE(v53) = v53 & 0xE0;
            *((_DWORD *)_ESI + 982722) = v124 & 7 ^ v53;
            *((_DWORD *)_ESI + 982723) = 0;
            *((_DWORD *)_ESI + 982724) = 0;
            *((_DWORD *)_ESI + 982725) = 0;
            *((_DWORD *)_ESI + 982726) = 0;
            if ( v119 < game->first_block_row_count || (v132 = 0, v119 >= game->completion_row_start) )
              v132 = 1;
            v54 = _ESI + 3930824;
            set_bod_object((_DWORD *)_ESI + 982706, 0);
            v55 = (char *)(v120 + v122 + (v51 << 8) + 20);
            v56 = normalize_segment_glyph_for_track_flags((int)game, *v55, v119, v132);
            switch ( v56 )
            {
              case ' ':
                _ESI[3930884] = 0;
                v57 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v57) = v57 & 0xDF;
                *((_DWORD *)_ESI + 982707) = v57;
                break;
              case '#':
                _ESI[3930884] = 32;
                v59 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v59) = v59 & 0xDF;
                *((_DWORD *)_ESI + 982707) = v59;
                break;
              case '$':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
                _ESI[3930884] = 23;
                v62 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v62) = v62 | 0x20;
                *((_DWORD *)_ESI + 982707) = v62;
                break;
              case '&':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70125));
                _ESI[3930884] = 34;
                v68 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v68) = v68 | 0x20;
                *((_DWORD *)_ESI + 982707) = v68;
                break;
              case '(':
                v74 = v130 + 1;
                v75 = *((_DWORD *)_ESI + 982707) & 0xFFFFFFDF;
                v76 = v130++ == 14;
                *((_DWORD *)_ESI + 982707) = v75;
                v77 = v75;
                if ( v76 )
                {
                  v130 = 0;
                  _ESI[3930884] = 22;
                }
                else
                {
                  if ( v74 == 8 )
                  {
                    set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 69943));
                    *((_DWORD *)_ESI + 982707) |= 0x20u;
                    store_color4f(
                      (Color4f *)&game->_pad_74622[672 * v119 + 3454158 + 84 * v124],
                      1.0,
                      1.0,
                      1.0,
                      0.99900001);
                  }
                  else
                  {
                    LOBYTE(v77) = v75 & 0xDF;
                    *((_DWORD *)_ESI + 982707) = v77;
                  }
                  _ESI[3930884] = 22;
                }
                break;
              case '+':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
                _ESI[3930884] = 24;
                v70 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v70) = v70 | 0x20;
                *((_DWORD *)_ESI + 982707) = v70;
                break;
              case ',':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 69705));
                _ESI[3930884] = 28;
                v69 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v69) = v69 | 0x20;
                *((_DWORD *)_ESI + 982707) = v69;
                break;
              case '-':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70125));
                _ESI[3930884] = 21;
                v72 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v72) = v72 | 0x20;
                *((_DWORD *)_ESI + 982707) = v72;
                break;
              case '.':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70125));
                _ESI[3930884] = 1;
                v66 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v66) = v66 | 0x20;
                *((_DWORD *)_ESI + 982707) = v66;
                break;
              case '0':
                if ( game->level_mode == 1 )
                {
                  __asm { fild    [esp+54h+var_30] }
                  v91 = *(_DWORD *)&byte_5CCAC8[_EBX];
                  BYTE1(v91) &= ~0x40u;
                  __asm { fsub    ds:flt_497210 }
                  *(_DWORD *)&byte_5CCAC8[_EBX] = v91 | 1;
                  *(_DWORD *)((char *)&unk_5CCB64 + _EBX) = 0;
                  __asm
                  {
                    fadd    ds:flt_497228
                    fstp    dword ptr [ebx+5CCB58h]
                  }
                  *(float *)(_EBX + 6081368) = _ET1;
                  __asm { fild    [esp+54h+var_40] }
                  *(_DWORD *)((char *)&unk_5CCB5C + _EBX) = *((_DWORD *)_ESI + 982711);
                  __asm
                  {
                    fadd    ds:flt_497228
                    fstp    dword ptr [ebx+5CCB60h]
                  }
                  *(float *)(_EBX + 6081376) = _ET1;
                  if ( game->_pad_00[2] )
                  {
                    __asm
                    {
                      fld     dword ptr [ebx+5CCB58h]
                      fmul    ds:flt_497214
                      fstp    dword ptr [ebx+5CCB58h]
                    }
                    *(float *)(_EBX + 6081368) = _ET1;
                  }
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
                if ( (byte_5CCAC8[_EBX] & 0xC0) == 0 )
                  goto LABEL_174;
                v96 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v96) = v96 & 0xDF;
                *((_DWORD *)_ESI + 982707) = v96;
                _ESI[3930884] = 0;
                break;
              case '<':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70475));
                *((_DWORD *)_ESI + 982713) = 0;
                *((_DWORD *)_ESI + 982714) = 0;
                _ESI[3930884] = 6;
                v84 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v84) = v84 | 0x20;
                *((_DWORD *)_ESI + 982707) = v84;
                break;
              case '=':
              case '|':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70013));
                _ESI[3930884] = 14;
                v73 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v73) = v73 | 0x20;
                *((_DWORD *)_ESI + 982707) = v73;
                break;
              case '>':
                if ( v119 > 0 && _ESI[3930212] == 3 )
                {
                  set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70475));
                  *((_DWORD *)_ESI + 982713) = 0;
                  *((_DWORD *)_ESI + 982714) = 0;
                  _ESI[3930884] = 9;
                  v78 = *((_DWORD *)_ESI + 982707);
                  LOBYTE(v78) = v78 | 0x20;
                  *((_DWORD *)_ESI + 982707) = v78;
                  _ESI[3930212] = 12;
                }
                else
                {
                  set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70475));
                  *((_DWORD *)_ESI + 982713) = 0;
                  *((_DWORD *)_ESI + 982714) = 0;
                  _ESI[3930884] = 3;
                  v79 = *((_DWORD *)_ESI + 982707);
                  LOBYTE(v79) = v79 | 0x20;
                  *((_DWORD *)_ESI + 982707) = v79;
                }
                break;
              case '@':
                _ESI[3930884] = 0;
                v60 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v60) = v60 & 0xDF;
                *((_DWORD *)_ESI + 982707) = v60;
                switch_track_mirror((int)game);
                break;
              case 'F':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
                _ESI[3930884] = 19;
                v65 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v65) = v65 | 0x20;
                *((_DWORD *)_ESI + 982707) = v65;
                break;
              case 'G':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
                _ESI[3930884] = 17;
                v61 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v61) = v61 | 0x20;
                *((_DWORD *)_ESI + 982707) = v61;
                break;
              case 'J':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
                _ESI[3930884] = 25;
                v71 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v71) = v71 | 0x20;
                *((_DWORD *)_ESI + 982707) = v71;
                break;
              case 'M':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
                _ESI[3930884] = 18;
                v64 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v64) = v64 | 0x20;
                *((_DWORD *)_ESI + 982707) = v64;
                break;
              case 'P':
              case 'p':
                if ( v56 == 80 )
                {
                  _ESI[3930884] = 30;
                }
                else if ( v56 == 112 )
                {
                  _ESI[3930884] = 29;
                }
                v86 = *(_DWORD *)((char *)&unk_5CCB68 + _EBX);
                if ( game->_pad_00[2] )
                  v87 = &game->_pad_ff25e8[336 * v86 + 980];
                else
                  v87 = &game->_pad_ff25e8[336 * v86 + 812];
                *((_DWORD *)_ESI + 982720) = v87;
                *((_DWORD *)_ESI + 982707) &= ~0x20u;
                if ( !v118 )
                {
                  v118 = 1;
                  set_bod_object((_DWORD *)_ESI + 982706, *(_DWORD *)(*((_DWORD *)_ESI + 982720) + 36));
                  *((_DWORD *)_ESI + 982707) |= 0x20u;
                  set_bod_object((char *)&unk_5CCB78 + _EBX, *(_DWORD *)(*((_DWORD *)_ESI + 982720) + 132));
                  *(_DWORD *)((char *)&unk_5CCB7C + _EBX) |= 0x20u;
                  *(_DWORD *)((char *)&unk_5CCB74 + _EBX) = *(_DWORD *)(v120 + 16404);
                  v88 = 0;
                  if ( *(int *)(*((_DWORD *)_ESI + 982720) + 72) > 0 )
                  {
                    v89 = &byte_5CCAC8[_EBX];
                    do
                    {
                      v90 = *(_DWORD *)v89;
                      if ( (*(_DWORD *)v89 & 0x40) != 0 )
                      {
                        LOBYTE(v90) = v90 | 0x80;
                        *(_DWORD *)v89 = v90;
                        *((_DWORD *)v89 + 42) = v54;
                      }
                      else
                      {
                        LOBYTE(v90) = v90 | 0x40;
                        *(_DWORD *)v89 = v90;
                        *((_DWORD *)v89 + 41) = v54;
                      }
                      ++v88;
                      v89 += 244;
                    }
                    while ( v88 < *(_DWORD *)(*((_DWORD *)_ESI + 982720) + 72) );
                  }
                }
                break;
              case 'R':
                _ESI[3930884] = 35;
                v58 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v58) = v58 & 0xDF;
                *((_DWORD *)_ESI + 982707) = v58;
                break;
              case '[':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70461));
                *((_DWORD *)_ESI + 982713) = 0;
                *((_DWORD *)_ESI + 982714) = 0;
                _ESI[3930884] = 5;
                v85 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v85) = v85 | 0x20;
                *((_DWORD *)_ESI + 982707) = v85;
                break;
              case '_':
LABEL_174:
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
                _ESI[3930884] = 15;
                v95 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v95) = v95 | 0x20;
                *((_DWORD *)_ESI + 982707) = v95;
                break;
              case 'o':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
                _ESI[3930884] = 16;
                v63 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v63) = v63 | 0x20;
                *((_DWORD *)_ESI + 982707) = v63;
                break;
              case 's':
                set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70125));
                _ESI[3930884] = 33;
                v67 = *((_DWORD *)_ESI + 982707);
                LOBYTE(v67) = v67 | 0x20;
                *((_DWORD *)_ESI + 982707) = v67;
                break;
              case '{':
                if ( v119 > 0 && _ESI[3930212] == 3 )
                {
                  set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70461));
                  *((_DWORD *)_ESI + 982713) = 0;
                  *((_DWORD *)_ESI + 982714) = 0;
                  _ESI[3930884] = 8;
                  v82 = *((_DWORD *)_ESI + 982707);
                  LOBYTE(v82) = v82 | 0x20;
                  *((_DWORD *)_ESI + 982707) = v82;
                  _ESI[3930212] = 11;
                }
                else
                {
                  set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70461));
                  *((_DWORD *)_ESI + 982713) = 0;
                  *((_DWORD *)_ESI + 982714) = 0;
                  _ESI[3930884] = 2;
                  v83 = *((_DWORD *)_ESI + 982707);
                  LOBYTE(v83) = v83 | 0x20;
                  *((_DWORD *)_ESI + 982707) = v83;
                }
                break;
              case '}':
                if ( v119 > 0 && _ESI[3930212] == 3 )
                {
                  set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70489));
                  *((_DWORD *)_ESI + 982713) = 0;
                  *((_DWORD *)_ESI + 982714) = 0;
                  _ESI[3930884] = 10;
                  v80 = *((_DWORD *)_ESI + 982707);
                  LOBYTE(v80) = v80 | 0x20;
                  *((_DWORD *)_ESI + 982707) = v80;
                  _ESI[3930212] = 13;
                }
                else
                {
                  set_bod_object((_DWORD *)_ESI + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70489));
                  *((_DWORD *)_ESI + 982713) = 0;
                  *((_DWORD *)_ESI + 982714) = 0;
                  _ESI[3930884] = 4;
                  v81 = *((_DWORD *)_ESI + 982707);
                  LOBYTE(v81) = v81 | 0x20;
                  *((_DWORD *)_ESI + 982707) = v81;
                }
                break;
              default:
                normalize_segment_glyph_for_track_flags((int)game, *v55, v119, 1);
                sub_449C00();
                break;
            }
            _EDI = (float *)(_ESI + 3930840);
            *((_DWORD *)_ESI + 982712) = 0;
            *((_DWORD *)_ESI + 982711) = 0;
            *((_DWORD *)_ESI + 982710) = 0;
            *(_DWORD *)((char *)&unk_5CCB90 + _EBX) = 0;
            *(_DWORD *)((char *)&unk_5CCB8C + _EBX) = 0;
            *(_DWORD *)((char *)&unk_5CCB88 + _EBX) = 0;
            v98 = _ESI[3930884];
            if ( v98 == 29 || v98 == 30 )
            {
              __asm { fild    [esp+54h+var_40] }
              *_EDI = 0.0;
              __asm
              {
                fadd    ds:flt_497228
                fst     [esp+54h+var_28]
                fsub    ds:flt_497228
                fst     dword ptr [esi+3BFAE0h]
              }
              *((float *)_ESI + 982712) = _ET1;
              if ( (byte_4DF934 & 0x20) != 0 )
              {
                *(_DWORD *)((char *)&unk_5CCB88 + _EBX) = 0;
                __asm { fstp    dword ptr [ebx+5CCB90h] }
                *(float *)(_EBX + 6081424) = _ET1;
                track_skirt_color = get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v135);
                v104 = (_DWORD *)((char *)&unk_5CCBA0 + _EBX);
                *v104 = *track_skirt_color;
                v104[1] = track_skirt_color[1];
                v104[2] = track_skirt_color[2];
                v104[3] = track_skirt_color[3];
                set_object_color(
                  *(_DWORD **)((char *)&unk_5CCB9C + _EBX),
                  *track_skirt_color,
                  track_skirt_color[1],
                  track_skirt_color[2],
                  track_skirt_color[3]);
              }
              else
              {
                v105 = *(_DWORD *)((char *)&unk_5CCB7C + _EBX);
                LOBYTE(v105) = v105 & 0xDF;
                __asm { fstp    st }
                *(_DWORD *)((char *)&unk_5CCB7C + _EBX) = v105;
              }
            }
            else
            {
              __asm
              {
                fild    [esp+54h+var_30]
                fsub    ds:flt_497210
                fadd    ds:flt_497228
                fstp    dword ptr [edi]
              }
              *_EDI = _ET1;
              *((_DWORD *)_ESI + 982711) = 0;
              v100 = _ESI[3930884];
              if ( v100 == 8 || v100 == 9 || v100 == 10 )
                *((_DWORD *)_ESI + 982711) = 1056964608;
              __asm
              {
                fild    [esp+54h+var_40]
                fadd    ds:flt_497228
                fstp    [esp+54h+var_28]
              }
              *((float *)_ESI + 982712) = v128;
            }
            if ( v119 < 4 && game->level_mode != 2 )
              *((_DWORD *)_ESI + 982711) = *(_DWORD *)(*(_DWORD *)&game->_pad_ff25e8[12996] + 52);
            if ( _ESI[3930884] == 28 )
            {
              __asm
              {
                fld     dword ptr [esi+3BFADCh]
                fsub    ds:flt_497548
                fstp    dword ptr [esi+3BFADCh]
              }
              *((float *)_ESI + 982711) = _ET1;
            }
            v107 = _ESI[3930884];
            if ( v107 == 1
              || v107 == 21
              || v107 == 20
              || v107 == 33
              || v107 == 34
              || v107 == 15
              || v107 == 16
              || v107 == 23
              || v107 == 24
              || v107 == 25
              || v107 == 26
              || v107 == 27
              || v107 == 18
              || v107 == 19
              || v107 == 17 )
            {
              v133 = 8 - v124;
              __asm
              {
                fild    [esp+54h+var_18]
                fmul    ds:flt_497428
                fstp    dword ptr [esi+3BFAE4h]
              }
              *((float *)_ESI + 982713) = _ET1;
              v134 = v119 % 8;
              __asm
              {
                fild    [esp+54h+var_18]
                fmul    ds:flt_497428
                fstp    dword ptr [esi+3BFAE8h]
              }
              *((float *)_ESI + 982714) = _ET1;
            }
            if ( _ESI[3930884] == 31 )
            {
              __asm
              {
                fld     dword ptr [edi]
                fmul    ds:flt_497434
                fstp    dword ptr [edi]
              }
              *_EDI = _ET1;
            }
            if ( _ESI[3930884] == 22 )
            {
              if ( game->level_mode != 3 || (game->runtime_flags & 0x400) != 0 )
                *((_DWORD *)_ESI + 982711) = -1069547520;
              *((float *)_ESI + 982712) = v128;
            }
            v111 = _ESI + 3930892;
            v112 = 4;
            do
            {
              v113 = (_DWORD *)*v111;
              if ( *v111 )
              {
                v113[6] = 0;
                v113[5] = 0;
                v113[4] = 0;
                v114 = (_DWORD *)(*v111 + 16);
                *v114 = *(_DWORD *)_EDI;
                v114[1] = *((_DWORD *)_ESI + 982711);
                v114[2] = *((_DWORD *)_ESI + 982712);
              }
              ++v111;
              --v112;
            }
            while ( v112 );
            ++v124;
          }
          while ( v124 < 8 );
          ++v122;
          v115 = ++v119 < game->runtime_row_count;
          v23 = v119;
          _EBP = (int)game;
        }
        while ( v115 );
      }
      if ( *(_DWORD *)(_EBP + 64) != 3 || !v117 )
        ++v125;
    }
    while ( v23 < *(_DWORD *)(_EBP + 84) );
  }
}

