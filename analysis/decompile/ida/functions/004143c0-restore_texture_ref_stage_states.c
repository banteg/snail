/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: restore_texture_ref_stage_states @ 0x4143c0 */
/* selector: restore_texture_ref_stage_states */

// Direct3DRenderer member that rebinds every registered D3D texture after a device reset and reapplies alpha and wrap texture-stage state from cRTexture flags.
void __thiscall restore_texture_ref_stage_states(Direct3DRenderer *renderer)
{
  int v1; // edi
  int32_t v2; // esi
  TextureRef *entries; // edi
  Direct3DDevice8Vtbl *vtbl; // ecx
  Direct3DDevice8 *device; // eax
  int v7; // [esp-4h] [ebp-Ch]
  int v8; // [esp+0h] [ebp-8h]

  v2 = 0;
  if ( g_texture_refs.count > 0 )
  {
    v7 = v1;
    entries = g_texture_refs.entries;
    do
    {
      ((void (__stdcall *)(Direct3DDevice8 *, _DWORD, Direct3DTexture8 *, int))renderer->device->vtbl->SetTexture)(
        renderer->device,
        0,
        g_d3d_texture_slots[v2],
        v7);
      g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 16, 3);
      g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 17, 3);
      if ( (entries->flags & 0x10000) != 0 )
      {
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 1, 4);
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 2, 2);
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 3, 0);
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 4, 4);
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 5, 2);
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 6, 0);
      }
      vtbl = g_direct3d_renderer.device->vtbl;
      if ( (entries->flags & 0x1000) != 0 )
      {
        ((void (__stdcall *)(Direct3DDevice8 *, _DWORD, int, int, int))vtbl->SetTextureStageState)(
          g_direct3d_renderer.device,
          0,
          13,
          1,
          v8);
        device = g_direct3d_renderer.device;
        v8 = 1;
      }
      else
      {
        ((void (__stdcall *)(Direct3DDevice8 *, _DWORD, int, int, int))vtbl->SetTextureStageState)(
          g_direct3d_renderer.device,
          0,
          13,
          3,
          v8);
        device = g_direct3d_renderer.device;
        v8 = 3;
      }
      v7 = 14;
      ((void (__stdcall *)(Direct3DDevice8 *, _DWORD))g_direct3d_renderer.device->vtbl->SetTextureStageState)(device, 0);
      ++v2;
      ++entries;
    }
    while ( v2 < g_texture_refs.count );
  }
}
