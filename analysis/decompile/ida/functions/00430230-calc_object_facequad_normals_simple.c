/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_facequad_normals_simple @ 0x430230 */
/* selector: calc_object_facequad_normals_simple */

// Recomputes only the per-face quad-normal pairs for the current vertex positions without rebuilding the full accumulated vertex-normal table. Used by the distort path before the toon edge pass reuses the updated face data.
int32_t __thiscall calc_object_facequad_normals_simple(Object *object)
{
  int32_t result; // eax
  int v3; // ebp
  int v4; // ebx
  Vec3 *vertices; // ecx
  ObjectFaceQuad *v6; // eax
  float *p_x; // edi
  float *v8; // edx
  float *v9; // edi
  float *v10; // eax
  ObjectFaceQuad *v11; // eax
  Vec3 *v12; // edi
  float *v13; // edx
  int vertex_3; // eax
  double v15; // st7
  Vec3 *v16; // eax
  int32_t v17; // [esp+8h] [ebp-58h]
  Vec3 rhs; // [esp+Ch] [ebp-54h] BYREF
  Vec3 v19; // [esp+18h] [ebp-48h]
  Vec3 v20; // [esp+24h] [ebp-3Ch]
  Vec3 v21; // [esp+30h] [ebp-30h]
  Vec3 out; // [esp+3Ch] [ebp-24h] BYREF
  Vec3 lhs; // [esp+48h] [ebp-18h] BYREF
  Vec3 vector; // [esp+54h] [ebp-Ch] BYREF

  request_object_facequad_normals(object);
  result = object->facequad_count;
  v3 = 0;
  v17 = 0;
  if ( result > 0 )
  {
    v4 = 0;
    do
    {
      vertices = object->vertices;
      v6 = &object->facequads[v4];
      p_x = &vertices[v6->vertex_0].x;
      v8 = &vertices[v6->vertex_1].x;
      v19.x = *v8 - *p_x;
      v19.y = v8[1] - p_x[1];
      v19.z = v8[2] - p_x[2];
      lhs = v19;
      v9 = &vertices[v6->vertex_0].x;
      v10 = &vertices[v6->vertex_2].x;
      v20.x = *v10 - *v9;
      v20.y = v10[1] - v9[1];
      v20.z = v10[2] - v9[2];
      rhs = v20;
      cross_vectors(&out, &lhs, &rhs);
      normalize_vector(&out);
      object->facequad_normals[v3] = out;
      v11 = &object->facequads[v4];
      if ( (v11->flags & 0x80u) == 0 )
      {
        v12 = object->vertices;
        v13 = &v12[v11->vertex_0].x;
        vertex_3 = v11->vertex_3;
        v15 = v12[vertex_3].x - *v13;
        v16 = &v12[vertex_3];
        v21.x = v15;
        v21.y = v16->y - v13[1];
        v21.z = v16->z - v13[2];
        rhs = v21;
        cross_vectors(&vector, &lhs, &rhs);
        normalize_vector(&vector);
        object->facequad_normals[v3 + 1] = vector;
      }
      result = v17 + 1;
      ++v4;
      v3 += 2;
      ++v17;
    }
    while ( v17 < object->facequad_count );
  }
  return result;
}
