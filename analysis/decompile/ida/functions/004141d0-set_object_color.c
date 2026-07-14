/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_object_color @ 0x4141d0 */
/* selector: set_object_color */

// Packs one object RGBA tint and, when grouped vertex buffers exist, rewrites the per-vertex diffuse colour lane so the next object draw uses that colour. Cross-port Android symbols match this helper's role to `G0SetColour(tColourSmall*)`.
void __cdecl set_object_color(Object *object, Color4f color)
{
  int32_t v2; // eax
  int v3; // ecx
  ColorBGRA8 out; // [esp+14h] [ebp-8h] BYREF
  int v5; // [esp+18h] [ebp-4h] BYREF

  noop_this_constructor(&out);
  pack_color_rgba_u8((tColourSmall *)&out, &color);
  if ( (object->flags & 0x80000) != 0 )
  {
    object->render_buffers->vertex_buffer->vtbl->Lock(
      object->render_buffers->vertex_buffer,
      0,
      24 * g_object_grouped_vertex_cursor,
      (void **)&v5,
      0);
    v2 = 0;
    if ( object->grouped_vertex_count > 0 )
    {
      v3 = 0;
      do
      {
        ++v2;
        *(ColorBGRA8 *)(v3 + v5 + 12) = out;
        v3 += 24;
      }
      while ( v2 < object->grouped_vertex_count );
    }
    object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);
  }
}

