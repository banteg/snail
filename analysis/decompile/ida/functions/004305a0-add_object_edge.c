/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_object_edge @ 0x4305a0 */
/* selector: add_object_edge */

// Adds or merges one candidate toon edge in the global build scratch array. Its two vertex members are 32-bit indices; new records store a normalized direction plus its original length, while shared records add the second face normal and may be removed when the join should not outline. iOS RObject.o names this `cRObject::AddEdge(int, int, int)`.
void __thiscall add_object_edge(Object *object, int32_t vertex_a, int32_t vertex_b, int32_t normal_index)
{
  int32_t v4; // ebp
  Object *v5; // edi
  int32_t build_count; // ebx
  Vec3 *v8; // edx
  int32_t *p_vertex_b; // ebp
  float *v10; // edi
  float *v11; // edi
  float *v12; // ebx
  Vec3 *vertices; // edx
  float *p_x; // eax
  float *v15; // ecx
  int32_t shift_index; // ebx
  int32_t found_index; // esi
  ObjectToonEdgeFlag flags; // eax
  Vec3 *facequad_normals; // eax
  int32_t copy_index; // eax
  ObjectToonEdge *v21; // esi
  ObjectToonEdge *v22; // edi
  int32_t edge_index; // [esp+10h] [ebp-38h]
  Vec3 vector; // [esp+18h] [ebp-30h] BYREF
  Vec3 rhs; // [esp+24h] [ebp-24h] BYREF
  Vec3 lhs; // [esp+30h] [ebp-18h] BYREF
  Vec3 out; // [esp+3Ch] [ebp-Ch] BYREF
  float *vertex_ba; // [esp+50h] [ebp+8h]

  v4 = normal_index;
  v5 = object;
  if ( vector_magnitude(&object->facequad_normals[normal_index]) < 0.89999998 )
    return;
  build_count = g_object_edge_build_count;
  edge_index = 0;
  if ( g_object_edge_build_count <= 0 )
  {
LABEL_13:
    g_object_edge_build_edges[build_count].flags = OBJECT_TOON_EDGE_FLAG_BOUNDARY;
    g_object_edge_build_edges[g_object_edge_build_count].vertex_a = vertex_a;
    g_object_edge_build_edges[g_object_edge_build_count].vertex_b = vertex_b;
    g_object_edge_build_edges[g_object_edge_build_count].normal_a = v4;
    g_object_edge_build_edges[g_object_edge_build_count].normal_b = 0;
    vertices = v5->vertices;
    p_x = &vertices[vertex_a].x;
    v15 = &vertices[vertex_b].x;
    rhs.x = *v15 - *p_x;
    rhs.y = v15[1] - p_x[1];
    rhs.z = v15[2] - p_x[2];
    vector = rhs;
    g_object_edge_build_edges[g_object_edge_build_count].length = normalize_vector(&vector);
    g_object_edge_build_edges[g_object_edge_build_count++].direction = vector;
    return;
  }
  v8 = v5->vertices;
  vertex_ba = &v8[vertex_b].x;
  p_vertex_b = &g_object_edge_build_edges->vertex_b;
  while ( 1 )
  {
    v10 = &v8[*(p_vertex_b - 1)].x;
    if ( *v10 != *vertex_ba || v10[1] != vertex_ba[1] || v10[2] != vertex_ba[2] )
      goto LABEL_11;
    v11 = &v8[*p_vertex_b].x;
    v12 = &v8[vertex_a].x;
    if ( *v11 == *v12 && v11[1] == v12[1] && v11[2] == v12[2] )
      break;
    build_count = g_object_edge_build_count;
LABEL_11:
    p_vertex_b += 9;
    if ( ++edge_index >= build_count )
    {
      v4 = normal_index;
      v5 = object;
      goto LABEL_13;
    }
  }
  shift_index = edge_index;
  found_index = edge_index;
  flags = g_object_edge_build_edges[edge_index].flags;
  if ( (flags & 1) != 0 )
  {
    LOBYTE(flags) = flags & 0xFE;
    g_object_edge_build_edges[found_index].flags = flags;
    g_object_edge_build_edges[found_index].flags |= 2u;
    g_object_edge_build_edges[found_index].normal_b = normal_index;
    if ( (object->flags & 4) == 0 )
    {
      facequad_normals = object->facequad_normals;
      lhs = facequad_normals[g_object_edge_build_edges[found_index].normal_a];
      rhs = facequad_normals[g_object_edge_build_edges[found_index].normal_b];
      cross_vectors(&out, &lhs, &rhs);
      if ( vector_magnitude(&out) <= 0.050000001
        || dot_vector(&out, &g_object_edge_build_edges[found_index].direction) > 0.0020000001 )
      {
        if ( edge_index < g_object_edge_build_count - 1 )
        {
          copy_index = edge_index;
          do
          {
            ++shift_index;
            v21 = &g_object_edge_build_edges[copy_index + 1];
            v22 = &g_object_edge_build_edges[copy_index++];
            qmemcpy(v22, v21, sizeof(ObjectToonEdge));
          }
          while ( shift_index < g_object_edge_build_count - 1 );
        }
        --g_object_edge_build_count;
      }
    }
  }
}
