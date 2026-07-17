/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: place_parcels_on_track @ 0x4438e0 */
/* selector: place_parcels_on_track */

// Implements `cRSubGame::PlaceParcels()` on the verified SubgameRuntime receiver: scans the embedded SubTracks definition into two global ParcelBucket scratch banks, claims rows in the owned runtime_rows slab, and projects flagged parcel offsets onto their track attachments.
void __thiscall place_parcels_on_track(SubgameRuntime *game)
{
  int32_t level_mode; // eax
  int32_t v2; // esi
  int i; // eax
  int32_t segment_count; // eax
  int v5; // ebp
  int32_t *p_row_count; // ebx
  int32_t v7; // eax
  int v8; // ecx
  int32_t v9; // edx
  ParcelBucket *p_y; // edi
  int v11; // eax
  Vec3 *p_position; // ebx
  int v13; // ebp
  int32_t *v14; // eax
  unsigned int v15; // eax
  double v16; // st7
  char *v17; // edi
  char *v18; // edi
  bool v19; // cc
  int32_t candidate_count; // eax
  int32_t segment_index; // edx
  int32_t v22; // edi
  int32_t *v23; // edx
  int32_t v24; // ecx
  int32_t parcel_count; // edi
  int v26; // eax
  int v27; // esi
  ParcelBucket *v28; // eax
  _DWORD *v29; // edx
  int32_t v30; // ebx
  int v31; // eax
  int v32; // edi
  int32_t v33; // eax
  Vec3 *v34; // ebx
  RuntimeRowStrideAnchor *parcel_set_runtime_row_anchor; // esi
  double v36; // st7
  float x; // ecx
  Vec3 *v38; // ecx
  ParcelBucket *v39; // edi
  int32_t *p_candidate_count; // edx
  int32_t *p_segment_index; // esi
  int32_t *v42; // eax
  int32_t v43; // edx
  int32_t *v44; // ecx
  int32_t *v45; // esi
  int32_t *v46; // edi
  int v47; // ebx
  int32_t v48; // eax
  RuntimeRowStrideAnchor *zero_runtime_row_anchor; // edi
  float v50; // eax
  char *v51; // edx
  int32_t v52; // ecx
  SubgameRuntime *v53; // ebp
  int32_t v54; // eax
  int32_t parcel_quota; // ecx
  SubRow *projection_row; // esi
  int v57; // edi
  TrackRowCell *primary_attachment_cell; // ecx
  float y; // edx
  int32_t track_cell_row_index; // eax
  float v61; // [esp+0h] [ebp-22Ch]
  float v62; // [esp+0h] [ebp-22Ch]
  int32_t *v63; // [esp+18h] [ebp-214h]
  int v64; // [esp+18h] [ebp-214h]
  int32_t v65; // [esp+18h] [ebp-214h]
  char *v66; // [esp+18h] [ebp-214h]
  int v67; // [esp+18h] [ebp-214h]
  int32_t v68; // [esp+18h] [ebp-214h]
  float v69; // [esp+1Ch] [ebp-210h]
  int32_t v70; // [esp+1Ch] [ebp-210h]
  ParcelBucket *out_angle; // [esp+20h] [ebp-20Ch] BYREF
  Vec3 *p_projection_payload; // [esp+24h] [ebp-208h]
  int v73; // [esp+28h] [ebp-204h]
  int32_t v74; // [esp+2Ch] [ebp-200h]
  SubgameRuntime *v75; // [esp+30h] [ebp-1FCh]
  int v76; // [esp+34h] [ebp-1F8h]
  int32_t *v77; // [esp+38h] [ebp-1F4h]
  int32_t *v78; // [esp+3Ch] [ebp-1F0h]
  int32_t *v79; // [esp+40h] [ebp-1ECh]
  float v80; // [esp+44h] [ebp-1E8h]
  int v81; // [esp+48h] [ebp-1E4h]
  int v82; // [esp+4Ch] [ebp-1E0h]
  float v83; // [esp+50h] [ebp-1DCh]
  int v84; // [esp+54h] [ebp-1D8h]
  int v85; // [esp+58h] [ebp-1D4h]
  TransformMatrix transform; // [esp+5Ch] [ebp-1D0h] BYREF
  _DWORD v87[100]; // [esp+9Ch] [ebp-190h] BYREF

  level_mode = game->level_mode;
  v75 = game;
  if ( level_mode == 1 )
  {
    place_challenge_parcels_on_track(game);
  }
  else
  {
    v2 = 0;
    if ( !level_mode || level_mode == 7 )
    {
      for ( i = 0; i < 2048; ++i )
      {
        g_zero_parcel_buckets[i].candidate_count = 0;
        g_parcel_set_buckets[i].candidate_count = 0;
      }
      segment_count = game->level_definition.segment_count;
      v5 = 0;
      v69 = 0.0;
      v73 = 0;
      v76 = 0;
      if ( segment_count > 0 )
      {
        p_row_count = &game->level_definition.segment_slots[0].row_count;
        v77 = v87;
        v63 = &game->level_definition.segment_slots[0].row_count;
        do
        {
          v7 = 0;
          p_projection_payload = nullptr;
          v74 = 0;
          *v77 = 10000;
          v8 = v76;
          while ( 1 )
          {
            v9 = 0;
            if ( *p_row_count > 0 )
            {
              v78 = p_row_count + 4;
              p_y = (ParcelBucket *)(p_row_count + 518);
              out_angle = (ParcelBucket *)(p_row_count + 518);
              while ( 1 )
              {
                if ( (p_y[-1].set_id & 1) != 0 && p_y[-1].segment_index == v7 )
                {
                  if ( v7 )
                  {
                    g_parcel_set_buckets[v8].segment_index = v2;
                    *(int32_t *)((char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].row
                               + v8 * 524) = v9;
                    v14 = (int32_t *)((char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].position
                                    + v8 * 524);
                    *v14 = p_y->candidates[0].row;
                    v14[1] = LODWORD(p_y->candidates[0].position.x);
                    v14[2] = LODWORD(p_y->candidates[0].position.y);
                    g_parcel_set_buckets[v8].set_id = v74;
                    ++g_parcel_set_buckets[v8].candidate_count;
                  }
                  else
                  {
                    v11 = v5;
                    g_zero_parcel_buckets[v11].segment_index = v2;
                    *(int32_t *)((char *)&g_zero_parcel_buckets[0].candidates[g_zero_parcel_buckets[v5].candidate_count].row
                               + v11 * 524) = v9;
                    p_position = &g_zero_parcel_buckets[v5].candidates[g_zero_parcel_buckets[v5].candidate_count].position;
                    LODWORD(p_position->x) = p_y->candidates[0].row;
                    p_position->y = p_y->candidates[0].position.x;
                    v13 = v73;
                    p_position->z = p_y->candidates[0].position.y;
                    g_zero_parcel_buckets[v11].set_id = 0;
                    v5 = v13 + 1;
                    ++g_zero_parcel_buckets[v11].candidate_count;
                    v73 = v5;
                    ++LODWORD(v69);
                  }
                }
                v73 = 0;
                v79 = v78;
                v15 = 131 * v5;
                do
                {
                  if ( *(char *)v79 == v74 + 48 )
                  {
                    v16 = (double)v73;
                    if ( v74 )
                    {
                      g_parcel_set_buckets[v8].segment_index = v2;
                      *(int32_t *)((char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].row
                                 + v8 * 524) = v9;
                      v18 = (char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].position
                          + v8 * 524;
                      v84 = 0;
                      v85 = 0;
                      v83 = v16 - 4.0 + 0.5;
                      *(float *)v18 = v83;
                      *((_DWORD *)v18 + 1) = v84;
                      *((_DWORD *)v18 + 2) = v85;
                      g_parcel_set_buckets[v8].set_id = v74;
                      ++g_parcel_set_buckets[v8].candidate_count;
                    }
                    else
                    {
                      g_zero_parcel_buckets[v15 / 0x83].segment_index = v2;
                      *(int32_t *)((char *)&g_zero_parcel_buckets[0].candidates[g_zero_parcel_buckets[v15 / 0x83].candidate_count].row
                                 + v15 * 4) = v9;
                      v17 = (char *)&g_zero_parcel_buckets[0].candidates[g_zero_parcel_buckets[v15 / 0x83].candidate_count].position
                          + v15 * 4;
                      v81 = 0;
                      v82 = 0;
                      v15 += 131;
                      v80 = v16 - 4.0 + 0.5;
                      *(float *)v17 = v80;
                      *((_DWORD *)v17 + 1) = v81;
                      *((_DWORD *)v17 + 2) = v82;
                      unk_53D188[v15] = 0;
                      ++v5;
                      ++unk_53D184[v15];
                      ++LODWORD(v69);
                    }
                  }
                  v19 = ++v73 < 8;
                  v79 += 64;
                }
                while ( v19 );
                ++v9;
                p_y = (ParcelBucket *)&out_angle->candidates[3].position.y;
                v73 = v5;
                v78 = (int32_t *)((char *)v78 + 1);
                p_row_count = v63;
                out_angle = (ParcelBucket *)((char *)out_angle + 56);
                if ( v9 >= *v63 )
                  break;
                v7 = v74;
              }
            }
            candidate_count = g_parcel_set_buckets[v8].candidate_count;
            if ( candidate_count > 0 )
            {
              segment_index = g_parcel_set_buckets[v8].segment_index;
              v22 = v87[segment_index];
              v23 = &v87[segment_index];
              if ( candidate_count < v22 )
                *v23 = candidate_count;
              if ( candidate_count > (int)p_projection_payload )
                p_projection_payload = (Vec3 *)candidate_count;
              ++v8;
              ++v76;
            }
            if ( ++v74 >= 10 )
              break;
            v7 = v74;
          }
          ++v2;
          v24 = v75->level_definition.segment_count;
          p_row_count += 4232;
          ++v77;
          v63 = p_row_count;
        }
        while ( v2 < v24 );
      }
      parcel_count = v75->level_definition.parcel_count;
      v26 = v75->level_definition.segment_count;
      v27 = 80 * parcel_count / 100 - (_DWORD)p_projection_payload;
      v74 = v27;
      out_angle = (ParcelBucket *)LODWORD(v69);
      if ( v26 <= 0 )
      {
        v28 = out_angle;
      }
      else
      {
        v64 = v26;
        v28 = out_angle;
        v29 = v87;
        do
        {
          if ( *v29 != 10000 )
            v28 = (ParcelBucket *)((char *)v28 + *v29);
          ++v29;
          --v64;
        }
        while ( v64 );
      }
      if ( (int)v28 < parcel_count )
        report_errorf(
          "Parcel Allocation could fail in %s.  Add more parcel Sets",
          v75->level_definition.level_display_name);
      if ( v75->level_definition.parcel_count - v27 > SLODWORD(v69) )
        report_errorf(
          "Parcel Allocation could fail in %s. Add more 0 parcels ",
          v75->level_definition.level_display_name);
      v30 = 0;
      v70 = 0;
      if ( v27 > 0 )
      {
        v31 = v76;
        do
        {
          if ( v31 <= 0 )
            break;
          v61 = (float)v76;
          v65 = 0;
          v32 = (__int64)random_float_below(v61);
          v33 = g_parcel_set_buckets[v32].candidate_count;
          v70 = v33 + v30;
          if ( v33 > 0 )
          {
            v34 = &g_parcel_set_buckets[v32].candidates[0].position;
            do
            {
              out_angle = (ParcelBucket *)(LODWORD(v34[-1].z)
                                         + v75->level_definition.segment_slots[g_parcel_set_buckets[v32].segment_index].row_base);
              parcel_set_runtime_row_anchor = (RuntimeRowStrideAnchor *)((char *)v75 + 244 * (_DWORD)out_angle);
              if ( (parcel_set_runtime_row_anchor->row.flags & 0x10) != 0 )
                report_errorf("Duplicate Parcel Request in %s.", v75->level_definition.level_display_name);
              v36 = (double)(int)out_angle;
              parcel_set_runtime_row_anchor->row.flags |= 0x11u;
              x = v34->x;
              p_projection_payload = &parcel_set_runtime_row_anchor->row.projection_payload;
              parcel_set_runtime_row_anchor->row.projection_payload.x = x;
              parcel_set_runtime_row_anchor->row.projection_payload.y = v34->y;
              parcel_set_runtime_row_anchor->row.projection_payload.z = v34->z;
              parcel_set_runtime_row_anchor->row.projection_payload.z = v36
                                                                      + parcel_set_runtime_row_anchor->row.projection_payload.z
                                                                      + 0.5;
              parcel_set_runtime_row_anchor->row.projection_payload.y = parcel_set_runtime_row_anchor->row.projection_payload.y
                                                                      + 1.0;
              if ( (parcel_set_runtime_row_anchor->row.flags & 0x20) != 0 )
                p_projection_payload->x = p_projection_payload->x * -1.0;
              v34 = (Vec3 *)((char *)v34 + 16);
              ++v65;
            }
            while ( v65 < g_parcel_set_buckets[v32].candidate_count );
          }
          v38 = nullptr;
          v79 = (int32_t *)g_parcel_set_buckets[v32].segment_index;
          v31 = v76;
          p_projection_payload = nullptr;
          if ( v76 > 0 )
          {
            v39 = (ParcelBucket *)(v76 - 1);
            p_candidate_count = &g_parcel_set_buckets[1].candidate_count;
            p_segment_index = &g_parcel_set_buckets[0].segment_index;
            out_angle = (ParcelBucket *)(v76 - 1);
            v78 = &g_parcel_set_buckets[1].candidate_count;
            v77 = &g_parcel_set_buckets[0].segment_index;
            do
            {
              if ( (int32_t *)*p_segment_index == v79 )
              {
                if ( (int)v38 < (int)v39 )
                {
                  v42 = p_candidate_count;
                  v66 = (char *)((char *)v39 - (char *)v38);
                  do
                  {
                    v43 = 0;
                    if ( *v42 > 0 )
                    {
                      v44 = v42 - 259;
                      do
                      {
                        v45 = v44 + 131;
                        v46 = v44;
                        ++v43;
                        v44 += 4;
                        *v46 = *v45;
                        v46[1] = v45[1];
                        v46[2] = v45[2];
                        v46[3] = v45[3];
                      }
                      while ( v43 < *v42 );
                      v38 = p_projection_payload;
                    }
                    *(v42 - 131) = *v42;
                    *(v42 - 129) = v42[2];
                    *(v42 - 130) = v42[1];
                    v42 += 131;
                    --v66;
                  }
                  while ( v66 );
                  v39 = out_angle;
                  p_candidate_count = v78;
                  p_segment_index = v77;
                }
                v38 = (Vec3 *)((char *)v38 - 1);
                p_segment_index -= 131;
                p_candidate_count -= 131;
                v39 = (ParcelBucket *)((char *)v39 - 1);
                --v76;
                out_angle = v39;
                v31 = v76;
              }
              v38 = (Vec3 *)((char *)v38 + 1);
              p_segment_index += 131;
              p_candidate_count += 131;
              p_projection_payload = v38;
              v77 = p_segment_index;
              v78 = p_candidate_count;
            }
            while ( (int)v38 < v31 );
          }
          v30 = v70;
        }
        while ( v70 < v74 );
      }
      if ( v30 < v75->level_definition.parcel_count )
      {
        p_projection_payload = (Vec3 *)(v5 - 1);
        do
        {
          if ( v5 <= 0 )
            break;
          v62 = (float)v73;
          v47 = (__int64)random_float_below(v62);
          v48 = g_zero_parcel_buckets[v47].segment_index;
          v70 += g_zero_parcel_buckets[v47].candidate_count;
          out_angle = &g_zero_parcel_buckets[v47];
          v67 = out_angle->candidates[0].row + v75->level_definition.segment_slots[v48].row_base;
          zero_runtime_row_anchor = (RuntimeRowStrideAnchor *)((char *)v75 + 244 * v67);
          if ( (zero_runtime_row_anchor->row.flags & 0x10) != 0 )
            report_errorf("Duplicate Parcel Request in %s.", v75->level_definition.level_display_name);
          zero_runtime_row_anchor->row.flags |= 0x11u;
          zero_runtime_row_anchor->row.projection_payload = g_zero_parcel_buckets[v47].candidates[0].position;
          zero_runtime_row_anchor->row.projection_payload.z = (double)v67
                                                            + zero_runtime_row_anchor->row.projection_payload.z
                                                            + 0.5;
          zero_runtime_row_anchor->row.projection_payload.y = zero_runtime_row_anchor->row.projection_payload.y + 1.0;
          if ( (zero_runtime_row_anchor->row.flags & 0x20) != 0 )
            zero_runtime_row_anchor->row.projection_payload.x = zero_runtime_row_anchor->row.projection_payload.x * -1.0;
          if ( v47 < (int)p_projection_payload )
          {
            v50 = *(float *)&out_angle;
            v51 = (char *)p_projection_payload - v47;
            do
            {
              --v51;
              *(_DWORD *)LODWORD(v50) = *(_DWORD *)(LODWORD(v50) + 524);
              *(_DWORD *)(LODWORD(v50) + 4) = *(_DWORD *)(LODWORD(v50) + 528);
              *(_DWORD *)(LODWORD(v50) + 8) = *(_DWORD *)(LODWORD(v50) + 532);
              *(_DWORD *)(LODWORD(v50) + 12) = *(_DWORD *)(LODWORD(v50) + 536);
              *(_DWORD *)(LODWORD(v50) + 512) = *(_DWORD *)(LODWORD(v50) + 1036);
              *(_DWORD *)(LODWORD(v50) + 520) = *(_DWORD *)(LODWORD(v50) + 1044);
              *(_DWORD *)(LODWORD(v50) + 516) = 0;
              LODWORD(v50) += 524;
            }
            while ( v51 );
          }
          --v5;
          v52 = v75->level_definition.parcel_count;
          p_projection_payload = (Vec3 *)((char *)p_projection_payload - 1);
          v73 = v5;
        }
        while ( v70 < v52 );
      }
      v53 = v75;
      v54 = v75->level_definition.parcel_count;
      if ( v70 != v54 )
      {
        report_errorf("Did not generate required Parcels(%i) in %s", v54, v75->level_definition.level_display_name);
        parcel_quota = v75->level_definition.parcel_quota;
        if ( parcel_quota )
          v75->level_definition.parcel_quota = v70 * v75->level_definition.parcel_count / parcel_quota;
      }
      v53->level_definition.parcel_count = v70;
      v68 = 0;
      if ( v53->runtime_row_count > 0 )
      {
        projection_row = v53->runtime_rows;
        do
        {
          if ( (projection_row->flags & 1) != 0 && (projection_row->flags & 0x40) != 0 )
          {
            v57 = (__int64)projection_row->projection_payload.z
                - get_track_cell_row_index(projection_row->primary_attachment_cell);
            if ( v57 < 0 )
              v57 = 0;
            primary_attachment_cell = projection_row->primary_attachment_cell;
            if ( primary_attachment_cell->attachment_template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
            {
              compute_kind42_attachment_transform(
                primary_attachment_cell->attachment_template_record,
                primary_attachment_cell->attachment_template_record->primary_samples[v57].special_scalar,
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
                &projection_row->primary_attachment_cell->attachment_template_record->bod.bod.vtable,
                &projection_row->projection_payload.x,
                v57,
                track_cell_row_index,
                &projection_row->projection_payload.x);
            }
          }
          ++projection_row;
          ++v68;
        }
        while ( v68 < v53->runtime_row_count );
      }
    }
  }
}
