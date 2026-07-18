/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: configure_sprite_render_state @ 0x413670 */
/* selector: configure_sprite_render_state */

// Chooses the sprite render-state preset from the sprite draw-mode lane at `+0x28` before one sprite quad is submitted.
int __cdecl configure_sprite_render_state(Sprite *sprite)
{
  int result; // eax

  result = sprite->draw_mode;
  switch ( result )
  {
    case 0:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      result = g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 6);
      break;
    case 1:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 1);
      result = g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 6);
      break;
    case 2:
      result = g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 0);
      break;
    case 9:
    case 10:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      result = g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 2);
      break;
    case 13:
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 27, 1);
      g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 19, 5);
      result = g_direct3d_renderer.device->vtbl->SetRenderState(g_direct3d_renderer.device, 20, 3);
      break;
    default:
      return result;
  }
  return result;
}
