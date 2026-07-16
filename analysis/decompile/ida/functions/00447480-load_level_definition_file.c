/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_level_definition_file @ 0x447480 */
/* selector: load_level_definition_file */

// Parses one Levels/*.txt definition into the owning SubTracks instance, including its SubSegments, display metadata, speed, hazard frequencies, landscape, parcel, and texture fields. Arcade definitions also populate the selected GalaxyRouteSlot's detail and description text in the root-owned Galaxy controller. Symbol-preserving iOS builds name the corresponding void overload `cRSubTracks::Init(char*)`; all Windows callers discard the path-dependent incidental value left in EAX.
void __thiscall load_level_definition_file(SubTracks *tracks, char *filename)
{
  char *case_insensitive_substring; // eax
  char *v4; // eax
  char v5; // cl
  char *i; // edx
  char *v7; // eax
  int v8; // edi
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  unsigned int v12; // eax
  char *description_text; // edx
  char *j; // ecx
  char *v15; // eax
  char *v16; // eax
  char v17; // cl
  int v18; // edx
  char *v19; // eax
  char *v20; // eax
  char *v21; // ecx
  char k; // dl
  _BYTE *v23; // ecx
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
  char *ii; // ecx
  int32_t segment_count; // eax
  _BYTE *v36; // ecx
  char *v37; // ecx
  char *v38; // edx
  char v39; // al
  char *v40; // eax
  char *v41; // eax
  char *v42; // eax
  char *v43; // eax
  unsigned int v44; // edx
  char v45; // cl
  char *message_text; // ecx
  char *v47; // eax
  char *v48; // edx
  char jj; // cl
  char *v50; // eax
  char *v51; // eax
  char v52; // dl
  char *m; // ecx
  _BYTE *v54; // ecx
  char *v55; // eax
  char *v56; // eax
  char v57; // dl
  char *n; // ecx
  _BYTE *v59; // ecx
  char *v60; // [esp-4h] [ebp-724h]
  char *cursor; // [esp+10h] [ebp-710h] BYREF
  char *v62; // [esp+14h] [ebp-70Ch] BYREF
  int v63; // [esp+18h] [ebp-708h]
  char *v64; // [esp+1Ch] [ebp-704h]
  char Buffer[512]; // [esp+20h] [ebp-700h] BYREF
  char v66[128]; // [esp+220h] [ebp-500h] BYREF
  char ArgList[128]; // [esp+2A0h] [ebp-480h] BYREF
  char segment_name[512]; // [esp+320h] [ebp-400h] BYREF
  char v69[512]; // [esp+520h] [ebp-200h] BYREF

  g_current_level_definition_name = filename;
  sprintf(Buffer, "Levels/%s", filename);
  if ( !load_file_bytes_from_archive_or_fs(Buffer, g_level_file_text_buffer, nullptr) )
  {
    report_errorf("Cannot find %s reverting to default.txt", Buffer);
    sprintf(Buffer, aLevelsDefaultT);
    load_file_bytes_from_archive_or_fs(Buffer, g_level_file_text_buffer, nullptr);
  }
  case_insensitive_substring = find_case_insensitive_substring(aName, g_level_file_text_buffer);
  cursor = case_insensitive_substring;
  if ( !case_insensitive_substring )
  {
    report_errorf("Cannot find Name:' in %s", Buffer);
    case_insensitive_substring = nullptr;
  }
  v4 = find_case_insensitive_substring(asc_4AC244, case_insensitive_substring) + 1;
  cursor = v4;
  v5 = *v4;
  for ( i = tracks->level_display_name; *v4 != 39; v5 = *v4 )
  {
    if ( v5 < 32 )
      break;
    *i++ = v5;
    cursor = ++v4;
  }
  *i = 0;
  if ( !g_game_base->subgame.galaxy.active )
  {
    v7 = find_case_insensitive_substring(aArcade, filename);
    cursor = v7;
    if ( v7 )
    {
      cursor = find_case_insensitive_substring(aE, v7) + 1;
      v8 = parse_next_signed_int(&cursor);
      sprintf(g_game_base->subgame.galaxy.route_slots[v8].record.detail_text, "%s", tracks->level_display_name);
      v9 = find_case_insensitive_substring(aGalaxytext, g_level_file_text_buffer);
      cursor = v9;
      if ( v9 )
      {
        v10 = find_case_insensitive_substring(asc_4A1568, v9);
        cursor = v10;
        if ( v10 )
        {
          cursor = (char *)advance_to_next_crlf_line(v10);
          v11 = find_case_insensitive_substring(asc_4AC1BC, cursor);
          if ( v11 )
          {
            v12 = (unsigned int)(v11 - 2);
            description_text = g_game_base->subgame.galaxy.route_slots[v8].record.description_text;
            for ( j = cursor; (unsigned int)cursor < v12; ++cursor )
            {
              if ( *j < 32 )
              {
                *description_text = 62;
                j = cursor;
                ++description_text;
                if ( *cursor < 32 )
                {
                  do
                    cursor = ++j;
                  while ( *j < 32 );
                }
              }
              *description_text++ = *j;
              j = cursor + 1;
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
  if ( cursor )
  {
    tracks->random_enabled = 1;
    v15 = find_case_insensitive_substring(aLength, g_level_file_text_buffer);
    cursor = v15;
    if ( !v15 )
    {
      report_errorf("Cannot Length: in %s", Buffer);
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
  if ( !v19 )
  {
    report_errorf("No Background: in %s", Buffer);
    return;
  }
  v20 = find_case_insensitive_substring(asc_4A1644, v19) + 1;
  cursor = v20;
  v21 = v69;
  for ( k = *v20; *v20 != 46; k = *v20 )
  {
    *v21++ = k;
    cursor = ++v20;
  }
  *v21 = 46;
  v23 = v21 + 1;
  v24 = g_game_base;
  *v23++ = 116;
  *v23++ = 120;
  *v23 = 116;
  v23[1] = 0;
  tracks->landscape_script_index = load_landscape_script_by_name((char *)&v24->subgame.landscape_manager, v69);
  v25 = find_case_insensitive_substring(aFringe, g_level_file_text_buffer);
  cursor = v25;
  if ( v25 )
  {
    cursor = find_case_insensitive_substring(asc_4A1644, v25) + 1;
    v63 = parse_next_signed_int(&cursor);
    tracks->fringe_color.r = (double)v63 * 0.0039215689;
    v63 = parse_next_signed_int(&cursor);
    tracks->fringe_color.g = (double)v63 * 0.0039215689;
    v63 = parse_next_signed_int(&cursor);
    tracks->fringe_color.b = (double)v63 * 0.0039215689;
  }
  else
  {
    report_errorf("No Fringe: in %s using white", Buffer);
    store_color4f(&tracks->fringe_color, 1.0, 1.0, 1.0, 1.0);
  }
  v26 = find_case_insensitive_substring(aTrack, g_level_file_text_buffer);
  cursor = v26;
  if ( v26 )
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
      }
    }
  }
  else
  {
    report_errorf("No Track: in %s using Track0.tga", Buffer);
    tracks->track_texture_set = 0;
  }
  v28 = find_case_insensitive_substring(aParcels, g_level_file_text_buffer);
  cursor = v28;
  if ( !v28 )
  {
    tracks->parcel_count = 0;
    report_errorf("No Parcel: in %s", Buffer);
    return;
  }
  cursor = find_case_insensitive_substring(asc_4A1644, v28);
  tracks->parcel_count = parse_next_signed_int(&cursor);
  v29 = find_case_insensitive_substring(aQuota, g_level_file_text_buffer);
  cursor = v29;
  if ( !v29 )
  {
    tracks->parcel_quota = 0;
    report_errorf("No Quota: in %s", Buffer);
    return;
  }
  cursor = find_case_insensitive_substring(asc_4A1644, v29);
  tracks->parcel_quota = parse_next_signed_int(&cursor);
  cursor = find_case_insensitive_substring(aSpeedSelect, g_level_file_text_buffer);
  if ( cursor )
  {
    tracks->selected_speed.bits = -1082130432;
  }
  else
  {
    v30 = find_case_insensitive_substring(aSpeed, g_level_file_text_buffer);
    cursor = v30;
    if ( v30 )
    {
      cursor = find_case_insensitive_substring(asc_4A1644, v30) + 1;
      tracks->selected_speed.value = parse_next_float32(&cursor);
    }
    else
    {
      report_errorf("Cannot find Speed: in Segment %s\n", Buffer);
      tracks->selected_speed.bits = 1120403456;
    }
  }
  cursor = find_case_insensitive_substring(aGarbage, g_level_file_text_buffer);
  if ( cursor )
    tracks->garbage_frequency = parse_next_float32(&cursor);
  else
    tracks->garbage_frequency = -1.0;
  cursor = find_case_insensitive_substring(aSalt, g_level_file_text_buffer);
  if ( cursor )
    tracks->salt_frequency = parse_next_float32(&cursor);
  else
    tracks->salt_frequency = -1.0;
  tracks->segment_count = 0;
  cursor = find_case_insensitive_substring(aSegmentsBegin, g_level_file_text_buffer);
  if ( !cursor )
  {
    report_errorf("Cannot find Segments Begin: in %s", Buffer);
    return;
  }
  v31 = find_case_insensitive_substring(aSegmentsEnd, g_level_file_text_buffer);
  v64 = v31;
  if ( !v31 )
  {
    report_errorf("Cannot find Segments End: in %s", Buffer);
    return;
  }
  crlf_line = (char *)advance_to_next_crlf_line(cursor);
  cursor = crlf_line;
  if ( !crlf_line )
    goto LABEL_105;
  if ( crlf_line >= v31 )
  {
LABEL_94:
    v50 = find_case_insensitive_substring(aFirst, g_level_file_text_buffer);
    cursor = v50;
    if ( !v50 )
    {
      report_errorf("Cannot find 'First:' in %s", Buffer);
      return;
    }
    v51 = (char *)advance_to_next_crlf_line(v50);
    cursor = v51;
    if ( v51 )
    {
      v52 = *v51;
      for ( m = segment_name; *v51 != 46; v52 = *v51 )
      {
        *m++ = v52;
        cursor = ++v51;
      }
      *m = 46;
      v54 = m + 1;
      *v54++ = 116;
      *v54++ = 120;
      *v54 = 116;
      v54[1] = 0;
      copy_segment_definition_to_level_slot(tracks, segment_name, &tracks->first_segment);
      v55 = find_case_insensitive_substring(aLast, g_level_file_text_buffer);
      cursor = v55;
      if ( !v55 )
      {
        report_errorf("Cannot find 'Last:' in %s", Buffer);
        return;
      }
      v56 = (char *)advance_to_next_crlf_line(v55);
      cursor = v56;
      if ( v56 )
      {
        v57 = *v56;
        for ( n = segment_name; *v56 != 46; v57 = *v56 )
        {
          *n++ = v57;
          cursor = ++v56;
        }
        *n = 46;
        v59 = n + 1;
        *v59++ = 116;
        *v59++ = 120;
        *v59 = 116;
        v59[1] = 0;
        copy_segment_definition_to_level_slot(tracks, segment_name, &tracks->last_segment);
        return;
      }
    }
LABEL_105:
    report_errorf("Unexpected end of file in %s", Buffer);
    return;
  }
  while ( 1 )
  {
    v33 = *crlf_line;
    for ( ii = segment_name; *crlf_line != 46; v33 = *crlf_line )
    {
      *ii++ = v33;
      cursor = ++crlf_line;
    }
    segment_count = tracks->segment_count;
    *ii = 46;
    v36 = ii + 1;
    *v36++ = 116;
    *v36++ = 120;
    *v36 = 116;
    v36[1] = 0;
    copy_segment_definition_to_level_slot(tracks, segment_name, &tracks->segment_slots[segment_count]);
    v37 = cursor + 3;
    v38 = v66;
    v62 = cursor + 3;
    v39 = cursor[3];
    if ( v39 >= 32 )
    {
      do
      {
        *v38++ = v39;
        v62 = ++v37;
        v39 = *v37;
      }
      while ( *v37 >= 32 );
    }
    *v38 = 0;
    v40 = find_case_insensitive_substring(aAngle, v66);
    v62 = v40;
    if ( v40 )
    {
      v62 = find_case_insensitive_substring(asc_4A2094, v40);
      v63 = parse_next_signed_int(&v62);
      tracks->segment_slots[tracks->segment_count].angle_radians.value = (double)v63 * 0.017453292;
    }
    else
    {
      tracks->segment_slots[tracks->segment_count].angle_radians.bits = 0;
    }
    tracks->segment_slots[tracks->segment_count].message_text[0] = 0;
    v41 = find_case_insensitive_substring(aMessage, v66);
    v62 = v41;
    if ( v41 )
    {
      v42 = find_case_insensitive_substring(asc_4A2094, v41) + 1;
      v62 = v42;
      if ( *v42 != 34 )
      {
        report_errorf(aNeedAfterMessa);
        return;
      }
      v43 = v42 + 1;
      v62 = v43;
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
          v43 = ++v62;
        }
        while ( (unsigned int)v62 < v44 );
      }
      *message_text = 0;
      v62 = find_case_insensitive_substring(aDuration_0, v66);
      tracks->segment_slots[tracks->segment_count].message_duration.bits = 1082130432;
      if ( v62 )
      {
        v62 = find_case_insensitive_substring(asc_4A2094, v62) + 1;
        tracks->segment_slots[tracks->segment_count].message_duration.value = parse_next_float32(&v62);
      }
      v62 = find_case_insensitive_substring(aSample, v66);
      tracks->segment_slots[tracks->segment_count].message_sample_id = -1;
      if ( v62 )
      {
        v47 = find_case_insensitive_substring(asc_4A2094, v62) + 2;
        v62 = v47;
        v48 = ArgList;
        for ( jj = *v47; *v47 != 34; jj = *v47 )
        {
          *v48++ = jj;
          v62 = ++v47;
        }
        *v48 = 0;
        tracks->segment_slots[tracks->segment_count].message_sample_id = find_registered_sound_sample_id_by_name(ArgList);
        if ( tracks->segment_slots[tracks->segment_count].message_sample_id == -1 )
          report_errorf("Cannot find sample %s in %s", ArgList, Buffer);
      }
    }
    v60 = cursor;
    ++tracks->segment_count;
    crlf_line = (char *)advance_to_next_crlf_line(v60);
    cursor = crlf_line;
    if ( !crlf_line )
      break;
    if ( crlf_line >= v64 )
      goto LABEL_94;
  }
  report_errorf("Unexpected end of file in %s", filename);
}
