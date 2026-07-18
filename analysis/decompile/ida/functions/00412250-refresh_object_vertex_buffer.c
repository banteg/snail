/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: refresh_object_vertex_buffer @ 0x412250 */
/* selector: refresh_object_vertex_buffer */

// Refreshes one built object's grouped vertex buffer from the current animated or distorted vertex source, preserving the authored UV lanes for the grouped draw path.
void __cdecl refresh_object_vertex_buffer(Object *object)
{
  Object *v1; // esi
  ObjectFlag flags; // ebx
  ObjectAnimation *animation; // edi
  int32_t v4; // eax
  int v5; // edx
  int v6; // ecx
  float *p_x; // edi
  ObjectRenderVertex *v8; // ebx
  int32_t v9; // ecx
  int v10; // edi
  int v11; // ebx
  float *v12; // edx
  ObjectRenderVertex *v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // eax
  ObjectRenderVertex *animated_vertices; // [esp+14h] [ebp+4h] SPLIT BYREF
  ObjectRenderVertex *dynamic_vertices; // [esp+14h] [ebp+4h] SPLIT BYREF

  v1 = object;
  flags = object->flags;
  if ( (flags & 0x200000) != 0 )
  {
    animation = object->animation;
    object->vertices = animation->frames[(__int64)((double)animation->generated_frame_count * animation->progress)]->vertices;
    v1->facequad_normals = animation->frames[(__int64)((double)animation->generated_frame_count * animation->progress)]->facequad_normals;
    if ( ((unsigned int)&g_sprite_manager.sprites[2527] & flags) != 0 )
      apply_distort_to_object(&v1->distort, v1);
    v1->render_buffers->vertex_buffer->vtbl->Lock(
      v1->render_buffers->vertex_buffer,
      0,
      24 * v1->grouped_vertex_count,
      (void **)&animated_vertices,
      0);
    v4 = 0;
    if ( v1->grouped_vertex_count > 0 )
    {
      v5 = 0;
      v6 = 0;
      do
      {
        p_x = &v1->vertices[v6].x;
        v8 = &animated_vertices[v5];
        ++v4;
        ++v6;
        v8->x = *p_x;
        ++v5;
        v8->y = p_x[1];
        v8->z = p_x[2];
      }
      while ( v4 < v1->grouped_vertex_count );
    }
  }
  else
  {
    if ( (flags & 4) == 0 )
      return;
    object->render_buffers->vertex_buffer->vtbl->Lock(
      object->render_buffers->vertex_buffer,
      0,
      24 * object->grouped_vertex_count,
      (void **)&dynamic_vertices,
      0);
    v9 = 0;
    if ( v1->grouped_vertex_count > 0 )
    {
      v10 = 0;
      v11 = 0;
      do
      {
        v12 = &v1->vertices[v11].x;
        v13 = &dynamic_vertices[v10];
        ++v11;
        ++v10;
        v13->x = *v12;
        v13->y = v12[1];
        v13->z = v12[2];
        v14 = v9 / 4;
        v15 = v9++ & 3;
        v16 = v15 + 6 * v14;
        dynamic_vertices[v10 - 1].u = v1->facequads->uv[v16].u;
        dynamic_vertices[v10 - 1].v = v1->facequads->uv[v16].v;
      }
      while ( v9 < v1->grouped_vertex_count );
    }
  }
  v1->render_buffers->vertex_buffer->vtbl->Unlock(v1->render_buffers->vertex_buffer);
}
