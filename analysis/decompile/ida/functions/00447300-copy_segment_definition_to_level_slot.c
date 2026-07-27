/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_segment_definition_to_level_slot @ 0x447300 */
/* selector: copy_segment_definition_to_level_slot */

// Implements the void `cRSubTracks::ImportSegment(char*, cRSubSegment*)` member: finds a root-owned catalog entry by its enumerated filename, transposes its column-major eight-lane glyph grid into a caller-selected SubSegment, and copies the authored row metadata including position and velocity vectors, path template, and ring-speed fields. The Windows body does not read its receiver, but all three callers establish the SubTracks owner in ECX before passing an ordinary, First, or Last 0x4220-byte inline destination.
void __thiscall copy_segment_definition_to_level_slot(SubTracks *tracks, char *segment_name, SubSegment *segment)
{
  SMTracks *catalog; // edi
  int32_t catalog_index; // esi
  char *catalog_filename_cursor; // ebp
  SubSegment *destination_segment; // ebp
  SegmentCatalogEntryAnchor *selected_entry_anchor; // edx
  char *destination_glyph_row_cursor; // edi
  char *source_glyph_lane_cursor; // ecx
  int32_t glyph_column_index; // eax
  char *source_glyph_column_cursor; // esi
  char glyph; // bl
  int32_t metadata_row_index; // esi
  int32_t *__shifted(AuthoredSegmentRowObjectIdCursorView,0x14) destination_metadata_cursor; // ecx
  int32_t *__shifted(AuthoredSegmentRowObjectIdCursorView,0x14) source_metadata_cursor; // eax
  Vec3 *source_local_position; // edi
  Vec3 *destination_local_position; // ebx
  int32_t glyph_lane_remaining; // [esp+14h] [ebp+4h]

  catalog = &g_game_base->subgame.sm_tracks;
  catalog_index = 0;
  if ( g_game_base->subgame.sm_tracks.count > 0 )
  {
    catalog_filename_cursor = g_game_base->subgame.sm_tracks.entries[0].filename;
    do
    {
      if ( strings_equal_case_insensitive_path(segment_name, catalog_filename_cursor) == 1 )
        break;
      ++catalog_index;
      catalog_filename_cursor += 16520;
    }
    while ( catalog_index < catalog->count );
  }
  if ( catalog_index == catalog->count )
  {
    report_errorf("Cannot find segment %s for %s", segment_name, g_current_level_definition_name);
  }
  else
  {
    destination_segment = segment;
    glyph_lane_remaining = 8;
    selected_entry_anchor = (SegmentCatalogEntryAnchor *)((char *)catalog + 16520 * catalog_index);
    destination_glyph_row_cursor = segment->glyph_rows[0];
    source_glyph_lane_cursor = selected_entry_anchor->entry.glyph_columns[0];
    do
    {
      glyph_column_index = 0;
      if ( selected_entry_anchor->entry.row_count > 0 )
      {
        source_glyph_column_cursor = source_glyph_lane_cursor;
        do
        {
          glyph = *source_glyph_column_cursor;
          source_glyph_column_cursor += 8;
          destination_glyph_row_cursor[glyph_column_index++] = glyph;
        }
        while ( glyph_column_index < selected_entry_anchor->entry.row_count );
      }
      ++source_glyph_lane_cursor;
      destination_glyph_row_cursor += 256;
      --glyph_lane_remaining;
    }
    while ( glyph_lane_remaining != 0 );
    metadata_row_index = 0;
    segment->row_count = selected_entry_anchor->entry.row_count;
    segment->source_name = selected_entry_anchor->entry.filename;
    segment->angle_radians.bits = 0;
    segment->path_index = selected_entry_anchor->entry.id;
    if ( selected_entry_anchor->entry.row_count > 0 )
    {
      destination_metadata_cursor = &segment->rows[0].object_id;
      source_metadata_cursor = &selected_entry_anchor->entry.rows[0].object_id;
      do
      {
        ADJ(destination_metadata_cursor)->flags = ADJ(source_metadata_cursor)->flags;
        ADJ(destination_metadata_cursor)->object_id = ADJ(source_metadata_cursor)->object_id;
        ++metadata_row_index;
        ADJ(destination_metadata_cursor)->object_position.x = ADJ(source_metadata_cursor)->object_position.x;
        ADJ(destination_metadata_cursor)->object_position.y = ADJ(source_metadata_cursor)->object_position.y;
        ADJ(destination_metadata_cursor)->object_position.z = ADJ(source_metadata_cursor)->object_position.z;
        ADJ(destination_metadata_cursor)->object_velocity.x = ADJ(source_metadata_cursor)->object_velocity.x;
        ADJ(destination_metadata_cursor)->object_velocity.y = ADJ(source_metadata_cursor)->object_velocity.y;
        ADJ(destination_metadata_cursor)->object_velocity.z = ADJ(source_metadata_cursor)->object_velocity.z;
        ADJ(destination_metadata_cursor)->parcel_set_id = ADJ(source_metadata_cursor)->parcel_set_id;
        source_local_position = &ADJ(source_metadata_cursor)->local_position;
        destination_local_position = &ADJ(destination_metadata_cursor)->local_position;
        source_metadata_cursor += 14;
        destination_metadata_cursor += 14;
        *destination_local_position = *source_local_position;
        *(destination_metadata_cursor - 7) = *(source_metadata_cursor - 7);
        *(destination_metadata_cursor - 6) = *(source_metadata_cursor - 6);
      }
      while ( metadata_row_index < selected_entry_anchor->entry.row_count );
      destination_segment = segment;
    }
    destination_segment->message_text[0] = 0;
    destination_segment->message_duration.bits = 0;
    destination_segment->message_sample_id = -1;
  }
}
