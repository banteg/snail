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
  SubSegmentRowStrideAnchor *segment_row_anchor; // esi
  char *v37; // eax
  int v38; // ecx
  char *v39; // eax
  int v40; // ecx
  RuntimeRowStrideAnchor *runtime_row_anchor; // ebx
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // eax
  int v46; // ebp
  RuntimeCellStrideAnchor *runtime_cell_anchor; // esi
  uint32_t lane_and_flags; // eax
  TrackRowCell *p_cell; // edi
  char *v50; // ebp
  char v51; // al
  uint32_t list_flags; // eax
  uint32_t v53; // eax
  uint32_t v54; // eax
  uint32_t v55; // eax
  uint32_t v56; // eax
  uint32_t v57; // eax
  uint32_t v58; // eax
  uint32_t v59; // eax
  uint32_t v60; // eax
  uint32_t v61; // eax
  uint32_t v62; // eax
  uint32_t v63; // eax
  uint32_t v64; // eax
  uint32_t v65; // eax
  uint32_t v66; // eax
  uint32_t v67; // eax
  uint32_t v68; // eax
  int v69; // ecx
  uint32_t v70; // ebp
  bool v71; // zf
  uint32_t v72; // eax
  uint32_t v73; // eax
  uint32_t v74; // eax
  uint32_t v75; // eax
  uint32_t v76; // eax
  uint32_t v77; // eax
  uint32_t v78; // eax
  uint32_t v79; // eax
  uint32_t v80; // eax
  int v81; // ecx
  PathPair *p_secondary; // ecx
  signed int v83; // edx
  char *v84; // ecx
  int v85; // eax
  int v86; // ecx
  uint32_t v87; // eax
  uint32_t v88; // eax
  Vec3 *p_anchor_position; // edi
  uint8_t tile_id; // al
  uint8_t v91; // al
  double v92; // st7
  double v93; // st7
  tColour *track_skirt_color; // eax
  int v95; // eax
  uint8_t v96; // al
  FringeObject **v97; // ecx
  int v98; // edx
  FringeObject *v99; // eax
  int p_position; // eax
  bool v101; // cc
  float v102; // [esp+0h] [ebp-5Ch]
  char v103; // [esp+1Ah] [ebp-42h]
  char v104; // [esp+1Bh] [ebp-41h]
  int32_t v105; // [esp+1Ch] [ebp-40h]
  SubSegment *p_first_segment; // [esp+20h] [ebp-3Ch]
  int32_t segment_row_index; // [esp+28h] [ebp-34h]
  int v109; // [esp+2Ch] [ebp-30h]
  int v110; // [esp+2Ch] [ebp-30h]
  int v111; // [esp+30h] [ebp-2Ch]
  FringeObject **p_fringe_front; // [esp+34h] [ebp-28h]
  float v113; // [esp+34h] [ebp-28h]
  int v114; // [esp+38h] [ebp-24h]
  int v115; // [esp+3Ch] [ebp-20h]
  int random_length; // [esp+40h] [ebp-1Ch]
  char v117; // [esp+40h] [ebp-1Ch]
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
          &game->current_high_score_record,
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
        &game->current_high_score_record,
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
      &game->current_high_score_record,
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
    clear_subgoldy_score_buckets(&game->player);
    game->player.visible_life_stock = 3;
  }
  zero_timer_counters(&game->player.stopwatch);
  game->player.score_tail = 0;
  game->player.movement_flag_selector = 0;
  set_math_random_seed(runtime_build_seed);
  select_level_track_texture_set(&g_game_base->track, game->level_definition.track_texture_set);
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
      v114 = 0;
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
    v114 = 0;
    game->completion_row_start = v9 - game->level_definition.last_segment.row_count;
    game->completion_row_start = v9 - game->level_definition.last_segment.row_count;
  }
  game->track_mirror_enabled = 0;
  game->track_mirror_repeat_count = 0;
  v115 = 0;
  v103 = 0;
  v111 = 0;
  game->player.follow_state.flag_3c = 0;
  p_fringe_front = &game->runtime_cells[0][0].fringe_front;
  v12 = (_DWORD *)((char *)&unk_5CCB5C + (_DWORD)game);
  v109 = 3200;
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
    --v109;
  }
  while ( v109 );
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
  v105 = 0;
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
            v102 = segment_count;
            p_last_segment = (int)&v23->level_definition.segment_slots[(__int64)((double)(int)(__int64)random_float_below(v102)
                                                                               * v23->base_subgame_rate)];
            p_first_segment = (SubSegment *)p_last_segment;
            *(_BYTE *)(p_last_segment + 8) = 1;
          }
          else
          {
            v26 = v114;
            v27 = v114++;
            p_last_segment = (int)v23->level_definition.segment_slots + 0x4000 * v27 + 512 * v26 + 32 * v26;
            p_first_segment = (SubSegment *)p_last_segment;
          }
        }
        else
        {
          p_last_segment = (int)&v23->level_definition.last_segment;
          v103 = 1;
          p_first_segment = &v23->level_definition.last_segment;
          v23->level_definition.last_segment.row_base = v22;
        }
      }
      else
      {
        p_last_segment = (int)&v23->level_definition.first_segment;
        v103 = 1;
        p_first_segment = &v23->level_definition.first_segment;
        v23->level_definition.first_segment.row_base = 0;
      }
      switch_track_mirror(v23);
      v28 = *(_DWORD *)(p_last_segment + 4);
      *(_DWORD *)p_last_segment = v22;
      if ( v28 < 0 )
        report_errorf(aNegativeSegmen);
      segment_row_index = 0;
      if ( v22 < v23->runtime_row_count )
      {
        do
        {
          if ( segment_row_index >= p_first_segment->row_count )
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
              segment_row_index = 0;
          }
          if ( v29 != 2 )
          {
            row_count = v31->row_count;
            v33 = v23->completion_row_start;
            if ( v22 + row_count - segment_row_index <= v33 )
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
                v35 = v22 + row_count - v33 - segment_row_index;
                v23->completion_row_start = v35 + v33;
                v23->runtime_row_count = v35 + runtime_row_count;
              }
            }
          }
          if ( v23->track_mirror_enabled )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v23 + 244 * v22] |= 0x20u;
          segment_row_anchor = (SubSegmentRowStrideAnchor *)((char *)v31 + 56 * segment_row_index);
          if ( (segment_row_anchor->row.flags & 0x100) != 0 )
          {
            v37 = &byte_5CCAC8[(_DWORD)v23 + 244 * v22];
            v38 = *(_DWORD *)v37;
            BYTE1(v38) = BYTE1(*(_DWORD *)v37) | 1;
            *(_DWORD *)v37 = v38;
          }
          if ( (BYTE1(segment_row_anchor->row.flags) & 0x80u) != 0 )
          {
            v39 = &byte_5CCAC8[(_DWORD)v23 + 244 * v22];
            v40 = *(_DWORD *)v39;
            BYTE1(v40) = BYTE1(*(_DWORD *)v39) | 0x80;
            *(_DWORD *)v39 = v40;
          }
          runtime_row_anchor = (RuntimeRowStrideAnchor *)((char *)v23 + 244 * v22);
          *(_DWORD *)((char *)&unk_5CCBB4 + (_DWORD)runtime_row_anchor) = v31;
          *(int *)((char *)unk_5CCBB8 + (_DWORD)runtime_row_anchor) = v111;
          if ( (segment_row_anchor->row.flags & 2) != 0 )
          {
            v42 = *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor];
            LOBYTE(v42) = v42 | 2;
            *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] = v42;
            set_bod_object(
              (BodBase *)((char *)&unk_5CCACC + (_DWORD)runtime_row_anchor),
              g_game_base->directx_loader.cached_x_mesh_slots[segment_row_anchor->row.object_id].object);
            set_matrix_identity((TransformMatrix *)((char *)&unk_5CCB04 + (_DWORD)runtime_row_anchor));
            *(Vec3 *)((char *)&unk_5CCB34 + (_DWORD)runtime_row_anchor) = segment_row_anchor->row.object_position;
            runtime_row_anchor->row.primary_body.transform.position.z = (double)v105
                                                                      + runtime_row_anchor->row.primary_body.transform.position.z;
            if ( (segment_row_anchor->row.flags & 8) != 0 )
            {
              v43 = *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor];
              LOBYTE(v43) = v43 | 8;
              *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] = v43;
              *(Vec3 *)((char *)&unk_5CCB4C + (_DWORD)runtime_row_anchor) = segment_row_anchor->row.object_velocity;
            }
            else
            {
              *(_DWORD *)((char *)&unk_5CCB54 + (_DWORD)runtime_row_anchor) = 0;
              *(_DWORD *)((char *)&unk_5CCB50 + (_DWORD)runtime_row_anchor) = 0;
              *(_DWORD *)((char *)&unk_5CCB4C + (_DWORD)runtime_row_anchor) = 0;
            }
            v31 = p_first_segment;
          }
          if ( (segment_row_anchor->row.flags & 1) != 0 )
          {
            *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] |= 0x4001u;
            *(_DWORD *)((char *)&unk_5CCB64 + (_DWORD)runtime_row_anchor) = v31->rows[segment_row_index].parcel_set_id;
            *(Vec3 *)((char *)&unk_5CCB58 + (_DWORD)runtime_row_anchor) = segment_row_anchor->row.local_position;
          }
          if ( (segment_row_anchor->row.flags & 8) != 0 )
          {
            v44 = *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor];
            LOBYTE(v44) = v44 | 8;
            *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] = v44;
            *(_DWORD *)((char *)&unk_5CCB68 + (_DWORD)runtime_row_anchor) = segment_row_anchor->row.path_template_index;
          }
          if ( (segment_row_anchor->row.flags & 4) != 0 )
          {
            v45 = *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor];
            LOBYTE(v45) = v45 | 4;
            *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] = v45;
          }
          if ( (segment_row_anchor->row.flags & 0x200) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] |= 0x200u;
          if ( (segment_row_anchor->row.flags & 0x400) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] |= 0x400u;
          if ( (segment_row_anchor->row.flags & 0x2000) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] |= 0x2000u;
          if ( (segment_row_anchor->row.flags & 0x800) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] |= 0x800u;
          if ( (segment_row_anchor->row.flags & 0x1000) != 0 )
            *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] |= 0x1000u;
          v104 = 0;
          v110 = 0;
          *((_DWORD *)&v23->runtime_rows[0].ring_speed + 60 * v22 + v22) = segment_row_anchor->row.ring_speed.bits;
          do
          {
            if ( game->track_mirror_enabled )
              v46 = 7 - v110;
            else
              v46 = v110;
            runtime_cell_anchor = (RuntimeCellStrideAnchor *)((char *)game + 672 * v105 + 84 * v110);
            lane_and_flags = runtime_cell_anchor->cell.lane_and_flags;
            LOBYTE(lane_and_flags) = lane_and_flags & 0xE0;
            runtime_cell_anchor->cell.lane_and_flags = v110 & 7 ^ lane_and_flags;
            runtime_cell_anchor->cell.fringe_front = nullptr;
            runtime_cell_anchor->cell.fringe_right = nullptr;
            runtime_cell_anchor->cell.fringe_left = nullptr;
            runtime_cell_anchor->cell.fringe_back = nullptr;
            if ( v105 < game->first_block_row_count || (v117 = 0, v105 >= game->completion_row_start) )
              v117 = 1;
            p_cell = &runtime_cell_anchor->cell;
            set_bod_object((BodBase *)&runtime_cell_anchor->cell, nullptr);
            v50 = &p_first_segment->glyph_rows[v46][segment_row_index];
            v51 = normalize_segment_glyph_for_track_flags((int)game, *v50, v105, v117);
            switch ( v51 )
            {
              case ' ':
                runtime_cell_anchor->cell.tile_id = 0;
                list_flags = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(list_flags) = list_flags & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = list_flags;
                break;
              case '#':
                runtime_cell_anchor->cell.tile_id = 32;
                v54 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v54) = v54 & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = v54;
                break;
              case '$':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 23;
                v57 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v57) = v57 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v57;
                break;
              case '&':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.floor_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 34;
                v63 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v63) = v63 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v63;
                break;
              case '(':
                v69 = v115 + 1;
                v70 = runtime_cell_anchor->cell.bod.list_flags & 0xFFFFFFDF;
                v71 = v115++ == 14;
                runtime_cell_anchor->cell.bod.list_flags = v70;
                v72 = v70;
                if ( v71 )
                {
                  v115 = 0;
                  runtime_cell_anchor->cell.tile_id = 22;
                }
                else
                {
                  if ( v69 == 8 )
                  {
                    set_bod_object(
                      (BodBase *)&runtime_cell_anchor->cell,
                      (Object *)g_game_base->root_bod_catalog.trampoline.object);
                    runtime_cell_anchor->cell.bod.list_flags |= 0x20u;
                    store_color4f(&game->runtime_cells[v105][v110].color, 1.0, 1.0, 1.0, 0.99900001);
                  }
                  else
                  {
                    LOBYTE(v72) = v70 & 0xDF;
                    runtime_cell_anchor->cell.bod.list_flags = v72;
                  }
                  runtime_cell_anchor->cell.tile_id = 22;
                }
                break;
              case '+':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 24;
                v65 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v65) = v65 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v65;
                break;
              case ',':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.universe_hole.object);
                runtime_cell_anchor->cell.tile_id = 28;
                v64 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v64) = v64 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v64;
                break;
              case '-':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.floor_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 21;
                v67 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v67) = v67 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v67;
                break;
              case '.':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.floor_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 1;
                v61 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v61) = v61 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v61;
                break;
              case '0':
                if ( game->level_mode == 1 )
                {
                  v86 = *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor];
                  BYTE1(v86) &= ~0x40u;
                  *(_DWORD *)&byte_5CCAC8[(_DWORD)runtime_row_anchor] = v86 | 1;
                  *(_DWORD *)((char *)&unk_5CCB64 + (_DWORD)runtime_row_anchor) = 0;
                  runtime_row_anchor->row.projection_payload.x = (double)v110 - 4.0 + 0.5;
                  *(float *)((char *)&unk_5CCB5C + (_DWORD)runtime_row_anchor) = runtime_cell_anchor->cell.anchor_position.y;
                  runtime_row_anchor->row.projection_payload.z = (double)v105 + 0.5;
                  if ( game->track_mirror_enabled )
                    runtime_row_anchor->row.projection_payload.x = runtime_row_anchor->row.projection_payload.x * -1.0;
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
                if ( (byte_5CCAC8[(_DWORD)runtime_row_anchor] & 0xC0) == 0 )
                  goto LABEL_174;
                v88 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v88) = v88 & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = v88;
                runtime_cell_anchor->cell.tile_id = 0;
                break;
              case '<':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.ramp_edges[1].object);
                runtime_cell_anchor->cell.render_arg_1c = 0.0;
                runtime_cell_anchor->cell.render_arg_20 = 0.0;
                runtime_cell_anchor->cell.tile_id = 6;
                v79 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v79) = v79 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v79;
                break;
              case '=':
              case '|':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.pillars[0].object);
                runtime_cell_anchor->cell.tile_id = 14;
                v68 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v68) = v68 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v68;
                break;
              case '>':
                if ( v105 > 0 && runtime_cell_anchor->previous_row_same_lane.tile_id == 3 )
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    (Object *)g_game_base->root_bod_catalog.ramp_edges[1].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = 9;
                  v73 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v73) = v73 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v73;
                  runtime_cell_anchor->previous_row_same_lane.tile_id = 12;
                }
                else
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    (Object *)g_game_base->root_bod_catalog.ramp_edges[1].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = 3;
                  v74 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v74) = v74 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v74;
                }
                break;
              case '@':
                runtime_cell_anchor->cell.tile_id = 0;
                v55 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v55) = v55 & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = v55;
                switch_track_mirror(game);
                break;
              case 'F':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 19;
                v60 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v60) = v60 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v60;
                break;
              case 'G':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 17;
                v56 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v56) = v56 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v56;
                break;
              case 'J':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 25;
                v66 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v66) = v66 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v66;
                break;
              case 'M':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 18;
                v59 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v59) = v59 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v59;
                break;
              case 'P':
              case 'p':
                if ( v51 == 80 )
                {
                  runtime_cell_anchor->cell.tile_id = 30;
                }
                else if ( v51 == 112 )
                {
                  runtime_cell_anchor->cell.tile_id = 29;
                }
                v81 = *(_DWORD *)((char *)&unk_5CCB68 + (_DWORD)runtime_row_anchor);
                if ( game->track_mirror_enabled )
                  p_secondary = (PathPair *)&game->path_pairs[v81].secondary;
                else
                  p_secondary = &game->path_pairs[v81];
                runtime_cell_anchor->cell.attachment_template_record = &p_secondary->primary;
                runtime_cell_anchor->cell.bod.list_flags &= ~0x20u;
                if ( !v104 )
                {
                  v104 = 1;
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    runtime_cell_anchor->cell.attachment_template_record->bod.object);
                  runtime_cell_anchor->cell.bod.list_flags |= 0x20u;
                  set_bod_object(
                    (BodBase *)((char *)&unk_5CCB78 + (_DWORD)runtime_row_anchor),
                    runtime_cell_anchor->cell.attachment_template_record->fringe_mesh_bod.object);
                  *(_DWORD *)((char *)&unk_5CCB7C + (_DWORD)runtime_row_anchor) |= 0x20u;
                  *(_DWORD *)((char *)&unk_5CCB74 + (_DWORD)runtime_row_anchor) = p_first_segment->angle_radians.bits;
                  v83 = 0;
                  if ( (int)runtime_cell_anchor->cell.attachment_template_record->row_span_count > 0 )
                  {
                    v84 = &byte_5CCAC8[(_DWORD)runtime_row_anchor];
                    do
                    {
                      v85 = *(_DWORD *)v84;
                      if ( (*(_DWORD *)v84 & 0x40) != 0 )
                      {
                        LOBYTE(v85) = v85 | 0x80;
                        *(_DWORD *)v84 = v85;
                        *((_DWORD *)v84 + 42) = p_cell;
                      }
                      else
                      {
                        LOBYTE(v85) = v85 | 0x40;
                        *(_DWORD *)v84 = v85;
                        *((_DWORD *)v84 + 41) = p_cell;
                      }
                      ++v83;
                      v84 += 244;
                    }
                    while ( v83 < (signed int)runtime_cell_anchor->cell.attachment_template_record->row_span_count );
                  }
                }
                break;
              case 'R':
                runtime_cell_anchor->cell.tile_id = 35;
                v53 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v53) = v53 & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = v53;
                break;
              case '[':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.ramp_edges[0].object);
                runtime_cell_anchor->cell.render_arg_1c = 0.0;
                runtime_cell_anchor->cell.render_arg_20 = 0.0;
                runtime_cell_anchor->cell.tile_id = 5;
                v80 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v80) = v80 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v80;
                break;
              case '_':
LABEL_174:
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 15;
                v87 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v87) = v87 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v87;
                break;
              case 'o':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 16;
                v58 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v58) = v58 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v58;
                break;
              case 's':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  (Object *)g_game_base->root_bod_catalog.floor_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = 33;
                v62 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v62) = v62 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v62;
                break;
              case '{':
                if ( v105 > 0 && runtime_cell_anchor->previous_row_same_lane.tile_id == 3 )
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    (Object *)g_game_base->root_bod_catalog.ramp_edges[0].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = 8;
                  v77 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v77) = v77 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v77;
                  runtime_cell_anchor->previous_row_same_lane.tile_id = 11;
                }
                else
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    (Object *)g_game_base->root_bod_catalog.ramp_edges[0].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = 2;
                  v78 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v78) = v78 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v78;
                }
                break;
              case '}':
                if ( v105 > 0 && runtime_cell_anchor->previous_row_same_lane.tile_id == 3 )
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    (Object *)g_game_base->root_bod_catalog.ramp_edges[2].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = 10;
                  v75 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v75) = v75 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v75;
                  runtime_cell_anchor->previous_row_same_lane.tile_id = 13;
                }
                else
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    (Object *)g_game_base->root_bod_catalog.ramp_edges[2].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = 4;
                  v76 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v76) = v76 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v76;
                }
                break;
              default:
                normalize_segment_glyph_for_track_flags((int)game, *v50, v105, 1);
                debug_report_stub();
                break;
            }
            p_anchor_position = &runtime_cell_anchor->cell.anchor_position;
            runtime_cell_anchor->cell.anchor_position.z = 0.0;
            runtime_cell_anchor->cell.anchor_position.y = 0.0;
            runtime_cell_anchor->cell.anchor_position.x = 0.0;
            *(_DWORD *)((char *)&unk_5CCB90 + (_DWORD)runtime_row_anchor) = 0;
            *(_DWORD *)((char *)&unk_5CCB8C + (_DWORD)runtime_row_anchor) = 0;
            *(_DWORD *)((char *)&unk_5CCB88 + (_DWORD)runtime_row_anchor) = 0;
            tile_id = runtime_cell_anchor->cell.tile_id;
            if ( tile_id == 29 || tile_id == 30 )
            {
              p_anchor_position->x = 0.0;
              v92 = (double)v105 + 0.5;
              v113 = v92;
              v93 = v92 - 0.5;
              runtime_cell_anchor->cell.anchor_position.z = v93;
              if ( (g_runtime_config.render_flags & 0x20) != 0 )
              {
                *(_DWORD *)((char *)&unk_5CCB88 + (_DWORD)runtime_row_anchor) = 0;
                runtime_row_anchor->row.attachment_body.position.z = v93;
                track_skirt_color = get_track_skirt_color(&g_game_base->subgame, &out);
                *(tColour *)((char *)&unk_5CCBA0 + (_DWORD)runtime_row_anchor) = *track_skirt_color;
                set_object_color(*(Object **)((char *)&unk_5CCB9C + (_DWORD)runtime_row_anchor), *track_skirt_color);
              }
              else
              {
                v95 = *(_DWORD *)((char *)&unk_5CCB7C + (_DWORD)runtime_row_anchor);
                LOBYTE(v95) = v95 & 0xDF;
                *(_DWORD *)((char *)&unk_5CCB7C + (_DWORD)runtime_row_anchor) = v95;
              }
            }
            else
            {
              p_anchor_position->x = (double)v110 - 4.0 + 0.5;
              runtime_cell_anchor->cell.anchor_position.y = 0.0;
              v91 = runtime_cell_anchor->cell.tile_id;
              if ( v91 == 8 || v91 == 9 || v91 == 10 )
                runtime_cell_anchor->cell.anchor_position.y = 0.5;
              v113 = (double)v105 + 0.5;
              runtime_cell_anchor->cell.anchor_position.z = v113;
            }
            if ( v105 < 4 && game->level_mode != 2 )
              runtime_cell_anchor->cell.anchor_position.y = game->path_pairs[36].primary.primary_samples->transform.position.y;
            if ( runtime_cell_anchor->cell.tile_id == 28 )
              runtime_cell_anchor->cell.anchor_position.y = runtime_cell_anchor->cell.anchor_position.y - 0.029999999;
            v96 = runtime_cell_anchor->cell.tile_id;
            if ( v96 == 1
              || v96 == 21
              || v96 == 20
              || v96 == 33
              || v96 == 34
              || v96 == 15
              || v96 == 16
              || v96 == 23
              || v96 == 24
              || v96 == 25
              || v96 == 26
              || v96 == 27
              || v96 == 18
              || v96 == 19
              || v96 == 17 )
            {
              runtime_cell_anchor->cell.render_arg_1c = (double)(8 - v110) * 0.125;
              runtime_cell_anchor->cell.render_arg_20 = (double)(v105 % 8) * 0.125;
            }
            if ( runtime_cell_anchor->cell.tile_id == 31 )
              p_anchor_position->x = p_anchor_position->x * 1.1;
            if ( runtime_cell_anchor->cell.tile_id == 22 )
            {
              if ( game->level_mode != 3 || (game->runtime_flags & 0x400) != 0 )
                runtime_cell_anchor->cell.anchor_position.y = -3.0;
              runtime_cell_anchor->cell.anchor_position.z = v113;
            }
            v97 = &runtime_cell_anchor->cell.fringe_front;
            v98 = 4;
            do
            {
              v99 = *v97;
              if ( *v97 )
              {
                v99->position.z = 0.0;
                v99->position.y = 0.0;
                v99->position.x = 0.0;
                p_position = (int)&(*v97)->position;
                *(float *)p_position = p_anchor_position->x;
                *(float *)(p_position + 4) = runtime_cell_anchor->cell.anchor_position.y;
                *(float *)(p_position + 8) = runtime_cell_anchor->cell.anchor_position.z;
              }
              ++v97;
              --v98;
            }
            while ( v98 );
            ++v110;
          }
          while ( v110 < 8 );
          ++segment_row_index;
          v101 = ++v105 < game->runtime_row_count;
          v22 = v105;
          v23 = game;
        }
        while ( v101 );
      }
      if ( v23->level_mode != 3 || !v103 )
        ++v111;
    }
    while ( v22 < v23->runtime_row_count );
  }
}
