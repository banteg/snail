/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_direct3d_renderer_defaults @ 0x411630 */
/* selector: initialize_direct3d_renderer_defaults */

// Seeds authored mouse client/clip rectangles and initializes the Direct3D renderer's inactive interface pointers and default presentation fields.
void __thiscall initialize_direct3d_renderer_defaults(Direct3DRenderer *renderer)
{
  g_mouse_uncaptured_clip_bottom = (__int64)g_authored_view_height;
  g_mouse_uncaptured_clip_top = 0;
  g_mouse_uncaptured_clip_rect = 0;
  g_mouse_uncaptured_clip_right = (__int64)g_authored_view_width;
  unk_4B7778 = (__int64)g_authored_view_width;
  unk_4B777C = (__int64)g_authored_view_height;
  g_mouse_captured_client_top = 0;
  g_mouse_captured_client_rect = 0;
  ((void (__stdcall *)(void *, _DWORD, _DWORD, _DWORD))AdjustWindowRectEx)(
    &g_mouse_uncaptured_clip_rect,
    g_windowed_adjust_style,
    0,
    0);
  renderer->d3d = nullptr;
  renderer->device = nullptr;
  renderer->requested_width = 640;
  renderer->requested_height = 480;
  renderer->unknown_bcb4 = 23;
  renderer->depth_stencil_format = 80;
  renderer->create_device_flags = 32;
  renderer->multisample_type = 0;
  renderer->unknown_bcb0 = 0;
  renderer->device_initialized = 0;
}
