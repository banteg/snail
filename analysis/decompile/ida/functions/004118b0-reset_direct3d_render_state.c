/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: reset_direct3d_render_state @ 0x4118b0 */
/* selector: reset_direct3d_render_state */

// Reapplies the Direct3D renderer's baseline device render states after device creation or reset.
void __thiscall reset_direct3d_render_state(Direct3DRenderer *renderer)
{
  renderer->device->vtbl->SetRenderState(renderer->device, 139, 0xFFFFFF);
  renderer->device->vtbl->SetRenderState(renderer->device, 137, 0);
  renderer->device->vtbl->SetRenderState(renderer->device, 22, 1);
  renderer->device->vtbl->SetRenderState(renderer->device, 7, 1);
  renderer->device->vtbl->SetRenderState(renderer->device, 16, 1);
  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 15, 1);
  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 24, 0);
  g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 25, 5);
}
