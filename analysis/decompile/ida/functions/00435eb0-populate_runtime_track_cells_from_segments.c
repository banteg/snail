/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: populate_runtime_track_cells_from_segments @ 0x435eb0 */
/* selector: populate_runtime_track_cells_from_segments */

// Windows implementation of authored `cRSubGame::BuildLevel()`. It copies authored segment rows into the generated runtime grid, seeds Goldy's visible life stock to 3 before `initialize_subgoldy` runs, and seeds the course row bounds: non-random levels use the final `Last:` block boundary while the mode-1 random branch keeps the authored `Length:` lane scaled by the challenge scalar before subtracting the final `Last:` block rows. Runtime cell object selection reuses each `SubLoc` cell's shared `cRBod`/`BodBase` prefix, while authored row models and installed path strips belong to the embedded `SubRow::row_model` and `SubRow::attachment_body`; there is no separate track-row BOD-slot owner.
void __thiscall populate_runtime_track_cells_from_segments(SubgameRuntime *game)
{
  int32_t runtime_build_seed; // esi
  int32_t level_mode; // eax
  int32_t v4; // eax
  int v5; // eax
  int32_t subgame_rebuild_selector; // eax
  int32_t v7; // eax
  int v8; // ecx
  int32_t v9; // esi
  int32_t v10; // eax
  int32_t *p_row_count; // ecx
  _DWORD *v12; // edi
  int v13; // ebp
  _DWORD *v14; // esi
  int v15; // ecx
  int v16; // edx
  FringeObject **v17; // eax
  int v18; // ecx
  FringeObject **v19; // esi
  int32_t v20; // eax
  uint8_t *p_visited; // ecx
  int32_t v22; // edi
  SubgameRuntime *v23; // ebp
  int p_last_segment; // esi
  double segment_count; // st7
  int v26; // eax
  int v27; // edx
  int v28; // eax
  int32_t v29; // ecx
  int32_t completion_row_start; // eax
  SubSegment *v31; // edx
  int32_t row_count; // eax
  int32_t v33; // esi
  int32_t runtime_row_count; // ecx
  int v35; // eax
  int32_t *v36; // esi
  char *v37; // eax
  int v38; // ecx
  char *v39; // eax
  int v40; // ecx
  uint8_t *v41; // ebx
  int v42; // eax
  _DWORD *v43; // edx
  int v44; // eax
  char *v45; // eax
  _DWORD *v46; // ecx
  int v47; // eax
  int v48; // eax
  int v49; // ebp
  char *v50; // esi
  int v51; // eax
  char *v52; // edi
  char *v53; // ebp
  char v54; // al
  int v55; // eax
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
  int v72; // ecx
  unsigned int v73; // ebp
  bool v74; // zf
  unsigned int v75; // eax
  int v76; // eax
  int v77; // eax
  int v78; // eax
  int v79; // eax
  int v80; // eax
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // ecx
  PathPair *p_secondary; // ecx
  int v86; // edx
  char *v87; // ecx
  int v88; // eax
  int v89; // ecx
  int v90; // eax
  int v91; // eax
  float *v92; // edi
  char v93; // al
  char v94; // al
  double v95; // st7
  double v96; // st7
  tColour *track_skirt_color; // eax
  int v98; // eax
  char v99; // al
  _DWORD *v100; // ecx
  int v101; // edx
  _DWORD *v102; // eax
  _DWORD *v103; // eax
  bool v104; // cc
  float v105; // [esp+0h] [ebp-5Ch]
  char v106; // [esp+1Ah] [ebp-42h]
  char v107; // [esp+1Bh] [ebp-41h]
  int32_t v108; // [esp+1Ch] [ebp-40h]
  SubSegment *p_first_segment; // [esp+20h] [ebp-3Ch]
  int32_t v111; // [esp+28h] [ebp-34h]
  int v112; // [esp+2Ch] [ebp-30h]
  int v113; // [esp+2Ch] [ebp-30h]
  int v114; // [esp+30h] [ebp-2Ch]
  FringeObject **p_fringe_front; // [esp+34h] [ebp-28h]
  float v116; // [esp+34h] [ebp-28h]
  int v117; // [esp+38h] [ebp-24h]
  int v118; // [esp+3Ch] [ebp-20h]
  int random_length; // [esp+40h] [ebp-1Ch]
  char v120; // [esp+40h] [ebp-1Ch]
  tColour out; // [esp+4Ch] [ebp-10h] BYREF

  if ( game->selected_level_record_active )
  {
    runtime_build_seed = game->selected_level_record->runtime_build_seed;
  }
  else
  {
    level_mode = game->level_mode;
    if ( level_mode == 4 || level_mode == 7 )
      runtime_build_seed = 0;
    else
      runtime_build_seed = (__int64)random_float_below(32768.0);
  }
  v4 = game->level_mode;
  if ( v4 )
  {
    v5 = v4 - 1;
    if ( v5 )
    {
      if ( v5 == 3 )
        initialize_high_score_entry(
          (HighScoreRecord *)&game->current_high_score_record,
          runtime_build_seed,
          game->level_mode_arg,
          game->rate_or_level_arg.level_arg_tail,
          game->runtime_flags,
          2,
          game->level_mode_arg);
    }
    else
    {
      initialize_high_score_entry(
        (HighScoreRecord *)&game->current_high_score_record,
        runtime_build_seed,
        game->level_mode_arg,
        game->rate_or_level_arg.level_arg_tail,
        game->runtime_flags,
        1,
        game->level_mode_arg);
    }
  }
  else
  {
    initialize_high_score_entry(
      (HighScoreRecord *)&game->current_high_score_record,
      runtime_build_seed,
      game->level_mode_arg,
      game->rate_or_level_arg.level_arg_tail,
      game->runtime_flags,
      0,
      game->level_mode_arg);
  }
  subgame_rebuild_selector = game->subgame_rebuild_selector;
  game->replay_update_cursor = 0;
  if ( subgame_rebuild_selector == 3 )
  {
    game->subgame_rebuild_selector = 1;
    game->player.total_score = 0;
    clear_subgoldy_score_buckets((int)&game->player);
    game->player.visible_life_stock = 3;
  }
  zero_timer_counters(&game->player.stopwatch);
  game->player.score_tail = 0;
  game->player.movement_flag_selector = 0;
  set_math_random_seed(runtime_build_seed);
  select_level_track_texture_set((int *)&g_game_base->texture_set_selector, game->level_definition.track_texture_set);
  v7 = game->level_mode;
  if ( !v7 || v7 == 7 || v7 == 4 || v7 == 1 )
  {
    game->first_block_row_count = game->level_definition.first_segment.row_count;
    random_length = game->level_definition.random_length;
    game->runtime_row_count = random_length;
    if ( v7 == 1 )
      game->runtime_row_count = (__int64)((game->challenge_difficulty_scalar * 0.64999998 + 0.34999999)
                                        * (double)random_length);
    if ( !game->level_definition.random_enabled )
    {
      v10 = 0;
      game->runtime_row_count = game->level_definition.first_segment.row_count
                              + game->level_definition.last_segment.row_count;
      if ( game->level_definition.segment_count > 0 )
      {
        p_row_count = &game->level_definition.segment_slots[0].row_count;
        do
        {
          ++v10;
          game->runtime_row_count += *p_row_count;
          p_row_count += 4232;
        }
        while ( v10 < game->level_definition.segment_count );
      }
      v117 = 0;
    }
    game->completion_row_start = game->runtime_row_count - game->level_definition.last_segment.row_count;
    if ( game->runtime_row_count >= 3100 )
      report_errorf("Track (%s) too long, Maximum Length %i", game->level_definition.level_display_name, 3100);
  }
  else if ( v7 == 3 )
  {
    game->first_block_row_count = game->level_definition.first_segment.row_count;
    v8 = 16;
    game->runtime_row_count = game->level_definition.first_segment.row_count
                            + game->level_definition.last_segment.row_count;
    do
    {
      v9 = game->level_definition.segment_slots[0].row_count + game->runtime_row_count;
      --v8;
      game->runtime_row_count = v9;
    }
    while ( v8 );
    v117 = 0;
    game->completion_row_start = v9 - game->level_definition.last_segment.row_count;
    game->completion_row_start = v9 - game->level_definition.last_segment.row_count;
  }
  game->track_mirror_enabled = 0;
  game->track_mirror_repeat_count = 0;
  v118 = 0;
  v106 = 0;
  v114 = 0;
  game->player.follow_state._pad_3c[0] = 0;
  p_fringe_front = &game->runtime_cells[0][0].fringe_front;
  v12 = (_DWORD *)((char *)&unk_5CCB5C + (_DWORD)game);
  v112 = 3200;
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
    v14 = p_fringe_front - 1;
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
      set_color_white((tColour *)(v14 - 6));
      v14 += 21;
      --v13;
    }
    while ( v13 );
    v17 = p_fringe_front;
    v18 = 8;
    do
    {
      v19 = v17;
      v17 += 21;
      --v18;
      *v19 = nullptr;
      v19[1] = nullptr;
      v19[2] = nullptr;
      v19[3] = nullptr;
    }
    while ( v18 );
    p_fringe_front = v17;
    v12 += 61;
    --v112;
  }
  while ( v112 );
  if ( game->level_definition.random_enabled == 1 )
  {
    v20 = 0;
    if ( game->level_definition.segment_count > 0 )
    {
      p_visited = &game->level_definition.segment_slots[0].visited;
      do
      {
        *p_visited = 0;
        ++v20;
        p_visited += 16928;
      }
      while ( v20 < game->level_definition.segment_count );
    }
  }
  v108 = 0;
  if ( game->runtime_row_count > 0 )
  {
    v22 = 0;
    v23 = game;
    do
    {
      if ( v22 )
      {
        if ( v22 != v23->completion_row_start || v23->level_definition.random_enabled )
        {
          v23->base_subgame_rate = 1.0;
          if ( v23->level_definition.random_enabled == 1 )
          {
            if ( v23->level_mode == 1 )
              segment_count = (v23->challenge_difficulty_scalar * 0.89999998 + 0.1)
                            * (double)v23->level_definition.segment_count;
            else
              segment_count = (double)v23->level_definition.segment_count;
            v105 = segment_count;
            p_last_segment = (int)&v23->level_definition.segment_slots[(__int64)((double)(int)(__int64)random_float_below(v105)
                                                                               * v23->base_subgame_rate)];
            p_first_segment = (SubSegment *)p_last_segment;
            *(_BYTE *)(p_last_segment + 8) = 1;
          }
          else
          {
            v26 = v117;
            v27 = v117++;
            p_last_segment = (int)v23->level_definition.segment_slots + 0x4000 * v27 + 512 * v26 + 32 * v26;
            p_first_segment = (SubSegment *)p_last_segment;
          }
        }
        else
        {
          p_last_segment = (int)&v23->level_definition.last_segment;
          v106 = 1;
          p_first_segment = &v23->level_definition.last_segment;
          v23->level_definition.last_segment.row_base = v22;
        }
      }
      else
      {
        p_last_segment = (int)&v23->level_definition.first_segment;
        v106 = 1;
        p_first_segment = &v23->level_definition.first_segment;
        v23->level_definition.first_segment.row_base = 0;
      }
      switch_track_mirror(v23);
      v28 = *(_DWORD *)(p_last_segment + 4);
      *(_DWORD *)p_last_segment = v22;
      if ( v28 < 0 )
        report_errorf(aNegativeSegmen);
      v111 = 0;
      if ( v22 < v23->runtime_row_count )
      {
        do
        {
          if ( v111 >= p_first_segment->row_count )
            break;
          v29 = v23->level_mode;
          if ( v29 == 2 || (completion_row_start = v23->completion_row_start, v22 < completion_row_start) )
          {
            v31 = p_first_segment;
          }
          else
          {
            if ( !v29
              || v29 == 4
              || v29 == 1
              || v29 == 7
              || (v31 = &v23->level_definition_scratch.segment_slots[1], v29 == 3) )
            {
              v31 = &v23->level_definition.last_segment;
            }
            p_first_segment = v31;
            if ( v22 == completion_row_start )
              v111 = 0;
          }
          if ( v29 != 2 )
          {
            row_count = v31->row_count;
            v33 = v23->completion_row_start;
            if ( v22 + row_count - v111 <= v33 )
            {
              v31 = p_first_segment;
            }
            else
            {
              v31 = p_first_segment;
              if ( p_first_segment != &v23->level_definition_scratch.segment_slots[1]
                && p_first_segment != &v23->level_definition_scratch.segment_slots[3]
                && p_first_segment != &v23->level_definition_scratch.segment_slots[4]
                && (!v29 || v29 == 4 || v29 == 1 || v29 == 7 || v29 == 3)
                && p_first_segment != &v23->level_definition.last_segment )
              {
                runtime_row_count = v23->runtime_row_count;
                v35 = v22 + row_count - v33 - v111;
                v23->completion_row_start = v35 + v33;
                v23->runtime_row_count = v35 + runtime_row_count;
              }
            }
          }
          if ( v23->track_mirror_enabled )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v23 + 244 * v22] |= 0x20u;
          v36 = &v31->row_base + 14 * v111;
          if ( (v36[517] & 0x100) != 0 )
          {
            v37 = &byte_5CCAC8[(_DWORD)v23 + 244 * v22];
            v38 = *(_DWORD *)v37;
            BYTE1(v38) = BYTE1(*(_DWORD *)v37) | 1;
            *(_DWORD *)v37 = v38;
          }
          if ( (BYTE1(v36[517]) & 0x80u) != 0 )
          {
            v39 = &byte_5CCAC8[(_DWORD)v23 + 244 * v22];
            v40 = *(_DWORD *)v39;
            BYTE1(v40) = BYTE1(*(_DWORD *)v39) | 0x80;
            *(_DWORD *)v39 = v40;
          }
          v41 = &v23->scan_reset + 244 * v22;
          *(_DWORD *)((char *)&unk_5CCBB4 + (_DWORD)v41) = v31;
          *(int *)((char *)unk_5CCBB8 + (_DWORD)v41) = v114;
          if ( (v36[517] & 2) != 0 )
          {
            v42 = *(_DWORD *)&byte_5CCAC8[(_DWORD)v41];
            LOBYTE(v42) = v42 | 2;
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] = v42;
            set_bod_object(
              (char *)&unk_5CCACC + (_DWORD)v41,
              *(_DWORD *)&g_game_base->unknown_000b48[188 * v36[522] + 295652]);
            set_matrix_identity((TransformMatrix *)((char *)&unk_5CCB04 + (_DWORD)v41));
            v43 = (_DWORD *)((char *)&unk_5CCB34 + (_DWORD)v41);
            *v43 = v36[523];
            v43[1] = v36[524];
            v43[2] = v36[525];
            *((float *)v41 + 1520335) = (double)v108 + *((float *)v41 + 1520335);
            if ( (v36[517] & 8) != 0 )
            {
              v44 = *(_DWORD *)&byte_5CCAC8[(_DWORD)v41];
              LOBYTE(v44) = v44 | 8;
              *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] = v44;
              v45 = (char *)&unk_5CCB4C + (_DWORD)v41;
              *(_DWORD *)((char *)&unk_5CCB4C + (_DWORD)v41) = v36[526];
              *((_DWORD *)v45 + 1) = v36[527];
              *((_DWORD *)v45 + 2) = v36[528];
            }
            else
            {
              *(_DWORD *)((char *)&unk_5CCB54 + (_DWORD)v41) = 0;
              *(_DWORD *)((char *)&unk_5CCB50 + (_DWORD)v41) = 0;
              *(_DWORD *)((char *)&unk_5CCB4C + (_DWORD)v41) = 0;
            }
            v31 = p_first_segment;
          }
          if ( (v36[517] & 1) != 0 )
          {
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] |= 0x4001u;
            v46 = (_DWORD *)((char *)&unk_5CCB58 + (_DWORD)v41);
            *(_DWORD *)((char *)&unk_5CCB64 + (_DWORD)v41) = v31->rows[v111].parcel_set_id;
            *v46 = v36[519];
            v46[1] = v36[520];
            v46[2] = v36[521];
          }
          if ( (v36[517] & 8) != 0 )
          {
            v47 = *(_DWORD *)&byte_5CCAC8[(_DWORD)v41];
            LOBYTE(v47) = v47 | 8;
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] = v47;
            *(_DWORD *)((char *)&unk_5CCB68 + (_DWORD)v41) = v36[529];
          }
          if ( (v36[517] & 4) != 0 )
          {
            v48 = *(_DWORD *)&byte_5CCAC8[(_DWORD)v41];
            LOBYTE(v48) = v48 | 4;
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] = v48;
          }
          if ( (v36[517] & 0x200) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] |= 0x200u;
          if ( (v36[517] & 0x400) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] |= 0x400u;
          if ( (v36[517] & 0x2000) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] |= 0x2000u;
          if ( (v36[517] & 0x800) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] |= 0x800u;
          if ( (v36[517] & 0x1000) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] |= 0x1000u;
          v107 = 0;
          v113 = 0;
          *((_DWORD *)&v23->runtime_rows[0].ring_speed + 60 * v22 + v22) = v36[530];
          do
          {
            if ( game->track_mirror_enabled )
              v49 = 7 - v113;
            else
              v49 = v113;
            v50 = (char *)game + 672 * v108 + 84 * v113;
            v51 = *((_DWORD *)v50 + 982722);
            LOBYTE(v51) = v51 & 0xE0;
            *((_DWORD *)v50 + 982722) = v113 & 7 ^ v51;
            *((_DWORD *)v50 + 982723) = 0;
            *((_DWORD *)v50 + 982724) = 0;
            *((_DWORD *)v50 + 982725) = 0;
            *((_DWORD *)v50 + 982726) = 0;
            if ( v108 < game->first_block_row_count || (v120 = 0, v108 >= game->completion_row_start) )
              v120 = 1;
            v52 = v50 + 3930824;
            set_bod_object((_DWORD *)v50 + 982706, 0);
            v53 = &p_first_segment->glyph_rows[v49][v111];
            v54 = normalize_segment_glyph_for_track_flags((int)game, *v53, v108, v120);
            switch ( v54 )
            {
              case ' ':
                v50[3930884] = 0;
                v55 = *((_DWORD *)v50 + 982707);
                LOBYTE(v55) = v55 & 0xDF;
                *((_DWORD *)v50 + 982707) = v55;
                break;
              case '#':
                v50[3930884] = 32;
                v57 = *((_DWORD *)v50 + 982707);
                LOBYTE(v57) = v57 & 0xDF;
                *((_DWORD *)v50 + 982707) = v57;
                break;
              case '$':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
                v50[3930884] = 23;
                v60 = *((_DWORD *)v50 + 982707);
                LOBYTE(v60) = v60 | 0x20;
                *((_DWORD *)v50 + 982707) = v60;
                break;
              case '&':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[277612]);
                v50[3930884] = 34;
                v66 = *((_DWORD *)v50 + 982707);
                LOBYTE(v66) = v66 | 0x20;
                *((_DWORD *)v50 + 982707) = v66;
                break;
              case '(':
                v72 = v118 + 1;
                v73 = *((_DWORD *)v50 + 982707) & 0xFFFFFFDF;
                v74 = v118++ == 14;
                *((_DWORD *)v50 + 982707) = v73;
                v75 = v73;
                if ( v74 )
                {
                  v118 = 0;
                  v50[3930884] = 22;
                }
                else
                {
                  if ( v72 == 8 )
                  {
                    set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[276884]);
                    *((_DWORD *)v50 + 982707) |= 0x20u;
                    store_color4f(&game->runtime_cells[v108][v113].color, 1.0, 1.0, 1.0, 0.99900001);
                  }
                  else
                  {
                    LOBYTE(v75) = v73 & 0xDF;
                    *((_DWORD *)v50 + 982707) = v75;
                  }
                  v50[3930884] = 22;
                }
                break;
              case '+':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
                v50[3930884] = 24;
                v68 = *((_DWORD *)v50 + 982707);
                LOBYTE(v68) = v68 | 0x20;
                *((_DWORD *)v50 + 982707) = v68;
                break;
              case ',':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[275932]);
                v50[3930884] = 28;
                v67 = *((_DWORD *)v50 + 982707);
                LOBYTE(v67) = v67 | 0x20;
                *((_DWORD *)v50 + 982707) = v67;
                break;
              case '-':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[277612]);
                v50[3930884] = 21;
                v70 = *((_DWORD *)v50 + 982707);
                LOBYTE(v70) = v70 | 0x20;
                *((_DWORD *)v50 + 982707) = v70;
                break;
              case '.':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[277612]);
                v50[3930884] = 1;
                v64 = *((_DWORD *)v50 + 982707);
                LOBYTE(v64) = v64 | 0x20;
                *((_DWORD *)v50 + 982707) = v64;
                break;
              case '0':
                if ( game->level_mode == 1 )
                {
                  v89 = *(_DWORD *)&byte_5CCAC8[(_DWORD)v41];
                  BYTE1(v89) &= ~0x40u;
                  *(_DWORD *)&byte_5CCAC8[(_DWORD)v41] = v89 | 1;
                  *(_DWORD *)((char *)&unk_5CCB64 + (_DWORD)v41) = 0;
                  *((float *)v41 + 1520342) = (double)v113 - 4.0 + 0.5;
                  *(_DWORD *)((char *)&unk_5CCB5C + (_DWORD)v41) = *((_DWORD *)v50 + 982711);
                  *((float *)v41 + 1520344) = (double)v108 + 0.5;
                  if ( game->track_mirror_enabled )
                    *((float *)v41 + 1520342) = *((float *)v41 + 1520342) * -1.0;
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
                if ( (byte_5CCAC8[(_DWORD)v41] & 0xC0) == 0 )
                  goto LABEL_174;
                v91 = *((_DWORD *)v50 + 982707);
                LOBYTE(v91) = v91 & 0xDF;
                *((_DWORD *)v50 + 982707) = v91;
                v50[3930884] = 0;
                break;
              case '<':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[279012]);
                *((_DWORD *)v50 + 982713) = 0;
                *((_DWORD *)v50 + 982714) = 0;
                v50[3930884] = 6;
                v82 = *((_DWORD *)v50 + 982707);
                LOBYTE(v82) = v82 | 0x20;
                *((_DWORD *)v50 + 982707) = v82;
                break;
              case '=':
              case '|':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[277164]);
                v50[3930884] = 14;
                v71 = *((_DWORD *)v50 + 982707);
                LOBYTE(v71) = v71 | 0x20;
                *((_DWORD *)v50 + 982707) = v71;
                break;
              case '>':
                if ( v108 > 0 && v50[3930212] == 3 )
                {
                  set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[279012]);
                  *((_DWORD *)v50 + 982713) = 0;
                  *((_DWORD *)v50 + 982714) = 0;
                  v50[3930884] = 9;
                  v76 = *((_DWORD *)v50 + 982707);
                  LOBYTE(v76) = v76 | 0x20;
                  *((_DWORD *)v50 + 982707) = v76;
                  v50[3930212] = 12;
                }
                else
                {
                  set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[279012]);
                  *((_DWORD *)v50 + 982713) = 0;
                  *((_DWORD *)v50 + 982714) = 0;
                  v50[3930884] = 3;
                  v77 = *((_DWORD *)v50 + 982707);
                  LOBYTE(v77) = v77 | 0x20;
                  *((_DWORD *)v50 + 982707) = v77;
                }
                break;
              case '@':
                v50[3930884] = 0;
                v58 = *((_DWORD *)v50 + 982707);
                LOBYTE(v58) = v58 & 0xDF;
                *((_DWORD *)v50 + 982707) = v58;
                switch_track_mirror(game);
                break;
              case 'F':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
                v50[3930884] = 19;
                v63 = *((_DWORD *)v50 + 982707);
                LOBYTE(v63) = v63 | 0x20;
                *((_DWORD *)v50 + 982707) = v63;
                break;
              case 'G':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
                v50[3930884] = 17;
                v59 = *((_DWORD *)v50 + 982707);
                LOBYTE(v59) = v59 | 0x20;
                *((_DWORD *)v50 + 982707) = v59;
                break;
              case 'J':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
                v50[3930884] = 25;
                v69 = *((_DWORD *)v50 + 982707);
                LOBYTE(v69) = v69 | 0x20;
                *((_DWORD *)v50 + 982707) = v69;
                break;
              case 'M':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
                v50[3930884] = 18;
                v62 = *((_DWORD *)v50 + 982707);
                LOBYTE(v62) = v62 | 0x20;
                *((_DWORD *)v50 + 982707) = v62;
                break;
              case 'P':
              case 'p':
                if ( v54 == 80 )
                {
                  v50[3930884] = 30;
                }
                else if ( v54 == 112 )
                {
                  v50[3930884] = 29;
                }
                v84 = *(_DWORD *)((char *)&unk_5CCB68 + (_DWORD)v41);
                if ( game->track_mirror_enabled )
                  p_secondary = (PathPair *)&game->path_pairs[v84].secondary;
                else
                  p_secondary = &game->path_pairs[v84];
                *((_DWORD *)v50 + 982720) = p_secondary;
                *((_DWORD *)v50 + 982707) &= ~0x20u;
                if ( !v107 )
                {
                  v107 = 1;
                  set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)(*((_DWORD *)v50 + 982720) + 36));
                  *((_DWORD *)v50 + 982707) |= 0x20u;
                  set_bod_object((char *)&unk_5CCB78 + (_DWORD)v41, *(_DWORD *)(*((_DWORD *)v50 + 982720) + 132));
                  *(_DWORD *)((char *)&unk_5CCB7C + (_DWORD)v41) |= 0x20u;
                  *(_DWORD *)((char *)&unk_5CCB74 + (_DWORD)v41) = p_first_segment->angle_radians.bits;
                  v86 = 0;
                  if ( *(int *)(*((_DWORD *)v50 + 982720) + 72) > 0 )
                  {
                    v87 = &byte_5CCAC8[(_DWORD)v41];
                    do
                    {
                      v88 = *(_DWORD *)v87;
                      if ( (*(_DWORD *)v87 & 0x40) != 0 )
                      {
                        LOBYTE(v88) = v88 | 0x80;
                        *(_DWORD *)v87 = v88;
                        *((_DWORD *)v87 + 42) = v52;
                      }
                      else
                      {
                        LOBYTE(v88) = v88 | 0x40;
                        *(_DWORD *)v87 = v88;
                        *((_DWORD *)v87 + 41) = v52;
                      }
                      ++v86;
                      v87 += 244;
                    }
                    while ( v86 < *(_DWORD *)(*((_DWORD *)v50 + 982720) + 72) );
                  }
                }
                break;
              case 'R':
                v50[3930884] = 35;
                v56 = *((_DWORD *)v50 + 982707);
                LOBYTE(v56) = v56 & 0xDF;
                *((_DWORD *)v50 + 982707) = v56;
                break;
              case '[':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278956]);
                *((_DWORD *)v50 + 982713) = 0;
                *((_DWORD *)v50 + 982714) = 0;
                v50[3930884] = 5;
                v83 = *((_DWORD *)v50 + 982707);
                LOBYTE(v83) = v83 | 0x20;
                *((_DWORD *)v50 + 982707) = v83;
                break;
              case '_':
LABEL_174:
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
                v50[3930884] = 15;
                v90 = *((_DWORD *)v50 + 982707);
                LOBYTE(v90) = v90 | 0x20;
                *((_DWORD *)v50 + 982707) = v90;
                break;
              case 'o':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278508]);
                v50[3930884] = 16;
                v61 = *((_DWORD *)v50 + 982707);
                LOBYTE(v61) = v61 | 0x20;
                *((_DWORD *)v50 + 982707) = v61;
                break;
              case 's':
                set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[277612]);
                v50[3930884] = 33;
                v65 = *((_DWORD *)v50 + 982707);
                LOBYTE(v65) = v65 | 0x20;
                *((_DWORD *)v50 + 982707) = v65;
                break;
              case '{':
                if ( v108 > 0 && v50[3930212] == 3 )
                {
                  set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278956]);
                  *((_DWORD *)v50 + 982713) = 0;
                  *((_DWORD *)v50 + 982714) = 0;
                  v50[3930884] = 8;
                  v80 = *((_DWORD *)v50 + 982707);
                  LOBYTE(v80) = v80 | 0x20;
                  *((_DWORD *)v50 + 982707) = v80;
                  v50[3930212] = 11;
                }
                else
                {
                  set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[278956]);
                  *((_DWORD *)v50 + 982713) = 0;
                  *((_DWORD *)v50 + 982714) = 0;
                  v50[3930884] = 2;
                  v81 = *((_DWORD *)v50 + 982707);
                  LOBYTE(v81) = v81 | 0x20;
                  *((_DWORD *)v50 + 982707) = v81;
                }
                break;
              case '}':
                if ( v108 > 0 && v50[3930212] == 3 )
                {
                  set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[279068]);
                  *((_DWORD *)v50 + 982713) = 0;
                  *((_DWORD *)v50 + 982714) = 0;
                  v50[3930884] = 10;
                  v78 = *((_DWORD *)v50 + 982707);
                  LOBYTE(v78) = v78 | 0x20;
                  *((_DWORD *)v50 + 982707) = v78;
                  v50[3930212] = 13;
                }
                else
                {
                  set_bod_object((_DWORD *)v50 + 982706, *(_DWORD *)&g_game_base->unknown_000b48[279068]);
                  *((_DWORD *)v50 + 982713) = 0;
                  *((_DWORD *)v50 + 982714) = 0;
                  v50[3930884] = 4;
                  v79 = *((_DWORD *)v50 + 982707);
                  LOBYTE(v79) = v79 | 0x20;
                  *((_DWORD *)v50 + 982707) = v79;
                }
                break;
              default:
                normalize_segment_glyph_for_track_flags((int)game, *v53, v108, 1);
                debug_report_stub();
                break;
            }
            v92 = (float *)(v50 + 3930840);
            *((_DWORD *)v50 + 982712) = 0;
            *((_DWORD *)v50 + 982711) = 0;
            *((_DWORD *)v50 + 982710) = 0;
            *(_DWORD *)((char *)&unk_5CCB90 + (_DWORD)v41) = 0;
            *(_DWORD *)((char *)&unk_5CCB8C + (_DWORD)v41) = 0;
            *(_DWORD *)((char *)&unk_5CCB88 + (_DWORD)v41) = 0;
            v93 = v50[3930884];
            if ( v93 == 29 || v93 == 30 )
            {
              *v92 = 0.0;
              v95 = (double)v108 + 0.5;
              v116 = v95;
              v96 = v95 - 0.5;
              *((float *)v50 + 982712) = v96;
              if ( (g_runtime_config.render_flags & 0x20) != 0 )
              {
                *(_DWORD *)((char *)&unk_5CCB88 + (_DWORD)v41) = 0;
                *((float *)v41 + 1520356) = v96;
                track_skirt_color = get_track_skirt_color((SubgameRuntime *)&g_game_base->subgame, &out);
                *(tColour *)((char *)&unk_5CCBA0 + (_DWORD)v41) = *track_skirt_color;
                set_object_color(*(Object **)((char *)&unk_5CCB9C + (_DWORD)v41), *track_skirt_color);
              }
              else
              {
                v98 = *(_DWORD *)((char *)&unk_5CCB7C + (_DWORD)v41);
                LOBYTE(v98) = v98 & 0xDF;
                *(_DWORD *)((char *)&unk_5CCB7C + (_DWORD)v41) = v98;
              }
            }
            else
            {
              *v92 = (double)v113 - 4.0 + 0.5;
              *((_DWORD *)v50 + 982711) = 0;
              v94 = v50[3930884];
              if ( v94 == 8 || v94 == 9 || v94 == 10 )
                *((_DWORD *)v50 + 982711) = 1056964608;
              v116 = (double)v108 + 0.5;
              *((float *)v50 + 982712) = v116;
            }
            if ( v108 < 4 && game->level_mode != 2 )
              *((_DWORD *)v50 + 982711) = LODWORD(game->path_pairs[36].primary.primary_samples->transform.position.y);
            if ( v50[3930884] == 28 )
              *((float *)v50 + 982711) = *((float *)v50 + 982711) - 0.029999999;
            v99 = v50[3930884];
            if ( v99 == 1
              || v99 == 21
              || v99 == 20
              || v99 == 33
              || v99 == 34
              || v99 == 15
              || v99 == 16
              || v99 == 23
              || v99 == 24
              || v99 == 25
              || v99 == 26
              || v99 == 27
              || v99 == 18
              || v99 == 19
              || v99 == 17 )
            {
              *((float *)v50 + 982713) = (double)(8 - v113) * 0.125;
              *((float *)v50 + 982714) = (double)(v108 % 8) * 0.125;
            }
            if ( v50[3930884] == 31 )
              *v92 = *v92 * 1.1;
            if ( v50[3930884] == 22 )
            {
              if ( game->level_mode != 3 || (game->runtime_flags & 0x400) != 0 )
                *((_DWORD *)v50 + 982711) = -1069547520;
              *((float *)v50 + 982712) = v116;
            }
            v100 = v50 + 3930892;
            v101 = 4;
            do
            {
              v102 = (_DWORD *)*v100;
              if ( *v100 )
              {
                v102[6] = 0;
                v102[5] = 0;
                v102[4] = 0;
                v103 = (_DWORD *)(*v100 + 16);
                *v103 = *(_DWORD *)v92;
                v103[1] = *((_DWORD *)v50 + 982711);
                v103[2] = *((_DWORD *)v50 + 982712);
              }
              ++v100;
              --v101;
            }
            while ( v101 );
            ++v113;
          }
          while ( v113 < 8 );
          ++v111;
          v104 = ++v108 < game->runtime_row_count;
          v22 = v108;
          v23 = game;
        }
        while ( v104 );
      }
      if ( v23->level_mode != 3 || !v106 )
        ++v114;
    }
    while ( v22 < v23->runtime_row_count );
  }
}
