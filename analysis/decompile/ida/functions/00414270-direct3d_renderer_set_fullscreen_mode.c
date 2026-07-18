/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: direct3d_renderer_set_fullscreen_mode @ 0x414270 */
/* selector: direct3d_renderer_set_fullscreen_mode */

// Direct3DRenderer member that owns the fullscreen presentation-parameter transition, resets the device and render state, restores the saved window placement, and recenters the cursor.
void __thiscall direct3d_renderer_set_fullscreen_mode(Direct3DRenderer *renderer, uint8_t enabled)
{
  uint32_t display_format; // edx

  if ( renderer->device_initialized )
  {
    renderer->present.windowed = enabled == 0;
    if ( enabled )
    {
      ((void (__stdcall *)(int, struct AnimationDispatchState *))GetWindowRect)(g_main_window, &g_saved_window_rect);
      g_saved_window_rect_valid = 1;
      renderer->present.fullscreen_refresh_rate_hz = 0;
      renderer->present.fullscreen_presentation_interval = 1;
      renderer->present.back_buffer_format = 22;
    }
    else
    {
      display_format = renderer->display_format;
      renderer->present.fullscreen_refresh_rate_hz = 0;
      renderer->present.fullscreen_presentation_interval = 0;
      renderer->present.back_buffer_format = display_format;
    }
    debug_report_stub();
    renderer->device->vtbl->Reset(renderer->device, &renderer->present);
    restore_texture_ref_stage_states(renderer);
    reset_direct3d_render_state(renderer);
    if ( enabled || g_saved_window_rect_valid != 1 )
      ShowCursor(0);
    else
      ((void (__stdcall *)(int, _DWORD, int32_t, _DWORD, int, int, int))SetWindowPos)(
        g_main_window,
        0,
        g_saved_window_rect.active,
        unk_50326C,
        unk_503270 - g_saved_window_rect.active,
        unk_503274 - unk_50326C,
        64);
    ((void (__stdcall *)(int, int))ShowWindow)(g_main_window, 5);
    ((void (__stdcall *)(int))SetForegroundWindow)(g_main_window);
    ((void (__stdcall *)(int))SetFocus)(g_main_window);
    SetCursorPos((__int64)(g_authored_view_width * 0.5), (__int64)(g_authored_view_height * 0.5));
  }
}
