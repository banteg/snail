/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_directx_loader @ 0x405c90 */
/* selector: initialize_directx_loader */

// Exact Windows `cRDirectX::Init()`: initializes the root-owned 0x5e10-byte X-file loader, clears its cached-mesh count, loads XAnimation.txt, and allocates the duplicate-vertex workspace after the fixed 128-slot mesh cache. Android and iOS preserve the same authored owner.
void __thiscall initialize_directx_loader(cRDirectX *loader)
{
  loader->cached_x_mesh_count = 0;
  loader->animation_bytes = (char *)load_file_bytes(g_x_animation_script_path, nullptr);
  initialize_duplicate_vertices(&loader->duplicate_vertices, 2000);
}
