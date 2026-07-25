/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_loading_screen @ 0x418b50 */
/* selector: initialize_loading_screen */

// Void cRLoadingBar::Init(): loads the loading-screen textures, seeds the full-screen and progress quads, and resets the loader counters. Startup discards EAX; the remaining 83.00% source shape is honest register scheduling, not return uncertainty.
void __thiscall initialize_loading_screen(LoadingBar *loading_bar)
{
  void *archive_data_base; // edi
  int32_t texture_from_file_in_memory; // eax
  void *v4; // edi
  int32_t texture_from_file; // eax
  LoadingQuadVertexView *background_quad; // [esp+8Ch] [ebp-8h] BYREF
  int out_size; // [esp+90h] [ebp-4h] BYREF

  g_runtime_config.last_loading_budget = 1276;
  if ( is_archive_index_loaded() )
  {
    archive_data_base = get_archive_data_base();
    load_file_bytes_from_archive_or_fs((char *)WideCharStr, archive_data_base, &out_size);
    texture_from_file_in_memory = d3dx_create_texture_from_file_in_memory_ex(
                                    g_direct3d_renderer.device,
                                    archive_data_base,
                                    out_size,
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
  g_direct3d_renderer.device->vtbl->SetTexture(g_direct3d_renderer.device, 0, g_loading_background_texture);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 16, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 17, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 13, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 14, 3);
  if ( is_archive_index_loaded() )
  {
    v4 = get_archive_data_base();
    load_file_bytes_from_archive_or_fs((char *)aSpritesLoading_0, v4, &out_size);
    texture_from_file = d3dx_create_texture_from_file_in_memory_ex(
                          g_direct3d_renderer.device,
                          v4,
                          out_size,
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
  g_direct3d_renderer.device->vtbl->SetTexture(g_direct3d_renderer.device, 0, g_loading_bar_on_texture);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 16, 3);
  g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 17, 3);
  g_loading_background_vertex_buffer = create_vertex_buffer(&g_direct3d_renderer.vertex_buffer_factory, 4, 258);
  g_loading_bar_vertex_buffer = create_vertex_buffer(&g_direct3d_renderer.vertex_buffer_factory, 4, 258);
  g_loading_background_vertex_buffer->vertex_buffer->vtbl->Lock(
    g_loading_background_vertex_buffer->vertex_buffer,
    0,
    80,
    (void **)&background_quad,
    0);
  background_quad->vertices[0].x = 0.0;
  background_quad->vertices[0].y = 0.0;
  background_quad->vertices[0].z = 0.0;
  background_quad->vertices[0].u = 0.0;
  background_quad->vertices[0].v = 0.0;
  background_quad->vertices[1].x = 640.0;
  background_quad->vertices[1].y = 0.0;
  background_quad->vertices[1].z = 0.0;
  background_quad->vertices[1].u = 1.0;
  background_quad->vertices[1].v = 0.0;
  background_quad->vertices[2].x = 640.0;
  background_quad->vertices[2].y = 480.0;
  background_quad->vertices[2].z = 0.0;
  background_quad->vertices[2].u = 1.0;
  background_quad->vertices[2].v = 1.0;
  background_quad->vertices[3].x = 0.0;
  background_quad->vertices[3].y = 480.0;
  background_quad->vertices[3].z = 0.0;
  background_quad->vertices[3].u = 0.0;
  background_quad->vertices[3].v = 1.0;
  g_loading_bar_vertex_buffer->vertex_buffer->vtbl->Unlock(g_loading_bar_vertex_buffer->vertex_buffer);
  begin_overlay_render_state();
  loading_bar->last_loading_budget = 0;
  loading_bar->previous_percent = 0;
  loading_bar->active = 1;
}
