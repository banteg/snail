/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_edges @ 0x4308b0 */
/* selector: calc_object_edges */

// Builds the unique edge list for one toon-enabled object from its face quads, optionally removes boundary edges for closed meshes, and stores the packed records later filtered by `render_object_toon`. iOS RObject.o names this `cRObject::CalcEdges()`.
void __thiscall calc_object_edges(Object *object)
{
  ObjectFaceQuad *facequads; // esi
  _BYTE *archive_data_base; // edi
  int32_t v4; // ecx
  int v5; // edi
  int32_t v6; // eax
  int v7; // edx
  int v8; // ebx
  int32_t v9; // [esp+4h] [ebp-4h]
  int v10; // [esp+4h] [ebp-4h]

  if ( (object->flags & 1) != 0 )
  {
    facequads = object->facequads;
    archive_data_base = get_archive_data_base();
    v4 = 0;
    g_object_edge_build_edges = archive_data_base;
    g_object_edge_build_count = 0;
    v9 = 0;
    if ( object->facequad_count > 0 )
    {
      v5 = 0;
      do
      {
        add_object_edge(object, facequads->vertex_0, facequads->vertex_1, v5);
        add_object_edge(object, facequads->vertex_2, facequads->vertex_0, v5);
        add_object_edge(object, facequads->vertex_1, facequads->vertex_2, v5);
        if ( (facequads->flags & 0x80u) == 0 )
        {
          add_object_edge(object, facequads->vertex_0, facequads->vertex_2, v5 + 1);
          add_object_edge(object, facequads->vertex_3, facequads->vertex_0, v5 + 1);
          add_object_edge(object, facequads->vertex_2, facequads->vertex_3, v5 + 1);
        }
        ++facequads;
        v5 += 2;
        ++v9;
      }
      while ( v9 < object->facequad_count );
      archive_data_base = (_BYTE *)g_object_edge_build_edges;
      v4 = g_object_edge_build_count;
    }
    if ( (BYTE1(object->flags) & 0x80u) != 0 )
    {
      v6 = 0;
      if ( v4 > 0 )
      {
        v7 = 0;
        v10 = 0;
        do
        {
          if ( (archive_data_base[v7] & 1) != 0 )
          {
            v8 = v6;
            if ( v6 < v4 - 1 )
            {
              do
              {
                ++v8;
                qmemcpy(&archive_data_base[v7], &archive_data_base[v7 + 36], 0x24u);
                v4 = g_object_edge_build_count;
                archive_data_base = (_BYTE *)g_object_edge_build_edges;
                v7 += 36;
              }
              while ( v8 < g_object_edge_build_count - 1 );
              v7 = v10;
            }
            --v4;
            --v6;
            g_object_edge_build_count = v4;
            v7 -= 36;
          }
          ++v6;
          v7 += 36;
          v10 = v7;
        }
        while ( v6 < v4 );
      }
    }
    request_object_edges(object, v4);
    qmemcpy(object->edges, g_object_edge_build_edges, 36 * g_object_edge_build_count);
  }
}
