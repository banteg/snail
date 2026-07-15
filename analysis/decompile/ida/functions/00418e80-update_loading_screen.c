/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_loading_screen @ 0x418e80 */
/* selector: update_loading_screen */

// Exact void cRLoadingBar::AI(): advances the normalized percentage, draws the loading background, and clips the fill quad into the recovered 192x289 to 448x321 window. All three Windows callers discard EAX.
void __thiscall update_loading_screen(LoadingBar *loading_bar)
{
  int32_t last_loading_budget; // ecx
  int32_t v3; // edi
  double v4; // st7
  double v5; // st7
  double v6; // st6
  double v7; // st7
  int v8; // [esp+88h] [ebp-8h] BYREF
  float v9; // [esp+8Ch] [ebp-4h]

  if ( !loading_bar->active )
    return;
  ++loading_bar->last_loading_budget;
  last_loading_budget = g_runtime_config.last_loading_budget;
  if ( !g_runtime_config.last_loading_budget )
  {
    last_loading_budget = 1;
    g_runtime_config.last_loading_budget = 1;
  }
  v8 = 100 * loading_bar->last_loading_budget / last_loading_budget;
  v3 = v8;
  if ( v8 >= 0 )
  {
    if ( v8 <= 100 )
      goto LABEL_9;
    v3 = 100;
  }
  else
  {
    v3 = 0;
  }
  v8 = v3;
LABEL_9:
  if ( v3 - loading_bar->previous_percent >= 1 )
  {
    v9 = (double)v8 * 0.92000002;
    if ( v3 > 98 )
      v9 = 100.0;
    ((void (__stdcall *)(Direct3DDevice8 *, _DWORD, _DWORD, int, int, int, _DWORD))g_direct3d_renderer.device->vtbl->Clear)(
      g_direct3d_renderer.device,
      0,
      0,
      2,
      -16777216,
      1065353216,
      0);
    g_direct3d_renderer.device->vtbl->BeginScene(g_direct3d_renderer.device);
    g_direct3d_renderer.device->vtbl->SetTexture(
      g_direct3d_renderer.device,
      0,
      (Direct3DTexture8 *)g_loading_background_texture);
    g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 13, 3);
    g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 14, 3);
    g_direct3d_renderer.device->vtbl->SetStreamSource(
      g_direct3d_renderer.device,
      0,
      *(ObjectVertexBuffer **)(g_loading_background_vertex_buffer + 8),
      20);
    g_direct3d_renderer.device->vtbl->SetVertexShader(g_direct3d_renderer.device, 258);
    g_direct3d_renderer.device->vtbl->DrawPrimitive(g_direct3d_renderer.device, 6, 0, 2);
    (*(void (__stdcall **)(_DWORD, _DWORD, int, int *, _DWORD))(**(_DWORD **)(g_loading_bar_vertex_buffer + 8) + 44))(
      *(_DWORD *)(g_loading_bar_vertex_buffer + 8),
      0,
      80,
      &v8,
      0);
    v4 = v9;
    *(_DWORD *)v8 = 1128267776;
    *(_DWORD *)(v8 + 4) = 1133543424;
    v5 = v4 * 2.5599999 + 192.0;
    *(_DWORD *)(v8 + 8) = 0;
    *(_DWORD *)(v8 + 12) = 0;
    *(_DWORD *)(v8 + 16) = 0;
    *(float *)(v8 + 20) = v5;
    v6 = v9 * 0.0099999998;
    *(_DWORD *)(v8 + 24) = 1133543424;
    *(_DWORD *)(v8 + 28) = 0;
    v9 = v6;
    *(float *)(v8 + 32) = v6;
    *(_DWORD *)(v8 + 36) = 0;
    *(float *)(v8 + 40) = v5;
    v7 = v9;
    *(_DWORD *)(v8 + 44) = 1134592000;
    *(_DWORD *)(v8 + 48) = 0;
    *(float *)(v8 + 52) = v7;
    *(_DWORD *)(v8 + 56) = 1065353216;
    *(_DWORD *)(v8 + 60) = 1128267776;
    *(_DWORD *)(v8 + 64) = 1134592000;
    *(_DWORD *)(v8 + 68) = 0;
    *(_DWORD *)(v8 + 72) = 0;
    *(_DWORD *)(v8 + 76) = 1065353216;
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(g_loading_bar_vertex_buffer + 8) + 48))(*(_DWORD *)(g_loading_bar_vertex_buffer + 8));
    g_direct3d_renderer.device->vtbl->SetTexture(
      g_direct3d_renderer.device,
      0,
      (Direct3DTexture8 *)g_loading_bar_on_texture);
    g_direct3d_renderer.device->vtbl->SetStreamSource(
      g_direct3d_renderer.device,
      0,
      *(ObjectVertexBuffer **)(g_loading_bar_vertex_buffer + 8),
      20);
    g_direct3d_renderer.device->vtbl->SetVertexShader(g_direct3d_renderer.device, 258);
    g_direct3d_renderer.device->vtbl->DrawPrimitive(g_direct3d_renderer.device, 6, 0, 2);
    g_direct3d_renderer.device->vtbl->EndScene(g_direct3d_renderer.device);
    present_backbuffer();
    loading_bar->previous_percent = v3;
  }
}
