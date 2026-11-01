/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: begin_overlay_render_state @ 0x411e10 */
/* selector: begin_overlay_render_state */

// Saves the current Direct3D projection and view transforms, installs an orthographic overlay projection and translated view matrix, and disables depth/fog state before overlay or font rendering.
int32_t begin_overlay_render_state()
{
  _DWORD v1[16]; // [esp+50h] [ebp-80h] BYREF
  int v2[16]; // [esp+90h] [ebp-40h] BYREF

  g_direct3d_renderer.device->vtbl->GetTransform(
    g_direct3d_renderer.device,
    3,
    (TransformMatrix *)&g_saved_d3d_projection_transform);
  g_direct3d_renderer.device->vtbl->GetTransform(
    g_direct3d_renderer.device,
    2,
    (TransformMatrix *)&g_saved_d3d_view_transform);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 13, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 14, 3);
  build_orthographic_projection_matrix((float *)v2, 640.0, -480.0, 0.0, 1.0);
  memset(&v1[11], 0, 16);
  memset(&v1[6], 0, 16);
  memset(&v1[1], 0, 16);
  v1[15] = 1065353216;
  v1[10] = 1065353216;
  v1[5] = 1065353216;
  v1[0] = 1065353216;
  g_direct3d_renderer.device->vtbl->SetTransform(g_direct3d_renderer.device, 3, (TransformMatrix *)v2);
  g_direct3d_renderer.device->vtbl->SetTransform(g_direct3d_renderer.device, 256, (TransformMatrix *)v1);
  D3DXMatrixTranslation((int)v1, -320.60001, -240.60001, 0.0);
  g_direct3d_renderer.device->vtbl->SetTransform(g_direct3d_renderer.device, 2, (TransformMatrix *)v1);
  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 7, 0);
  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 14, 0);
  return g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 137, 0);
}
