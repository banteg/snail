/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: present_backbuffer @ 0x413520 */
/* selector: present_backbuffer */

// Presents the Direct3D backbuffer with null source, destination, window, and dirty-region arguments.
int32_t __cdecl present_backbuffer()
{
  return g_direct3d_renderer.device->vtbl->Present(g_direct3d_renderer.device, nullptr, nullptr, 0, nullptr);
}
