/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_cull_mode @ 0x4129f0 */
/* selector: set_cull_mode */

// Programs the shared renderer cull state from the one-bit front-vs-back-face selection. Cross-port Android symbols match this helper to `G0SetCull(int)`.
int32_t __cdecl set_cull_mode(int32_t cull_front)
{
  return direct3d_renderer_set_cull_mode(&g_direct3d_renderer, cull_front);
}
