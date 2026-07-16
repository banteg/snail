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
  float *v35; // esi
  float *v36; // eax
  double v37; // st7
  float x; // ecx
  float *v39; // ecx
  ParcelBucket *v40; // edi
  int32_t *p_candidate_count; // edx
  int32_t *p_segment_index; // esi
  int32_t *v43; // eax
  int32_t v44; // edx
  int32_t *v45; // ecx
  int32_t *v46; // esi
  int32_t *v47; // edi
  int v48; // ebx
  int v49; // esi
  int32_t v50; // eax
  float *v51; // edi
  float *v52; // edx
  float v53; // eax
  char *v54; // edx
  int32_t v55; // ecx
  SubgameRuntime *v56; // ebp
  int32_t v57; // eax
  int32_t parcel_quota; // ecx
  char *v59; // esi
  int v60; // edi
  SubLoc *v61; // ecx
  float y; // edx
  int32_t track_cell_row_index; // eax
  float v64; // [esp+0h] [ebp-22Ch]
  float v65; // [esp+0h] [ebp-22Ch]
  int32_t *v66; // [esp+18h] [ebp-214h]
  int v67; // [esp+18h] [ebp-214h]
  int32_t v68; // [esp+18h] [ebp-214h]
  char *v69; // [esp+18h] [ebp-214h]
  int v70; // [esp+18h] [ebp-214h]
  int32_t v71; // [esp+18h] [ebp-214h]
  float v72; // [esp+1Ch] [ebp-210h]
  int32_t v73; // [esp+1Ch] [ebp-210h]
  ParcelBucket *out_angle; // [esp+20h] [ebp-20Ch] BYREF
  float *v75; // [esp+24h] [ebp-208h]
  int v76; // [esp+28h] [ebp-204h]
  int32_t v77; // [esp+2Ch] [ebp-200h]
  SubgameRuntime *v78; // [esp+30h] [ebp-1FCh]
  int v79; // [esp+34h] [ebp-1F8h]
  int32_t *v80; // [esp+38h] [ebp-1F4h]
  int32_t *v81; // [esp+3Ch] [ebp-1F0h]
  int32_t *v82; // [esp+40h] [ebp-1ECh]
  float v83; // [esp+44h] [ebp-1E8h]
  int v84; // [esp+48h] [ebp-1E4h]
  int v85; // [esp+4Ch] [ebp-1E0h]
  float v86; // [esp+50h] [ebp-1DCh]
  int v87; // [esp+54h] [ebp-1D8h]
  int v88; // [esp+58h] [ebp-1D4h]
  TransformMatrix transform; // [esp+5Ch] [ebp-1D0h] BYREF
  _DWORD v90[100]; // [esp+9Ch] [ebp-190h] BYREF

  level_mode = game->level_mode;
  v78 = game;
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
      v72 = 0.0;
      v76 = 0;
      v79 = 0;
      if ( segment_count > 0 )
      {
        p_row_count = &game->level_definition.segment_slots[0].row_count;
        v80 = v90;
        v66 = &game->level_definition.segment_slots[0].row_count;
        do
        {
          v7 = 0;
          v75 = nullptr;
          v77 = 0;
          *v80 = 10000;
          v8 = v79;
          while ( 1 )
          {
            v9 = 0;
            if ( *p_row_count > 0 )
            {
              v81 = p_row_count + 4;
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
                    g_parcel_set_buckets[v8].set_id = v77;
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
                    v13 = v76;
                    p_position->z = p_y->candidates[0].position.y;
                    g_zero_parcel_buckets[v11].set_id = 0;
                    v5 = v13 + 1;
                    ++g_zero_parcel_buckets[v11].candidate_count;
                    v76 = v5;
                    ++LODWORD(v72);
                  }
                }
                v76 = 0;
                v82 = v81;
                v15 = 131 * v5;
                do
                {
                  if ( *(char *)v82 == v77 + 48 )
                  {
                    v16 = (double)v76;
                    if ( v77 )
                    {
                      g_parcel_set_buckets[v8].segment_index = v2;
                      *(int32_t *)((char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].row
                                 + v8 * 524) = v9;
                      v18 = (char *)&g_parcel_set_buckets[0].candidates[g_parcel_set_buckets[v8].candidate_count].position
                          + v8 * 524;
                      v87 = 0;
                      v88 = 0;
                      v86 = v16 - 4.0 + 0.5;
                      *(float *)v18 = v86;
                      *((_DWORD *)v18 + 1) = v87;
                      *((_DWORD *)v18 + 2) = v88;
                      g_parcel_set_buckets[v8].set_id = v77;
                      ++g_parcel_set_buckets[v8].candidate_count;
                    }
                    else
                    {
                      g_zero_parcel_buckets[v15 / 0x83].segment_index = v2;
                      *(int32_t *)((char *)&g_zero_parcel_buckets[0].candidates[g_zero_parcel_buckets[v15 / 0x83].candidate_count].row
                                 + v15 * 4) = v9;
                      v17 = (char *)&g_zero_parcel_buckets[0].candidates[g_zero_parcel_buckets[v15 / 0x83].candidate_count].position
                          + v15 * 4;
                      v84 = 0;
                      v85 = 0;
                      v15 += 131;
                      v83 = v16 - 4.0 + 0.5;
                      *(float *)v17 = v83;
                      *((_DWORD *)v17 + 1) = v84;
                      *((_DWORD *)v17 + 2) = v85;
                      unk_53D188[v15] = 0;
                      ++v5;
                      ++unk_53D184[v15];
                      ++LODWORD(v72);
                    }
                  }
                  v19 = ++v76 < 8;
                  v82 += 64;
                }
                while ( v19 );
                ++v9;
                p_y = (ParcelBucket *)&out_angle->candidates[3].position.y;
                v76 = v5;
                v81 = (int32_t *)((char *)v81 + 1);
                p_row_count = v66;
                out_angle = (ParcelBucket *)((char *)out_angle + 56);
                if ( v9 >= *v66 )
                  break;
                v7 = v77;
              }
            }
            candidate_count = g_parcel_set_buckets[v8].candidate_count;
            if ( candidate_count > 0 )
            {
              segment_index = g_parcel_set_buckets[v8].segment_index;
              v22 = v90[segment_index];
              v23 = &v90[segment_index];
              if ( candidate_count < v22 )
                *v23 = candidate_count;
              if ( candidate_count > (int)v75 )
                v75 = (float *)candidate_count;
              ++v8;
              ++v79;
            }
            if ( ++v77 >= 10 )
              break;
            v7 = v77;
          }
          ++v2;
          v24 = v78->level_definition.segment_count;
          p_row_count += 4232;
          ++v80;
          v66 = p_row_count;
        }
        while ( v2 < v24 );
      }
      parcel_count = v78->level_definition.parcel_count;
      v26 = v78->level_definition.segment_count;
      v27 = 80 * parcel_count / 100 - (_DWORD)v75;
      v77 = v27;
      *(float *)&out_angle = v72;
      if ( v26 <= 0 )
      {
        v28 = out_angle;
      }
      else
      {
        v67 = v26;
        v28 = out_angle;
        v29 = v90;
        do
        {
          if ( *v29 != 10000 )
            v28 = (ParcelBucket *)((char *)v28 + *v29);
          ++v29;
          --v67;
        }
        while ( v67 );
      }
      if ( (int)v28 < parcel_count )
        report_errorf(
          "Parcel Allocation could fail in %s.  Add more parcel Sets",
          v78->level_definition.level_display_name);
      if ( v78->level_definition.parcel_count - v27 > SLODWORD(v72) )
        report_errorf(
          "Parcel Allocation could fail in %s. Add more 0 parcels ",
          v78->level_definition.level_display_name);
      v30 = 0;
      v73 = 0;
      if ( v27 > 0 )
      {
        v31 = v79;
        do
        {
          if ( v31 <= 0 )
            break;
          v64 = (float)v79;
          v68 = 0;
          v32 = (__int64)random_float_below(v64);
          v33 = g_parcel_set_buckets[v32].candidate_count;
          v73 = v33 + v30;
          if ( v33 > 0 )
          {
            v34 = &g_parcel_set_buckets[v32].candidates[0].position;
            do
            {
              out_angle = (ParcelBucket *)(LODWORD(v34[-1].z)
                                         + v78->level_definition.segment_slots[g_parcel_set_buckets[v32].segment_index].row_base);
              v35 = (float *)(&v78->scan_reset + 244 * (_DWORD)out_angle);
              if ( (byte_5CCAC8[(_DWORD)v35] & 0x10) != 0 )
                report_errorf("Duplicate Parcel Request in %s.", v78->level_definition.level_display_name);
              v36 = (float *)((char *)&unk_5CCB58 + (_DWORD)v35);
              v37 = (double)(int)out_angle;
              *(_DWORD *)&byte_5CCAC8[(_DWORD)v35] |= 0x11u;
              x = v34->x;
              v75 = v36;
              *v36 = x;
              v36[1] = v34->y;
              v36[2] = v34->z;
              v35[1520344] = v37 + v35[1520344] + 0.5;
              v35[1520343] = v35[1520343] + 1.0;
              if ( (byte_5CCAC8[(_DWORD)v35] & 0x20) != 0 )
                *v75 = *v75 * -1.0;
              v34 = (Vec3 *)((char *)v34 + 16);
              ++v68;
            }
            while ( v68 < g_parcel_set_buckets[v32].candidate_count );
          }
          v39 = nullptr;
          v82 = (int32_t *)g_parcel_set_buckets[v32].segment_index;
          v31 = v79;
          v75 = nullptr;
          if ( v79 > 0 )
          {
            v40 = (ParcelBucket *)(v79 - 1);
            p_candidate_count = &g_parcel_set_buckets[1].candidate_count;
            p_segment_index = &g_parcel_set_buckets[0].segment_index;
            out_angle = (ParcelBucket *)(v79 - 1);
            v81 = &g_parcel_set_buckets[1].candidate_count;
            v80 = &g_parcel_set_buckets[0].segment_index;
            do
            {
              if ( (int32_t *)*p_segment_index == v82 )
              {
                if ( (int)v39 < (int)v40 )
                {
                  v43 = p_candidate_count;
                  v69 = (char *)((char *)v40 - (char *)v39);
                  do
                  {
                    v44 = 0;
                    if ( *v43 > 0 )
                    {
                      v45 = v43 - 259;
                      do
                      {
                        v46 = v45 + 131;
                        v47 = v45;
                        ++v44;
                        v45 += 4;
                        *v47 = *v46;
                        v47[1] = v46[1];
                        v47[2] = v46[2];
                        v47[3] = v46[3];
                      }
                      while ( v44 < *v43 );
                      v39 = v75;
                    }
                    *(v43 - 131) = *v43;
                    *(v43 - 129) = v43[2];
                    *(v43 - 130) = v43[1];
                    v43 += 131;
                    --v69;
                  }
                  while ( v69 );
                  v40 = out_angle;
                  p_candidate_count = v81;
                  p_segment_index = v80;
                }
                v39 = (float *)((char *)v39 - 1);
                p_segment_index -= 131;
                p_candidate_count -= 131;
                v40 = (ParcelBucket *)((char *)v40 - 1);
                --v79;
                out_angle = v40;
                v31 = v79;
              }
              v39 = (float *)((char *)v39 + 1);
              p_segment_index += 131;
              p_candidate_count += 131;
              v75 = v39;
              v80 = p_segment_index;
              v81 = p_candidate_count;
            }
            while ( (int)v39 < v31 );
          }
          v30 = v73;
        }
        while ( v73 < v77 );
      }
      if ( v30 < v78->level_definition.parcel_count )
      {
        v75 = (float *)(v5 - 1);
        do
        {
          if ( v5 <= 0 )
            break;
          v65 = (float)v76;
          v48 = (__int64)random_float_below(v65);
          v49 = v48;
          v50 = g_zero_parcel_buckets[v48].segment_index;
          v73 += g_zero_parcel_buckets[v48].candidate_count;
          out_angle = &g_zero_parcel_buckets[v48];
          v70 = out_angle->candidates[0].row + v78->level_definition.segment_slots[v50].row_base;
          v51 = (float *)(&v78->scan_reset + 244 * v70);
          if ( (byte_5CCAC8[(_DWORD)v51] & 0x10) != 0 )
            report_errorf("Duplicate Parcel Request in %s.", v78->level_definition.level_display_name);
          *(_DWORD *)&byte_5CCAC8[(_DWORD)v51] |= 0x11u;
          v52 = (float *)((char *)&unk_5CCB58 + (_DWORD)v51);
          *v52 = g_zero_parcel_buckets[v48].candidates[0].position.x;
          v52[1] = g_zero_parcel_buckets[v49].candidates[0].position.y;
          v52[2] = g_zero_parcel_buckets[v49].candidates[0].position.z;
          v51[1520344] = (double)v70 + v51[1520344] + 0.5;
          v51[1520343] = v51[1520343] + 1.0;
          if ( (byte_5CCAC8[(_DWORD)v51] & 0x20) != 0 )
            *(float *)((char *)&unk_5CCB58 + (_DWORD)v51) = *(float *)((char *)&unk_5CCB58 + (_DWORD)v51) * -1.0;
          if ( v48 < (int)v75 )
          {
            v53 = *(float *)&out_angle;
            v54 = (char *)v75 - v48;
            do
            {
              --v54;
              *(_DWORD *)LODWORD(v53) = *(_DWORD *)(LODWORD(v53) + 524);
              *(_DWORD *)(LODWORD(v53) + 4) = *(_DWORD *)(LODWORD(v53) + 528);
              *(_DWORD *)(LODWORD(v53) + 8) = *(_DWORD *)(LODWORD(v53) + 532);
              *(_DWORD *)(LODWORD(v53) + 12) = *(_DWORD *)(LODWORD(v53) + 536);
              *(_DWORD *)(LODWORD(v53) + 512) = *(_DWORD *)(LODWORD(v53) + 1036);
              *(_DWORD *)(LODWORD(v53) + 520) = *(_DWORD *)(LODWORD(v53) + 1044);
              *(_DWORD *)(LODWORD(v53) + 516) = 0;
              LODWORD(v53) += 524;
            }
            while ( v54 );
          }
          --v5;
          v55 = v78->level_definition.parcel_count;
          v75 = (float *)((char *)v75 - 1);
          v76 = v5;
        }
        while ( v73 < v55 );
      }
      v56 = v78;
      v57 = v78->level_definition.parcel_count;
      if ( v73 != v57 )
      {
        report_errorf("Did not generate required Parcels(%i) in %s", v57, v78->level_definition.level_display_name);
        parcel_quota = v78->level_definition.parcel_quota;
        if ( parcel_quota )
          v78->level_definition.parcel_quota = v73 * v78->level_definition.parcel_count / parcel_quota;
      }
      v56->level_definition.parcel_count = v73;
      v71 = 0;
      if ( v56->runtime_row_count > 0 )
      {
        v59 = &byte_5CCAC8[(_DWORD)v56];
        do
        {
          if ( (*(_DWORD *)v59 & 1) != 0 && (*(_DWORD *)v59 & 0x40) != 0 )
          {
            v60 = (__int64)*((float *)v59 + 38) - get_track_cell_row_index(*((SubLoc **)v59 + 41));
            if ( v60 < 0 )
              v60 = 0;
            v61 = *((SubLoc **)v59 + 41);
            if ( v61->attachment_template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
            {
              compute_kind42_attachment_transform(
                v61->attachment_template_record,
                v61->attachment_template_record->primary_samples[v60].special_scalar,
                *((float *)v59 + 36),
                *((float *)v59 + 37),
                &transform,
                (float *)&out_angle);
              y = transform.position.y;
              *((_DWORD *)v59 + 36) = LODWORD(transform.position.x);
              *((float *)v59 + 37) = y;
            }
            else
            {
              track_cell_row_index = get_track_cell_row_index(v61);
              get_path_position_at_node(
                *(_DWORD **)(*((_DWORD *)v59 + 41) + 56),
                (float *)v59 + 36,
                v60,
                track_cell_row_index,
                (float *)v59 + 36);
            }
          }
          v59 += 244;
          ++v71;
        }
        while ( v71 < v56->runtime_row_count );
      }
    }
  }
}
