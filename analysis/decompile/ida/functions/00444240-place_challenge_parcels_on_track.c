/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: place_challenge_parcels_on_track @ 0x444240 */
/* selector: place_challenge_parcels_on_track */

// Implements the authored void `cRSubGame::PlaceParcelsSurvival()` method on the verified SubgameRuntime receiver: derives the quota from owned completion/difficulty state, records eligible runtime_rows indices in the global `gParcelGroupSurvival0` scratch bank, and randomly claims rows while compacting that bank in place. Cross-port path-dependent return residues are incidental and the Windows caller discards EAX.
void __thiscall place_challenge_parcels_on_track(SubgameRuntime *game)
{
  int32_t v2; // eax
  int32_t *zero_bucket_count_lane; // eax
  int32_t candidate_count; // esi
  int32_t runtime_row_index; // eax
  int32_t *survival_row_index_write; // edx
  int32_t *parcel_set_id_cursor; // ecx
  int32_t placed_count; // edi
  int32_t last_candidate_index; // ebx
  __int64 v10; // rax
  int32_t *selected_row_index_entry; // esi
  RuntimeRowStrideAnchor *challenge_runtime_row_anchor; // ecx
  int32_t entries_to_shift; // ecx
  SubRow *projection_row; // esi
  int32_t path_node; // edi
  cRSubLoc *primary_attachment_cell; // ecx
  float y; // ecx
  int32_t track_cell_row_index; // eax
  float upper_bound; // [esp+0h] [ebp-60h]
  int32_t remaining_candidate_count; // [esp+18h] [ebp-48h]
  int32_t projection_scan_index; // [esp+18h] [ebp-48h]
  int out_angle; // [esp+1Ch] [ebp-44h] BYREF
  TransformMatrix transform; // [esp+20h] [ebp-40h] BYREF

  v2 = (__int64)((double)game->challenge_speed_value * 50.0 * 0.0099999998 + game->challenge_difficulty_scalar * 50.0)
     + 1;
  game->level_definition.parcel_count = v2;
  game->level_definition.parcel_quota = v2;
  zero_bucket_count_lane = &g_zero_parcel_buckets[0].candidate_count;
  do
  {
    *zero_bucket_count_lane = 0;
    zero_bucket_count_lane += 131;
  }
  while ( (int)zero_bucket_count_lane < (int)g_zero_parcel_bucket_count_lane_end );
  candidate_count = 0;
  runtime_row_index = 0;
  remaining_candidate_count = 0;
  if ( game->runtime_row_count > 0 )
  {
    survival_row_index_write = g_parcel_group_survival_0;
    parcel_set_id_cursor = &game->runtime_rows[0].parcel_set_id;
    do
    {
      if ( (*(_BYTE *)(parcel_set_id_cursor - 39) & 1) != 0 && *parcel_set_id_cursor == 0 )
      {
        *survival_row_index_write = runtime_row_index;
        ++candidate_count;
        ++survival_row_index_write;
      }
      ++runtime_row_index;
      parcel_set_id_cursor += 61;
    }
    while ( runtime_row_index < game->runtime_row_count );
    remaining_candidate_count = candidate_count;
  }
  placed_count = 0;
  if ( game->level_definition.parcel_count > 0 )
  {
    last_candidate_index = candidate_count - 1;
    while ( candidate_count > 0 )
    {
      upper_bound = (float)remaining_candidate_count;
      v10 = (__int64)random_float_below(upper_bound, aP3);
      selected_row_index_entry = (int32_t *)(4 * v10 + 6572008);
      out_angle = g_parcel_group_survival_0[(_DWORD)v10];
      ++placed_count;
      challenge_runtime_row_anchor = (RuntimeRowStrideAnchor *)((char *)game + 244 * out_angle);
      challenge_runtime_row_anchor->row.flags |= 0x11u;
      challenge_runtime_row_anchor->row.parcel_spawn_position.y = challenge_runtime_row_anchor->row.parcel_spawn_position.y
                                                                + 1.0;
      if ( (challenge_runtime_row_anchor->row.flags & 0x20) != 0 )
        challenge_runtime_row_anchor->row.parcel_spawn_position.x = challenge_runtime_row_anchor->row.parcel_spawn_position.x
                                                                  * -1.0;
      if ( (challenge_runtime_row_anchor->row.flags & 0x4000) != 0 )
        challenge_runtime_row_anchor->row.parcel_spawn_position.z = (double)out_angle
                                                                  + challenge_runtime_row_anchor->row.parcel_spawn_position.z
                                                                  + 0.5;
      if ( (int)v10 < last_candidate_index )
      {
        entries_to_shift = last_candidate_index - v10;
        do
        {
          *selected_row_index_entry = selected_row_index_entry[1];
          ++selected_row_index_entry;
          --entries_to_shift;
        }
        while ( entries_to_shift != 0 );
      }
      --last_candidate_index;
      --remaining_candidate_count;
      if ( placed_count >= game->level_definition.parcel_count )
        break;
      candidate_count = remaining_candidate_count;
    }
  }
  game->level_definition.parcel_count = placed_count;
  debug_report_stub("Challenge parcel count %i\n", placed_count);
  projection_scan_index = 0;
  if ( game->runtime_row_count > 0 )
  {
    projection_row = game->runtime_rows;
    do
    {
      if ( (projection_row->flags & 1) != 0 && (projection_row->flags & 0x40) != 0 )
      {
        path_node = (__int64)projection_row->parcel_spawn_position.z
                  - get_track_cell_row_index(projection_row->primary_attachment_cell);
        if ( path_node < 0 )
          path_node = 0;
        primary_attachment_cell = projection_row->primary_attachment_cell;
        if ( primary_attachment_cell->attachment_template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
        {
          compute_kind42_attachment_transform(
            primary_attachment_cell->attachment_template_record,
            primary_attachment_cell->attachment_template_record->primary_samples[path_node].special_scalar,
            projection_row->parcel_spawn_position.x,
            projection_row->parcel_spawn_position.y,
            &transform,
            (float *)&out_angle);
          y = transform.position.y;
          projection_row->parcel_spawn_position.x = transform.position.x;
          projection_row->parcel_spawn_position.y = y;
        }
        else
        {
          track_cell_row_index = get_track_cell_row_index(primary_attachment_cell);
          get_path_position_at_node(
            projection_row->primary_attachment_cell->attachment_template_record,
            &projection_row->parcel_spawn_position,
            path_node,
            track_cell_row_index,
            &projection_row->parcel_spawn_position);
        }
      }
      ++projection_row;
      ++projection_scan_index;
    }
    while ( projection_scan_index < game->runtime_row_count );
  }
}
