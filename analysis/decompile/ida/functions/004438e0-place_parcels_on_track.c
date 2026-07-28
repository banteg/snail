/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: place_parcels_on_track @ 0x4438e0 */
/* selector: place_parcels_on_track */

// Implements the authored void `cRSubGame::PlaceParcels()` method on the verified cRSubGame receiver: borrows a row_count-rooted cursor across the embedded SubTracks segment slots, scans authored rows and glyphs into the cross-port `gGroup`/`gGroup0` global ParcelBucket scratch banks, claims rows in the owned runtime_rows slab, and projects flagged parcel offsets onto their track attachments. Mobile and Windows keep digit 0 on the natural catalog path; Windows and Android reset the maximum parcel-set size for each segment and retain only the final segment's maximum when deriving the 80-percent set target.
void __thiscall place_parcels_on_track(cRSubGame *game)
{
  int32_t level_mode; // eax
  int32_t v2; // esi
  int i; // eax
  int32_t segment_count; // eax
  int v5; // ebp
  SubSegmentParcelScanAnchor *segment_row_count_anchor; // ebx
  int32_t v7; // eax
  int v8; // ecx
  int32_t v9; // edx
  Vec3 *authored_parcel_position; // edi
  int v11; // eax
  Vec3 *p_position; // ebx
  int v13; // ebp
  unsigned int v14; // eax
  double v15; // st7
  char *v16; // edi
  char *v17; // edi
  bool v18; // cc
  int32_t candidate_count; // eax
  int32_t segment_index; // edx
  int32_t v21; // edi
  int32_t *v22; // edx
  int32_t v23; // ecx
  int32_t parcel_count; // edi
  int v25; // eax
  int v26; // esi
  Vec3 *v27; // eax
  _DWORD *v28; // edx
  int32_t v29; // ebx
  int v30; // eax
  int v31; // edi
  int32_t v32; // eax
  Vec3 *__shifted(ParcelCandidatePositionCursorView,4) parcel_set_candidate_position; // ebx
  RuntimeRowStrideAnchor *parcel_set_runtime_row_anchor; // esi
  double v35; // st7
  float x; // ecx
  Vec3 *v37; // ecx
  Vec3 *v38; // edi
  int32_t *p_candidate_count; // edx
  int32_t *p_segment_index; // esi
  int32_t *v41; // eax
  int32_t v42; // edx
  int32_t *v43; // ecx
  int32_t *v44; // esi
  int32_t *v45; // edi
  int v46; // ebx
  int32_t v47; // eax
  RuntimeRowStrideAnchor *zero_runtime_row_anchor; // edi
  float v49; // eax
  char *v50; // edx
  int32_t v51; // ecx
  cRSubGame *v52; // ebp
  int32_t v53; // eax
  int32_t parcel_quota; // ecx
  SubRow *projection_row; // esi
  int32_t v56; // edi
  cRSubLoc *primary_attachment_cell; // ecx
  float y; // edx
  int32_t track_cell_row_index; // eax
  float upper_bound; // [esp+0h] [ebp-22Ch]
  float upper_bounda; // [esp+0h] [ebp-22Ch]
  SubSegmentParcelScanAnchor *p_row_count; // [esp+18h] [ebp-214h]
  int v63; // [esp+18h] [ebp-214h]
  int32_t v64; // [esp+18h] [ebp-214h]
  char *v65; // [esp+18h] [ebp-214h]
  int v66; // [esp+18h] [ebp-214h]
  int32_t v67; // [esp+18h] [ebp-214h]
  float v68; // [esp+1Ch] [ebp-210h]
  int32_t v69; // [esp+1Ch] [ebp-210h]
  Vec3 *out_angle; // [esp+20h] [ebp-20Ch] BYREF
  Vec3 *p_parcel_spawn_position; // [esp+24h] [ebp-208h]
  int v72; // [esp+28h] [ebp-204h]
  int32_t v73; // [esp+2Ch] [ebp-200h]
  cRSubGame *v74; // [esp+30h] [ebp-1FCh]
  int v75; // [esp+34h] [ebp-1F8h]
  int32_t *v76; // [esp+38h] [ebp-1F4h]
  int32_t *v77; // [esp+3Ch] [ebp-1F0h]
  char *v78; // [esp+40h] [ebp-1ECh]
  float v79; // [esp+44h] [ebp-1E8h]
  int v80; // [esp+48h] [ebp-1E4h]
  int v81; // [esp+4Ch] [ebp-1E0h]
  float v82; // [esp+50h] [ebp-1DCh]
  int v83; // [esp+54h] [ebp-1D8h]
  int v84; // [esp+58h] [ebp-1D4h]
  TransformMatrix transform; // [esp+5Ch] [ebp-1D0h] BYREF
  _DWORD v86[100]; // [esp+9Ch] [ebp-190h] BYREF

  level_mode = game->level_mode;
  v74 = game;
  if ( level_mode == 1 )
  {
    place_challenge_parcels_on_track(game);
  }
  else
  {
    v2 = 0;
    if ( level_mode == 0 || level_mode == 7 )
    {
      for ( i = 0; i < 2048; ++i )
      {
        g_zero_parcel_buckets[i].candidate_count = 0;
        g_parcel_set_buckets[i].candidate_count = 0;
      }
      segment_count = game->level_definition.segment_count;
      v5 = 0;
      v68 = 0.0;
      v72 = 0;
      v75 = 0;
      if ( segment_count > 0 )
      {
        segment_row_count_anchor = (SubSegmentParcelScanAnchor *)&game->level_definition.segment_slots[0].row_count;
        v76 = v86;
        p_row_count = (SubSegmentParcelScanAnchor *)&game->level_definition.segment_slots[0].row_count;
        do
        {
          v7 = 0;
          p_parcel_spawn_position = nullptr;
          v73 = 0;
          *v76 = 10000;
          v8 = v75;
          while ( 1 )
          {
            v9 = 0;
            if ( segment_row_count_anchor->row_count > 0 )
            {
              v77 = (int32_t *)segment_row_count_anchor->glyph_rows[0];
              authored_parcel_position = &segment_row_count_anchor->rows[0].local_position;
              out_angle = &segment_row_count_anchor->rows[0].local_position;
              while ( 1 )
              {
                if ( (LOBYTE(authored_parcel_position[-1].y) & 1) != 0 && LODWORD(authored_parcel_position[-1].z) == v7 )
                {
                  if ( v7 != 0 )
                  {
                    g_parcel_set_buckets[v8].segment_index = v2;
                    *(int32_t *)((char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].row
                               + v8 * 524) = v9;
                    *(Vec3 *)((char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].position
                            + v8 * 524) = *authored_parcel_position;
                    g_parcel_set_buckets[v8].set_id = v73;
                    ++g_parcel_set_buckets[v8].candidate_count;
                  }
                  else
                  {
                    v11 = v5;
                    g_zero_parcel_buckets[v11].segment_index = v2;
                    *(int32_t *)((char *)&g_zero_parcel_buckets[0].candidates[g_zero_parcel_buckets[v5].candidate_count].row
                               + v11 * 524) = v9;
                    p_position = &g_zero_parcel_buckets[v5].candidates[g_zero_parcel_buckets[v5].candidate_count].position;
                    p_position->x = authored_parcel_position->x;
                    p_position->y = authored_parcel_position->y;
                    v13 = v72;
                    p_position->z = authored_parcel_position->z;
                    g_zero_parcel_buckets[v11].set_id = 0;
                    v5 = v13 + 1;
                    ++g_zero_parcel_buckets[v11].candidate_count;
                    v72 = v5;
                    ++LODWORD(v68);
                  }
                }
                v72 = 0;
                v78 = (char *)v77;
                v14 = 131 * v5;
                do
                {
                  if ( *v78 == v73 + 48 )
                  {
                    v15 = (double)v72;
                    if ( v73 != 0 )
                    {
                      g_parcel_set_buckets[v8].segment_index = v2;
                      *(int32_t *)((char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].row
                                 + v8 * 524) = v9;
                      v17 = (char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].position
                          + v8 * 524;
                      v83 = 0;
                      v84 = 0;
                      v82 = v15 - 4.0 + 0.5;
                      *(float *)v17 = v82;
                      *((_DWORD *)v17 + 1) = v83;
                      *((_DWORD *)v17 + 2) = v84;
                      g_parcel_set_buckets[v8].set_id = v73;
                      ++g_parcel_set_buckets[v8].candidate_count;
                    }
                    else
                    {
                      g_zero_parcel_buckets[v14 / 0x83].segment_index = v2;
                      *(int32_t *)((char *)&g_zero_parcel_buckets[0].candidates[g_zero_parcel_buckets[v14 / 0x83].candidate_count].row
                                 + v14 * 4) = v9;
                      v16 = (char *)&g_zero_parcel_buckets[0].candidates[g_zero_parcel_buckets[v14 / 0x83].candidate_count].position
                          + v14 * 4;
                      v80 = 0;
                      v81 = 0;
                      v14 += 131;
                      v79 = v15 - 4.0 + 0.5;
                      *(float *)v16 = v79;
                      *((_DWORD *)v16 + 1) = v80;
                      *((_DWORD *)v16 + 2) = v81;
                      unk_53D188[v14] = 0;
                      ++v5;
                      ++unk_53D184[v14];
                      ++LODWORD(v68);
                    }
                  }
                  v18 = ++v72 < 8;
                  v78 += 256;
                }
                while ( v18 );
                ++v9;
                authored_parcel_position = (Vec3 *)((char *)out_angle + 56);
                v72 = v5;
                v77 = (int32_t *)((char *)v77 + 1);
                segment_row_count_anchor = p_row_count;
                out_angle = (Vec3 *)((char *)out_angle + 56);
                if ( v9 >= p_row_count->row_count )
                  break;
                v7 = v73;
              }
            }
            candidate_count = g_parcel_set_buckets[v8].candidate_count;
            if ( candidate_count > 0 )
            {
              segment_index = g_parcel_set_buckets[v8].segment_index;
              v21 = v86[segment_index];
              v22 = &v86[segment_index];
              if ( candidate_count < v21 )
                *v22 = candidate_count;
              if ( candidate_count > (int)p_parcel_spawn_position )
                p_parcel_spawn_position = (Vec3 *)candidate_count;
              ++v8;
              ++v75;
            }
            if ( ++v73 >= 10 )
              break;
            v7 = v73;
          }
          ++v2;
          v23 = v74->level_definition.segment_count;
          ++segment_row_count_anchor;
          ++v76;
          p_row_count = segment_row_count_anchor;
        }
        while ( v2 < v23 );
      }
      parcel_count = v74->level_definition.parcel_count;
      v25 = v74->level_definition.segment_count;
      v26 = 80 * parcel_count / 100 - (_DWORD)p_parcel_spawn_position;
      v73 = v26;
      out_angle = (Vec3 *)LODWORD(v68);
      if ( v25 <= 0 )
      {
        v27 = out_angle;
      }
      else
      {
        v63 = v25;
        v27 = out_angle;
        v28 = v86;
        do
        {
          if ( *v28 != 10000 )
            v27 = (Vec3 *)((char *)v27 + *v28);
          ++v28;
          --v63;
        }
        while ( v63 != 0 );
      }
      if ( (int)v27 < parcel_count )
        report_errorf(
          "Parcel Allocation could fail in %s.  Add more parcel Sets",
          v74->level_definition.level_display_name);
      if ( v74->level_definition.parcel_count - v26 > SLODWORD(v68) )
        report_errorf(
          "Parcel Allocation could fail in %s. Add more 0 parcels ",
          v74->level_definition.level_display_name);
      v29 = 0;
      v69 = 0;
      if ( v26 > 0 )
      {
        v30 = v75;
        do
        {
          if ( v30 <= 0 )
            break;
          upper_bound = (float)v75;
          v64 = 0;
          v31 = (__int64)random_float_below(upper_bound, aP1);
          v32 = g_parcel_set_buckets[v31].candidate_count;
          v69 = v32 + v29;
          if ( v32 > 0 )
          {
            parcel_set_candidate_position = &g_parcel_set_buckets[v31].candidates[0].position;
            do
            {
              out_angle = (Vec3 *)(ADJ(parcel_set_candidate_position)->row
                                 + v74->level_definition.segment_slots[g_parcel_set_buckets[v31].segment_index].row_base);
              parcel_set_runtime_row_anchor = (RuntimeRowStrideAnchor *)((char *)v74 + 244 * (_DWORD)out_angle);
              if ( (parcel_set_runtime_row_anchor->row.flags & 0x10) != 0 )
                report_errorf("Duplicate Parcel Request in %s.", v74->level_definition.level_display_name);
              v35 = (double)(int)out_angle;
              parcel_set_runtime_row_anchor->row.flags |= 0x11u;
              x = ADJ(parcel_set_candidate_position)->position.x;
              p_parcel_spawn_position = &parcel_set_runtime_row_anchor->row.parcel_spawn_position;
              parcel_set_runtime_row_anchor->row.parcel_spawn_position.x = x;
              parcel_set_runtime_row_anchor->row.parcel_spawn_position.y = ADJ(parcel_set_candidate_position)->position.y;
              parcel_set_runtime_row_anchor->row.parcel_spawn_position.z = ADJ(parcel_set_candidate_position)->position.z;
              parcel_set_runtime_row_anchor->row.parcel_spawn_position.z = v35
                                                                         + parcel_set_runtime_row_anchor->row.parcel_spawn_position.z
                                                                         + 0.5;
              parcel_set_runtime_row_anchor->row.parcel_spawn_position.y = parcel_set_runtime_row_anchor->row.parcel_spawn_position.y
                                                                         + 1.0;
              if ( (parcel_set_runtime_row_anchor->row.flags & 0x20) != 0 )
                p_parcel_spawn_position->x = p_parcel_spawn_position->x * -1.0;
              parcel_set_candidate_position = (Vec3 *__shifted(ParcelCandidatePositionCursorView,4))((char *)parcel_set_candidate_position + 16);
              ++v64;
            }
            while ( v64 < g_parcel_set_buckets[v31].candidate_count );
          }
          v37 = nullptr;
          v78 = (char *)g_parcel_set_buckets[v31].segment_index;
          v30 = v75;
          p_parcel_spawn_position = nullptr;
          if ( v75 > 0 )
          {
            v38 = (Vec3 *)(v75 - 1);
            p_candidate_count = &g_parcel_set_buckets[1].candidate_count;
            p_segment_index = &g_parcel_set_buckets[0].segment_index;
            out_angle = (Vec3 *)(v75 - 1);
            v77 = &g_parcel_set_buckets[1].candidate_count;
            v76 = &g_parcel_set_buckets[0].segment_index;
            do
            {
              if ( (char *)*p_segment_index == v78 )
              {
                if ( (int)v37 < (int)v38 )
                {
                  v41 = p_candidate_count;
                  v65 = (char *)((char *)v38 - (char *)v37);
                  do
                  {
                    v42 = 0;
                    if ( *v41 > 0 )
                    {
                      v43 = v41 - 259;
                      do
                      {
                        v44 = v43 + 131;
                        v45 = v43;
                        ++v42;
                        v43 += 4;
                        *v45 = *v44;
                        v45[1] = v44[1];
                        v45[2] = v44[2];
                        v45[3] = v44[3];
                      }
                      while ( v42 < *v41 );
                      v37 = p_parcel_spawn_position;
                    }
                    *(v41 - 131) = *v41;
                    *(v41 - 129) = v41[2];
                    *(v41 - 130) = v41[1];
                    v41 += 131;
                    --v65;
                  }
                  while ( v65 != nullptr );
                  v38 = out_angle;
                  p_candidate_count = v77;
                  p_segment_index = v76;
                }
                v37 = (Vec3 *)((char *)v37 - 1);
                p_segment_index -= 131;
                p_candidate_count -= 131;
                v38 = (Vec3 *)((char *)v38 - 1);
                --v75;
                out_angle = v38;
                v30 = v75;
              }
              v37 = (Vec3 *)((char *)v37 + 1);
              p_segment_index += 131;
              p_candidate_count += 131;
              p_parcel_spawn_position = v37;
              v76 = p_segment_index;
              v77 = p_candidate_count;
            }
            while ( (int)v37 < v30 );
          }
          v29 = v69;
        }
        while ( v69 < v73 );
      }
      if ( v29 < v74->level_definition.parcel_count )
      {
        p_parcel_spawn_position = (Vec3 *)(v5 - 1);
        do
        {
          if ( v5 <= 0 )
            break;
          upper_bounda = (float)v72;
          v46 = (__int64)random_float_below(upper_bounda, aP2);
          v47 = g_zero_parcel_buckets[v46].segment_index;
          v69 += g_zero_parcel_buckets[v46].candidate_count;
          out_angle = (Vec3 *)&g_zero_parcel_buckets[v46];
          v66 = LODWORD(out_angle->x) + v74->level_definition.segment_slots[v47].row_base;
          zero_runtime_row_anchor = (RuntimeRowStrideAnchor *)((char *)v74 + 244 * v66);
          if ( (zero_runtime_row_anchor->row.flags & 0x10) != 0 )
            report_errorf("Duplicate Parcel Request in %s.", v74->level_definition.level_display_name);
          zero_runtime_row_anchor->row.flags |= 0x11u;
          zero_runtime_row_anchor->row.parcel_spawn_position = g_zero_parcel_buckets[v46].candidates[0].position;
          zero_runtime_row_anchor->row.parcel_spawn_position.z = (double)v66
                                                               + zero_runtime_row_anchor->row.parcel_spawn_position.z
                                                               + 0.5;
          zero_runtime_row_anchor->row.parcel_spawn_position.y = zero_runtime_row_anchor->row.parcel_spawn_position.y
                                                               + 1.0;
          if ( (zero_runtime_row_anchor->row.flags & 0x20) != 0 )
            zero_runtime_row_anchor->row.parcel_spawn_position.x = zero_runtime_row_anchor->row.parcel_spawn_position.x
                                                                 * -1.0;
          if ( v46 < (int)p_parcel_spawn_position )
          {
            v49 = *(float *)&out_angle;
            v50 = (char *)p_parcel_spawn_position - v46;
            do
            {
              --v50;
              *(_DWORD *)LODWORD(v49) = *(_DWORD *)(LODWORD(v49) + 524);
              *(_DWORD *)(LODWORD(v49) + 4) = *(_DWORD *)(LODWORD(v49) + 528);
              *(_DWORD *)(LODWORD(v49) + 8) = *(_DWORD *)(LODWORD(v49) + 532);
              *(_DWORD *)(LODWORD(v49) + 12) = *(_DWORD *)(LODWORD(v49) + 536);
              *(_DWORD *)(LODWORD(v49) + 512) = *(_DWORD *)(LODWORD(v49) + 1036);
              *(_DWORD *)(LODWORD(v49) + 520) = *(_DWORD *)(LODWORD(v49) + 1044);
              *(_DWORD *)(LODWORD(v49) + 516) = 0;
              LODWORD(v49) += 524;
            }
            while ( v50 != nullptr );
          }
          --v5;
          v51 = v74->level_definition.parcel_count;
          p_parcel_spawn_position = (Vec3 *)((char *)p_parcel_spawn_position - 1);
          v72 = v5;
        }
        while ( v69 < v51 );
      }
      v52 = v74;
      v53 = v74->level_definition.parcel_count;
      if ( v69 != v53 )
      {
        report_errorf("Did not generate required Parcels(%i) in %s", v53, v74->level_definition.level_display_name);
        parcel_quota = v74->level_definition.parcel_quota;
        if ( parcel_quota != 0 )
          v74->level_definition.parcel_quota = v69 * v74->level_definition.parcel_count / parcel_quota;
      }
      v52->level_definition.parcel_count = v69;
      v67 = 0;
      if ( v52->runtime_row_count > 0 )
      {
        projection_row = v52->runtime_rows;
        do
        {
          if ( (projection_row->flags & 1) != 0 && (projection_row->flags & 0x40) != 0 )
          {
            v56 = (__int64)projection_row->parcel_spawn_position.z
                - get_track_cell_row_index(projection_row->primary_attachment_cell);
            if ( v56 < 0 )
              v56 = 0;
            primary_attachment_cell = projection_row->primary_attachment_cell;
            if ( primary_attachment_cell->attachment_template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
            {
              compute_kind42_attachment_transform(
                primary_attachment_cell->attachment_template_record,
                primary_attachment_cell->attachment_template_record->primary_samples[v56].special_scalar,
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
                v56,
                track_cell_row_index,
                &projection_row->parcel_spawn_position);
            }
          }
          ++projection_row;
          ++v67;
        }
        while ( v67 < v52->runtime_row_count );
      }
    }
  }
}
