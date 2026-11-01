/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: begin_sprite_depth_render_state @ 0x413540 */
/* selector: begin_sprite_depth_render_state */

// Exact Windows `G0RenderSprite3DStart()` platform implementation: saves the active Direct3D view transform, installs identity view and texture transforms, and prepares texture-stage state before `render_game_frame` depth-sorts sprites. Android and iOS preserve the same GL.o render-pass boundary with OpenGL state.
int32_t begin_sprite_depth_render_state()
{
  _DWORD v1[16]; // [esp+18h] [ebp-40h] BYREF

  memset(&v1[11], 0, 16);
  memset(&v1[6], 0, 16);
  memset(&v1[1], 0, 16);
  v1[15] = 1065353216;
  v1[10] = 1065353216;
  v1[5] = 1065353216;
  v1[0] = 1065353216;
  g_direct3d_renderer.device->vtbl->GetTransform(
    g_direct3d_renderer.device,
    2,
    (TransformMatrix *)&g_saved_d3d_view_transform);
  g_direct3d_renderer.device->vtbl->SetTransform(g_direct3d_renderer.device, 2, (TransformMatrix *)v1);
  g_direct3d_renderer.device->vtbl->SetTransform(g_direct3d_renderer.device, 256, (TransformMatrix *)v1);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 13, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 14, 3);
  return g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 24, 0);
}
