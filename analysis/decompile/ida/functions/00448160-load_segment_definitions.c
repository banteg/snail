/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_segment_definitions @ 0x448160 */
/* selector: load_segment_definitions */

// Implements the void `cRSMTracks::Import()` member: parses SEGMENTS/*.TXT into the exact 0x25cfb4-byte SMTracks owner, stores the internal `Name:'...'` display label separately from the enumerated filename, and fills each 0x4088-byte entry's complete 256-row authored metadata bank with parcel, model, velocity, path, ring, ring-speed, and jetpack-off data.
void __thiscall load_segment_definitions(SMTracks *tracks)
{
  int32_t count; // eax
  int32_t v3; // ebp
  char *v4; // edi
  char *case_insensitive_substring; // eax
  char v6; // cl
  char *v7; // eax
  int v8; // edx
  int32_t *v9; // esi
  char *v10; // eax
  char *v11; // eax
  char v12; // cl
  char *v13; // eax
  int v14; // esi
  char *v15; // eax
  _BYTE *crlf_line; // eax
  _BYTE *v17; // eax
  _BYTE *v18; // edi
  int v19; // ebp
  SMTracks *v20; // ecx
  char *v21; // edi
  char *v22; // esi
  int v23; // eax
  char v24; // bl
  int v25; // edx
  char *v26; // edi
  int v27; // eax
  char v28; // al
  char *i; // ecx
  char *v30; // eax
  char *v31; // eax
  char *v32; // ecx
  char j; // dl
  int v34; // eax
  _BYTE *v35; // ecx
  GameRoot *v36; // edx
  char *v37; // eax
  char *v38; // eax
  int v39; // edx
  char *v40; // eax
  int v41; // eax
  char *v42; // ecx
  char *v43; // eax
  char *v44; // eax
  char *v45; // edx
  char k; // cl
  PathManager *p_path_manager; // ecx
  int32_t segment_path_index_by_name; // eax
  int v49; // eax
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // eax
  char *v56; // eax
  double v57; // st7
  int v58; // eax
  bool v59; // cc
  const char *v60; // eax
  char *cursor; // [esp+10h] [ebp-114E0h] BYREF
  int32_t *p_row_count; // [esp+14h] [ebp-114DCh]
  char *v63; // [esp+18h] [ebp-114D8h]
  SMTracks *v64; // [esp+1Ch] [ebp-114D4h]
  int32_t v65; // [esp+20h] [ebp-114D0h]
  int v66; // [esp+24h] [ebp-114CCh]
  int v67; // [esp+28h] [ebp-114C8h]
  int v68; // [esp+2Ch] [ebp-114C4h]
  char name[64]; // [esp+30h] [ebp-114C0h] BYREF
  char v70[512]; // [esp+70h] [ebp-11480h] BYREF
  char mesh_name[128]; // [esp+270h] [ebp-11280h] BYREF
  char Buffer[512]; // [esp+2F0h] [ebp-11200h] BYREF
  char buffer[4096]; // [esp+4F0h] [ebp-11000h] BYREF
  char names[65536]; // [esp+14F0h] [ebp-10000h] BYREF

  v64 = tracks;
  tracks->count = 0;
  enumerate_matching_archive_or_fs_entries(aSegments, (char *)aTxt, &tracks->count, (EnumeratedEntryName *)names);
  count = tracks->count;
  if ( tracks->count < 150 )
  {
    v3 = 0;
    v65 = 0;
    if ( count > 0 )
    {
      v4 = names;
      v67 = 0;
      v66 = 0;
      v63 = names;
      p_row_count = &tracks->entries[0].row_count;
      while ( 2 )
      {
        sprintf(Buffer, "Segments/%s", v4);
        load_file_bytes_from_archive_or_fs(Buffer, buffer, nullptr);
        case_insensitive_substring = find_case_insensitive_substring(aId, buffer);
        if ( case_insensitive_substring )
        {
          v6 = case_insensitive_substring[3];
          v7 = case_insensitive_substring + 3;
          v8 = 0;
          if ( v6 >= 48 )
          {
            do
            {
              if ( v6 > 57 )
                break;
              ++v7;
              v8 = v6 + 10 * v8 - 48;
              v6 = *v7;
            }
            while ( *v7 >= 48 );
          }
          v9 = p_row_count - 17;
          v9[16] = v8;
          sprintf((char *const)v9, "%s", v4);
          v10 = find_case_insensitive_substring(aName, buffer);
          if ( v10 )
          {
            v11 = find_case_insensitive_substring(asc_4AC244, v10);
            v12 = v11[1];
            v13 = v11 + 1;
            if ( v12 != 39 )
            {
              v14 = (char *)v9 - v13;
              do
              {
                v13[v14 - 64] = v12;
                v12 = *++v13;
              }
              while ( v12 != 39 );
            }
            v15 = find_case_insensitive_substring(aData, buffer);
            if ( v15 )
            {
              crlf_line = (_BYTE *)advance_to_next_crlf_line(v15);
              if ( crlf_line )
              {
                v17 = (_BYTE *)advance_to_next_crlf_line(crlf_line);
                v18 = v17;
                if ( v17 )
                {
                  if ( *v17 == 64 )
                  {
                    v68 = 0;
                    *p_row_count = 0;
                    while ( *v18 != 64 || v18[1] != 64 || v18[2] != 64 )
                    {
                      v19 = (__int16)v68 + v67;
                      v20 = v64;
                      v21 = v18 + 1;
                      v22 = (char *)v64 + 56 * v19;
                      v23 = 0;
                      *((_DWORD *)v22 + 547) = 0;
                      do
                      {
                        v24 = *v21++;
                        v25 = v23 + 8 * (v66 + *p_row_count);
                        ++v23;
                        v20->entries[0].glyph_columns[0][v25] = v24;
                      }
                      while ( v23 < 8 );
                      if ( *v21 != 64 )
                      {
                        report_errorf("Data line must end with '@' in Segment %s\n", &names[128 * v65]);
                        return;
                      }
                      v26 = v21 + 1;
                      ++*p_row_count;
                      if ( *v26 == 42 )
                      {
                        v27 = *((_DWORD *)v22 + 547);
                        LOBYTE(v27) = v27 | 4;
                        *((_DWORD *)v22 + 547) = v27;
                      }
                      v28 = *v26;
                      for ( i = v70; v28 != 13; ++v26 )
                      {
                        *i = v28;
                        v28 = v26[1];
                        ++i;
                      }
                      *i = 0;
                      v30 = find_case_insensitive_substring(a3dmodel, v70);
                      cursor = v30;
                      if ( v30 )
                      {
                        v31 = find_case_insensitive_substring(asc_4A2094, v30) + 1;
                        cursor = v31;
                        v32 = mesh_name;
                        for ( j = *v31; *v31 != 46; j = *v31 )
                        {
                          *v32++ = j;
                          cursor = ++v31;
                        }
                        v34 = *((_DWORD *)v22 + 547);
                        *v32 = 46;
                        v35 = v32 + 1;
                        LOBYTE(v34) = v34 | 2;
                        *((_DWORD *)v22 + 547) = v34;
                        v36 = g_game_base;
                        *v35 = 120;
                        v35[1] = 0;
                        *((_DWORD *)v22 + 552) = load_or_reuse_cached_x_mesh(&v36->directx_loader, mesh_name);
                        cursor = find_case_insensitive_substring(asc_4AC438, cursor);
                        *((float *)v22 + 553) = parse_next_float32(&cursor);
                        *((float *)v22 + 554) = parse_next_float32(&cursor);
                        *((float *)v22 + 555) = parse_next_float32(&cursor);
                        v37 = find_case_insensitive_substring(aVelocity, v70);
                        cursor = v37;
                        if ( v37 )
                        {
                          v38 = find_case_insensitive_substring(asc_4A2094, v37);
                          v39 = *((_DWORD *)v22 + 547) | 8;
                          cursor = v38 + 1;
                          *((_DWORD *)v22 + 547) = v39;
                          cursor = find_case_insensitive_substring(asc_4AC438, v38 + 1);
                          *((float *)v22 + 556) = parse_next_float32(&cursor);
                          *((float *)v22 + 557) = parse_next_float32(&cursor);
                          *((float *)v22 + 558) = parse_next_float32(&cursor);
                        }
                      }
                      v40 = find_case_insensitive_substring(aParcel, v70);
                      cursor = v40;
                      if ( v40 )
                      {
                        *((_DWORD *)v22 + 547) |= 1u;
                        cursor = find_case_insensitive_substring(asc_4A2094, v40) + 1;
                        v41 = parse_next_signed_int(&cursor);
                        v42 = cursor;
                        *((_DWORD *)v22 + 548) = v41;
                        cursor = find_case_insensitive_substring(asc_4AC438, v42) + 1;
                        *((float *)v22 + 549) = parse_next_float32(&cursor);
                        *((float *)v22 + 550) = parse_next_float32(&cursor);
                        *((float *)v22 + 551) = parse_next_float32(&cursor);
                      }
                      v43 = find_case_insensitive_substring(aPath, v70);
                      cursor = v43;
                      if ( v43 )
                      {
                        v44 = find_case_insensitive_substring(asc_4A2094, v43) + 1;
                        cursor = v44;
                        v45 = name;
                        for ( k = *v44; *v44 >= 32; k = *v44 )
                        {
                          *v45++ = k;
                          cursor = ++v44;
                        }
                        p_path_manager = &g_game_base->subgame.path_manager;
                        *v45 = 0;
                        segment_path_index_by_name = find_segment_path_index_by_name(p_path_manager, name);
                        *((_DWORD *)v22 + 559) = segment_path_index_by_name;
                        if ( segment_path_index_by_name == -1 )
                        {
                          report_errorf("Unknown path %s in %s", name, v63);
                        }
                        else
                        {
                          v49 = *((_DWORD *)v22 + 547);
                          LOBYTE(v49) = v49 | 8;
                          *((_DWORD *)v22 + 547) = v49;
                        }
                      }
                      cursor = find_case_insensitive_substring(aNofall, v70);
                      if ( cursor )
                      {
                        v50 = *((_DWORD *)v22 + 547);
                        BYTE1(v50) |= 1u;
                        *((_DWORD *)v22 + 547) = v50;
                      }
                      cursor = find_case_insensitive_substring(aRingNone, v70);
                      if ( cursor )
                      {
                        v51 = *((_DWORD *)v22 + 547);
                        BYTE1(v51) |= 2u;
                        *((_DWORD *)v22 + 547) = v51;
                      }
                      cursor = find_case_insensitive_substring(aRingNormal, v70);
                      if ( cursor )
                      {
                        v52 = *((_DWORD *)v22 + 547);
                        BYTE1(v52) |= 4u;
                        *((_DWORD *)v22 + 547) = v52;
                      }
                      cursor = find_case_insensitive_substring(aRingPowerup, v70);
                      if ( cursor )
                      {
                        v53 = *((_DWORD *)v22 + 547);
                        BYTE1(v53) |= 0x20u;
                        *((_DWORD *)v22 + 547) = v53;
                      }
                      cursor = find_case_insensitive_substring(aRingExplode, v70);
                      if ( cursor )
                      {
                        v54 = *((_DWORD *)v22 + 547);
                        BYTE1(v54) |= 8u;
                        *((_DWORD *)v22 + 547) = v54;
                      }
                      cursor = find_case_insensitive_substring(aRingSlow, v70);
                      if ( cursor )
                      {
                        v55 = *((_DWORD *)v22 + 547);
                        BYTE1(v55) |= 0x10u;
                        *((_DWORD *)v22 + 547) = v55;
                      }
                      v56 = find_case_insensitive_substring(aRingspeed, v70);
                      cursor = v56;
                      if ( v56 )
                      {
                        cursor = find_case_insensitive_substring(asc_4A2094, v56) + 1;
                        v57 = parse_next_float32(&cursor);
                        v64->entries[0].rows[v19].ring_speed.value = v57;
                      }
                      else
                      {
                        v64->entries[0].rows[v19].ring_speed.bits = 0;
                      }
                      cursor = find_case_insensitive_substring(aJetpackOff, v70);
                      if ( cursor )
                      {
                        v58 = *((_DWORD *)v22 + 547);
                        BYTE1(v58) |= 0x80u;
                        *((_DWORD *)v22 + 547) = v58;
                      }
                      v18 = (_BYTE *)advance_to_next_crlf_line(v26);
                      if ( !v18 )
                      {
                        v60 = &names[128 * v65];
                        goto LABEL_71;
                      }
                      v3 = v65;
                      ++v68;
                    }
                    ++v3;
                    v67 += 295;
                    v59 = v3 < v64->count;
                    v65 = v3;
                    v66 += 2065;
                    p_row_count += 4130;
                    v63 += 128;
                    if ( v59 )
                    {
                      v4 = v63;
                      continue;
                    }
                  }
                  else
                  {
                    report_errorf("Data line must start with '@' in Segment %s\n", &names[128 * v3]);
                  }
                }
                else
                {
                  v60 = &names[128 * v3];
LABEL_71:
                  report_errorf("Unexpected end of file in Segment %s\n", v60);
                }
              }
              else
              {
                report_errorf("Unexpected end of file in Segment %s\n", &names[128 * v3]);
              }
            }
            else
            {
              report_errorf("Cannot find Data: in Segment %s\n", &names[128 * v3]);
            }
          }
          else
          {
            report_errorf("Cannot find Name: in Segment %s\n", &names[128 * v3]);
          }
        }
        else
        {
          report_errorf("Cannot find ID: in Segment %s\n", &names[128 * v3]);
        }
        break;
      }
    }
  }
  else
  {
    report_errorf(aTooManySegment);
  }
}
