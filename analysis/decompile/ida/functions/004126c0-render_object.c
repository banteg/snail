/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_object @ 0x4126c0 */
/* selector: render_object */

// Renders one built object through the grouped Direct3D path: refreshes animated vertices, sets world transform and cull mode, binds each texture group, applies the blend preset and tint, submits indexed primitives, and optionally dispatches the toon edge pass. Its third and fourth arguments are the float texture-U and texture-V values forwarded from `BodBase +0x1c/+0x20`. Cross-port Android symbols match this helper to `G0RenderObject(cRObject*, tMatrix*, float, float, tColourSmall*, bool)`.
int __cdecl render_object(
        Object *object,
        TransformMatrix *matrix,
        float texture_u,
        float texture_v,
        tColour *color,
        char after_sprites)
{
  int result; // eax
  int32_t v7; // esi
  char v8; // cl
  ObjectFlag flags; // eax
  _BYTE v10[64]; // [esp+1Ch] [ebp-40h] BYREF

  result = object->flags;
  if ( (result & 0x80000) != 0 && (result & 0x40000) == 0 )
  {
    result = object->vertex_count;
    if ( result )
    {
      refresh_object_vertex_buffer(object);
      qmemcpy(v10, matrix, sizeof(v10));
      g_direct3d_renderer.device->vtbl->SetTransform(g_direct3d_renderer.device, 256, (TransformMatrix *)v10);
      set_cull_mode((object->flags & 0x100000) == 0);
      v7 = 0;
      if ( object->texture_group_count > 0 )
      {
        v8 = g_object_render_pass_filter;
        do
        {
          if ( v8 )
          {
            if ( v8 != 1 || after_sprites != 1 || (object->group_texture_refs[v7]->flags & 0x10000) != 0 )
            {
LABEL_13:
              if ( object->group_texture_refs[v7] )
              {
                if ( (object->flags & 8) != 0 )
                  bind_texture_ref(object->override_texture_ref);
                else
                  bind_texture_ref(object->group_texture_refs[v7]);
                if ( SLOBYTE(object->flags) >= 0 )
                {
                  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 24, 0);
                }
                else
                {
                  g_object_texture_transform_matrix.basis_forward.x = texture_u;
                  g_object_texture_transform_matrix.basis_forward.y = 1.0 - texture_v;
                  g_direct3d_renderer.device->vtbl->SetTransform(
                    g_direct3d_renderer.device,
                    16,
                    &g_object_texture_transform_matrix);
                  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 24, 2);
                }
                if ( LODWORD(color->a) == 1065353216 || (object->group_texture_refs[v7]->flags & 0x10000) == 0 )
                {
                  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 0);
                }
                else
                {
                  set_blend_mode(object->blend_mode);
                  flags = object->flags;
                  if ( (flags & 0x50) != 0 )
                  {
                    LOBYTE(flags) = flags & 0xBF;
                    object->flags = flags;
                    set_object_color(object, *color);
                  }
                }
                g_direct3d_renderer.device->vtbl->SetStreamSource(
                  g_direct3d_renderer.device,
                  0,
                  object->render_buffers->vertex_buffer,
                  24);
                g_direct3d_renderer.device->vtbl->SetVertexShader(g_direct3d_renderer.device, 322);
                g_direct3d_renderer.device->vtbl->SetIndices(
                  g_direct3d_renderer.device,
                  object->index_buffer->buffer,
                  0);
                g_direct3d_renderer.device->vtbl->DrawIndexedPrimitive(
                  g_direct3d_renderer.device,
                  4,
                  0,
                  object->grouped_vertex_count,
                  object->group_index_starts[v7],
                  object->group_primitive_counts[v7]);
                v8 = g_object_render_pass_filter;
                g_render_triangle_count += object->group_primitive_counts[v7];
                ++g_draw_primitive_call_count;
              }
            }
          }
          else if ( after_sprites != 1 || (object->group_texture_refs[v7]->flags & 0x10000) == 0 )
          {
            goto LABEL_13;
          }
          ++v7;
        }
        while ( v7 < object->texture_group_count );
      }
      return render_object_toon(object, matrix);
    }
  }
  return result;
}
