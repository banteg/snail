/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: set_immediate_blend_mode @ 0x412e50 */
/* selector: set_immediate_blend_mode */

// Void immediate-quad half of the Windows G0SetBlend split: programs the alpha-blend render state selected by draw_textured_quad_immediate. Its sole caller discards EAX.
void __cdecl set_immediate_blend_mode(int32_t blend_mode)
{
  switch ( blend_mode )
  {
    case 0:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 0);
      return;
    case 1:
    case 4:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 6);
      return;
    case 2:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 1);
      goto LABEL_11;
    case 3:
    case 7:
    case 15:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      goto LABEL_11;
    case 5:
    case 8:
    case 11:
    case 13:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      goto LABEL_9;
    case 6:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 2);
LABEL_9:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 2);
      break;
    case 9:
    case 12:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 2);
      break;
    case 14:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 10);
LABEL_11:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 6);
      break;
    default:
      return;
  }
}
