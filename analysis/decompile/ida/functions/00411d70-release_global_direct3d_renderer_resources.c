/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: release_global_direct3d_renderer_resources @ 0x411d70 */
/* selector: release_global_direct3d_renderer_resources */

// Loads the process-owned Direct3D renderer singleton and tail-calls its renderer-resource teardown method for window/input failure and shutdown paths.
void __cdecl release_global_direct3d_renderer_resources()
{
  release_direct3d_renderer_resources(&g_direct3d_renderer);
}
