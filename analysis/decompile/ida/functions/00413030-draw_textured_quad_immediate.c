/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_textured_quad_immediate @ 0x413030 */
/* selector: draw_textured_quad_immediate */

// Void G0RenderFont counterpart: builds one immediate 2D textured quad in the transient UI vertex buffer, supporting explicit corner coordinates, axis-aligned size, or centered rotation before submitting the quad as a six-index primitive. All three Windows callers discard EAX.
void __cdecl draw_textured_quad_immediate(
        TextureRef *texture,
        float x0,
        float y0,
        float x1,
        float y1,
        float x2,
        float y2,
        float x3,
        float y3,
        float width,
        float height,
        float u0,
        float v0,
        float u1,
        float v1,
        tColour *color,
        int32_t blend_mode,
        float rotation)
{
  char v19; // c3
  char v21; // c3
  double v22; // st7
  double v23; // st7
  double v24; // st7
  double v25; // st6
  double v26; // st7
  int32_t v27; // eax
  float v28; // [esp+20h] [ebp-14h]
  ImmediateQuadVertexBlock *quad; // [esp+2Ch] [ebp-8h] BYREF
  ColorBGRA8 out; // [esp+30h] [ebp-4h] BYREF
  float x0a; // [esp+3Ch] [ebp+8h]
  float y0a; // [esp+40h] [ebp+Ch]
  float widtha; // [esp+5Ch] [ebp+28h]
  float widthb; // [esp+5Ch] [ebp+28h]
  float heighta; // [esp+60h] [ebp+2Ch]

  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 22, 1);
  bind_texture_ref(texture);
  set_immediate_blend_mode(blend_mode);
  noop_this_constructor(&out);
  pack_color_rgba_u8((tColourSmall *)&out, color);
  g_direct3d_renderer.renderer_state->vertex_buffer->vtbl->Lock(
    g_direct3d_renderer.renderer_state->vertex_buffer,
    0,
    96,
    (void **)&quad,
    0);
  if ( v19 )
  {
    quad->vertices[0].x = x0;
    quad->vertices[0].y = y0;
    quad->vertices[0].z = 0.0;
    quad->vertices[0].u = u0;
    quad->vertices[0].v = v0;
    if ( v21 )
    {
      quad->vertices[0].diffuse = (uint32_t)out;
      quad->vertices[1].x = x1;
      quad->vertices[1].y = y1;
      quad->vertices[1].z = 0.0;
      quad->vertices[1].u = u1;
      quad->vertices[1].v = v0;
      quad->vertices[1].diffuse = (uint32_t)out;
      quad->vertices[2].x = x2;
      quad->vertices[2].y = y2;
      quad->vertices[2].z = 0.0;
      quad->vertices[2].u = u1;
      quad->vertices[2].v = v1;
      quad->vertices[2].diffuse = (uint32_t)out;
      quad->vertices[3].x = x3;
      quad->vertices[3].y = y3;
    }
    else
    {
      v22 = x0 + width;
      quad->vertices[0].diffuse = (uint32_t)out;
      quad->vertices[1].x = v22;
      quad->vertices[1].y = y0;
      quad->vertices[1].z = 0.0;
      quad->vertices[1].u = u1;
      quad->vertices[1].v = v0;
      quad->vertices[1].diffuse = (uint32_t)out;
      quad->vertices[2].x = v22;
      v23 = y0 + height;
      quad->vertices[2].y = v23;
      quad->vertices[2].z = 0.0;
      quad->vertices[2].u = u1;
      quad->vertices[2].v = v1;
      quad->vertices[2].diffuse = (uint32_t)out;
      quad->vertices[3].x = x0;
      quad->vertices[3].y = v23;
    }
    quad->vertices[3].z = 0.0;
    quad->vertices[3].u = u0;
    quad->vertices[3].v = v1;
    quad->vertices[3].diffuse = (uint32_t)out;
  }
  else
  {
    v24 = width * 0.5;
    x0a = v24 + x0;
    v25 = height * 0.5;
    widtha = v25;
    y0a = v25 + y0;
    v28 = widtha * widtha + v24 * v24;
    heighta = square_root(v28) * 1.414;
    widthb = sine(rotation) * heighta;
    v26 = cosine(rotation) * heighta;
    quad->vertices[0].x = widthb + x0a;
    quad->vertices[0].y = v26 + y0a;
    quad->vertices[0].z = 0.0;
    quad->vertices[0].u = u0;
    quad->vertices[0].v = v0;
    quad->vertices[0].diffuse = (uint32_t)out;
    quad->vertices[1].x = x0a - v26;
    quad->vertices[1].y = widthb + y0a;
    quad->vertices[1].z = 0.0;
    quad->vertices[1].u = u1;
    quad->vertices[1].v = v0;
    quad->vertices[1].diffuse = (uint32_t)out;
    quad->vertices[2].x = x0a - widthb;
    quad->vertices[2].y = y0a - v26;
    quad->vertices[2].z = 0.0;
    quad->vertices[2].u = u1;
    quad->vertices[2].v = v1;
    quad->vertices[2].diffuse = (uint32_t)out;
    quad->vertices[3].x = v26 + x0a;
    quad->vertices[3].y = y0a - widthb;
    quad->vertices[3].z = 0.0;
    quad->vertices[3].u = u0;
    quad->vertices[3].v = v1;
    quad->vertices[3].diffuse = (uint32_t)out;
  }
  g_direct3d_renderer.renderer_state->vertex_buffer->vtbl->Unlock(g_direct3d_renderer.renderer_state->vertex_buffer);
  g_direct3d_renderer.device->vtbl->SetStreamSource(
    g_direct3d_renderer.device,
    0,
    g_direct3d_renderer.renderer_state->vertex_buffer,
    24);
  g_direct3d_renderer.device->vtbl->SetVertexShader(g_direct3d_renderer.device, 322);
  v27 = g_direct3d_renderer.device->vtbl->DrawPrimitive(g_direct3d_renderer.device, 6, 0, 2);
  g_render_triangle_count += 2;
  ++g_draw_primitive_call_count;
  if ( v27 )
    report_errorf(aDrawPrimitiveF);
  else
    ++g_render_successful_primitive_count;
}
