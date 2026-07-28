/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: populate_runtime_track_cells_from_segments @ 0x435eb0 */
/* selector: populate_runtime_track_cells_from_segments */

// Windows implementation of authored `cRSubGame::BuildLevel()`. It copies authored segment rows into the generated runtime grid, seeds Goldy's visible life stock to 3 before `initialize_subgoldy` runs, and seeds the course row bounds: non-random levels use the final `Last:` block boundary while the mode-1 random branch keeps the authored `Length:` lane scaled by the challenge scalar before subtracting the final `Last:` block rows. Each lane iteration writes the physical runtime `SubLoc` selected by `lane`, while a distinct mirrored authored lane indexes the borrowed active `SubSegment::glyph_rows`; first/last-block bounds produce the byte `edge_row` input consumed by the glyph normalizer. Runtime cell object selection reuses each `SubLoc` cell's shared `cRBod`/`BodBase` prefix and borrows render objects from the root catalog, while authored row models and installed path strips belong to the embedded `SubRow::row_model` and `SubRow::attachment_body`; there is no separate track-row BOD-slot owner.
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
  int32_t *segment_row_count_cursor; // ecx
  SubRowParcelSpawnYStrideCursor *parcel_spawn_y_cursor; // edi
  int32_t cell_lanes_remaining; // ebp
  TrackRowCellLaneAndFlagsStrideCursor *lane_and_flags_cursor; // esi
  uint32_t cell_lane_and_flags; // ecx
  uint32_t cell_list_flags; // edx
  TrackRowCellFringeFrontStrideCursor *next_row_fringe_front_cursor; // eax
  int32_t remaining_cell_lanes; // ecx
  TrackRowCellFringeFrontStrideCursor *cell_fringe_front_cursor; // esi
  int32_t visited_segment_index; // eax
  uint8_t *visited_cursor; // ecx
  int32_t runtime_row_index; // edi
  SubgameRuntime *build_runtime_owner; // ebp
  SubSegment *selected_segment; // esi
  double segment_count; // st7
  int32_t v26; // eax
  int32_t v27; // edx
  int32_t selected_segment_row_count; // eax
  int32_t v29; // ecx
  int32_t completion_row_start; // eax
  SubSegment *source_segment; // edx
  int32_t row_count; // eax
  int32_t v33; // esi
  int32_t runtime_row_count; // ecx
  int v35; // eax
  SubSegmentRowStrideAnchor *segment_row_anchor; // esi
  SubRow *v37; // eax
  uint32_t flags; // ecx
  SubRow *v39; // eax
  uint32_t v40; // ecx
  RuntimeRowStrideAnchor *runtime_row_anchor; // ebx
  uint32_t v42; // eax
  uint32_t v43; // eax
  uint32_t v44; // eax
  uint32_t v45; // eax
  int32_t v46; // ebp
  RuntimeCellStrideAnchor *runtime_cell_anchor; // esi
  uint32_t lane_and_flags; // eax
  TrackRowCell *runtime_cell; // edi
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
  int32_t attachment_template_index; // ecx
  cRPath *selected_attachment_path; // ecx
  int32_t attachment_span_index; // edx
  SubRow *stamped_row; // ecx
  uint32_t v85; // eax
  uint32_t v86; // ecx
  uint32_t v87; // eax
  uint32_t v88; // eax
  char v89; // al
  Vec3 *p_anchor_position; // edi
  SubLocTileId tile_id; // al
  SubLocTileId v92; // al
  double v93; // st7
  double v94; // st7
  tColour *track_skirt_color; // eax
  uint32_t v96; // eax
  SubLocTileId v97; // al
  Fringe **fringe_slot; // ecx
  int32_t remaining_fringe_slots; // edx
  Fringe *fringe_object; // eax
  Vec3 *fringe_position; // eax
  bool v102; // cc
  float upper_bound; // [esp+0h] [ebp-5Ch]
  char *v104; // [esp+4h] [ebp-58h]
  char *source_name; // [esp+4h] [ebp-58h]
  char first_or_last_row; // [esp+1Ah] [ebp-42h]
  char attachment_entry_installed; // [esp+1Bh] [ebp-41h]
  int32_t build_row; // [esp+1Ch] [ebp-40h]
  SubSegment *active_segment; // [esp+20h] [ebp-3Ch]
  int32_t segment_row_index; // [esp+28h] [ebp-34h]
  int32_t rows_remaining; // [esp+2Ch] [ebp-30h]
  int32_t lane; // [esp+2Ch] [ebp-30h]
  int32_t row_event_owner; // [esp+30h] [ebp-2Ch]
  TrackRowCellFringeFrontStrideCursor *row_fringe_front_cursor; // [esp+34h] [ebp-28h]
  float v116; // [esp+34h] [ebp-28h]
  int32_t segment_cursor; // [esp+38h] [ebp-24h]
  int32_t trampoline_counter; // [esp+3Ch] [ebp-20h]
  int edge_row; // [esp+40h] [ebp-1Ch]
  char edge_rowa; // [esp+40h] [ebp-1Ch]
  tColour out; // [esp+4Ch] [ebp-10h] BYREF

  if ( game->selected_level_record_active != 0 )
  {
    runtime_build_seed = game->selected_level_record->runtime_build_seed;
  }
  else
  {
    level_mode = game->level_mode;
    if ( level_mode == 4 || level_mode == 7 )
      runtime_build_seed = 0;
    else
      runtime_build_seed = (__int64)random_float_below(32768.0, aSeed);
  }
  v4 = game->level_mode;
  if ( v4 != 0 )
  {
    v5 = v4 - 1;
    if ( v5 != 0 )
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
  game->player.shooting_tier = 0;
  set_math_random_seed(runtime_build_seed);
  select_level_track_texture_set(&g_game_base->track, game->level_definition.track_texture_set);
  v7 = game->level_mode;
  if ( v7 == 0 || v7 == 7 || v7 == 4 || v7 == 1 )
  {
    game->first_block_row_count = game->level_definition.first_segment.row_count;
    edge_row = game->level_definition.random_length;
    game->runtime_row_count = edge_row;
    if ( v7 == 1 )
      game->runtime_row_count = (__int64)((game->challenge_difficulty_scalar * 0.64999998 + 0.34999999)
                                        * (double)edge_row);
    if ( game->level_definition.random_enabled == 0 )
    {
      v10 = 0;
      game->runtime_row_count = game->level_definition.first_segment.row_count
                              + game->level_definition.last_segment.row_count;
      if ( game->level_definition.segment_count > 0 )
      {
        segment_row_count_cursor = &game->level_definition.segment_slots[0].row_count;
        do
        {
          ++v10;
          game->runtime_row_count += *segment_row_count_cursor;
          segment_row_count_cursor += 4232;
        }
        while ( v10 < game->level_definition.segment_count );
      }
      segment_cursor = 0;
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
    while ( v8 != 0 );
    segment_cursor = 0;
    game->completion_row_start = v9 - game->level_definition.last_segment.row_count;
    game->completion_row_start = v9 - game->level_definition.last_segment.row_count;
  }
  game->track_mirror_enabled = 0;
  game->track_mirror_repeat_count = 0;
  trampoline_counter = 0;
  first_or_last_row = 0;
  row_event_owner = 0;
  game->player.follow_state.flag_3c = 0;
  row_fringe_front_cursor = (TrackRowCellFringeFrontStrideCursor *)&game->runtime_cells[0][0].fringe_front;
  parcel_spawn_y_cursor = (SubRowParcelSpawnYStrideCursor *)&game->runtime_rows[0].parcel_spawn_position.y;
  for ( rows_remaining = 3200; rows_remaining != 0; --rows_remaining )
  {
    cell_lanes_remaining = 8;
    *(_DWORD *)parcel_spawn_y_cursor[-1]._stride_tail = 0;
    parcel_spawn_y_cursor->installed_heading_delta = 0.0;
    parcel_spawn_y_cursor->attachment_template_index = 0;
    parcel_spawn_y_cursor->ring_speed = 0.0;
    parcel_spawn_y_cursor->primary_attachment_cell = nullptr;
    parcel_spawn_y_cursor->parcel_spawn_z = 0.0;
    parcel_spawn_y_cursor->parcel_spawn_y = 0.0;
    *(_DWORD *)&parcel_spawn_y_cursor[-1]._stride_tail[144] = 0;
    parcel_spawn_y_cursor->parcel_set_id = 0;
    parcel_spawn_y_cursor->source_segment = nullptr;
    parcel_spawn_y_cursor->row_event_id = 0;
    lane_and_flags_cursor = (TrackRowCellLaneAndFlagsStrideCursor *)&row_fringe_front_cursor[-1]._stride_tail[64];
    do
    {
      cell_lane_and_flags = lane_and_flags_cursor->lane_and_flags;
      BYTE1(cell_lane_and_flags) = BYTE1(lane_and_flags_cursor->lane_and_flags) & 0x5F;
      lane_and_flags_cursor->lane_and_flags = cell_lane_and_flags;
      lane_and_flags_cursor[-1]._stride_tail[61] = 0;
      LOWORD(lane_and_flags_cursor->lane_and_flags) = 0;
      lane_and_flags_cursor->lane_and_flags &= 0xFFFFAFA7;
      LOWORD(lane_and_flags_cursor->lane_and_flags) = 0;
      cell_list_flags = *(_DWORD *)&lane_and_flags_cursor[-1]._stride_tail[4];
      LOBYTE(cell_list_flags) = cell_list_flags & 0x7F;
      *(_DWORD *)&lane_and_flags_cursor[-1]._stride_tail[4] = cell_list_flags;
      set_color_white((tColour *)&lane_and_flags_cursor[-1]._stride_tail[40]);
      ++lane_and_flags_cursor;
      --cell_lanes_remaining;
    }
    while ( cell_lanes_remaining != 0 );
    next_row_fringe_front_cursor = row_fringe_front_cursor;
    remaining_cell_lanes = 8;
    do
    {
      cell_fringe_front_cursor = next_row_fringe_front_cursor++;
      --remaining_cell_lanes;
      cell_fringe_front_cursor->fringe_front = nullptr;
      cell_fringe_front_cursor->fringe_right = nullptr;
      cell_fringe_front_cursor->fringe_left = nullptr;
      cell_fringe_front_cursor->fringe_back = nullptr;
    }
    while ( remaining_cell_lanes != 0 );
    row_fringe_front_cursor = next_row_fringe_front_cursor;
    ++parcel_spawn_y_cursor;
  }
  if ( game->level_definition.random_enabled == 1 )
  {
    visited_segment_index = 0;
    if ( game->level_definition.segment_count > 0 )
    {
      visited_cursor = &game->level_definition.segment_slots[0].visited;
      do
      {
        *visited_cursor = 0;
        ++visited_segment_index;
        visited_cursor += 16928;
      }
      while ( visited_segment_index < game->level_definition.segment_count );
    }
  }
  build_row = 0;
  if ( game->runtime_row_count > 0 )
  {
    runtime_row_index = 0;
    build_runtime_owner = game;
    do
    {
      if ( runtime_row_index != 0 )
      {
        if ( runtime_row_index != build_runtime_owner->completion_row_start
          || build_runtime_owner->level_definition.random_enabled != 0 )
        {
          build_runtime_owner->base_subgame_rate = 1.0;
          if ( build_runtime_owner->level_definition.random_enabled == 1 )
          {
            if ( build_runtime_owner->level_mode == 1 )
            {
              v104 = aSegdif;
              segment_count = (build_runtime_owner->challenge_difficulty_scalar * 0.89999998 + 0.1)
                            * (double)build_runtime_owner->level_definition.segment_count;
            }
            else
            {
              segment_count = (double)build_runtime_owner->level_definition.segment_count;
              v104 = aSegtra;
            }
            upper_bound = segment_count;
            selected_segment = &build_runtime_owner->level_definition.segment_slots[(__int64)((double)(int)(__int64)random_float_below(upper_bound, v104)
                                                                                            * build_runtime_owner->base_subgame_rate)];
            active_segment = selected_segment;
            selected_segment->visited = 1;
          }
          else
          {
            v26 = segment_cursor;
            v27 = segment_cursor++;
            selected_segment = (SubSegment *)((char *)build_runtime_owner->level_definition.segment_slots
                                            + 0x4000 * v27
                                            + 512 * v26
                                            + 32 * v26);
            active_segment = selected_segment;
          }
        }
        else
        {
          selected_segment = &build_runtime_owner->level_definition.last_segment;
          first_or_last_row = 1;
          active_segment = &build_runtime_owner->level_definition.last_segment;
          build_runtime_owner->level_definition.last_segment.row_base = runtime_row_index;
        }
      }
      else
      {
        selected_segment = &build_runtime_owner->level_definition.first_segment;
        first_or_last_row = 1;
        active_segment = &build_runtime_owner->level_definition.first_segment;
        build_runtime_owner->level_definition.first_segment.row_base = 0;
      }
      switch_track_mirror(build_runtime_owner);
      selected_segment_row_count = selected_segment->row_count;
      selected_segment->row_base = runtime_row_index;
      if ( selected_segment_row_count < 0 )
        report_errorf(aNegativeSegmen);
      segment_row_index = 0;
      if ( runtime_row_index < build_runtime_owner->runtime_row_count )
      {
        do
        {
          if ( segment_row_index >= active_segment->row_count )
            break;
          v29 = build_runtime_owner->level_mode;
          if ( v29 == 2
            || (completion_row_start = build_runtime_owner->completion_row_start,
                runtime_row_index < completion_row_start) )
          {
            source_segment = active_segment;
          }
          else
          {
            if ( v29 == 0
              || v29 == 4
              || v29 == 1
              || v29 == 7
              || (source_segment = &build_runtime_owner->level_definition_scratch.segment_slots[1], v29 == 3) )
            {
              source_segment = &build_runtime_owner->level_definition.last_segment;
            }
            active_segment = source_segment;
            if ( runtime_row_index == completion_row_start )
              segment_row_index = 0;
          }
          if ( v29 != 2 )
          {
            row_count = source_segment->row_count;
            v33 = build_runtime_owner->completion_row_start;
            if ( runtime_row_index + row_count - segment_row_index <= v33 )
            {
              source_segment = active_segment;
            }
            else
            {
              source_segment = active_segment;
              if ( active_segment != &build_runtime_owner->level_definition_scratch.segment_slots[1]
                && active_segment != &build_runtime_owner->level_definition_scratch.segment_slots[3]
                && active_segment != &build_runtime_owner->level_definition_scratch.segment_slots[4]
                && (v29 == 0 || v29 == 4 || v29 == 1 || v29 == 7 || v29 == 3)
                && active_segment != &build_runtime_owner->level_definition.last_segment )
              {
                runtime_row_count = build_runtime_owner->runtime_row_count;
                v35 = runtime_row_index + row_count - v33 - segment_row_index;
                build_runtime_owner->completion_row_start = v35 + v33;
                build_runtime_owner->runtime_row_count = v35 + runtime_row_count;
              }
            }
          }
          if ( build_runtime_owner->track_mirror_enabled != 0 )
            build_runtime_owner->runtime_rows[runtime_row_index].flags |= 0x20u;
          segment_row_anchor = (SubSegmentRowStrideAnchor *)((char *)source_segment + 56 * segment_row_index);
          if ( (segment_row_anchor->row.flags & 0x100) != 0 )
          {
            v37 = &build_runtime_owner->runtime_rows[runtime_row_index];
            flags = v37->flags;
            BYTE1(flags) = BYTE1(v37->flags) | 1;
            v37->flags = flags;
          }
          if ( (BYTE1(segment_row_anchor->row.flags) & 0x80u) != 0 )
          {
            v39 = &build_runtime_owner->runtime_rows[runtime_row_index];
            v40 = v39->flags;
            BYTE1(v40) = BYTE1(v39->flags) | 0x80;
            v39->flags = v40;
          }
          runtime_row_anchor = (RuntimeRowStrideAnchor *)((char *)build_runtime_owner + 244 * runtime_row_index);
          runtime_row_anchor->row.source_segment = source_segment;
          runtime_row_anchor->row.row_event_id = row_event_owner;
          if ( (segment_row_anchor->row.flags & 2) != 0 )
          {
            v42 = runtime_row_anchor->row.flags;
            LOBYTE(v42) = v42 | 2;
            runtime_row_anchor->row.flags = v42;
            set_bod_object(
              &runtime_row_anchor->row.row_model.body.bod,
              g_game_base->directx_loader.cached_x_mesh_slots[segment_row_anchor->row.object_id].object);
            set_matrix_identity(&runtime_row_anchor->row.row_model.body.transform);
            runtime_row_anchor->row.row_model.body.transform.position = segment_row_anchor->row.object_position;
            runtime_row_anchor->row.row_model.body.transform.position.z = (double)build_row
                                                                        + runtime_row_anchor->row.row_model.body.transform.position.z;
            if ( (segment_row_anchor->row.flags & 8) != 0 )
            {
              v43 = runtime_row_anchor->row.flags;
              LOBYTE(v43) = v43 | 8;
              runtime_row_anchor->row.flags = v43;
              runtime_row_anchor->row.row_model.velocity = segment_row_anchor->row.object_velocity;
            }
            else
            {
              runtime_row_anchor->row.row_model.velocity.z = 0.0;
              runtime_row_anchor->row.row_model.velocity.y = 0.0;
              runtime_row_anchor->row.row_model.velocity.x = 0.0;
            }
            source_segment = active_segment;
          }
          if ( (segment_row_anchor->row.flags & 1) != 0 )
          {
            runtime_row_anchor->row.flags |= 0x4001u;
            runtime_row_anchor->row.parcel_set_id = source_segment->rows[segment_row_index].parcel_set_id;
            runtime_row_anchor->row.parcel_spawn_position = segment_row_anchor->row.local_position;
          }
          if ( (segment_row_anchor->row.flags & 8) != 0 )
          {
            v44 = runtime_row_anchor->row.flags;
            LOBYTE(v44) = v44 | 8;
            runtime_row_anchor->row.flags = v44;
            runtime_row_anchor->row.attachment_template_index = segment_row_anchor->row.path_template_index;
          }
          if ( (segment_row_anchor->row.flags & 4) != 0 )
          {
            v45 = runtime_row_anchor->row.flags;
            LOBYTE(v45) = v45 | 4;
            runtime_row_anchor->row.flags = v45;
          }
          if ( (segment_row_anchor->row.flags & 0x200) != 0 )
            runtime_row_anchor->row.flags |= 0x200u;
          if ( (segment_row_anchor->row.flags & 0x400) != 0 )
            runtime_row_anchor->row.flags |= 0x400u;
          if ( (segment_row_anchor->row.flags & 0x2000) != 0 )
            runtime_row_anchor->row.flags |= 0x2000u;
          if ( (segment_row_anchor->row.flags & 0x800) != 0 )
            runtime_row_anchor->row.flags |= 0x800u;
          if ( (segment_row_anchor->row.flags & 0x1000) != 0 )
            runtime_row_anchor->row.flags |= 0x1000u;
          attachment_entry_installed = 0;
          lane = 0;
          *((_DWORD *)&build_runtime_owner->runtime_rows[0].ring_speed + 60 * runtime_row_index + runtime_row_index) = segment_row_anchor->row.ring_speed.bits;
          do
          {
            if ( game->track_mirror_enabled != 0 )
              v46 = 7 - lane;
            else
              v46 = lane;
            runtime_cell_anchor = (RuntimeCellStrideAnchor *)((char *)game + 672 * build_row + 84 * lane);
            lane_and_flags = runtime_cell_anchor->cell.lane_and_flags;
            LOBYTE(lane_and_flags) = lane_and_flags & 0xE0;
            runtime_cell_anchor->cell.lane_and_flags = lane & 7 ^ lane_and_flags;
            runtime_cell_anchor->cell.fringe_front = nullptr;
            runtime_cell_anchor->cell.fringe_right = nullptr;
            runtime_cell_anchor->cell.fringe_left = nullptr;
            runtime_cell_anchor->cell.fringe_back = nullptr;
            if ( build_row < game->first_block_row_count || (edge_rowa = 0, build_row >= game->completion_row_start) )
              edge_rowa = 1;
            runtime_cell = &runtime_cell_anchor->cell;
            set_bod_object((BodBase *)&runtime_cell_anchor->cell, nullptr);
            v50 = &active_segment->glyph_rows[v46][segment_row_index];
            v51 = normalize_segment_glyph_for_track_flags(game, *v50, build_row, edge_rowa);
            switch ( v51 )
            {
              case ' ':
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_EMPTY;
                list_flags = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(list_flags) = list_flags & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = list_flags;
                break;
              case '#':
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_FLOOR_HASH_MARKER;
                v54 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v54) = v54 & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = v54;
                break;
              case '$':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_HEALTH_PICKUP;
                v57 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v57) = v57 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v57;
                break;
              case '&':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.floor_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SALT_HAZARD;
                v63 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v63) = v63 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v63;
                break;
              case '(':
                v69 = trampoline_counter + 1;
                v70 = runtime_cell_anchor->cell.bod.list_flags & 0xFFFFFFDF;
                v71 = trampoline_counter++ == 14;
                runtime_cell_anchor->cell.bod.list_flags = v70;
                v72 = v70;
                if ( v71 )
                {
                  trampoline_counter = 0;
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_TRAMPOLINE;
                }
                else
                {
                  if ( v69 == 8 )
                  {
                    set_bod_object(
                      (BodBase *)&runtime_cell_anchor->cell,
                      g_game_base->root_bod_catalog.trampoline.object);
                    runtime_cell_anchor->cell.bod.list_flags |= 0x20u;
                    store_color4f(&game->runtime_cells[build_row][lane].color, 1.0, 1.0, 1.0, 0.99900001);
                  }
                  else
                  {
                    LOBYTE(v72) = v70 & 0xDF;
                    runtime_cell_anchor->cell.bod.list_flags = v72;
                  }
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_TRAMPOLINE;
                }
                break;
              case '+':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SPEEDUP_PICKUP;
                v65 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v65) = v65 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v65;
                break;
              case ',':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.universe_hole.object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_UNIVERSE_HOLE;
                v64 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v64) = v64 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v64;
                break;
              case '-':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.floor_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_FLOOR_DASH;
                v67 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v67) = v67 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v67;
                break;
              case '.':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.floor_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_FLOOR_DOT;
                v61 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v61) = v61 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v61;
                break;
              case '0':
                if ( game->level_mode == 1 )
                {
                  v86 = runtime_row_anchor->row.flags;
                  BYTE1(v86) &= ~0x40u;
                  runtime_row_anchor->row.flags = v86 | 1;
                  runtime_row_anchor->row.parcel_set_id = 0;
                  runtime_row_anchor->row.parcel_spawn_position.x = (double)lane - 4.0 + 0.5;
                  runtime_row_anchor->row.parcel_spawn_position.y = runtime_cell_anchor->cell.anchor_position.y;
                  runtime_row_anchor->row.parcel_spawn_position.z = (double)build_row + 0.5;
                  if ( game->track_mirror_enabled != 0 )
                    runtime_row_anchor->row.parcel_spawn_position.x = runtime_row_anchor->row.parcel_spawn_position.x
                                                                    * -1.0;
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
                if ( (runtime_row_anchor->row.flags & 0xC0) == 0 )
                  goto LABEL_174;
                v88 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v88) = v88 & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = v88;
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_EMPTY;
                break;
              case '<':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.ramp_edges[1].object);
                runtime_cell_anchor->cell.render_arg_1c = 0.0;
                runtime_cell_anchor->cell.render_arg_20 = 0.0;
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_LESS;
                v79 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v79) = v79 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v79;
                break;
              case '=':
              case '|':
                set_bod_object((BodBase *)&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.pillars[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_WALL2;
                v68 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v68) = v68 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v68;
                break;
              case '>':
                if ( build_row > 0 && runtime_cell_anchor->previous_row_same_lane.tile_id == SUBLOC_TILE_RAMP_GREATER )
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    g_game_base->root_bod_catalog.ramp_edges[1].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_GREATER_RAISED;
                  v73 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v73) = v73 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v73;
                  runtime_cell_anchor->previous_row_same_lane.tile_id = SUBLOC_TILE_RAMP_GREATER_BACKPATCH;
                }
                else
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    g_game_base->root_bod_catalog.ramp_edges[1].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_GREATER;
                  v74 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v74) = v74 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v74;
                }
                break;
              case '@':
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_EMPTY;
                v55 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v55) = v55 & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = v55;
                switch_track_mirror(game);
                break;
              case 'F':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SLIDE_F;
                v60 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v60) = v60 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v60;
                break;
              case 'G':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_GLYPH_G;
                v56 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v56) = v56 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v56;
                break;
              case 'J':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_JETPACK_PICKUP;
                v66 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v66) = v66 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v66;
                break;
              case 'M':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SLUG_HAZARD;
                v59 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v59) = v59 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v59;
                break;
              case 'P':
              case 'p':
                if ( v51 == 80 )
                {
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_PATH_ENTRY_UPPERCASE;
                }
                else if ( v51 == 112 )
                {
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_PATH_ENTRY_LOWERCASE;
                }
                attachment_template_index = runtime_row_anchor->row.attachment_template_index;
                if ( game->track_mirror_enabled != 0 )
                  selected_attachment_path = &game->path_pairs[attachment_template_index].secondary;
                else
                  selected_attachment_path = &game->path_pairs[attachment_template_index].primary;
                runtime_cell_anchor->cell.attachment_template_record = selected_attachment_path;
                runtime_cell_anchor->cell.bod.list_flags &= ~0x20u;
                if ( attachment_entry_installed == 0 )
                {
                  attachment_entry_installed = 1;
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    runtime_cell_anchor->cell.attachment_template_record->bod.object);
                  runtime_cell_anchor->cell.bod.list_flags |= 0x20u;
                  set_bod_object(
                    &runtime_row_anchor->row.attachment_body,
                    runtime_cell_anchor->cell.attachment_template_record->fringe_mesh_bod.object);
                  runtime_row_anchor->row.attachment_body.bod.list_flags |= 0x20u;
                  LODWORD(runtime_row_anchor->row.installed_heading_delta) = active_segment->angle_radians.bits;
                  attachment_span_index = 0;
                  if ( (int)runtime_cell_anchor->cell.attachment_template_record->row_span_count > 0 )
                  {
                    stamped_row = &runtime_row_anchor->row;
                    do
                    {
                      v85 = stamped_row->flags;
                      if ( (stamped_row->flags & 0x40) != 0 )
                      {
                        LOBYTE(v85) = v85 | 0x80;
                        stamped_row->flags = v85;
                        stamped_row->secondary_attachment_cell = runtime_cell;
                      }
                      else
                      {
                        LOBYTE(v85) = v85 | 0x40;
                        stamped_row->flags = v85;
                        stamped_row->primary_attachment_cell = runtime_cell;
                      }
                      ++attachment_span_index;
                      ++stamped_row;
                    }
                    while ( attachment_span_index < (signed int)runtime_cell_anchor->cell.attachment_template_record->row_span_count );
                  }
                }
                break;
              case 'R':
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RING_MARKER;
                v53 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v53) = v53 & 0xDF;
                runtime_cell_anchor->cell.bod.list_flags = v53;
                break;
              case '[':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.ramp_edges[0].object);
                runtime_cell_anchor->cell.render_arg_1c = 0.0;
                runtime_cell_anchor->cell.render_arg_20 = 0.0;
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_LEFT_BRACKET;
                v80 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v80) = v80 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v80;
                break;
              case '_':
LABEL_174:
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SLIDE_UNDERSCORE;
                v87 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v87) = v87 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v87;
                break;
              case 'o':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.slide_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SLIDE_O;
                v58 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v58) = v58 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v58;
                break;
              case 's':
                set_bod_object(
                  (BodBase *)&runtime_cell_anchor->cell,
                  g_game_base->root_bod_catalog.floor_slices.storage[0].object);
                runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_GARBAGE_HAZARD;
                v62 = runtime_cell_anchor->cell.bod.list_flags;
                LOBYTE(v62) = v62 | 0x20;
                runtime_cell_anchor->cell.bod.list_flags = v62;
                break;
              case '{':
                if ( build_row > 0 && runtime_cell_anchor->previous_row_same_lane.tile_id == SUBLOC_TILE_RAMP_GREATER )
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    g_game_base->root_bod_catalog.ramp_edges[0].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED;
                  v77 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v77) = v77 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v77;
                  runtime_cell_anchor->previous_row_same_lane.tile_id = SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH;
                }
                else
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    g_game_base->root_bod_catalog.ramp_edges[0].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_LEFT_BRACE;
                  v78 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v78) = v78 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v78;
                }
                break;
              case '}':
                if ( build_row > 0 && runtime_cell_anchor->previous_row_same_lane.tile_id == SUBLOC_TILE_RAMP_GREATER )
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    g_game_base->root_bod_catalog.ramp_edges[2].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED;
                  v75 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v75) = v75 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v75;
                  runtime_cell_anchor->previous_row_same_lane.tile_id = SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH;
                }
                else
                {
                  set_bod_object(
                    (BodBase *)&runtime_cell_anchor->cell,
                    g_game_base->root_bod_catalog.ramp_edges[2].object);
                  runtime_cell_anchor->cell.render_arg_1c = 0.0;
                  runtime_cell_anchor->cell.render_arg_20 = 0.0;
                  runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_RIGHT_BRACE;
                  v76 = runtime_cell_anchor->cell.bod.list_flags;
                  LOBYTE(v76) = v76 | 0x20;
                  runtime_cell_anchor->cell.bod.list_flags = v76;
                }
                break;
              default:
                source_name = active_segment->source_name;
                v89 = normalize_segment_glyph_for_track_flags(game, *v50, build_row, 1);
                debug_report_stub("TrackError:%c in Segment %s\n", v89, source_name);
                break;
            }
            p_anchor_position = &runtime_cell_anchor->cell.anchor_position;
            runtime_cell_anchor->cell.anchor_position.z = 0.0;
            runtime_cell_anchor->cell.anchor_position.y = 0.0;
            runtime_cell_anchor->cell.anchor_position.x = 0.0;
            runtime_row_anchor->row.attachment_body.position.z = 0.0;
            runtime_row_anchor->row.attachment_body.position.y = 0.0;
            runtime_row_anchor->row.attachment_body.position.x = 0.0;
            tile_id = runtime_cell_anchor->cell.tile_id;
            if ( tile_id == SUBLOC_TILE_PATH_ENTRY_LOWERCASE || tile_id == SUBLOC_TILE_PATH_ENTRY_UPPERCASE )
            {
              p_anchor_position->x = 0.0;
              v93 = (double)build_row + 0.5;
              v116 = v93;
              v94 = v93 - 0.5;
              runtime_cell_anchor->cell.anchor_position.z = v94;
              if ( (g_runtime_config.render_flags & 0x20) != 0 )
              {
                runtime_row_anchor->row.attachment_body.position.x = 0.0;
                runtime_row_anchor->row.attachment_body.position.z = v94;
                track_skirt_color = get_track_skirt_color(&g_game_base->subgame, &out);
                runtime_row_anchor->row.attachment_body.color = *track_skirt_color;
                set_object_color(runtime_row_anchor->row.attachment_body.object, *track_skirt_color);
              }
              else
              {
                v96 = runtime_row_anchor->row.attachment_body.bod.list_flags;
                LOBYTE(v96) = v96 & 0xDF;
                runtime_row_anchor->row.attachment_body.bod.list_flags = v96;
              }
            }
            else
            {
              p_anchor_position->x = (double)lane - 4.0 + 0.5;
              runtime_cell_anchor->cell.anchor_position.y = 0.0;
              v92 = runtime_cell_anchor->cell.tile_id;
              if ( v92 == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
                || v92 == SUBLOC_TILE_RAMP_GREATER_RAISED
                || v92 == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED )
              {
                runtime_cell_anchor->cell.anchor_position.y = 0.5;
              }
              v116 = (double)build_row + 0.5;
              runtime_cell_anchor->cell.anchor_position.z = v116;
            }
            if ( build_row < 4 && game->level_mode != 2 )
              runtime_cell_anchor->cell.anchor_position.y = game->path_pairs[36].primary.primary_samples->transform.position.y;
            if ( runtime_cell_anchor->cell.tile_id == SUBLOC_TILE_UNIVERSE_HOLE )
              runtime_cell_anchor->cell.anchor_position.y = runtime_cell_anchor->cell.anchor_position.y - 0.029999999;
            v97 = runtime_cell_anchor->cell.tile_id;
            if ( v97 == SUBLOC_TILE_FLOOR_DOT
              || v97 == SUBLOC_TILE_FLOOR_DASH
              || v97 == SUBLOC_TILE_FLOOR_VARIANT_14
              || v97 == SUBLOC_TILE_GARBAGE_HAZARD
              || v97 == SUBLOC_TILE_SALT_HAZARD
              || v97 == SUBLOC_TILE_SLIDE_UNDERSCORE
              || v97 == SUBLOC_TILE_SLIDE_O
              || v97 == SUBLOC_TILE_HEALTH_PICKUP
              || v97 == SUBLOC_TILE_SPEEDUP_PICKUP
              || v97 == SUBLOC_TILE_JETPACK_PICKUP
              || v97 == SUBLOC_TILE_SLIDE_VARIANT_1A
              || v97 == SUBLOC_TILE_FLOOR_VARIANT_1B
              || v97 == SUBLOC_TILE_SLUG_HAZARD
              || v97 == SUBLOC_TILE_SLIDE_F
              || v97 == SUBLOC_TILE_GLYPH_G )
            {
              runtime_cell_anchor->cell.render_arg_1c = (double)(8 - lane) * 0.125;
              runtime_cell_anchor->cell.render_arg_20 = (double)(build_row % 8) * 0.125;
            }
            if ( runtime_cell_anchor->cell.tile_id == SUBLOC_TILE_WIDE_VARIANT_1F )
              p_anchor_position->x = p_anchor_position->x * 1.1;
            if ( runtime_cell_anchor->cell.tile_id == SUBLOC_TILE_TRAMPOLINE )
            {
              if ( game->level_mode != 3 || (game->runtime_flags & 0x400) != 0 )
                runtime_cell_anchor->cell.anchor_position.y = -3.0;
              runtime_cell_anchor->cell.anchor_position.z = v116;
            }
            fringe_slot = &runtime_cell_anchor->cell.fringe_front;
            for ( remaining_fringe_slots = 4; remaining_fringe_slots != 0; --remaining_fringe_slots )
            {
              fringe_object = *fringe_slot;
              if ( *fringe_slot != nullptr )
              {
                fringe_object->bod.position.z = 0.0;
                fringe_object->bod.position.y = 0.0;
                fringe_object->bod.position.x = 0.0;
                fringe_position = &(*fringe_slot)->bod.position;
                fringe_position->x = p_anchor_position->x;
                fringe_position->y = runtime_cell_anchor->cell.anchor_position.y;
                fringe_position->z = runtime_cell_anchor->cell.anchor_position.z;
              }
              ++fringe_slot;
            }
            ++lane;
          }
          while ( lane < 8 );
          ++segment_row_index;
          v102 = ++build_row < game->runtime_row_count;
          runtime_row_index = build_row;
          build_runtime_owner = game;
        }
        while ( v102 );
      }
      if ( build_runtime_owner->level_mode != 3 || first_or_last_row == 0 )
        ++row_event_owner;
    }
    while ( runtime_row_index < build_runtime_owner->runtime_row_count );
  }
}
