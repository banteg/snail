/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_object_texture_group_buffers @ 0x413d50 */
/* selector: build_object_texture_group_buffers */

// Allocates one Object's texture-group tables, expands each Object-owned face run through six advancing index lanes, uploads the grouped scratch's scalar diffuse plus aggregate UV/XYZ render payload, and retains the resulting Direct3D vertex and index buffers. iOS RObject.o names the owner family `cRObject::BuildGLVertexArray()`.
void __cdecl build_object_texture_group_buffers(Object *object)
{
  int v1; // esi
  int v3; // edi
  int32_t *tracked_memory; // eax
  TextureRef **v5; // eax
  int32_t v6; // ecx
  int32_t v7; // ebp
  int32_t i; // esi
  int32_t facequad_count; // eax
  ObjectFaceQuad *v10; // eax
  int32_t v11; // ecx
  int32_t texture_group_count; // edx
  int32_t v13; // eax
  int32_t v14; // edi
  char *v15; // esi
  _WORD *v16; // ebp
  int32_t v17; // eax
  int32_t v18; // ecx
  ObjectIndexBuffer *index_buffer; // eax
  ObjectRenderBuffers *render_buffers; // edx
  int32_t v21; // edx
  int v22; // eax
  int v23; // ecx
  float *p_u; // esi
  ObjectGroupedVertex *v25; // esi
  float *v26; // edi
  float x; // ebp
  int v28; // [esp-1Ch] [ebp-50h]
  int v29; // [esp-14h] [ebp-48h]
  int v30; // [esp-4h] [ebp-38h]
  char *v31; // [esp+Ch] [ebp-28h]
  char *v32; // [esp+10h] [ebp-24h]
  _WORD *v33; // [esp+14h] [ebp-20h]
  int32_t v34; // [esp+18h] [ebp-1Ch]
  _WORD *v35; // [esp+1Ch] [ebp-18h]
  int32_t v36; // [esp+20h] [ebp-14h]
  int v37; // [esp+24h] [ebp-10h] BYREF
  int32_t v38; // [esp+28h] [ebp-Ch]
  char *archive_data_end; // [esp+2Ch] [ebp-8h]
  char *v40; // [esp+30h] [ebp-4h] BYREF
  int32_t objecta; // [esp+38h] [ebp+4h]
  int32_t v42; // [esp+3Ch] [ebp+8h]

  v3 = 0;
  if ( object->vertex_count )
  {
    v30 = v1;
    object->flags |= 0x80000u;
    tracked_memory = (int32_t *)allocate_tracked_memory(4 * object->texture_group_count, aDxTexturegroup);
    v29 = 4 * object->texture_group_count;
    object->group_index_starts = tracked_memory;
    v5 = (TextureRef **)allocate_tracked_memory(v29, aDxTexturegroup_0);
    v28 = 4 * object->texture_group_count;
    object->group_texture_refs = v5;
    object->group_primitive_counts = (int32_t *)allocate_tracked_memory(v28, aDxTexturegroup_1);
    g_object_grouped_vertex_scratch = (ObjectGroupedVertex *)get_archive_data_base();
    archive_data_end = (char *)get_archive_data_end();
    g_object_grouped_vertex_cursor = 0;
    v6 = 0;
    v7 = 0;
    v36 = 0;
    objecta = 0;
    if ( (object->flags & 4) != 0 )
    {
      for ( i = 0; i < object->vertex_count; ++i )
      {
        facequad_count = object->facequad_count;
        v38 = 0;
        if ( facequad_count > 0 )
        {
          do
          {
            v10 = &object->facequads[v3];
            if ( v10->vertex_0 == i )
            {
              get_or_append_object_texture_group_vertex(object, i, v10->uv[0].u, v10->uv[0].v);
            }
            else if ( v10->vertex_1 == i )
            {
              get_or_append_object_texture_group_vertex(object, i, v10->uv[1].u, v10->uv[1].v);
            }
            else if ( v10->vertex_2 == i )
            {
              get_or_append_object_texture_group_vertex(object, i, v10->uv[2].u, v10->uv[2].v);
            }
            else if ( (v10->flags & 0x80u) == 0 && v10->vertex_3 == i )
            {
              get_or_append_object_texture_group_vertex(object, i, v10->uv[3].u, v10->uv[3].v);
            }
            v11 = object->facequad_count;
            ++v3;
            ++v38;
          }
          while ( v38 < v11 );
          v6 = 0;
          v3 = 0;
        }
      }
    }
    texture_group_count = object->texture_group_count;
    v13 = 0;
    v38 = 0;
    if ( texture_group_count > 0 )
    {
      while ( 1 )
      {
        v34 = 0;
        v14 = v6;
        object->group_texture_refs[v13] = object->facequads[v6].texture_ref;
        object->group_index_starts[v13] = v7;
        if ( v6 < object->texture_group_ends[v13] )
        {
          v15 = &archive_data_end[2 * v7];
          v35 = v15 + 10;
          v16 = v15 + 4;
          v33 = v15 + 8;
          v32 = &archive_data_end[2 * objecta + 6];
          v31 = &archive_data_end[2 * objecta + 2];
          do
          {
            *(_WORD *)v15 = get_or_append_object_texture_group_vertex(
                              object,
                              object->facequads[v14].vertex_0,
                              object->facequads[v14].uv[0].u,
                              object->facequads[v14].uv[0].v);
            *(_WORD *)v31 = get_or_append_object_texture_group_vertex(
                              object,
                              object->facequads[v14].vertex_1,
                              object->facequads[v14].uv[1].u,
                              object->facequads[v14].uv[1].v);
            *v16 = get_or_append_object_texture_group_vertex(
                     object,
                     object->facequads[v14].vertex_2,
                     object->facequads[v14].uv[2].u,
                     object->facequads[v14].uv[2].v);
            if ( (object->facequads[v14].flags & 0x80u) != 0 )
            {
              objecta += 3;
              v15 += 6;
              v31 += 6;
              v16 += 3;
              v32 += 6;
              v33 += 3;
              v35 += 3;
              v17 = v34 + 1;
            }
            else
            {
              *(_WORD *)v32 = *(_WORD *)v15;
              *v33 = *v16;
              *v35 = get_or_append_object_texture_group_vertex(
                       object,
                       object->facequads[v14].vertex_3,
                       object->facequads[v14].uv[3].u,
                       object->facequads[v14].uv[3].v);
              objecta += 6;
              v15 += 12;
              v31 += 12;
              v16 += 6;
              v32 += 12;
              v33 += 6;
              v35 += 6;
              v17 = v34 + 2;
            }
            v34 = v17;
            ++v14;
            ++v36;
          }
          while ( v36 < object->texture_group_ends[v38] );
          v7 = objecta;
          v13 = v38;
        }
        object->group_primitive_counts[v13] = v34;
        v18 = object->texture_group_count;
        v38 = ++v13;
        if ( v13 >= v18 )
          break;
        v6 = v36;
      }
    }
    object->grouped_vertex_count = g_object_grouped_vertex_cursor;
    object->render_buffers = create_vertex_buffer(
                               &g_direct3d_renderer.vertex_buffer_factory,
                               g_object_grouped_vertex_cursor,
                               322);
    index_buffer = create_index_buffer(&g_direct3d_renderer.index_buffer_factory, v7);
    render_buffers = object->render_buffers;
    object->index_buffer = index_buffer;
    ((void (__stdcall *)(ObjectVertexBuffer *, _DWORD, int, int *, _DWORD, int))render_buffers->vertex_buffer->vtbl->Lock)(
      render_buffers->vertex_buffer,
      0,
      24 * g_object_grouped_vertex_cursor,
      &v37,
      0,
      v30);
    v21 = 0;
    if ( g_object_grouped_vertex_cursor > 0 )
    {
      v22 = 0;
      v23 = 0;
      do
      {
        *(_DWORD *)(v22 + v38 + 12) = g_object_grouped_vertex_scratch[v23].diffuse;
        p_u = &g_object_grouped_vertex_scratch[v23].u;
        *(float *)(v22 + v38 + 16) = *p_u;
        *(float *)(v22 + v38 + 20) = p_u[1];
        v25 = &g_object_grouped_vertex_scratch[v23];
        v26 = (float *)(v22 + v38);
        ++v21;
        x = g_object_grouped_vertex_scratch[v23++].x;
        *v26 = x;
        v22 += 24;
        v26[1] = v25->y;
        v26[2] = v25->z;
      }
      while ( v21 < g_object_grouped_vertex_cursor );
      v7 = v42;
    }
    ((void (__cdecl *)(ObjectVertexBuffer *))object->render_buffers->vertex_buffer->vtbl->Unlock)(object->render_buffers->vertex_buffer);
    object->index_buffer->buffer->vtbl->Lock(object->index_buffer->buffer, 0, 2 * v7, (void **)&v40, 0);
    qmemcpy(v40, archive_data_end, 2 * v7);
    object->index_buffer->buffer->vtbl->Unlock(object->index_buffer->buffer);
    if ( (object->flags & 0x4000) != 0 )
      object->toon_index_buffer = create_index_buffer(&g_direct3d_renderer.index_buffer_factory, v7);
  }
  else
  {
    object->group_index_starts = nullptr;
    object->group_texture_refs = nullptr;
    object->group_primitive_counts = nullptr;
    object->render_buffers = nullptr;
    object->index_buffer = nullptr;
  }
}
