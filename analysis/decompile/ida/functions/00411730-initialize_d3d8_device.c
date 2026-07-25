/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_d3d8_device @ 0x411730 */
/* selector: initialize_d3d8_device */

void __thiscall initialize_d3d8_device(Direct3DRenderer *renderer, uint8_t use_present_interval_one)
{
  Direct3D8 *v3; // eax
  uint32_t v4; // edx
  uint32_t depth_stencil_format; // ecx
  HWND v6; // ecx
  uint32_t multisample_type; // edx
  uint32_t requested_height; // ecx
  Direct3D8 *d3d; // eax
  Direct3D8 *v10; // eax
  _DWORD v11[3]; // [esp+8h] [ebp-10h] BYREF
  uint32_t v12; // [esp+14h] [ebp-4h]

  v3 = (Direct3D8 *)Direct3DCreate8(220);
  renderer->d3d = v3;
  if ( !v3 )
    abort_startup_with_3d_error();
  if ( renderer->d3d->vtbl->GetAdapterDisplayMode(renderer->d3d, 0, (D3DDisplayMode *)v11) < 0 )
    abort_startup_with_3d_error();
  v4 = v12;
  renderer->display_format = v12;
  memset(&renderer->present, 0, sizeof(renderer->present));
  depth_stencil_format = renderer->depth_stencil_format;
  renderer->present.windowed = 1;
  renderer->present.swap_effect = 4;
  renderer->present.enable_auto_depth_stencil = 1;
  renderer->present.auto_depth_stencil_format = depth_stencil_format;
  v6 = g_main_window;
  renderer->present.back_buffer_format = v4;
  renderer->present.device_window = v6;
  multisample_type = renderer->multisample_type;
  renderer->present.back_buffer_width = renderer->requested_width;
  requested_height = renderer->requested_height;
  renderer->present.multisample_type = multisample_type;
  renderer->present.back_buffer_height = requested_height;
  renderer->present.fullscreen_refresh_rate_hz = 0;
  if ( use_present_interval_one )
    renderer->present.fullscreen_presentation_interval = 1;
  else
    renderer->present.fullscreen_presentation_interval = 0;
  d3d = renderer->d3d;
  renderer->create_device_flags = 64;
  if ( d3d->vtbl->CreateDevice(d3d, 0, 1, g_main_window, 64, &renderer->present, &renderer->device) < 0 )
  {
    v10 = renderer->d3d;
    renderer->create_device_flags = 32;
    if ( v10->vtbl->CreateDevice(v10, 0, 1, g_main_window, 32, &renderer->present, &renderer->device) < 0 )
      abort_startup_with_3d_error();
  }
  debug_report_stub();
  reset_direct3d_render_state(renderer);
  query_direct3d_device_caps(renderer);
  renderer->device_initialized = 1;
}
