/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_segment_definitions @ 0x448160 */
/* selector: load_segment_definitions */

// Implements the void `cRSMTracks::Import()` member: parses SEGMENTS/*.TXT into the exact 0x25cfb4-byte SMTracks owner, stores the internal `Name:'...'` display label separately from the enumerated filename, and fills each 0x4088-byte entry's complete 256-row authored metadata bank with parcel, model, velocity, path, ring, ring-speed, and jetpack-off data.
void __thiscall load_segment_definitions(SMTracks *tracks)
{
  int32_t count; // eax
  int32_t segment_index; // ebp
  const char *segment_file_name; // edi
  char *case_insensitive_substring; // eax
  char v6; // cl
  char *v7; // eax
  int v8; // edx
  char *entry_filename_cursor; // esi
  char *v10; // eax
  char *v11; // eax
  char v12; // cl
  char *v13; // eax
  char *v14; // esi
  char *v15; // eax
  char *crlf_line; // eax
  char *v17; // eax
  char *data_line_cursor; // edi
  int32_t flattened_row_index; // ebp
  SMTracks *glyph_catalog; // ecx
  char *glyph_cursor; // edi
  SegmentCatalogRowStrideAnchor *row_stride_anchor; // esi
  int32_t lane_index; // eax
  char glyph; // bl
  int v25; // edx
  char *option_cursor; // edi
  int32_t flags; // eax
  char option_char; // al
  char *option_out_cursor; // ecx
  char *v30; // eax
  char *model_value_cursor; // eax
  char *mesh_name_cursor; // ecx
  char mesh_char; // dl
  int32_t v34; // eax
  char *v35; // ecx
  GameRoot *v36; // edx
  char *v37; // eax
  char *v38; // eax
  int32_t v39; // edx
  char *v40; // eax
  int32_t v41; // eax
  char *v42; // ecx
  char *v43; // eax
  char *path_value_cursor; // eax
  char *path_name_cursor; // edx
  char path_char; // cl
  cRPathManager *p_path_manager; // ecx
  int32_t segment_path_index_by_name; // eax
  int32_t v49; // eax
  int32_t v50; // eax
  int32_t v51; // eax
  int32_t v52; // eax
  int32_t v53; // eax
  int32_t v54; // eax
  int32_t v55; // eax
  char *v56; // eax
  double v57; // st7
  int32_t v58; // eax
  bool v59; // cc
  const char *v60; // eax
  char *parse_cursor; // [esp+10h] [ebp-114E0h] BYREF
  int32_t *row_count_cursor; // [esp+14h] [ebp-114DCh]
  char *segment_file_name_cursor; // [esp+18h] [ebp-114D8h]
  SMTracks *tracks_after_stack_probe; // [esp+1Ch] [ebp-114D4h]
  int32_t segment_index_spill; // [esp+20h] [ebp-114D0h]
  int32_t glyph_row_base; // [esp+24h] [ebp-114CCh]
  int32_t segment_row_base; // [esp+28h] [ebp-114C8h]
  int32_t row_index; // [esp+2Ch] [ebp-114C4h]
  char path_name[64]; // [esp+30h] [ebp-114C0h] BYREF
  char option_text[512]; // [esp+70h] [ebp-11480h] BYREF
  char mesh_name[128]; // [esp+270h] [ebp-11280h] BYREF
  char file_path[512]; // [esp+2F0h] [ebp-11200h] BYREF
  char file_buffer[4096]; // [esp+4F0h] [ebp-11000h] BYREF
  char segment_files[512][128]; // [esp+14F0h] [ebp-10000h] BYREF

  tracks_after_stack_probe = tracks;
  tracks->count = 0;
  enumerate_matching_archive_or_fs_entries(aSegments, (char *)aTxt, &tracks->count, segment_files);
  count = tracks->count;
  if ( tracks->count < 150 )
  {
    segment_index = 0;
    segment_index_spill = 0;
    if ( count > 0 )
    {
      segment_file_name = segment_files[0];
      segment_row_base = 0;
      glyph_row_base = 0;
      segment_file_name_cursor = segment_files[0];
      row_count_cursor = &tracks->entries[0].row_count;
      while ( 2 )
      {
        sprintf(file_path, "Segments/%s", segment_file_name);
        load_file_bytes_from_archive_or_fs(file_path, file_buffer, nullptr);
        case_insensitive_substring = find_case_insensitive_substring(aId, file_buffer);
        if ( case_insensitive_substring != nullptr )
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
          entry_filename_cursor = (char *)(row_count_cursor - 17);
          *((_DWORD *)entry_filename_cursor + 16) = v8;
          sprintf(entry_filename_cursor, "%s", segment_file_name);
          v10 = find_case_insensitive_substring(aName, file_buffer);
          if ( v10 != nullptr )
          {
            v11 = find_case_insensitive_substring(asc_4AC244, v10);
            v12 = v11[1];
            v13 = v11 + 1;
            if ( v12 != 39 )
            {
              v14 = (char *)(entry_filename_cursor - v13);
              do
              {
                v13[(_DWORD)(v14 - 64)] = v12;
                v12 = *++v13;
              }
              while ( v12 != 39 );
            }
            v15 = find_case_insensitive_substring(aData, file_buffer);
            if ( v15 != nullptr )
            {
              crlf_line = advance_to_next_crlf_line(v15);
              if ( crlf_line != nullptr )
              {
                v17 = advance_to_next_crlf_line(crlf_line);
                data_line_cursor = v17;
                if ( v17 != nullptr )
                {
                  if ( *v17 == 64 )
                  {
                    row_index = 0;
                    *row_count_cursor = 0;
                    while ( *data_line_cursor != 64 || data_line_cursor[1] != 64 || data_line_cursor[2] != 64 )
                    {
                      flattened_row_index = (__int16)row_index + segment_row_base;
                      glyph_catalog = tracks_after_stack_probe;
                      glyph_cursor = data_line_cursor + 1;
                      row_stride_anchor = (SegmentCatalogRowStrideAnchor *)((char *)tracks_after_stack_probe
                                                                          + 56 * flattened_row_index);
                      lane_index = 0;
                      row_stride_anchor->row.flags = 0;
                      do
                      {
                        glyph = *glyph_cursor++;
                        v25 = lane_index + 8 * (glyph_row_base + *row_count_cursor);
                        ++lane_index;
                        glyph_catalog->entries[0].glyph_columns[0][v25] = glyph;
                      }
                      while ( lane_index < 8 );
                      if ( *glyph_cursor != 64 )
                      {
                        report_errorf("Data line must end with '@' in Segment %s\n", segment_files[segment_index_spill]);
                        return;
                      }
                      option_cursor = glyph_cursor + 1;
                      ++*row_count_cursor;
                      if ( *option_cursor == 42 )
                      {
                        flags = row_stride_anchor->row.flags;
                        LOBYTE(flags) = flags | 4;
                        row_stride_anchor->row.flags = flags;
                      }
                      option_char = *option_cursor;
                      for ( option_out_cursor = option_text; option_char != 13; ++option_cursor )
                      {
                        *option_out_cursor = option_char;
                        option_char = option_cursor[1];
                        ++option_out_cursor;
                      }
                      *option_out_cursor = 0;
                      v30 = find_case_insensitive_substring(a3dmodel, option_text);
                      parse_cursor = v30;
                      if ( v30 != nullptr )
                      {
                        model_value_cursor = find_case_insensitive_substring(asc_4A2094, v30) + 1;
                        parse_cursor = model_value_cursor;
                        mesh_name_cursor = mesh_name;
                        for ( mesh_char = *model_value_cursor; *model_value_cursor != 46; mesh_char = *model_value_cursor )
                        {
                          *mesh_name_cursor++ = mesh_char;
                          parse_cursor = ++model_value_cursor;
                        }
                        v34 = row_stride_anchor->row.flags;
                        *mesh_name_cursor = 46;
                        v35 = mesh_name_cursor + 1;
                        LOBYTE(v34) = v34 | 2;
                        row_stride_anchor->row.flags = v34;
                        v36 = g_game_base;
                        *v35 = 120;
                        v35[1] = 0;
                        row_stride_anchor->row.object_id = load_or_reuse_cached_x_mesh(&v36->directx_loader, mesh_name);
                        parse_cursor = find_case_insensitive_substring(asc_4AC438, parse_cursor);
                        row_stride_anchor->row.object_position.x = parse_next_float32(&parse_cursor);
                        row_stride_anchor->row.object_position.y = parse_next_float32(&parse_cursor);
                        row_stride_anchor->row.object_position.z = parse_next_float32(&parse_cursor);
                        v37 = find_case_insensitive_substring(aVelocity, option_text);
                        parse_cursor = v37;
                        if ( v37 != nullptr )
                        {
                          v38 = find_case_insensitive_substring(asc_4A2094, v37);
                          v39 = row_stride_anchor->row.flags | 8;
                          parse_cursor = v38 + 1;
                          row_stride_anchor->row.flags = v39;
                          parse_cursor = find_case_insensitive_substring(asc_4AC438, v38 + 1);
                          row_stride_anchor->row.object_velocity.x = parse_next_float32(&parse_cursor);
                          row_stride_anchor->row.object_velocity.y = parse_next_float32(&parse_cursor);
                          row_stride_anchor->row.object_velocity.z = parse_next_float32(&parse_cursor);
                        }
                      }
                      v40 = find_case_insensitive_substring(aParcel, option_text);
                      parse_cursor = v40;
                      if ( v40 != nullptr )
                      {
                        row_stride_anchor->row.flags |= 1u;
                        parse_cursor = find_case_insensitive_substring(asc_4A2094, v40) + 1;
                        v41 = parse_next_signed_int(&parse_cursor);
                        v42 = parse_cursor;
                        row_stride_anchor->row.parcel_set_id = v41;
                        parse_cursor = find_case_insensitive_substring(asc_4AC438, v42) + 1;
                        row_stride_anchor->row.local_position.x = parse_next_float32(&parse_cursor);
                        row_stride_anchor->row.local_position.y = parse_next_float32(&parse_cursor);
                        row_stride_anchor->row.local_position.z = parse_next_float32(&parse_cursor);
                      }
                      v43 = find_case_insensitive_substring(aPath, option_text);
                      parse_cursor = v43;
                      if ( v43 != nullptr )
                      {
                        path_value_cursor = find_case_insensitive_substring(asc_4A2094, v43) + 1;
                        parse_cursor = path_value_cursor;
                        path_name_cursor = path_name;
                        for ( path_char = *path_value_cursor; *path_value_cursor >= 32; path_char = *path_value_cursor )
                        {
                          *path_name_cursor++ = path_char;
                          parse_cursor = ++path_value_cursor;
                        }
                        p_path_manager = &g_game_base->subgame.path_manager;
                        *path_name_cursor = 0;
                        segment_path_index_by_name = find_segment_path_index_by_name(p_path_manager, path_name);
                        row_stride_anchor->row.path_template_index = segment_path_index_by_name;
                        if ( segment_path_index_by_name == -1 )
                        {
                          report_errorf("Unknown path %s in %s", path_name, segment_file_name_cursor);
                        }
                        else
                        {
                          v49 = row_stride_anchor->row.flags;
                          LOBYTE(v49) = v49 | 8;
                          row_stride_anchor->row.flags = v49;
                        }
                      }
                      parse_cursor = find_case_insensitive_substring(aNofall, option_text);
                      if ( parse_cursor != nullptr )
                      {
                        v50 = row_stride_anchor->row.flags;
                        BYTE1(v50) |= 1u;
                        row_stride_anchor->row.flags = v50;
                      }
                      parse_cursor = find_case_insensitive_substring(aRingNone, option_text);
                      if ( parse_cursor != nullptr )
                      {
                        v51 = row_stride_anchor->row.flags;
                        BYTE1(v51) |= 2u;
                        row_stride_anchor->row.flags = v51;
                      }
                      parse_cursor = find_case_insensitive_substring(aRingNormal, option_text);
                      if ( parse_cursor != nullptr )
                      {
                        v52 = row_stride_anchor->row.flags;
                        BYTE1(v52) |= 4u;
                        row_stride_anchor->row.flags = v52;
                      }
                      parse_cursor = find_case_insensitive_substring(aRingPowerup, option_text);
                      if ( parse_cursor != nullptr )
                      {
                        v53 = row_stride_anchor->row.flags;
                        BYTE1(v53) |= 0x20u;
                        row_stride_anchor->row.flags = v53;
                      }
                      parse_cursor = find_case_insensitive_substring(aRingExplode, option_text);
                      if ( parse_cursor != nullptr )
                      {
                        v54 = row_stride_anchor->row.flags;
                        BYTE1(v54) |= 8u;
                        row_stride_anchor->row.flags = v54;
                      }
                      parse_cursor = find_case_insensitive_substring(aRingSlow, option_text);
                      if ( parse_cursor != nullptr )
                      {
                        v55 = row_stride_anchor->row.flags;
                        BYTE1(v55) |= 0x10u;
                        row_stride_anchor->row.flags = v55;
                      }
                      v56 = find_case_insensitive_substring(aRingspeed, option_text);
                      parse_cursor = v56;
                      if ( v56 != nullptr )
                      {
                        parse_cursor = find_case_insensitive_substring(asc_4A2094, v56) + 1;
                        v57 = parse_next_float32(&parse_cursor);
                        tracks_after_stack_probe->entries[0].rows[flattened_row_index].ring_speed.value = v57;
                      }
                      else
                      {
                        tracks_after_stack_probe->entries[0].rows[flattened_row_index].ring_speed.bits = 0;
                      }
                      parse_cursor = find_case_insensitive_substring(aJetpackOff, option_text);
                      if ( parse_cursor != nullptr )
                      {
                        v58 = row_stride_anchor->row.flags;
                        BYTE1(v58) |= 0x80u;
                        row_stride_anchor->row.flags = v58;
                      }
                      data_line_cursor = advance_to_next_crlf_line(option_cursor);
                      if ( data_line_cursor == nullptr )
                      {
                        v60 = segment_files[segment_index_spill];
                        goto LABEL_71;
                      }
                      segment_index = segment_index_spill;
                      ++row_index;
                    }
                    ++segment_index;
                    segment_row_base += 295;
                    v59 = segment_index < tracks_after_stack_probe->count;
                    segment_index_spill = segment_index;
                    glyph_row_base += 2065;
                    row_count_cursor += 4130;
                    segment_file_name_cursor += 128;
                    if ( v59 )
                    {
                      segment_file_name = segment_file_name_cursor;
                      continue;
                    }
                  }
                  else
                  {
                    report_errorf("Data line must start with '@' in Segment %s\n", segment_files[segment_index]);
                  }
                }
                else
                {
                  v60 = segment_files[segment_index];
LABEL_71:
                  report_errorf("Unexpected end of file in Segment %s\n", v60);
                }
              }
              else
              {
                report_errorf("Unexpected end of file in Segment %s\n", segment_files[segment_index]);
              }
            }
            else
            {
              report_errorf("Cannot find Data: in Segment %s\n", segment_files[segment_index]);
            }
          }
          else
          {
            report_errorf("Cannot find Name: in Segment %s\n", segment_files[segment_index]);
          }
        }
        else
        {
          report_errorf("Cannot find ID: in Segment %s\n", segment_files[segment_index]);
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
