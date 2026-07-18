/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_sprite_quad @ 0x4137f0 */
/* selector: draw_sprite_quad */

// Builds and submits one textured sprite quad from the sprite color, scale, angle, and stretch lanes. The star-field pass at `initialize_star_field` and `update_star_positions` reaches this helper through the shared sprite renderer.
int __cdecl draw_sprite_quad(Vec3 *position, Sprite *sprite)
{
  Sprite *v2; // esi
  double v3; // st7
  double v4; // st6
  double v5; // st6
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st6
  double v10; // st6
  int result; // eax
  TextureRef *texture_ref; // [esp+20h] [ebp-54h]
  float v13; // [esp+20h] [ebp-54h]
  float v14; // [esp+20h] [ebp-54h]
  ColorBGRA8 out; // [esp+2Ch] [ebp-48h] BYREF
  float v16; // [esp+30h] [ebp-44h]
  int v17[16]; // [esp+34h] [ebp-40h] BYREF
  ObjectRenderVertex *vertices; // [esp+78h] [ebp+4h] SPLIT BYREF
  Vec3 v19; // 0:^18.12

  v19 = *position;
  memset(&v17[11], 0, 16);
  memset(&v17[6], 0, 16);
  memset(&v17[1], 0, 16);
  v17[15] = 1065353216;
  v17[10] = 1065353216;
  v17[5] = 1065353216;
  v17[0] = 1065353216;
  D3DXMatrixTranslation((int)v17, v19.x, v19.y, v19.z);
  g_direct3d_renderer.device->vtbl->SetTransform(g_direct3d_renderer.device, 2, (TransformMatrix *)v17);
  v2 = sprite;
  texture_ref = sprite->texture_ref;
  *(float *)&sprite = (1.0 - sprite->progress) * sprite->size_start + sprite->size_end * sprite->progress;
  bind_texture_ref(texture_ref);
  configure_sprite_render_state((int)v2);
  if ( (v2->flags & 0x1000) != 0 )
    v16 = 1.0;
  else
    v16 = (1.0 - v2->progress) * v2->color.a;
  noop_this_constructor(&out);
  pack_color_rgba_u8((tColourSmall *)&out, &v2->color);
  out.a = (__int64)(v16 * 255.0);
  g_direct3d_renderer.renderer_state->vertex_buffer->vtbl->Lock(
    g_direct3d_renderer.renderer_state->vertex_buffer,
    0,
    96,
    (void **)&vertices,
    0);
  if ( v2->facing_angle == 0.0 )
  {
    v3 = -*(float *)&sprite;
    vertices->x = v3;
    vertices->y = *(float *)&sprite;
    v4 = *(float *)&sprite;
    vertices->z = 0.0;
    vertices->u = 0.0;
    vertices->v = 0.0;
    vertices->diffuse = (uint32_t)out;
    vertices[1].x = v4;
    vertices[1].y = *(float *)&sprite;
    v5 = *(float *)&sprite;
    vertices[1].z = 0.0;
    vertices[1].u = 1.0;
    vertices[1].v = 0.0;
    vertices[1].diffuse = (uint32_t)out;
    vertices[2].x = v5;
    vertices[2].y = v3;
    vertices[2].z = 0.0;
    vertices[2].u = 1.0;
    vertices[2].v = 1.0;
    vertices[2].diffuse = (uint32_t)out;
    vertices[3].x = v3;
  }
  else
  {
    v13 = v2->facing_angle + 0.78539819;
    v6 = cosine(v13);
    v16 = v6 * *(float *)&sprite * 1.414;
    v14 = v2->facing_angle + 0.78539819;
    v7 = sine(v14);
    v8 = v7 * *(float *)&sprite * 1.414;
    vertices->x = -v8;
    vertices->y = v16;
    v9 = v16;
    vertices->z = 0.0;
    vertices->u = 0.0;
    vertices->v = 0.0;
    vertices->diffuse = (uint32_t)out;
    vertices[1].x = v9;
    vertices[1].y = v8;
    vertices[1].z = 0.0;
    vertices[1].u = 1.0;
    vertices[1].v = 0.0;
    vertices[1].diffuse = (uint32_t)out;
    vertices[2].x = v8;
    vertices[2].y = -v16;
    v10 = v16;
    vertices[2].z = 0.0;
    vertices[2].u = 1.0;
    vertices[2].v = 1.0;
    vertices[2].diffuse = (uint32_t)out;
    vertices[3].x = -(v10 * v2->corner_scale);
    v3 = -(v8 * v2->corner_scale);
  }
  vertices[3].y = v3;
  vertices[3].z = 0.0;
  vertices[3].u = 0.0;
  vertices[3].v = 1.0;
  vertices[3].diffuse = (uint32_t)out;
  g_direct3d_renderer.renderer_state->vertex_buffer->vtbl->Unlock(g_direct3d_renderer.renderer_state->vertex_buffer);
  g_direct3d_renderer.device->vtbl->SetStreamSource(
    g_direct3d_renderer.device,
    0,
    g_direct3d_renderer.renderer_state->vertex_buffer,
    24);
  g_direct3d_renderer.device->vtbl->SetVertexShader(g_direct3d_renderer.device, 322);
  result = g_direct3d_renderer.device->vtbl->DrawPrimitive(g_direct3d_renderer.device, 6, 0, 2);
  g_render_triangle_count += 2;
  ++g_draw_primitive_call_count;
  if ( result )
    return report_errorf(aDrawPrimitiveF);
  return result;
}
