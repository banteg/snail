/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: end_overlay_render_state @ 0x411de0 */
/* selector: end_overlay_render_state */

// Restores the saved Direct3D projection and view transforms after an orthographic overlay/font render pass.
int32_t end_overlay_render_state()
{
  g_direct3d_renderer.device->vtbl->SetTransform(
    g_direct3d_renderer.device,
    3,
    (TransformMatrix *)&g_saved_d3d_projection_transform);
  return g_direct3d_renderer.device->vtbl->SetTransform(
           g_direct3d_renderer.device,
           2,
           (TransformMatrix *)&g_saved_d3d_view_transform);
}
