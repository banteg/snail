/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_segment_definition_to_level_slot @ 0x447300 */
/* selector: copy_segment_definition_to_level_slot */

// Implements the void `cRSubTracks::ImportSegment(char*, cRSubSegment*)` member: finds a root-owned catalog entry by its enumerated filename, transposes its column-major eight-lane glyph grid into a caller-selected SubSegment, and copies the authored row metadata including position and velocity vectors, path template, and ring-speed fields. The Windows body does not read its receiver, but all three callers establish the SubTracks owner in ECX before passing an ordinary, First, or Last 0x4220-byte inline destination.
void __thiscall copy_segment_definition_to_level_slot(SubTracks *tracks, char *segment_name, SubSegment *segment)
{
  SMTracks *p_sm_tracks; // edi
  int32_t v4; // esi
  char *filename; // ebp
  SubSegment *v6; // ebp
  SegmentCatalogEntryAnchor *selected_entry_anchor; // edx
  char *v8; // edi
  char *v9; // ecx
  int32_t v10; // eax
  char *v11; // esi
  char v12; // bl
  int32_t v13; // esi
  int32_t *p_object_id; // ecx
  int32_t *v15; // eax
  int32_t *v16; // edi
  int32_t *v17; // ebx
  int ArgList; // [esp+14h] [ebp+4h]

  p_sm_tracks = &g_game_base->subgame.sm_tracks;
  v4 = 0;
  if ( g_game_base->subgame.sm_tracks.count > 0 )
  {
    filename = g_game_base->subgame.sm_tracks.entries[0].filename;
    do
    {
      if ( strings_equal_case_insensitive_path(segment_name, filename) )
        break;
      ++v4;
      filename += 16520;
    }
    while ( v4 < p_sm_tracks->count );
  }
  if ( v4 == p_sm_tracks->count )
  {
    report_errorf("Cannot find segment %s for %s", segment_name, g_current_level_definition_name);
  }
  else
  {
    v6 = segment;
    ArgList = 8;
    selected_entry_anchor = (SegmentCatalogEntryAnchor *)((char *)p_sm_tracks + 16520 * v4);
    v8 = segment->glyph_rows[0];
    v9 = selected_entry_anchor->entry.glyph_columns[0];
    do
    {
      v10 = 0;
      if ( selected_entry_anchor->entry.row_count > 0 )
      {
        v11 = v9;
        do
        {
          v12 = *v11;
          v11 += 8;
          v8[v10++] = v12;
        }
        while ( v10 < selected_entry_anchor->entry.row_count );
      }
      ++v9;
      v8 += 256;
      --ArgList;
    }
    while ( ArgList );
    v13 = 0;
    segment->row_count = selected_entry_anchor->entry.row_count;
    segment->source_name = selected_entry_anchor->entry.filename;
    segment->angle_radians.bits = 0;
    segment->path_index = selected_entry_anchor->entry.id;
    if ( selected_entry_anchor->entry.row_count > 0 )
    {
      p_object_id = &segment->rows[0].object_id;
      v15 = &selected_entry_anchor->entry.rows[0].object_id;
      do
      {
        *(p_object_id - 5) = *(v15 - 5);
        *p_object_id = *v15;
        ++v13;
        p_object_id[1] = v15[1];
        p_object_id[2] = v15[2];
        p_object_id[3] = v15[3];
        p_object_id[4] = v15[4];
        p_object_id[5] = v15[5];
        p_object_id[6] = v15[6];
        *(p_object_id - 4) = *(v15 - 4);
        v16 = v15 - 3;
        v17 = p_object_id - 3;
        v15 += 14;
        p_object_id += 14;
        *v17 = *v16;
        v17[1] = v16[1];
        v17[2] = v16[2];
        *(p_object_id - 7) = *(v15 - 7);
        *(p_object_id - 6) = *(v15 - 6);
      }
      while ( v13 < selected_entry_anchor->entry.row_count );
      v6 = segment;
    }
    v6->message_text[0] = 0;
    v6->message_duration.bits = 0;
    v6->message_sample_id = -1;
  }
}
