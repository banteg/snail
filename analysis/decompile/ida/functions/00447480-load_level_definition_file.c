/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_level_definition_file @ 0x447480 */
/* selector: load_level_definition_file */

// Parses one Levels/*.txt definition into the owning SubTracks instance, including its SubSegments, display metadata, speed, hazard frequencies, landscape, parcel, and texture fields. Arcade definitions also populate the selected GalaxyRouteSlot's detail and description text in the root-owned Galaxy controller. Symbol-preserving iOS builds name the corresponding void overload `cRSubTracks::Init(char*)`; all Windows callers discard the path-dependent incidental value left in EAX.
void __thiscall load_level_definition_file(SubTracks *tracks, char *filename)
{
  char *case_insensitive_substring; // eax
  char *v4; // eax
  char v5; // cl
  char *level_display_name_cursor; // edx
  char *v7; // eax
  int v8; // edi
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  unsigned int v12; // eax
  char *description_text; // edx
  char *i; // ecx
  char *v15; // eax
  char *v16; // eax
  char v17; // cl
  int v18; // edx
  char *v19; // eax
  char *v20; // eax
  char *script_name_cursor; // ecx
  char j; // dl
  char *v23; // ecx
  GameRoot *v24; // edx
  char *v25; // eax
  char *v26; // eax
  char v27; // al
  char *v28; // eax
  char *v29; // eax
  char *v30; // eax
  char *v31; // edi
  char *crlf_line; // eax
  char v33; // dl
  char *segment_name_cursor; // ecx
  int32_t segment_count; // eax
  char *v36; // ecx
  char *v37; // ecx
  char *line_options_cursor; // edx
  char v39; // al
  char *v40; // eax
  char *v41; // eax
  char *v42; // eax
  char *v43; // eax
  unsigned int v44; // edx
  char v45; // cl
  char *message_text; // ecx
  char *v47; // eax
  char *sample_name_cursor; // edx
  char k; // cl
  char *v50; // eax
  char *v51; // eax
  char v52; // dl
  char *first_segment_name_cursor; // ecx
  char *v54; // ecx
  char *v55; // eax
  char *v56; // eax
  char v57; // dl
  char *last_segment_name_cursor; // ecx
  char *v59; // ecx
  char *v60; // [esp-4h] [ebp-724h]
  char *cursor; // [esp+10h] [ebp-710h] BYREF
  char *line_cursor; // [esp+14h] [ebp-70Ch] BYREF
  int32_t parsed_int; // [esp+18h] [ebp-708h]
  char *segments_end; // [esp+1Ch] [ebp-704h]
  char level_path[512]; // [esp+20h] [ebp-700h] BYREF
  char line_options[128]; // [esp+220h] [ebp-500h] BYREF
  char sample_name[128]; // [esp+2A0h] [ebp-480h] BYREF
  char segment_name[512]; // [esp+320h] [ebp-400h] BYREF
  char script_name[512]; // [esp+520h] [ebp-200h] BYREF

  g_current_level_definition_name = filename;
  sprintf(level_path, "Levels/%s", filename);
  if ( load_file_bytes_from_archive_or_fs(level_path, g_level_file_text_buffer, nullptr) == nullptr )
  {
    report_errorf("Cannot find %s reverting to default.txt", level_path);
    sprintf(level_path, aLevelsDefaultT);
    load_file_bytes_from_archive_or_fs(level_path, g_level_file_text_buffer, nullptr);
  }
  case_insensitive_substring = find_case_insensitive_substring(aName, g_level_file_text_buffer);
  cursor = case_insensitive_substring;
  if ( case_insensitive_substring == nullptr )
  {
    report_errorf("Cannot find Name:' in %s", level_path);
    case_insensitive_substring = nullptr;
  }
  v4 = find_case_insensitive_substring(asc_4AC244, case_insensitive_substring) + 1;
  cursor = v4;
  v5 = *v4;
  for ( level_display_name_cursor = tracks->level_display_name; *v4 != 39; v5 = *v4 )
  {
    if ( v5 < 32 )
      break;
    *level_display_name_cursor++ = v5;
    cursor = ++v4;
  }
  *level_display_name_cursor = 0;
  if ( g_game_base->subgame.galaxy.active == 0 )
  {
    v7 = find_case_insensitive_substring(aArcade, filename);
    cursor = v7;
    if ( v7 != nullptr )
    {
      cursor = find_case_insensitive_substring(aE, v7) + 1;
      v8 = parse_next_signed_int(&cursor);
      sprintf(g_game_base->subgame.galaxy.route_slots[v8].record.detail_text, "%s", tracks->level_display_name);
      v9 = find_case_insensitive_substring(aGalaxytext, g_level_file_text_buffer);
      cursor = v9;
      if ( v9 != nullptr )
      {
        v10 = find_case_insensitive_substring(asc_4A1568, v9);
        cursor = v10;
        if ( v10 != nullptr )
        {
          cursor = advance_to_next_crlf_line(v10);
          v11 = find_case_insensitive_substring(asc_4AC1BC, cursor);
          if ( v11 != nullptr )
          {
            v12 = (unsigned int)(v11 - 2);
            description_text = g_game_base->subgame.galaxy.route_slots[v8].record.description_text;
            for ( i = cursor; (unsigned int)cursor < v12; ++cursor )
            {
              if ( *i < 32 )
              {
                *description_text = 62;
                i = cursor;
                ++description_text;
                if ( *cursor < 32 )
                {
                  do
                    cursor = ++i;
                  while ( *i < 32 );
                }
              }
              *description_text++ = *i;
              i = cursor + 1;
            }
            *description_text = 0;
          }
          else
          {
            report_warningf("Cannot find } for GalaxyText: in %s", filename);
            rstrcpy_checked_ascii(
              g_game_base->subgame.galaxy.route_slots[v8].record.description_text,
              aTextErrorMissi_0);
          }
        }
        else
        {
          report_warningf("Cannot find { for GalaxyText: in %s", filename);
          rstrcpy_checked_ascii(g_game_base->subgame.galaxy.route_slots[v8].record.description_text, aTextErrorMissi);
        }
      }
      else
      {
        report_warningf("Cannot find GalaxyText: in %s", filename);
        rstrcpy_checked_ascii(g_game_base->subgame.galaxy.route_slots[v8].record.description_text, aTextMissing);
      }
    }
  }
  cursor = find_case_insensitive_substring(aRandomYes, g_level_file_text_buffer);
  if ( cursor != nullptr )
  {
    tracks->random_enabled = 1;
    v15 = find_case_insensitive_substring(aLength, g_level_file_text_buffer);
    cursor = v15;
    if ( v15 == nullptr )
    {
      report_errorf("Cannot Length: in %s", level_path);
      return;
    }
    v16 = find_case_insensitive_substring(asc_4A1644, v15) + 1;
    cursor = v16;
    tracks->random_length = 0;
    v17 = *v16;
    if ( *v16 != 97 && v17 != 65 && v17 >= 48 )
    {
      do
      {
        if ( v17 > 57 )
          break;
        ++v16;
        v18 = 5 * tracks->random_length;
        cursor = v16;
        tracks->random_length = v17 + 2 * v18 - 48;
        v17 = *v16;
      }
      while ( *v16 >= 48 );
    }
  }
  else
  {
    tracks->random_enabled = 0;
    tracks->random_length = 0;
  }
  v19 = find_case_insensitive_substring(aBackground, g_level_file_text_buffer);
  cursor = v19;
  if ( v19 == nullptr )
  {
    report_errorf("No Background: in %s", level_path);
    return;
  }
  v20 = find_case_insensitive_substring(asc_4A1644, v19) + 1;
  cursor = v20;
  script_name_cursor = script_name;
  for ( j = *v20; *v20 != 46; j = *v20 )
  {
    *script_name_cursor++ = j;
    cursor = ++v20;
  }
  *script_name_cursor = 46;
  v23 = script_name_cursor + 1;
  v24 = g_game_base;
  *v23++ = 116;
  *v23++ = 120;
  *v23 = 116;
  v23[1] = 0;
  tracks->landscape_script_index = load_landscape_script_by_name(&v24->subgame.landscape_manager, script_name);
  v25 = find_case_insensitive_substring(aFringe, g_level_file_text_buffer);
  cursor = v25;
  if ( v25 != nullptr )
  {
    cursor = find_case_insensitive_substring(asc_4A1644, v25) + 1;
    parsed_int = parse_next_signed_int(&cursor);
    tracks->fringe_color.r = (double)parsed_int * 0.0039215689;
    parsed_int = parse_next_signed_int(&cursor);
    tracks->fringe_color.g = (double)parsed_int * 0.0039215689;
    parsed_int = parse_next_signed_int(&cursor);
    tracks->fringe_color.b = (double)parsed_int * 0.0039215689;
  }
  else
  {
    report_errorf("No Fringe: in %s using white", level_path);
    store_color4f(&tracks->fringe_color, 1.0, 1.0, 1.0, 1.0);
  }
  v26 = find_case_insensitive_substring(aTrack, g_level_file_text_buffer);
  cursor = v26;
  if ( v26 != nullptr )
  {
    cursor = find_case_insensitive_substring(asc_4A1644, v26) + 1;
    v27 = *cursor;
    if ( *cursor == 48 )
    {
      tracks->track_texture_set = 0;
    }
    else
    {
      switch ( v27 )
      {
        case '1':
          tracks->track_texture_set = 1;
          break;
        case '2':
          tracks->track_texture_set = 2;
          break;
        case '3':
          tracks->track_texture_set = 3;
          break;
        case 'r':
          tracks->track_texture_set = 5;
          break;
        default:
          break;
      }
    }
  }
  else
  {
    report_errorf("No Track: in %s using Track0.tga", level_path);
    tracks->track_texture_set = 0;
  }
  v28 = find_case_insensitive_substring(aParcels, g_level_file_text_buffer);
  cursor = v28;
  if ( v28 == nullptr )
  {
    tracks->parcel_count = 0;
    report_errorf("No Parcel: in %s", level_path);
    return;
  }
  cursor = find_case_insensitive_substring(asc_4A1644, v28);
  tracks->parcel_count = parse_next_signed_int(&cursor);
  v29 = find_case_insensitive_substring(aQuota, g_level_file_text_buffer);
  cursor = v29;
  if ( v29 == nullptr )
  {
    tracks->parcel_quota = 0;
    report_errorf("No Quota: in %s", level_path);
    return;
  }
  cursor = find_case_insensitive_substring(asc_4A1644, v29);
  tracks->parcel_quota = parse_next_signed_int(&cursor);
  cursor = find_case_insensitive_substring(aSpeedSelect, g_level_file_text_buffer);
  if ( cursor != nullptr )
  {
    tracks->selected_speed.bits = -1082130432;
  }
  else
  {
    v30 = find_case_insensitive_substring(aSpeed, g_level_file_text_buffer);
    cursor = v30;
    if ( v30 != nullptr )
    {
      cursor = find_case_insensitive_substring(asc_4A1644, v30) + 1;
      tracks->selected_speed.value = parse_next_float32(&cursor);
    }
    else
    {
      report_errorf("Cannot find Speed: in Segment %s\n", level_path);
      tracks->selected_speed.bits = 1120403456;
    }
  }
  cursor = find_case_insensitive_substring(aGarbage, g_level_file_text_buffer);
  if ( cursor != nullptr )
    tracks->garbage_frequency = parse_next_float32(&cursor);
  else
    tracks->garbage_frequency = -1.0;
  cursor = find_case_insensitive_substring(aSalt, g_level_file_text_buffer);
  if ( cursor != nullptr )
    tracks->salt_frequency = parse_next_float32(&cursor);
  else
    tracks->salt_frequency = -1.0;
  tracks->segment_count = 0;
  cursor = find_case_insensitive_substring(aSegmentsBegin, g_level_file_text_buffer);
  if ( cursor == nullptr )
  {
    report_errorf("Cannot find Segments Begin: in %s", level_path);
    return;
  }
  v31 = find_case_insensitive_substring(aSegmentsEnd, g_level_file_text_buffer);
  segments_end = v31;
  if ( v31 == nullptr )
  {
    report_errorf("Cannot find Segments End: in %s", level_path);
    return;
  }
  crlf_line = advance_to_next_crlf_line(cursor);
  cursor = crlf_line;
  if ( crlf_line == nullptr )
    goto LABEL_105;
  if ( crlf_line >= v31 )
  {
LABEL_94:
    v50 = find_case_insensitive_substring(aFirst, g_level_file_text_buffer);
    cursor = v50;
    if ( v50 == nullptr )
    {
      report_errorf("Cannot find 'First:' in %s", level_path);
      return;
    }
    v51 = advance_to_next_crlf_line(v50);
    cursor = v51;
    if ( v51 != nullptr )
    {
      v52 = *v51;
      for ( first_segment_name_cursor = segment_name; *v51 != 46; v52 = *v51 )
      {
        *first_segment_name_cursor++ = v52;
        cursor = ++v51;
      }
      *first_segment_name_cursor = 46;
      v54 = first_segment_name_cursor + 1;
      *v54++ = 116;
      *v54++ = 120;
      *v54 = 116;
      v54[1] = 0;
      copy_segment_definition_to_level_slot(tracks, segment_name, &tracks->first_segment);
      v55 = find_case_insensitive_substring(aLast, g_level_file_text_buffer);
      cursor = v55;
      if ( v55 == nullptr )
      {
        report_errorf("Cannot find 'Last:' in %s", level_path);
        return;
      }
      v56 = advance_to_next_crlf_line(v55);
      cursor = v56;
      if ( v56 != nullptr )
      {
        v57 = *v56;
        for ( last_segment_name_cursor = segment_name; *v56 != 46; v57 = *v56 )
        {
          *last_segment_name_cursor++ = v57;
          cursor = ++v56;
        }
        *last_segment_name_cursor = 46;
        v59 = last_segment_name_cursor + 1;
        *v59++ = 116;
        *v59++ = 120;
        *v59 = 116;
        v59[1] = 0;
        copy_segment_definition_to_level_slot(tracks, segment_name, &tracks->last_segment);
        return;
      }
    }
LABEL_105:
    report_errorf("Unexpected end of file in %s", level_path);
    return;
  }
  while ( 1 )
  {
    v33 = *crlf_line;
    for ( segment_name_cursor = segment_name; *crlf_line != 46; v33 = *crlf_line )
    {
      *segment_name_cursor++ = v33;
      cursor = ++crlf_line;
    }
    segment_count = tracks->segment_count;
    *segment_name_cursor = 46;
    v36 = segment_name_cursor + 1;
    *v36++ = 116;
    *v36++ = 120;
    *v36 = 116;
    v36[1] = 0;
    copy_segment_definition_to_level_slot(tracks, segment_name, &tracks->segment_slots[segment_count]);
    v37 = cursor + 3;
    line_options_cursor = line_options;
    line_cursor = cursor + 3;
    v39 = cursor[3];
    if ( v39 >= 32 )
    {
      do
      {
        *line_options_cursor++ = v39;
        line_cursor = ++v37;
        v39 = *v37;
      }
      while ( *v37 >= 32 );
    }
    *line_options_cursor = 0;
    v40 = find_case_insensitive_substring(aAngle, line_options);
    line_cursor = v40;
    if ( v40 != nullptr )
    {
      line_cursor = find_case_insensitive_substring(asc_4A2094, v40);
      parsed_int = parse_next_signed_int(&line_cursor);
      tracks->segment_slots[tracks->segment_count].angle_radians.value = (double)parsed_int * 0.017453292;
    }
    else
    {
      tracks->segment_slots[tracks->segment_count].angle_radians.bits = 0;
    }
    tracks->segment_slots[tracks->segment_count].message_text[0] = 0;
    v41 = find_case_insensitive_substring(aMessage, line_options);
    line_cursor = v41;
    if ( v41 != nullptr )
    {
      v42 = find_case_insensitive_substring(asc_4A2094, v41) + 1;
      line_cursor = v42;
      if ( *v42 != 34 )
      {
        report_errorf(aNeedAfterMessa);
        return;
      }
      v43 = v42 + 1;
      line_cursor = v43;
      v44 = (unsigned int)v43;
      if ( *v43 != 34 )
      {
        do
          v45 = *(_BYTE *)++v44;
        while ( v45 != 34 );
      }
      message_text = tracks->segment_slots[tracks->segment_count].message_text;
      if ( (unsigned int)v43 < v44 )
      {
        do
        {
          *message_text++ = *v43;
          v43 = ++line_cursor;
        }
        while ( (unsigned int)line_cursor < v44 );
      }
      *message_text = 0;
      line_cursor = find_case_insensitive_substring(aDuration_0, line_options);
      tracks->segment_slots[tracks->segment_count].message_duration.bits = 1082130432;
      if ( line_cursor != nullptr )
      {
        line_cursor = find_case_insensitive_substring(asc_4A2094, line_cursor) + 1;
        tracks->segment_slots[tracks->segment_count].message_duration.value = parse_next_float32(&line_cursor);
      }
      line_cursor = find_case_insensitive_substring(aSample, line_options);
      tracks->segment_slots[tracks->segment_count].message_sample_id = -1;
      if ( line_cursor != nullptr )
      {
        v47 = find_case_insensitive_substring(asc_4A2094, line_cursor) + 2;
        line_cursor = v47;
        sample_name_cursor = sample_name;
        for ( k = *v47; *v47 != 34; k = *v47 )
        {
          *sample_name_cursor++ = k;
          line_cursor = ++v47;
        }
        *sample_name_cursor = 0;
        tracks->segment_slots[tracks->segment_count].message_sample_id = find_registered_sound_sample_id_by_name(sample_name);
        if ( tracks->segment_slots[tracks->segment_count].message_sample_id == -1 )
          report_errorf("Cannot find sample %s in %s", sample_name, level_path);
      }
    }
    v60 = cursor;
    ++tracks->segment_count;
    crlf_line = advance_to_next_crlf_line(v60);
    cursor = crlf_line;
    if ( crlf_line == nullptr )
      break;
    if ( crlf_line >= segments_end )
      goto LABEL_94;
  }
  report_errorf("Unexpected end of file in %s", filename);
}
