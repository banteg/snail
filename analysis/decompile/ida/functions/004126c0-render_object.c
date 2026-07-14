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
  tColour *v7; // edi
  int32_t v8; // esi
  char v9; // cl
  uint32_t flags; // eax
  int v11; // [esp+Ch] [ebp-50h]
  float *v12; // [esp+10h] [ebp-4Ch]
  _BYTE v13[64]; // [esp+1Ch] [ebp-40h] BYREF
  _UNKNOWN *retaddr; // [esp+5Ch] [ebp+0h] BYREF

  result = object->flags;
  if ( (result & 0x80000) != 0 && (result & 0x40000) == 0 )
  {
    result = object->vertex_count;
    if ( result )
    {
      refresh_object_vertex_buffer(object);
      qmemcpy(v13, matrix, sizeof(v13));
      v7 = (tColour *)&retaddr;
      (*(void (__stdcall **)(int, int, _BYTE *))(*(_DWORD *)g_d3d_device + 148))(g_d3d_device, 256, v13);
      set_cull_mode((object->flags & 0x100000) == 0);
      v8 = 0;
      if ( object->texture_group_count > 0 )
      {
        v7 = color;
        v9 = g_object_render_pass_filter;
        do
        {
          if ( v9 )
          {
            if ( v9 != 1 || after_sprites != 1 || (object->group_texture_refs[v8]->flags & 0x10000) != 0 )
            {
LABEL_13:
              if ( object->group_texture_refs[v8] )
              {
                if ( (object->flags & 8) != 0 )
                  bind_texture_ref((int)object->override_texture_ref);
                else
                  bind_texture_ref((int)object->group_texture_refs[v8]);
                if ( SLOBYTE(object->flags) >= 0 )
                {
                  (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)g_d3d_device + 252))(
                    g_d3d_device,
                    0,
                    24,
                    0);
                }
                else
                {
                  unk_5031F8 = LODWORD(texture_u);
                  unk_5031FC = 1.0 - texture_v;
                  (*(void (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)g_d3d_device + 148))(
                    g_d3d_device,
                    16,
                    g_object_texture_transform_matrix);
                  (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)g_d3d_device + 252))(g_d3d_device, 0, 24, 2);
                }
                if ( LODWORD(color->a) == 1065353216 || (object->group_texture_refs[v8]->flags & 0x10000) == 0 )
                {
                  (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)g_d3d_device + 200))(g_d3d_device, 27, 0);
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
                (*(void (__stdcall **)(int, _DWORD, ObjectVertexBuffer *, int))(*(_DWORD *)g_d3d_device + 332))(
                  g_d3d_device,
                  0,
                  object->render_buffers->vertex_buffer,
                  24);
                (*(void (__stdcall **)(int, int))(*(_DWORD *)g_d3d_device + 304))(g_d3d_device, 322);
                (*(void (__stdcall **)(int, ObjectIndexBufferResource *, _DWORD))(*(_DWORD *)g_d3d_device + 340))(
                  g_d3d_device,
                  object->index_buffer->buffer,
                  0);
                (*(void (__stdcall **)(int, int, _DWORD, int32_t, int32_t, int32_t))(*(_DWORD *)g_d3d_device + 284))(
                  g_d3d_device,
                  4,
                  0,
                  object->grouped_vertex_count,
                  object->group_index_starts[v8],
                  object->group_primitive_counts[v8]);
                v9 = g_object_render_pass_filter;
                g_render_triangle_count += object->group_primitive_counts[v8];
                ++g_draw_primitive_call_count;
              }
            }
          }
          else if ( after_sprites != 1 || (object->group_texture_refs[v8]->flags & 0x10000) == 0 )
          {
            goto LABEL_13;
          }
          ++v8;
        }
        while ( v8 < object->texture_group_count );
      }
      return render_object_toon((int)object, (int)v7, v8, (int)object, (int)matrix, v11, v12);
    }
  }
  return result;
}

