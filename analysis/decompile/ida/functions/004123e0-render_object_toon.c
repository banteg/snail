/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_object_toon @ 0x4123e0 */
/* selector: render_object_toon */

// Draws one object's optional toon edge pass by transforming the camera delta into object space, selecting boundary or silhouette edges against their two face normals, and submitting the selected vertex pairs as line primitives. The pass uses the global sprite manager for its line texture and the global D3D device for drawing. Cross-port Android symbols match this helper to `G0RenderToon(cRObject*, tMatrix*)`.
int __cdecl render_object_toon(Object *object, TransformMatrix *matrix)
{
  ObjectIndexBufferResource *v2; // ebp
  int v3; // edi
  int v4; // esi
  int result; // eax
  double v7; // st7
  int32_t edge_count; // eax
  int v9; // ebp
  int v10; // esi
  ObjectToonEdge *v11; // eax
  Vec3 *facequad_normals; // ecx
  const Vec3 *v13; // edi
  int32_t normal_b; // edx
  int vertex_a; // eax
  const Vec3 *v16; // ecx
  Vec3 *vertices; // edx
  double v18; // st7
  Vec3 *v19; // eax
  double v20; // st7
  ObjectIndexBuffer *toon_index_buffer; // ecx
  TextureRef *sprite_texture; // eax
  uint32_t v23; // esi
  int32_t v24; // ecx
  float v25; // [esp+34h] [ebp-C4h]
  float v26; // [esp+38h] [ebp-C0h]
  ObjectIndexBufferResource *buffer; // [esp+40h] [ebp-B8h]
  int v28; // [esp+50h] [ebp-A8h] BYREF
  __int128 v29; // [esp+54h] [ebp-A4h]
  Vec3 vector; // [esp+64h] [ebp-94h] BYREF
  float v31; // [esp+70h] [ebp-88h]
  float v32; // [esp+74h] [ebp-84h]
  Vec3 v33; // [esp+78h] [ebp-80h] BYREF
  float v34[14]; // [esp+C0h] [ebp-38h] BYREF
  float *v35; // [esp+108h] [ebp+10h]

  result = object->flags;
  if ( (result & 0x4000) != 0 )
  {
    v26 = g_render_projection_far_z + 30.0;
    v25 = g_render_projection_near_z + 0.0040000002;
    build_perspective_projection_matrix((int)&v33, g_render_projection_param_a, g_render_projection_param_b, v25, v26);
    ((void (__stdcall *)(Direct3DDevice8 *, int, Vec3 *, int, int))g_direct3d_renderer.device->vtbl->SetTransform)(
      g_direct3d_renderer.device,
      3,
      &v33,
      v3,
      v4);
    *(float *)&v29 = *(float *)(g_render_camera_source_matrix + 48) - v35[12];
    *((float *)&v29 + 1) = *(float *)(g_render_camera_source_matrix + 52) - v35[13];
    v7 = *(float *)(g_render_camera_source_matrix + 56) - v35[14];
    vector = (Vec3)v29;
    qmemcpy(v34, v35, 0x40u);
    *((float *)&v29 + 2) = v7;
    invert_matrix_in_place((TransformMatrix *)v34);
    rotate_vector_by_matrix(&vector, (const TransformMatrix *)v34);
    vector_magnitude(&vector);
    g_direct3d_renderer.device->vtbl->SetIndices(g_direct3d_renderer.device, object->toon_index_buffer->buffer, 0);
    g_direct3d_renderer.device->vtbl->SetStreamSource(
      g_direct3d_renderer.device,
      0,
      object->render_buffers->vertex_buffer,
      24);
    edge_count = object->edge_count;
    HIDWORD(v29) = 0;
    if ( edge_count > 0 )
    {
      buffer = v2;
      v9 = 0;
      while ( 1 )
      {
        v10 = 0;
        ((void (__stdcall *)(ObjectIndexBufferResource *, _DWORD, int, int *, _DWORD, ObjectIndexBufferResource *))object->toon_index_buffer->buffer->vtbl->Lock)(
          object->toon_index_buffer->buffer,
          0,
          2 * object->vertex_count,
          &v28,
          0,
          buffer);
        v11 = &object->edges[v9];
        if ( (v11->flags & 1) != 0 )
          break;
        facequad_normals = object->facequad_normals;
        v13 = &facequad_normals[v11->normal_a];
        normal_b = v11->normal_b;
        vertex_a = v11->vertex_a;
        v16 = &facequad_normals[normal_b];
        vertices = object->vertices;
        v18 = vector.y - vertices[vertex_a].x;
        v19 = &vertices[vertex_a];
        *((float *)&v29 + 1) = v18;
        *((float *)&v29 + 2) = vector.z - v19->y;
        *((float *)&v29 + 3) = v31 - v19->z;
        v33 = *(Vec3 *)((char *)&v29 + 4);
        v32 = dot_vector(&v33, v16);
        v20 = dot_vector(&v33, v13);
        if ( v20 * v32 < 0.0099999998 )
        {
          *(_WORD *)v29 = object->edges[v9].vertex_a;
          *(_WORD *)(v29 + 2) = object->edges[v9].vertex_b;
          goto LABEL_8;
        }
LABEL_9:
        toon_index_buffer = object->toon_index_buffer;
        buffer = toon_index_buffer->buffer;
        ((void (*)(void))toon_index_buffer->buffer->vtbl->Unlock)();
        if ( v10 > 0 )
        {
          sprite_texture = (TextureRef *)get_sprite_texture(93);
          bind_texture_ref(sprite_texture);
          v23 = v10 / 2;
          g_direct3d_renderer.device->vtbl->DrawIndexedPrimitive(
            g_direct3d_renderer.device,
            2,
            0,
            object->grouped_vertex_count,
            0,
            v23);
          g_render_triangle_count += v23;
          ++g_draw_primitive_call_count;
        }
        v24 = object->edge_count;
        ++v9;
        ++HIDWORD(v29);
        if ( SHIDWORD(v29) >= v24 )
          goto LABEL_12;
      }
      *(_WORD *)v29 = v11->vertex_a;
      *(_WORD *)(v29 + 2) = object->edges[v9].vertex_b;
LABEL_8:
      v10 = 2;
      goto LABEL_9;
    }
LABEL_12:
    build_perspective_projection_matrix(
      (int)&v33.z,
      g_render_projection_param_a,
      g_render_projection_param_b,
      g_render_projection_near_z,
      g_render_projection_far_z);
    return ((int (__stdcall *)(Direct3DDevice8 *))g_direct3d_renderer.device->vtbl->SetTransform)(g_direct3d_renderer.device);
  }
  return result;
}
