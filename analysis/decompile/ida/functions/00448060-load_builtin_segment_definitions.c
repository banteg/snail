/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_builtin_segment_definitions @ 0x448060 */
/* selector: load_builtin_segment_definitions */

// Initializes the secondary SubTracks owner from the shipped `SubSegmentRaw*` table at `0x4a63d0`, including records such as `Start`, `Finish`, and `Filler` plus their eight authored glyph rows and path metadata. The inconsistent incidental return register proves the Windows member is void; symbol-preserving iOS builds name the corresponding overload `cRSubTracks::Init(cRSubSegmentRaw**)`.
void __thiscall load_builtin_segment_definitions(SubTracks *tracks, SubSegmentRaw **raw_segments)
{
  char *v3; // esi
  int32_t v4; // eax
  int v5; // edi
  int32_t segment_count; // eax
  int v7; // esi
  char v8; // dl
  int v9; // ebp
  int32_t v10; // esi
  int32_t grid_offset; // [esp+8h] [ebp+4h]

  tracks->segment_count = 0;
  tracks->random_length = 1000;
  if ( *(*raw_segments)->glyph_rows[0] )
  {
    do
    {
      v3 = raw_segments[tracks->segment_count]->glyph_rows[0];
      v4 = 0;
      if ( *v3 )
      {
        do
          ++v4;
        while ( v3[v4] );
      }
      grid_offset = 0;
      v5 = 40;
      tracks->segment_slots[tracks->segment_count].row_count = v4;
      raw_segments[tracks->segment_count]->row_count = v4;
      do
      {
        segment_count = tracks->segment_count;
        v7 = 0;
        v8 = **(_BYTE **)((char *)&raw_segments[tracks->segment_count]->row_count + v5);
        do
        {
          v9 = v7 + grid_offset + 16928 * segment_count;
          ++v7;
          tracks->segment_slots[0].glyph_rows[0][v9] = v8;
          segment_count = tracks->segment_count;
          v8 = *(_BYTE *)(*(int32_t *)((char *)&raw_segments[tracks->segment_count]->row_count + v5) + v7);
        }
        while ( v8 );
        v5 += 4;
        grid_offset += 256;
      }
      while ( v5 < 72 );
      tracks->segment_slots[segment_count].source_name = raw_segments[segment_count]->source_name;
      tracks->segment_slots[tracks->segment_count].path_index = raw_segments[tracks->segment_count]->path_index;
      v10 = tracks->segment_count + 1;
      tracks->segment_count = v10;
    }
    while ( *raw_segments[v10]->glyph_rows[0] );
  }
}
