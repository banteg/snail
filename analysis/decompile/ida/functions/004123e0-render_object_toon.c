/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_object_toon @ 0x4123e0 */
/* selector: render_object_toon */

// Draws one object's optional toon edge pass by transforming the camera delta into object space, selecting boundary or silhouette edges against their two face normals, and submitting the selected vertex pairs as line primitives. The pass uses the global sprite manager for its line texture and the global D3D device for drawing. Cross-port Android symbols match this helper to `G0RenderToon(cRObject*, tMatrix*)`.
void __cdecl render_object_toon(Object *object, TransformMatrix *matrix)
{
  ObjectIndexBufferResource *v2; // ebp
  int v3; // edi
  int v4; // esi
  double v6; // st7
  int32_t edge_count; // eax
  int v8; // ebp
  int v9; // esi
  ObjectToonEdge *v10; // eax
  Vec3 *facequad_normals; // ecx
  const Vec3 *v12; // edi
  int32_t normal_b; // edx
  int vertex_a; // eax
  const Vec3 *v15; // ecx
  Vec3 *vertices; // edx
  double v17; // st7
  Vec3 *v18; // eax
  double v19; // st7
  ObjectIndexBuffer *toon_index_buffer; // ecx
  TextureRef *sprite_texture; // eax
  uint32_t v22; // esi
  int32_t v23; // ecx
  float near_z; // [esp+34h] [ebp-C4h]
  float far_z; // [esp+38h] [ebp-C0h]
  ObjectIndexBufferResource *buffer; // [esp+40h] [ebp-B8h]
  int v27; // [esp+50h] [ebp-A8h] BYREF
  __int128 v28; // [esp+54h] [ebp-A4h]
  Vec3 vector; // [esp+64h] [ebp-94h] BYREF
  float v30; // [esp+70h] [ebp-88h]
  float v31; // [esp+74h] [ebp-84h]
  TransformMatrix v32; // [esp+78h] [ebp-80h] BYREF
  float v33[14]; // [esp+C0h] [ebp-38h] BYREF
  float *v34; // [esp+108h] [ebp+10h]

  if ( (object->flags & 0x4000) != 0 )
  {
    far_z = g_render_projection_far_z + 30.0;
    near_z = g_render_projection_near_z + 0.0040000002;
    build_perspective_projection_matrix(&v32, g_render_projection_param_a, g_render_projection_param_b, near_z, far_z);
    ((void (__stdcall *)(Direct3DDevice8 *, int, TransformMatrix *, int, int))g_direct3d_renderer.device->vtbl->SetTransform)(
      g_direct3d_renderer.device,
      3,
      &v32,
      v3,
      v4);
    *(float *)&v28 = g_render_camera_source_matrix->position.x - v34[12];
    *((float *)&v28 + 1) = g_render_camera_source_matrix->position.y - v34[13];
    v6 = g_render_camera_source_matrix->position.z - v34[14];
    vector = (Vec3)v28;
    qmemcpy(v33, v34, 0x40u);
    *((float *)&v28 + 2) = v6;
    invert_matrix_in_place((TransformMatrix *)v33);
    rotate_vector_by_matrix(&vector, (const TransformMatrix *)v33);
    vector_magnitude(&vector);
    g_direct3d_renderer.device->vtbl->SetIndices(g_direct3d_renderer.device, object->toon_index_buffer->buffer, 0);
    g_direct3d_renderer.device->vtbl->SetStreamSource(
      g_direct3d_renderer.device,
      0,
      object->render_buffers->vertex_buffer,
      24);
    edge_count = object->edge_count;
    HIDWORD(v28) = 0;
    if ( edge_count > 0 )
    {
      buffer = v2;
      v8 = 0;
      while ( 1 )
      {
        v9 = 0;
        ((void (__stdcall *)(ObjectIndexBufferResource *, _DWORD, int, int *, _DWORD, ObjectIndexBufferResource *))object->toon_index_buffer->buffer->vtbl->Lock)(
          object->toon_index_buffer->buffer,
          0,
          2 * object->vertex_count,
          &v27,
          0,
          buffer);
        v10 = &object->edges[v8];
        if ( (v10->flags & 1) != 0 )
          break;
        facequad_normals = object->facequad_normals;
        v12 = &facequad_normals[v10->normal_a];
        normal_b = v10->normal_b;
        vertex_a = v10->vertex_a;
        v15 = &facequad_normals[normal_b];
        vertices = object->vertices;
        v17 = vector.y - vertices[vertex_a].x;
        v18 = &vertices[vertex_a];
        *((float *)&v28 + 1) = v17;
        *((float *)&v28 + 2) = vector.z - v18->y;
        *((float *)&v28 + 3) = v30 - v18->z;
        v32.basis_right = *(Vec3 *)((char *)&v28 + 4);
        v31 = dot_vector(&v32.basis_right, v15);
        v19 = dot_vector(&v32.basis_right, v12);
        if ( v19 * v31 < 0.0099999998 )
        {
          *(_WORD *)v28 = object->edges[v8].vertex_a;
          *(_WORD *)(v28 + 2) = object->edges[v8].vertex_b;
          goto LABEL_8;
        }
LABEL_9:
        toon_index_buffer = object->toon_index_buffer;
        buffer = toon_index_buffer->buffer;
        ((void (*)(void))toon_index_buffer->buffer->vtbl->Unlock)();
        if ( v9 > 0 )
        {
          sprite_texture = get_sprite_texture(&g_sprite_manager, 93);
          bind_texture_ref(sprite_texture);
          v22 = v9 / 2;
          g_direct3d_renderer.device->vtbl->DrawIndexedPrimitive(
            g_direct3d_renderer.device,
            2,
            0,
            object->grouped_vertex_count,
            0,
            v22);
          g_render_triangle_count += v22;
          ++g_draw_primitive_call_count;
        }
        v23 = object->edge_count;
        ++v8;
        ++HIDWORD(v28);
        if ( SHIDWORD(v28) >= v23 )
          goto LABEL_12;
      }
      *(_WORD *)v28 = v10->vertex_a;
      *(_WORD *)(v28 + 2) = object->edges[v8].vertex_b;
LABEL_8:
      v9 = 2;
      goto LABEL_9;
    }
LABEL_12:
    build_perspective_projection_matrix(
      (TransformMatrix *)&v32.basis_right.z,
      g_render_projection_param_a,
      g_render_projection_param_b,
      g_render_projection_near_z,
      g_render_projection_far_z);
    ((void (__stdcall *)(Direct3DDevice8 *))g_direct3d_renderer.device->vtbl->SetTransform)(g_direct3d_renderer.device);
  }
}
