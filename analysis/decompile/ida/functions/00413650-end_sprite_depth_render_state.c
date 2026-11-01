/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: end_sprite_depth_render_state @ 0x413650 */
/* selector: end_sprite_depth_render_state */

// Exact Windows `G0RenderSprite3DEnd()` platform implementation: restores the Direct3D view transform saved by `G0RenderSprite3DStart()` after the sprite depth bucket pass. Android and iOS preserve the same GL.o pass terminator while flushing and dismantling their OpenGL sprite batch.
int32_t end_sprite_depth_render_state()
{
  return g_direct3d_renderer.device->vtbl->SetTransform(
           g_direct3d_renderer.device,
           2,
           (TransformMatrix *)&g_saved_d3d_view_transform);
}
