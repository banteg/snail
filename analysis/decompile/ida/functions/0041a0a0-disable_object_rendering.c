/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: disable_object_rendering @ 0x41a0a0 */
/* selector: disable_object_rendering */

// Exact Windows `ObjectProcNull(cRObject*)`: sets the Object's 0x40000 render-suppression flag checked by render_object. Android and iOS preserve the authored free-function name and the same two cRGame::LoadPaths callsites immediately after binding the selected path objects into their BodBase owners.
int __cdecl disable_object_rendering(int a1)
{
  *(_DWORD *)(a1 + 16) |= 0x40000u;
  return a1;
}
