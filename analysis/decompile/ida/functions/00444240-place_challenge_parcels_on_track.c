/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: place_challenge_parcels_on_track @ 0x444240 */
/* selector: place_challenge_parcels_on_track */

// Implements `cRSubGame::PlaceParcelsSurvival()` on the verified SubgameRuntime receiver: derives the quota from owned completion/difficulty state, records eligible runtime_rows indices in the global `gParcelGroupSurvival0` scratch bank, and randomly claims rows while compacting that bank in place.
int32_t __thiscall place_challenge_parcels_on_track(SubgameRuntime *game)
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
  uint8_t *v12; // ecx
  int v13; // ecx
  int32_t result; // eax
  char *v15; // esi
  int v16; // edi
  SubLoc *v17; // ecx
  float y; // ecx
  int32_t track_cell_row_index; // eax
  float v20; // [esp+0h] [ebp-60h]
  int v21; // [esp+18h] [ebp-48h]
  int32_t v22; // [esp+18h] [ebp-48h]
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
  v21 = 0;
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
    v21 = v4;
  }
  v8 = 0;
  if ( game->level_definition.parcel_count > 0 )
  {
    v9 = v4 - 1;
    while ( v4 > 0 )
    {
      v20 = (float)v21;
      v10 = (__int64)random_float_below(v20);
      v11 = (_DWORD *)(4 * v10 + 6572008);
      out_angle = g_parcel_group_survival_0[(_DWORD)v10];
      ++v8;
      v12 = &game->scan_reset + 244 * out_angle;
      *(_DWORD *)&byte_5CCAC8[(_DWORD)v12] |= 0x11u;
      *((float *)v12 + 1520343) = *((float *)v12 + 1520343) + 1.0;
      if ( (byte_5CCAC8[(_DWORD)v12] & 0x20) != 0 )
        *((float *)v12 + 1520342) = *((float *)v12 + 1520342) * -1.0;
      if ( (*(_DWORD *)&byte_5CCAC8[(_DWORD)v12] & 0x4000) != 0 )
        *((float *)v12 + 1520344) = (double)out_angle + *((float *)v12 + 1520344) + 0.5;
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
      --v21;
      if ( v8 >= game->level_definition.parcel_count )
        break;
      v4 = v21;
    }
  }
  game->level_definition.parcel_count = v8;
  debug_report_stub();
  result = game->runtime_row_count;
  v22 = 0;
  if ( result > 0 )
  {
    v15 = &byte_5CCAC8[(_DWORD)game];
    do
    {
      if ( (*(_DWORD *)v15 & 1) != 0 && (*(_DWORD *)v15 & 0x40) != 0 )
      {
        v16 = (__int64)*((float *)v15 + 38) - get_track_cell_row_index(*((SubLoc **)v15 + 41));
        if ( v16 < 0 )
          v16 = 0;
        v17 = *((SubLoc **)v15 + 41);
        if ( v17->attachment_template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
        {
          compute_kind42_attachment_transform(
            v17->attachment_template_record,
            v17->attachment_template_record->primary_samples[v16].special_scalar,
            *((float *)v15 + 36),
            *((float *)v15 + 37),
            &transform,
            (float *)&out_angle);
          y = transform.position.y;
          *((_DWORD *)v15 + 36) = LODWORD(transform.position.x);
          *((float *)v15 + 37) = y;
        }
        else
        {
          track_cell_row_index = get_track_cell_row_index(v17);
          get_path_position_at_node(
            *(_DWORD **)(*((_DWORD *)v15 + 41) + 56),
            (float *)v15 + 36,
            v16,
            track_cell_row_index,
            (float *)v15 + 36);
        }
      }
      result = v22 + 1;
      v15 += 244;
      ++v22;
    }
    while ( v22 < game->runtime_row_count );
  }
  return result;
}
