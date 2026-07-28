/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: copy_segment_definition_to_level_slot @ 0x447300 */

0044730d        struct cRSMTracks* catalog = &g_game_base->subgame.sm_tracks
00447313        int32_t catalog_index = 0
00447318        if (catalog->count s> 0)
0044731a        char* catalog_filename_cursor = &catalog->entries[0].filename
0044732a        if (strings_equal_case_insensitive_path(segment_name, catalog_filename_cursor) == 1)
0044732a        break
0044732e        catalog_index += 1
0044732f        catalog_filename_cursor = &catalog_filename_cursor[0x4088]
00447337        do while (catalog_index s< catalog->count)
0044733b        if (catalog_index == catalog->count)
0044734a        report_errorf("Cannot find segment %s for %s", segment_name, g_current_level_definition_name)
00447356        return
0044735b        struct SubSegment* destination_segment = segment
00447364        int32_t glyph_lane_remaining = 8
00447371        struct SegmentCatalogEntryAnchor* selected_entry_anchor = catalog + catalog_index * 0x4088
00447374        char* destination_glyph_row_cursor = &destination_segment->glyph_rows
00447377        char* source_glyph_lane_cursor = &selected_entry_anchor->entry.glyph_columns
004473ae        bool cond:0_1
00447383        int32_t glyph_column_index = 0
00447387        if (selected_entry_anchor->entry.row_count s> 0)
00447389        char* source_glyph_column_cursor = source_glyph_lane_cursor
0044738b        char glyph = *source_glyph_column_cursor
0044738d        source_glyph_column_cursor = &source_glyph_column_cursor[8]
00447390        destination_glyph_row_cursor[glyph_column_index] = glyph
00447399        glyph_column_index += 1
0044739c        do while (glyph_column_index s< selected_entry_anchor->entry.row_count)
004473a2        source_glyph_lane_cursor = &source_glyph_lane_cursor[1]
004473a3        destination_glyph_row_cursor = &destination_glyph_row_cursor[0x100]
004473a9        cond:0_1 = glyph_lane_remaining != 1
004473aa        glyph_lane_remaining -= 1
004473ae        do while (cond:0_1)
004473b9        int32_t metadata_row_index = 0
004473bb        destination_segment->row_count = selected_entry_anchor->entry.row_count
004473be        destination_segment->source_name = &selected_entry_anchor->entry.filename
004473c1        __builtin_memset(&destination_segment->angle_radians, 0, 4)
004473cd        destination_segment->path_index = selected_entry_anchor->entry.id
004473d8        if (selected_entry_anchor->entry.row_count s> 0)
004473da        struct AuthoredSegmentRowObjectIdCursorView* destination_metadata_cursor = &destination_segment->rows[0].object_id
004473e0        struct AuthoredSegmentRowObjectIdCursorView* source_metadata_cursor = &selected_entry_anchor->entry.rows[0].object_id
004473ec        destination_metadata_cursor->flags = source_metadata_cursor->flags
004473f1        destination_metadata_cursor->object_id = source_metadata_cursor->object_id
004473f6        metadata_row_index += 1
004473f9        destination_metadata_cursor->object_position.x = source_metadata_cursor->object_position.x
004473fe        destination_metadata_cursor->object_position.y = source_metadata_cursor->object_position.y
00447404        destination_metadata_cursor->object_position.z = source_metadata_cursor->object_position.z
0044740f        destination_metadata_cursor->object_velocity.x = source_metadata_cursor->object_velocity.x
00447414        destination_metadata_cursor->object_velocity.y = source_metadata_cursor->object_velocity.y
0044741a        destination_metadata_cursor->object_velocity.z = source_metadata_cursor->object_velocity.z
00447420        destination_metadata_cursor->parcel_set_id = source_metadata_cursor->parcel_set_id
00447423        struct Vec3* source_local_position = source_metadata_cursor - 0xc
00447426        struct Vec3* destination_local_position = destination_metadata_cursor - 0xc
00447429        source_metadata_cursor = &source_metadata_cursor[1]
0044742e        destination_metadata_cursor = &destination_metadata_cursor[1]
00447431        destination_local_position->x = source_local_position->x
00447436        destination_local_position->y = source_local_position->y
0044743c        destination_local_position->z = source_local_position->z
00447442        destination_metadata_cursor->__offset(0xfffffffffffffff8).d = source_metadata_cursor->__offset(0xfffffffffffffff8).d
00447448        destination_metadata_cursor->flags:-4.d = source_metadata_cursor->flags:-4.d
00447453        do while (metadata_row_index s< selected_entry_anchor->entry.row_count)
00447455        destination_segment = segment
0044745a        destination_segment->message_text[0] = 0
00447461        __builtin_memset(&destination_segment->message_duration, 0, 4)
0044746b        destination_segment->message_sample_id = 0xffffffff
00447478        return
