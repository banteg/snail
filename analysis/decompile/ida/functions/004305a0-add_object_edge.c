/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_object_edge @ 0x4305a0 */
/* selector: add_object_edge */

// Adds or merges one candidate toon edge in the global build scratch array. Its two vertex members are 32-bit indices; new records store a normalized direction plus its original length, while shared records add the second face normal and may be removed when the join should not outline. iOS RObject.o names this `cRObject::AddEdge(int, int, int)`.
void __thiscall add_object_edge(Object *object, int vertex_a, int vertex_b, int normal_index)
{
  int v4; // ebp
  Object *v5; // edi
  int v6; // ebx
  Vec3 *v8; // edx
  _DWORD *v9; // ebp
  float *v10; // edi
  float *v11; // edi
  float *v12; // ebx
  Vec3 *vertices; // edx
  float *p_x; // eax
  float *v15; // ecx
  int v16; // ebx
  int v17; // esi
  int v18; // eax
  Vec3 *facequad_normals; // eax
  int v20; // eax
  const void *v21; // esi
  void *v22; // edi
  int v23; // [esp+10h] [ebp-38h]
  Vec3 vector; // [esp+18h] [ebp-30h] BYREF
  Vec3 rhs; // [esp+24h] [ebp-24h] BYREF
  Vec3 lhs; // [esp+30h] [ebp-18h] BYREF
  Vec3 out; // [esp+3Ch] [ebp-Ch] BYREF
  float *vertex_ba; // [esp+50h] [ebp+8h]

  v4 = normal_index;
  v5 = object;
  if ( vector_magnitude(&object->facequad_normals[normal_index]) < 0.89999998 )
    return;
  v6 = g_object_edge_build_count;
  v23 = 0;
  if ( g_object_edge_build_count <= 0 )
  {
LABEL_13:
    *(_DWORD *)(g_object_edge_build_edges + 36 * v6) = 1;
    *(_DWORD *)(g_object_edge_build_edges + 36 * g_object_edge_build_count + 4) = vertex_a;
    *(_DWORD *)(g_object_edge_build_edges + 36 * g_object_edge_build_count + 8) = vertex_b;
    *(_DWORD *)(g_object_edge_build_edges + 36 * g_object_edge_build_count + 12) = v4;
    *(_DWORD *)(g_object_edge_build_edges + 36 * g_object_edge_build_count + 16) = 0;
    vertices = v5->vertices;
    p_x = &vertices[vertex_a].x;
    v15 = &vertices[vertex_b].x;
    rhs.x = *v15 - *p_x;
    rhs.y = v15[1] - p_x[1];
    rhs.z = v15[2] - p_x[2];
    vector = rhs;
    *(float *)(g_object_edge_build_edges + 36 * g_object_edge_build_count + 32) = normalize_vector(&vector);
    *(Vec3 *)(g_object_edge_build_edges + 36 * g_object_edge_build_count++ + 20) = vector;
    return;
  }
  v8 = v5->vertices;
  vertex_ba = &v8[vertex_b].x;
  v9 = (_DWORD *)(g_object_edge_build_edges + 8);
  while ( 1 )
  {
    v10 = &v8[*(v9 - 1)].x;
    if ( *v10 != *vertex_ba || v10[1] != vertex_ba[1] || v10[2] != vertex_ba[2] )
      goto LABEL_11;
    v11 = &v8[*v9].x;
    v12 = &v8[vertex_a].x;
    if ( *v11 == *v12 && v11[1] == v12[1] && v11[2] == v12[2] )
      break;
    v6 = g_object_edge_build_count;
LABEL_11:
    v9 += 9;
    if ( ++v23 >= v6 )
    {
      v4 = normal_index;
      v5 = object;
      goto LABEL_13;
    }
  }
  v16 = v23;
  v17 = 36 * v23;
  v18 = *(_DWORD *)(36 * v23 + g_object_edge_build_edges);
  if ( (v18 & 1) != 0 )
  {
    LOBYTE(v18) = v18 & 0xFE;
    *(_DWORD *)(v17 + g_object_edge_build_edges) = v18;
    *(_DWORD *)(v17 + g_object_edge_build_edges) |= 2u;
    *(_DWORD *)(v17 + g_object_edge_build_edges + 16) = normal_index;
    if ( (object->flags & 4) == 0 )
    {
      facequad_normals = object->facequad_normals;
      lhs = facequad_normals[*(_DWORD *)(v17 + g_object_edge_build_edges + 12)];
      rhs = facequad_normals[*(_DWORD *)(v17 + g_object_edge_build_edges + 16)];
      cross_vectors(&out, &lhs, &rhs);
      if ( vector_magnitude(&out) <= 0.050000001
        || dot_vector(&out, (const Vec3 *)(v17 + g_object_edge_build_edges + 20)) > 0.0020000001 )
      {
        if ( v23 < g_object_edge_build_count - 1 )
        {
          v20 = 36 * v23;
          do
          {
            ++v16;
            v21 = (const void *)(v20 + g_object_edge_build_edges + 36);
            v22 = (void *)(v20 + g_object_edge_build_edges);
            v20 += 36;
            qmemcpy(v22, v21, 0x24u);
          }
          while ( v16 < g_object_edge_build_count - 1 );
        }
        --g_object_edge_build_count;
      }
    }
  }
}
