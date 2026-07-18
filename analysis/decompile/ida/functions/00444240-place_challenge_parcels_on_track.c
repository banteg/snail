/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: place_challenge_parcels_on_track @ 0x444240 */
/* selector: place_challenge_parcels_on_track */

// Implements `cRSubGame::PlaceParcelsSurvival()` on the verified SubgameRuntime receiver: derives the quota from owned completion/difficulty state, records eligible runtime_rows indices in the global `gParcelGroupSurvival0` scratch bank, and randomly claims rows while compacting that bank in place.
void __thiscall place_challenge_parcels_on_track(SubgameRuntime *game)
{
  int32_t v2; // eax
  int32_t *p_candidate_count; // eax
  int v4; // esi
  int32_t v5; // eax
  int *v6; // edx
  _DWORD *v7; // ecx
  int32_t v8; // edi
  int v9; // ebx
  __int64 v10; // rax
  _DWORD *v11; // esi
  RuntimeRowStrideAnchor *challenge_runtime_row_anchor; // ecx
  int v13; // ecx
  SubRow *projection_row; // esi
  int32_t v15; // edi
  TrackRowCell *primary_attachment_cell; // ecx
  float y; // ecx
  int32_t track_cell_row_index; // eax
  float v19; // [esp+0h] [ebp-60h]
  int v20; // [esp+18h] [ebp-48h]
  int32_t v21; // [esp+18h] [ebp-48h]
  int out_angle; // [esp+1Ch] [ebp-44h] BYREF
  TransformMatrix transform; // [esp+20h] [ebp-40h] BYREF

  v2 = (__int64)((double)game->completion_bonus_x_source * 50.0 * 0.0099999998 + game->challenge_difficulty_scalar
                                                                               * 50.0)
     + 1;
  game->level_definition.parcel_count = v2;
  game->level_definition.parcel_quota = v2;
  p_candidate_count = &g_zero_parcel_buckets[0].candidate_count;
  do
  {
    *p_candidate_count = 0;
    p_candidate_count += 131;
  }
  while ( (int)p_candidate_count < (int)g_zero_parcel_bucket_count_lane_end );
  v4 = 0;
  v5 = 0;
  v20 = 0;
  if ( game->runtime_row_count > 0 )
  {
    v6 = g_parcel_group_survival_0;
    v7 = (_DWORD *)((char *)&unk_5CCB64 + (_DWORD)game);
    do
    {
      if ( (*(_BYTE *)(v7 - 39) & 1) != 0 && !*v7 )
      {
        *v6 = v5;
        ++v4;
        ++v6;
      }
      ++v5;
      v7 += 61;
    }
    while ( v5 < game->runtime_row_count );
    v20 = v4;
  }
  v8 = 0;
  if ( game->level_definition.parcel_count > 0 )
  {
    v9 = v4 - 1;
    while ( v4 > 0 )
    {
      v19 = (float)v20;
      v10 = (__int64)random_float_below(v19);
      v11 = (_DWORD *)(4 * v10 + 6572008);
      out_angle = g_parcel_group_survival_0[(_DWORD)v10];
      ++v8;
      challenge_runtime_row_anchor = (RuntimeRowStrideAnchor *)((char *)game + 244 * out_angle);
      challenge_runtime_row_anchor->row.flags |= 0x11u;
      challenge_runtime_row_anchor->row.projection_payload.y = challenge_runtime_row_anchor->row.projection_payload.y
                                                             + 1.0;
      if ( (challenge_runtime_row_anchor->row.flags & 0x20) != 0 )
        challenge_runtime_row_anchor->row.projection_payload.x = challenge_runtime_row_anchor->row.projection_payload.x
                                                               * -1.0;
      if ( (challenge_runtime_row_anchor->row.flags & 0x4000) != 0 )
        challenge_runtime_row_anchor->row.projection_payload.z = (double)out_angle
                                                               + challenge_runtime_row_anchor->row.projection_payload.z
                                                               + 0.5;
      if ( (int)v10 < v9 )
      {
        v13 = v9 - v10;
        do
        {
          *v11 = v11[1];
          ++v11;
          --v13;
        }
        while ( v13 );
      }
      --v9;
      --v20;
      if ( v8 >= game->level_definition.parcel_count )
        break;
      v4 = v20;
    }
  }
  game->level_definition.parcel_count = v8;
  debug_report_stub();
  v21 = 0;
  if ( game->runtime_row_count > 0 )
  {
    projection_row = game->runtime_rows;
    do
    {
      if ( (projection_row->flags & 1) != 0 && (projection_row->flags & 0x40) != 0 )
      {
        v15 = (__int64)projection_row->projection_payload.z
            - get_track_cell_row_index(projection_row->primary_attachment_cell);
        if ( v15 < 0 )
          v15 = 0;
        primary_attachment_cell = projection_row->primary_attachment_cell;
        if ( primary_attachment_cell->attachment_template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
        {
          compute_kind42_attachment_transform(
            primary_attachment_cell->attachment_template_record,
            primary_attachment_cell->attachment_template_record->primary_samples[v15].special_scalar,
            projection_row->projection_payload.x,
            projection_row->projection_payload.y,
            &transform,
            (float *)&out_angle);
          y = transform.position.y;
          projection_row->projection_payload.x = transform.position.x;
          projection_row->projection_payload.y = y;
        }
        else
        {
          track_cell_row_index = get_track_cell_row_index(primary_attachment_cell);
          get_path_position_at_node(
            projection_row->primary_attachment_cell->attachment_template_record,
            &projection_row->projection_payload,
            v15,
            track_cell_row_index,
            &projection_row->projection_payload);
        }
      }
      ++projection_row;
      ++v21;
    }
    while ( v21 < game->runtime_row_count );
  }
}
