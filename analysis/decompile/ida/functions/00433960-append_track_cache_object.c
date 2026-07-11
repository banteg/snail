/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: append_track_cache_object @ 0x433960 */
/* selector: append_track_cache_object */

// Appends one source object's triangle or quad faces to a render-cache family by emitting deduplicated vertices and indices.
int32_t __thiscall append_track_cache_object(
        TrackRenderCacheManager *manager,
        int32_t row_index,
        Object *source,
        Vec3 *position,
        ObjectRenderVertex *vertices,
        int32_t *vertex_count,
        uint16_t *indices,
        int32_t *index_count,
        int32_t max_vertices,
        int32_t max_indices,
        uint32_t color,
        uint8_t project_uv)
{
  int v12; // ebp
  float y; // edx
  float z; // eax
  ObjectFaceQuad *facequads; // ecx
  int32_t v16; // eax
  int32_t v17; // eax
  int32_t result; // eax
  int32_t i; // [esp+10h] [ebp-10h]
  Vec3 v21; // [esp+14h] [ebp-Ch] BYREF

  v12 = 0;
  for ( i = 0; i < source->facequad_count; ++i )
  {
    y = position->y;
    z = position->z;
    v21.x = position->x;
    facequads = source->facequads;
    v21.y = y;
    v21.z = z;
    indices[*index_count] = add_track_cache_vertex(
                              manager,
                              source,
                              &v21,
                              facequads[v12].vertex_0,
                              facequads[v12].uv[0].u,
                              facequads[v12].uv[0].v,
                              vertices,
                              vertex_count,
                              max_vertices,
                              max_indices,
                              color,
                              project_uv);
    indices[*index_count + 1] = add_track_cache_vertex(
                                  manager,
                                  source,
                                  &v21,
                                  source->facequads[v12].vertex_1,
                                  source->facequads[v12].uv[1].u,
                                  source->facequads[v12].uv[1].v,
                                  vertices,
                                  vertex_count,
                                  max_vertices,
                                  max_indices,
                                  color,
                                  project_uv);
    indices[*index_count + 2] = add_track_cache_vertex(
                                  manager,
                                  source,
                                  &v21,
                                  source->facequads[v12].vertex_2,
                                  source->facequads[v12].uv[2].u,
                                  source->facequads[v12].uv[2].v,
                                  vertices,
                                  vertex_count,
                                  max_vertices,
                                  max_indices,
                                  color,
                                  project_uv);
    v16 = *index_count;
    if ( (source->facequads[v12].flags & 0x80u) != 0 )
    {
      v17 = v16 + 3;
    }
    else
    {
      indices[v16 + 3] = indices[v16];
      indices[*index_count + 4] = indices[*index_count + 2];
      indices[*index_count + 5] = add_track_cache_vertex(
                                    manager,
                                    source,
                                    &v21,
                                    source->facequads[v12].vertex_3,
                                    source->facequads[v12].uv[3].u,
                                    source->facequads[v12].uv[3].v,
                                    vertices,
                                    vertex_count,
                                    max_vertices,
                                    max_indices,
                                    color,
                                    project_uv);
      v17 = *index_count + 6;
    }
    *index_count = v17;
    ++v12;
  }
  result = *index_count;
  if ( *index_count > max_indices )
    return report_errorf(aIndexCacheOver);
  return result;
}
