/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_grid_cell_at_world_position @ 0x43d410 */
/* selector: get_track_grid_cell_at_world_position */

// Exact Windows `cRSubGame::LocFromPos(tVector)`: clamps world-space x and z into the eight-lane gameplay grid and returns the owned compact 0x54-byte `cRSubLoc` runtime cell. Android and iOS preserve the same lane/row clamp and row-major ownership with port-specific capacities and strides.
cRSubLoc *__thiscall get_track_grid_cell_at_world_position(cRSubGame *game, Vec3 *position)
{
  int v2; // esi
  __int64 z; // rax

  v2 = (__int64)(position->x + 4.0);
  z = (__int64)position->z;
  if ( v2 >= 0 )
  {
    if ( v2 > 7 )
      v2 = 7;
  }
  else
  {
    v2 = 0;
  }
  if ( (int)z >= 0 )
  {
    if ( (int)z > 3199 )
      LODWORD(z) = 3199;
  }
  else
  {
    LODWORD(z) = 0;
  }
  return &game->runtime_cells[z][v2];
}
