/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_fullscreen_mode @ 0x414260 */
/* selector: set_fullscreen_mode */

// Switches the renderer's display mode between windowed (`0`) and fullscreen (`1`) through the shared device wrapper, updates the saved window rectangle bookkeeping, and recenters the cursor after the mode change.
void __cdecl set_fullscreen_mode(uint8_t enabled)
{
  direct3d_renderer_set_fullscreen_mode(&g_direct3d_renderer, enabled);
}
