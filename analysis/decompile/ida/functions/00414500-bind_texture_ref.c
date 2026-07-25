/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: bind_texture_ref @ 0x414500 */
/* selector: bind_texture_ref */

// Binds one texture ref, skips redundant binds through the cached current-texture lane, and applies the texture-stage wrap-vs-clamp state from the ref flags. Cross-port Android symbols match this helper to `G0BindTexture(int)`.
void __cdecl bind_texture_ref(TextureRef *texture)
{
  int32_t v1; // eax
  Direct3DDevice8Vtbl *vtbl; // ecx

  if ( texture != g_current_texture_ref )
  {
    g_current_texture_ref = texture;
    v1 = g_direct3d_renderer.device->vtbl->SetTexture(
           g_direct3d_renderer.device,
           0,
           g_d3d_texture_slots[texture->slot_index]);
    ++g_texture_bind_call_count;
    if ( v1 )
    {
      report_errorf("SetTexture Failed %s", texture->name);
    }
    else
    {
      vtbl = g_direct3d_renderer.device->vtbl;
      if ( (texture->flags & 0x1000) != 0 )
      {
        vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 13, 1);
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 14, 1);
      }
      else
      {
        vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 13, 3);
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 14, 3);
      }
    }
  }
}
