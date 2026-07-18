/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_track_cache_vertex @ 0x433830 */
/* selector: add_track_cache_vertex */

// Transforms and deduplicates one source object vertex into a cRSegmentCache family staging buffer, optionally projecting track UVs.
int32_t __thiscall add_track_cache_vertex(
        SegmentCache *manager,
        Object *source,
        Vec3 *position,
        int32_t source_index,
        float u,
        float v,
        ObjectRenderVertex *vertices,
        int32_t *vertex_count,
        int32_t max_vertices,
        int32_t max_indices,
        uint32_t color,
        uint8_t project_uv)
{
  Vec3 *v12; // eax
  double v13; // st7
  int32_t v14; // ecx
  float *p_z; // edx
  ObjectRenderVertex *v16; // eax
  int v17; // eax
  float v19; // [esp+4h] [ebp-8h]
  float v20; // [esp+8h] [ebp-4h]

  v12 = &source->vertices[source_index];
  v13 = v12->x + position->x;
  v19 = v12->y + position->y;
  v20 = v12->z + position->z;
  if ( project_uv )
  {
    u = (v13 + 4.0) * 0.125;
    v = (v20 - manager->build_cache_row_base) * 0.125;
  }
  v14 = 0;
  if ( *vertex_count <= 0 )
  {
LABEL_11:
    vertices[v14].x = v13;
    v16 = &vertices[v14];
    v16->y = v19;
    v16->z = v20;
    v16->u = u;
    v16->v = 1.0 - v;
    v16->diffuse = color;
    v17 = *vertex_count + 1;
    *vertex_count = v17;
    if ( v17 > max_vertices )
      report_errorf(aVertexCacheOve);
    return *vertex_count - 1;
  }
  else
  {
    p_z = &vertices->z;
    while ( v13 != *(p_z - 2) || *(p_z - 1) != v19 || *p_z != v20 || p_z[2] != u || 1.0 - v != p_z[3] )
    {
      ++v14;
      p_z += 6;
      if ( v14 >= *vertex_count )
        goto LABEL_11;
    }
    return v14;
  }
}
