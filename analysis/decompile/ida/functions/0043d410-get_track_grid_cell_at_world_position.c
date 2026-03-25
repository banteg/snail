/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_grid_cell_at_world_position @ 0x43d410 */
/* selector: get_track_grid_cell_at_world_position */

// Clamps world-space x and z into the 8-lane gameplay grid and returns the compact 0x54-byte runtime cell.
char *__thiscall sub_43D410(char *this, float *a2)
{
  int v2; // esi
  __int64 v3; // rax

  v2 = (__int64)(*a2 + 4.0);
  v3 = (__int64)a2[2];
  if ( v2 >= 0 )
  {
    if ( v2 > 7 )
      v2 = 7;
  }
  else
  {
    v2 = 0;
  }
  if ( (int)v3 >= 0 )
  {
    if ( (int)v3 > 3199 )
      LODWORD(v3) = 3199;
  }
  else
  {
    LODWORD(v3) = 0;
  }
  return this + 672 * v3 + 84 * v2 + 3930824;
}

