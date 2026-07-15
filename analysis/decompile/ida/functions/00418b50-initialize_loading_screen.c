/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_loading_screen @ 0x418b50 */
/* selector: initialize_loading_screen */

// Void cRLoadingBar::Init(): loads the loading-screen textures, seeds the full-screen and progress quads, and resets the loader counters. Startup discards EAX; the remaining 83.00% source shape is honest register scheduling, not return uncertainty.
void __thiscall initialize_loading_screen(LoadingBar *loading_bar)
{
  _BYTE *archive_data_base; // edi
  int32_t texture_from_file_in_memory; // eax
  _BYTE *v4; // edi
  int32_t texture_from_file; // eax
  _DWORD *v6; // [esp+8Ch] [ebp-8h] BYREF
  int v7; // [esp+90h] [ebp-4h] BYREF

  g_runtime_config.last_loading_budget = 1276;
  if ( is_archive_index_loaded() )
  {
    archive_data_base = (_BYTE *)get_archive_data_base();
    load_file_bytes_from_archive_or_fs((char *)WideCharStr, archive_data_base, (CompletionResultScreen *)&v7);
    texture_from_file_in_memory = d3dx_create_texture_from_file_in_memory_ex(
                                    g_direct3d_renderer.device,
                                    archive_data_base,
                                    v7,
                                    0,
                                    0,
                                    1u,
                                    0,
                                    0x15u,
                                    1u,
                                    3u,
                                    3u,
                                    0xFF00FF00,
                                    nullptr,
                                    nullptr,
                                    (void **)&g_loading_background_texture);
  }
  else
  {
    texture_from_file_in_memory = d3dx_create_texture_from_file_ex(
                                    g_direct3d_renderer.device,
                                    (char *)WideCharStr,
                                    0,
                                    0,
                                    1u,
                                    0,
                                    0x15u,
                                    1u,
                                    3u,
                                    3u,
                                    0xFF00FF00,
                                    nullptr,
                                    nullptr,
                                    (void **)&g_loading_background_texture);
  }
  if ( texture_from_file_in_memory < 0 )
  {
    report_errorf(aFailedToCreate_0);
    d3dx_create_texture_from_file(
      g_direct3d_renderer.device,
      (char *)aSpritesDebugTg,
      (void **)&g_loading_background_texture);
  }
  g_direct3d_renderer.device->vtbl->SetTexture(
    g_direct3d_renderer.device,
    0,
    (Direct3DTexture8 *)g_loading_background_texture);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 16, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 17, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 13, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 14, 3);
  if ( is_archive_index_loaded() )
  {
    v4 = (_BYTE *)get_archive_data_base();
    load_file_bytes_from_archive_or_fs((char *)aSpritesLoading_0, v4, (CompletionResultScreen *)&v7);
    texture_from_file = d3dx_create_texture_from_file_in_memory_ex(
                          g_direct3d_renderer.device,
                          v4,
                          v7,
                          0,
                          0,
                          1u,
                          0,
                          0x15u,
                          1u,
                          3u,
                          3u,
                          0xFF00FF00,
                          nullptr,
                          nullptr,
                          (void **)&g_loading_bar_on_texture);
  }
  else
  {
    texture_from_file = d3dx_create_texture_from_file_ex(
                          g_direct3d_renderer.device,
                          (char *)aSpritesLoading_0,
                          0,
                          0,
                          1u,
                          0,
                          0x15u,
                          1u,
                          3u,
                          3u,
                          0xFF00FF00,
                          nullptr,
                          nullptr,
                          (void **)&g_loading_bar_on_texture);
  }
  if ( texture_from_file < 0 )
  {
    report_errorf(aFailedToCreate_1);
    d3dx_create_texture_from_file(
      g_direct3d_renderer.device,
      (char *)aSpritesDebugTg,
      (void **)&g_loading_bar_on_texture);
  }
  g_direct3d_renderer.device->vtbl->SetTexture(
    g_direct3d_renderer.device,
    0,
    (Direct3DTexture8 *)g_loading_bar_on_texture);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 16, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 17, 3);
  g_loading_background_vertex_buffer = create_vertex_buffer(&g_direct3d_renderer.vertex_buffer_factory, 4, 258);
  g_loading_bar_vertex_buffer = create_vertex_buffer(&g_direct3d_renderer.vertex_buffer_factory, 4, 258);
  (*(void (__stdcall **)(_DWORD, _DWORD, int, _DWORD **, _DWORD))(**(_DWORD **)(g_loading_background_vertex_buffer + 8)
                                                                + 44))(
    *(_DWORD *)(g_loading_background_vertex_buffer + 8),
    0,
    80,
    &v6,
    0);
  *v6 = 0;
  v6[1] = 0;
  v6[2] = 0;
  v6[3] = 0;
  v6[4] = 0;
  v6[5] = 1142947840;
  v6[6] = 0;
  v6[7] = 0;
  v6[8] = 1065353216;
  v6[9] = 0;
  v6[10] = 1142947840;
  v6[11] = 1139802112;
  v6[12] = 0;
  v6[13] = 1065353216;
  v6[14] = 1065353216;
  v6[15] = 0;
  v6[16] = 1139802112;
  v6[17] = 0;
  v6[18] = 0;
  v6[19] = 1065353216;
  (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(g_loading_bar_vertex_buffer + 8) + 48))(*(_DWORD *)(g_loading_bar_vertex_buffer
                                                                                                  + 8));
  begin_overlay_render_state();
  loading_bar->last_loading_budget = 0;
  loading_bar->previous_percent = 0;
  loading_bar->active = 1;
}
