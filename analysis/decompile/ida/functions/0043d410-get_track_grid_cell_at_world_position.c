/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_grid_cell_at_world_position @ 0x43d410 */
/* selector: get_track_grid_cell_at_world_position */

// Clamps world-space x and z into the 8-lane gameplay grid and returns the compact 0x54-byte runtime cell.
TrackRowCell *__thiscall get_track_grid_cell_at_world_position(Game *game, Vec3 *position)
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
  return (TrackRowCell *)&game->_pad_74622[672 * z + 3454118 + 84 * v2];
}

