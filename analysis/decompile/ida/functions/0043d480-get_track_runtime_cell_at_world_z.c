/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_runtime_cell_at_world_z @ 0x43d480 */
/* selector: get_track_runtime_cell_at_world_z */

// Exact Windows `cRSubGame::RowFromPos(tVector)`: clamps world z into the generated row array and returns the authored `SubRow` runtime record. Android preserves the same owned-row lookup with a port-specific capacity and stride; the Windows 0xf4 stride and 3200-row slab agree with the constructor ledger's `Size of cRSubRow` total of 0xbea00 bytes.
SubRow *__thiscall get_track_runtime_cell_at_world_z(cRSubGame *game, Vec3 *position)
{
  __int64 z; // rax

  z = (__int64)position->z;
  if ( (int)z < 0 )
    return game->runtime_rows;
  if ( (int)z > 3199 )
    LODWORD(z) = 3199;
  return &game->runtime_rows[z];
}
