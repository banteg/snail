/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_blend_mode @ 0x412d00 */
/* selector: set_blend_mode */

// Void object-rendering half of the Windows G0SetBlend split: maps one render blend preset through the shared lookup table and programs the matching alpha-blend state. Its sole caller discards EAX.
void __cdecl set_blend_mode(int32_t blend_mode)
{
  switch ( blend_mode )
  {
    case 0:
    case 6:
    case 9:
    case 12:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 6);
      break;
    case 1:
    case 8:
    case 20:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      goto LABEL_7;
    case 5:
    case 13:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 2);
      break;
    case 7:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 2);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 2);
      break;
    case 19:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 2);
LABEL_7:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 6);
      break;
    default:
      return;
  }
}
