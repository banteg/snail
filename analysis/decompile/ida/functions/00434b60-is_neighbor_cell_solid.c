/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_neighbor_cell_solid @ 0x434b60 */
/* selector: is_neighbor_cell_solid */

// Exact Windows implementation of `cRSubGame::TestLoc(cRSubLoc*, int, int)`: derives the source row with SubLoc::Yi, applies lane and row offsets with bounds checks, probes the eight-lane runtime grid, rejects SubLoc::IsEmpty, then excludes tile ids 35, 0, 22, and 28. Android preserves the same method body and constants.
bool __thiscall is_neighbor_cell_solid(_DWORD *this, SubLoc *cell, int a3, int a4)
{
  int32_t track_cell_row_index; // eax
  uint32_t v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  _DWORD *v10; // eax
  int v11; // esi
  bool result; // al

  track_cell_row_index = get_track_cell_row_index(cell);
  v6 = cell->lane_and_flags & 7;
  result = false;
  if ( v6 + a3 < 8 )
  {
    v7 = a4 + track_cell_row_index;
    if ( v7 >= 0 && v7 < *(this + 21) )
    {
      v8 = 21 * (a3 + v6 + 8 * v7);
      v9 = *((unsigned __int8 *)this + 4 * v8 + 3930884);
      v10 = this + v8;
      v11 = v9;
      if ( !(unsigned __int8)is_sub_loc_empty((TrackRowCell *)(v10 + 982706))
        && v11
        && v11 != 35
        && v11 != 28
        && v11 != 22 )
      {
        return true;
      }
    }
  }
  return result;
}
