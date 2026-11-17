/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: direct3d_renderer_set_cull_mode @ 0x411700 */
/* selector: direct3d_renderer_set_cull_mode */

// Renderer-wrapper method that maps the one-bit cull selector to Direct3D render state 0x16 values before object rendering.
int32_t __thiscall direct3d_renderer_set_cull_mode(Direct3DRenderer *renderer, uint8_t cull_front)
{
  Direct3DDevice8 *device; // eax

  device = renderer->device;
  if ( cull_front != 0 )
    return device->vtbl->SetRenderState(device, 22, 3);
  else
    return device->vtbl->SetRenderState(device, 22, 1);
}
