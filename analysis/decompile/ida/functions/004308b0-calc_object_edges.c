/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_edges @ 0x4308b0 */
/* selector: calc_object_edges */

// Builds the unique edge list for one toon-enabled object from its face quads, optionally removes boundary edges for closed meshes, and stores the packed records later filtered by `render_object_toon`. iOS RObject.o names this `cRObject::CalcEdges()`.
void __thiscall calc_object_edges(Object *object)
{
  ObjectFaceQuad *facequads; // esi
  ObjectToonEdge *build_edges; // edi
  int32_t edge_count; // ecx
  int32_t normal_index; // edi
  int32_t edge_index; // eax
  int32_t edge_offset; // edx
  int32_t shift_index; // ebx
  int32_t face_index; // [esp+4h] [ebp-4h]
  int32_t saved_edge_offset; // [esp+4h] [ebp-4h]

  if ( (object->flags & 1) != 0 )
  {
    facequads = object->facequads;
    build_edges = (ObjectToonEdge *)get_archive_data_base();
    edge_count = 0;
    g_object_edge_build_edges = build_edges;
    g_object_edge_build_count = 0;
    face_index = 0;
    if ( object->facequad_count > 0 )
    {
      normal_index = 0;
      do
      {
        add_object_edge(object, facequads->vertex_0, facequads->vertex_1, normal_index);
        add_object_edge(object, facequads->vertex_2, facequads->vertex_0, normal_index);
        add_object_edge(object, facequads->vertex_1, facequads->vertex_2, normal_index);
        if ( (facequads->flags & 0x80u) == 0 )
        {
          add_object_edge(object, facequads->vertex_0, facequads->vertex_2, normal_index + 1);
          add_object_edge(object, facequads->vertex_3, facequads->vertex_0, normal_index + 1);
          add_object_edge(object, facequads->vertex_2, facequads->vertex_3, normal_index + 1);
        }
        ++facequads;
        normal_index += 2;
        ++face_index;
      }
      while ( face_index < object->facequad_count );
      build_edges = g_object_edge_build_edges;
      edge_count = g_object_edge_build_count;
    }
    if ( (BYTE1(object->flags) & 0x80u) != 0 )
    {
      edge_index = 0;
      if ( edge_count > 0 )
      {
        edge_offset = 0;
        saved_edge_offset = 0;
        do
        {
          if ( (*((_BYTE *)&build_edges->flags + edge_offset) & 1) != 0 )
          {
            shift_index = edge_index;
            if ( edge_index < edge_count - 1 )
            {
              do
              {
                ++shift_index;
                qmemcpy(
                  (char *)build_edges + edge_offset,
                  (char *)&build_edges[1] + edge_offset,
                  sizeof(ObjectToonEdge));
                edge_count = g_object_edge_build_count;
                build_edges = g_object_edge_build_edges;
                edge_offset += 36;
              }
              while ( shift_index < g_object_edge_build_count - 1 );
              edge_offset = saved_edge_offset;
            }
            --edge_count;
            --edge_index;
            g_object_edge_build_count = edge_count;
            edge_offset -= 36;
          }
          ++edge_index;
          edge_offset += 36;
          saved_edge_offset = edge_offset;
        }
        while ( edge_index < edge_count );
      }
    }
    request_object_edges(object, edge_count);
    qmemcpy(object->edges, g_object_edge_build_edges, 36 * g_object_edge_build_count);
  }
}
