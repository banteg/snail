/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: clean_duplicate_vertices @ 0x419f80 */
/* selector: clean_duplicate_vertices */

// Exact void Windows `cRDuplicateVertices::Clean(int)`: scans the owner's 10-byte records and clears later live flags for duplicate vertex pairs while retaining the otherwise-unused stack argument proven by `retn 4`. Android preserves the owner and algorithm; its incompatible empty and populated R0 residues prove the result is incidental.
void __thiscall clean_duplicate_vertices(DuplicateVertices *duplicate_vertices, int32_t unused)
{
  int32_t active_count; // eax
  int32_t v3; // ebx
  int v4; // edi
  int32_t v5; // esi
  int v6; // edx
  DuplicateVertexRecord *records; // eax

  active_count = duplicate_vertices->active_count;
  v3 = 0;
  if ( duplicate_vertices->active_count > 0 )
  {
    v4 = 0;
    do
    {
      v5 = v3;
      if ( v3 < active_count )
      {
        v6 = v4 * 10;
        do
        {
          records = duplicate_vertices->records;
          if ( *(uint16_t *)((char *)&records->source_vertex + v6) == records[v4].compare_vertex )
            *(_WORD *)&records->_pad_04[v6 + 4] = 0;
          ++v5;
          v6 += 10;
        }
        while ( v5 < duplicate_vertices->active_count );
      }
      active_count = duplicate_vertices->active_count;
      ++v3;
      ++v4;
    }
    while ( v3 < duplicate_vertices->active_count );
  }
}
