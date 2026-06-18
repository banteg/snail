/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cached_x_mesh_slot @ 0x408470 */
/* selector: initialize_cached_x_mesh_slot */

// Constructs one 0xbc-byte cached X-mesh object slot by seeding the shared BOD header and installing the cache-slot callback table. The slot bank starts at `game + 0x48e08`; `load_or_reuse_cached_x_mesh(game + 0x48e00, ...)` stores names at slot `+0x3c` and object BOD refs at slot `+0x24`.
_DWORD *__thiscall initialize_cached_x_mesh_slot(_DWORD *this)
{
  initialize_bod_base(this);
  *this = g_cached_x_mesh_slot_vtable;
  return this;
}
