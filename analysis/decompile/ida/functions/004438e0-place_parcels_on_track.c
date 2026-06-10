/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: place_parcels_on_track @ 0x4438e0 */
/* selector: place_parcels_on_track */

// Places parcels for the current course and projects flagged parcel offsets onto generated track rows. Cross-port Android and iOS symbols match this helper to `cRSubGame::PlaceParcels()`.
int32_t __thiscall place_parcels_on_track(Game *game)
{
  int32_t result; // eax
  float v2; // esi
  int i; // eax
  int32_t level_segment_count; // eax
  int v5; // ebp
  int *v6; // ebx
  int v7; // eax
  int v8; // ecx
  float v9; // edx
  float *v10; // edi
  int v11; // eax
  float *v12; // ebx
  int v13; // ebp
  _DWORD *v14; // eax
  int v15; // eax
  double v16; // st7
  float *v17; // edi
  char *v18; // edi
  bool v19; // cc
  int v20; // eax
  int v21; // edx
  int v22; // edi
  int *v23; // edx
  int32_t v24; // ecx
  int v25; // edi
  int v26; // eax
  int v27; // esi
  float *v28; // eax
  _DWORD *v29; // edx
  int v30; // ebx
  int v31; // eax
  int v32; // edi
  int v33; // eax
  float *v34; // ebx
  float *v35; // esi
  float *v36; // eax
  double v37; // st7
  float v38; // ecx
  float *v39; // ecx
  float *v40; // edi
  int *v41; // edx
  int *v42; // esi
  int *v43; // eax
  int v44; // edx
  int *v45; // ecx
  int *v46; // esi
  int *v47; // edi
  int v48; // ebx
  int v49; // esi
  float v50; // eax
  float *v51; // edi
  float *v52; // edx
  float v53; // eax
  char *v54; // edx
  int v55; // ecx
  Game *v56; // ebp
  int v57; // eax
  int v58; // ecx
  char *v59; // esi
  int v60; // edi
  _DWORD *v61; // ecx
  float y; // edx
  int track_cell_row_index; // eax
  float v64; // [esp+0h] [ebp-22Ch]
  float v65; // [esp+0h] [ebp-22Ch]
  uint8_t *v66; // [esp+18h] [ebp-214h]
  int v67; // [esp+18h] [ebp-214h]
  int v68; // [esp+18h] [ebp-214h]
  char *v69; // [esp+18h] [ebp-214h]
  int v70; // [esp+18h] [ebp-214h]
  int32_t v71; // [esp+18h] [ebp-214h]
  float v72; // [esp+1Ch] [ebp-210h]
  int v73; // [esp+1Ch] [ebp-210h]
  float *out_angle; // [esp+20h] [ebp-20Ch] BYREF
  float *v75; // [esp+24h] [ebp-208h]
  int v76; // [esp+28h] [ebp-204h]
  int v77; // [esp+2Ch] [ebp-200h]
  Game *v78; // [esp+30h] [ebp-1FCh]
  int v79; // [esp+34h] [ebp-1F8h]
  int *v80; // [esp+38h] [ebp-1F4h]
  char *v81; // [esp+3Ch] [ebp-1F0h]
  char *v82; // [esp+40h] [ebp-1ECh]
  float v83; // [esp+44h] [ebp-1E8h]
  int v84; // [esp+48h] [ebp-1E4h]
  int v85; // [esp+4Ch] [ebp-1E0h]
  float v86; // [esp+50h] [ebp-1DCh]
  int v87; // [esp+54h] [ebp-1D8h]
  int v88; // [esp+58h] [ebp-1D4h]
  TransformMatrix transform; // [esp+5Ch] [ebp-1D0h] BYREF
  _DWORD v90[100]; // [esp+9Ch] [ebp-190h] BYREF

  result = game->level_mode;
  v78 = game;
  if ( result == 1 )
    return place_challenge_parcels_on_track((int)game);
  v2 = 0.0;
  if ( !result || result == 7 )
  {
    for ( i = 0; i < 268288; i += 131 )
    {
      flt_4DFAFC[i + 95781] = 0.0;
      unk_6489E8[i] = 0;
    }
    level_segment_count = game->level_segment_count;
    v5 = 0;
    v72 = 0.0;
    v76 = 0;
    v79 = 0;
    if ( level_segment_count > 0 )
    {
      v6 = (int *)&game->_pad_a878[4];
      v80 = v90;
      v66 = &game->_pad_a878[4];
      do
      {
        v7 = 0;
        v75 = nullptr;
        v77 = 0;
        *v80 = 10000;
        v8 = 131 * v79;
        while ( 1 )
        {
          v9 = 0.0;
          if ( *v6 > 0 )
          {
            v81 = (char *)(v6 + 4);
            v10 = (float *)(v6 + 518);
            out_angle = (float *)(v6 + 518);
            while ( 1 )
            {
              if ( (*(_BYTE *)(v10 - 2) & 1) != 0 && *((_DWORD *)v10 - 1) == v7 )
              {
                if ( v7 )
                {
                  *(float *)&unk_6489F0[v8] = v2;
                  *(float *)&unk_6487E8[4 * unk_6489E8[v8] + v8] = v9;
                  v14 = (_DWORD *)((char *)&unk_6487EC + 16 * unk_6489E8[v8] + v8 * 4);
                  *v14 = *(_DWORD *)v10;
                  v14[1] = *((_DWORD *)v10 + 1);
                  v14[2] = *((_DWORD *)v10 + 2);
                  unk_6489EC[v8] = v77;
                  ++unk_6489E8[v8];
                }
                else
                {
                  v11 = 131 * v5;
                  flt_4DFAFC[v11 + 95783] = v2;
                  flt_4DFAFC[4 * LODWORD(flt_4DFAFC[131 * v5 + 95781]) + 95653 + v11] = v9;
                  v12 = &flt_4DFAFC[131 * v5 + 95654 + 4 * LODWORD(flt_4DFAFC[131 * v5 + 95781])];
                  *v12 = *v10;
                  v12[1] = v10[1];
                  v13 = v76;
                  v12[2] = v10[2];
                  flt_4DFAFC[v11 + 95782] = 0.0;
                  v5 = v13 + 1;
                  ++LODWORD(flt_4DFAFC[v11 + 95781]);
                  v76 = v5;
                  ++LODWORD(v72);
                }
              }
              v76 = 0;
              v82 = v81;
              v15 = 131 * v5;
              do
              {
                if ( *v82 == v77 + 48 )
                {
                  v16 = (double)v76;
                  if ( v77 )
                  {
                    *(float *)&unk_6489F0[v8] = v2;
                    *(float *)&unk_6487E8[4 * unk_6489E8[v8] + v8] = v9;
                    v18 = (char *)&unk_6487EC + 16 * unk_6489E8[v8] + v8 * 4;
                    v87 = 0;
                    v88 = 0;
                    v86 = v16 - 4.0 + 0.5;
                    *(float *)v18 = v86;
                    *((_DWORD *)v18 + 1) = v87;
                    *((_DWORD *)v18 + 2) = v88;
                    unk_6489EC[v8] = v77;
                    ++unk_6489E8[v8];
                  }
                  else
                  {
                    flt_4DFAFC[v15 + 95783] = v2;
                    flt_4DFAFC[4 * LODWORD(flt_4DFAFC[v15 + 95781]) + 95653 + v15] = v9;
                    v17 = &flt_4DFAFC[4 * LODWORD(flt_4DFAFC[v15 + 95781]) + 95654 + v15];
                    v84 = 0;
                    v85 = 0;
                    v15 += 131;
                    v83 = v16 - 4.0 + 0.5;
                    *v17 = v83;
                    *((_DWORD *)v17 + 1) = v84;
                    *((_DWORD *)v17 + 2) = v85;
                    flt_4DFAFC[v15 + 95651] = 0.0;
                    ++v5;
                    ++LODWORD(flt_4DFAFC[v15 + 95650]);
                    ++LODWORD(v72);
                  }
                }
                v19 = ++v76 < 8;
                v82 += 256;
              }
              while ( v19 );
              ++LODWORD(v9);
              v10 = out_angle + 14;
              v76 = v5;
              ++v81;
              v6 = (int *)v66;
              out_angle += 14;
              if ( SLODWORD(v9) >= *(_DWORD *)v66 )
                break;
              v7 = v77;
            }
          }
          v20 = unk_6489E8[v8];
          if ( v20 > 0 )
          {
            v21 = unk_6489F0[v8];
            v22 = v90[v21];
            v23 = &v90[v21];
            if ( v20 < v22 )
              *v23 = v20;
            if ( v20 > (int)v75 )
              v75 = (float *)v20;
            v8 += 131;
            ++v79;
          }
          if ( ++v77 >= 10 )
            break;
          v7 = v77;
        }
        ++LODWORD(v2);
        v24 = v78->level_segment_count;
        v6 += 4232;
        ++v80;
        v66 = (uint8_t *)v6;
      }
      while ( SLODWORD(v2) < v24 );
    }
    v25 = *(_DWORD *)&v78->_pad_74622[1293246];
    v26 = v78->level_segment_count;
    v27 = 80 * v25 / 100 - (_DWORD)v75;
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
          v28 = (float *)((char *)v28 + *v29);
        ++v29;
        --v67;
      }
      while ( v67 );
    }
    if ( (int)v28 < v25 )
      report_errorf(
        "Parcel Allocation could fail in %s.  Add more parcel Sets",
        (const char *)&v78->_pad_74622[1293102]);
    if ( *(_DWORD *)&v78->_pad_74622[1293246] - v27 > SLODWORD(v72) )
      report_errorf("Parcel Allocation could fail in %s. Add more 0 parcels ", (const char *)&v78->_pad_74622[1293102]);
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
        v32 = 131 * (__int64)random_float_below(v64);
        v33 = unk_6489E8[v32];
        v73 = v33 + v30;
        if ( v33 > 0 )
        {
          v34 = (float *)((char *)&unk_6487EC + v32 * 4);
          do
          {
            out_angle = (float *)(*((_DWORD *)v34 - 1) + *(_DWORD *)&v78->_pad_a878[16928 * unk_6489F0[v32]]);
            v35 = (float *)&v78->_pad_00[244 * (_DWORD)out_angle];
            if ( (byte_5CCAC8[(_DWORD)v35] & 0x10) != 0 )
              report_errorf("Duplicate Parcel Request in %s.", (const char *)&v78->_pad_74622[1293102]);
            v36 = (float *)((char *)&unk_5CCB58 + (_DWORD)v35);
            v37 = (double)(int)out_angle;
            *(_DWORD *)&byte_5CCAC8[(_DWORD)v35] |= 0x11u;
            v38 = *v34;
            v75 = v36;
            *v36 = v38;
            v36[1] = v34[1];
            v36[2] = v34[2];
            v35[1520344] = v37 + v35[1520344] + 0.5;
            v35[1520343] = v35[1520343] + 1.0;
            if ( (byte_5CCAC8[(_DWORD)v35] & 0x20) != 0 )
              *v75 = *v75 * -1.0;
            v34 += 4;
            ++v68;
          }
          while ( v68 < unk_6489E8[v32] );
        }
        v39 = nullptr;
        v82 = (char *)unk_6489F0[v32];
        v31 = v79;
        v75 = nullptr;
        if ( v79 > 0 )
        {
          v40 = (float *)(v79 - 1);
          v41 = (int *)&unk_648BF4;
          v42 = unk_6489F0;
          out_angle = (float *)(v79 - 1);
          v81 = (char *)&unk_648BF4;
          v80 = unk_6489F0;
          do
          {
            if ( (char *)*v42 == v82 )
            {
              if ( (int)v39 < (int)v40 )
              {
                v43 = v41;
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
                v41 = (int *)v81;
                v42 = v80;
              }
              v39 = (float *)((char *)v39 - 1);
              v42 -= 131;
              v41 -= 131;
              v40 = (float *)((char *)v40 - 1);
              --v79;
              out_angle = v40;
              v31 = v79;
            }
            v39 = (float *)((char *)v39 + 1);
            v42 += 131;
            v41 += 131;
            v75 = v39;
            v80 = v42;
            v81 = (char *)v41;
          }
          while ( (int)v39 < v31 );
        }
        v30 = v73;
      }
      while ( v73 < v77 );
    }
    if ( v30 < *(_DWORD *)&v78->_pad_74622[1293246] )
    {
      v75 = (float *)(v5 - 1);
      do
      {
        if ( v5 <= 0 )
          break;
        v65 = (float)v76;
        v48 = (__int64)random_float_below(v65);
        v49 = 131 * v48;
        v50 = flt_4DFAFC[131 * v48 + 95783];
        v73 += LODWORD(flt_4DFAFC[131 * v48 + 95781]);
        out_angle = &flt_4DFAFC[131 * v48 + 95653];
        v70 = *(_DWORD *)out_angle + *(_DWORD *)&v78->_pad_a878[16928 * LODWORD(v50)];
        v51 = (float *)&v78->_pad_00[244 * v70];
        if ( (byte_5CCAC8[(_DWORD)v51] & 0x10) != 0 )
          report_errorf("Duplicate Parcel Request in %s.", (const char *)&v78->_pad_74622[1293102]);
        *(_DWORD *)&byte_5CCAC8[(_DWORD)v51] |= 0x11u;
        v52 = (float *)((char *)&unk_5CCB58 + (_DWORD)v51);
        *v52 = flt_4DFAFC[131 * v48 + 95654];
        v52[1] = flt_4DFAFC[v49 + 95655];
        v52[2] = flt_4DFAFC[v49 + 95656];
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
        v55 = *(_DWORD *)&v78->_pad_74622[1293246];
        v75 = (float *)((char *)v75 - 1);
        v76 = v5;
      }
      while ( v73 < v55 );
    }
    v56 = v78;
    v57 = *(_DWORD *)&v78->_pad_74622[1293246];
    if ( v73 != v57 )
    {
      report_errorf("Did not generate required Parcels(%i) in %s", v57, (const char *)&v78->_pad_74622[1293102]);
      v58 = *(_DWORD *)&v78->_pad_74622[1293254];
      if ( v58 )
        *(_DWORD *)&v78->_pad_74622[1293254] = v73 * *(_DWORD *)&v78->_pad_74622[1293246] / v58;
    }
    *(_DWORD *)&v56->_pad_74622[1293246] = v73;
    result = v56->runtime_row_count;
    v71 = 0;
    if ( result > 0 )
    {
      v59 = &byte_5CCAC8[(_DWORD)v56];
      do
      {
        if ( (*(_DWORD *)v59 & 1) != 0 && (*(_DWORD *)v59 & 0x40) != 0 )
        {
          v60 = (__int64)*((float *)v59 + 38) - get_track_cell_row_index(*((_DWORD **)v59 + 41));
          if ( v60 < 0 )
            v60 = 0;
          v61 = *((_DWORD **)v59 + 41);
          if ( *(_DWORD *)(v61[14] + 56) == 42 )
          {
            compute_kind42_attachment_transform(
              *(float *)(*(_DWORD *)(v61[14] + 88) + 168 * v60 + 160),
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
        result = v71 + 1;
        v59 += 244;
        ++v71;
      }
      while ( v71 < v56->runtime_row_count );
    }
  }
  return result;
}

