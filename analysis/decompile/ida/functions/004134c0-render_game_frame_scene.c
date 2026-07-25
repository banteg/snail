/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_game_frame_scene @ 0x4134c0 */
/* selector: render_game_frame_scene */

// Clears the backbuffer, opens a Direct3D scene, updates display-mode view state, renders one game frame, and closes the scene.
void __cdecl render_game_frame_scene()
{
  ((void (__stdcall *)(Direct3DDevice8 *, _DWORD, _DWORD, int, int, int, _DWORD))g_direct3d_renderer.device->vtbl->Clear)(
    g_direct3d_renderer.device,
    0,
    0,
    2,
    -16777216,
    1065353216,
    0);
  g_direct3d_renderer.device->vtbl->BeginScene(g_direct3d_renderer.device);
  g_render_successful_primitive_count = 0;
  update_display_mode_view_state(&g_display_mode_state);
  render_game_frame(g_game_base);
  g_direct3d_renderer.device->vtbl->EndScene(g_direct3d_renderer.device);
}
