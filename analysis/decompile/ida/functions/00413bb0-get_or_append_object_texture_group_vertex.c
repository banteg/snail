/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_or_append_object_texture_group_vertex @ 0x413bb0 */
/* selector: get_or_append_object_texture_group_vertex */

// Returns the existing grouped-render vertex matching one object vertex index plus UVs, or appends a new record field-by-field through the shared global texture-group build scratch when no match exists.
int32_t __cdecl get_or_append_object_texture_group_vertex(Object *object, int vertex_index, float u, float v)
{
  Vec3 *v4; // edx
  int32_t v5; // edx
  float *p_y; // ecx
  int32_t v7; // esi
  float x; // [esp+10h] [ebp-Ch]
  float y; // [esp+14h] [ebp-8h]
  float z; // [esp+18h] [ebp-4h]

  if ( vertex_index >= object->vertex_count )
    report_errorf(aVertexrefOutOf);
  v4 = &object->vertices[vertex_index];
  x = v4->x;
  y = v4->y;
  z = v4->z;
  v5 = 0;
  if ( g_object_grouped_vertex_cursor > 0 )
  {
    p_y = &g_object_grouped_vertex_scratch->y;
    do
    {
      if ( (object->flags & 4) != 0 )
      {
        if ( *((_DWORD *)p_y + 5) == vertex_index && p_y[3] == u && 1.0 - v == p_y[4] )
          return v5;
      }
      else if ( *(p_y - 1) == x && *p_y == y && p_y[1] == z && p_y[3] == u && 1.0 - v == p_y[4] )
      {
        return v5;
      }
      ++v5;
      p_y += 7;
    }
    while ( v5 < g_object_grouped_vertex_cursor );
  }
  v7 = v5;
  g_object_grouped_vertex_scratch[v7].x = x;
  g_object_grouped_vertex_scratch[v7].y = y;
  g_object_grouped_vertex_scratch[v7].z = z;
  g_object_grouped_vertex_scratch[v7].u = u;
  g_object_grouped_vertex_scratch[v7].v = 1.0 - v;
  if ( (object->flags & 0x10000) != 0 )
    pack_color_rgba_u8(
      (tColourSmall *)&g_object_grouped_vertex_scratch[v7].diffuse,
      &object->vertex_colours[vertex_index]);
  else
    g_object_grouped_vertex_scratch[v7].diffuse = -1;
  g_object_grouped_vertex_scratch[v7].source_vertex = vertex_index;
  return g_object_grouped_vertex_cursor++;
}
