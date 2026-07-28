/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_neighbor_cell_solid @ 0x434b60 */
/* selector: is_neighbor_cell_solid */

// Exact Windows implementation of `cRSubGame::TestLoc(cRSubLoc*, int, int)`: derives the source row with cRSubLoc::Yi, applies lane and row offsets with bounds checks, probes the eight-lane runtime grid, rejects cRSubLoc::IsEmpty, then excludes tile ids 35, 0, 22, and 28. Android preserves the same method body and constants.
bool __thiscall is_neighbor_cell_solid(SubgameRuntime *game, cRSubLoc *cell, int32_t lane_offset, int32_t row_offset)
{
  int32_t track_cell_row_index; // eax
  uint32_t v6; // ecx
  int32_t v7; // eax
  unsigned int v8; // eax
  int tile_id; // ecx
  char *v10; // eax
  int v11; // esi
  bool result; // al

  track_cell_row_index = get_track_cell_row_index(cell);
  v6 = cell->lane_and_flags & 7;
  result = false;
  if ( v6 + lane_offset < 8 )
  {
    v7 = row_offset + track_cell_row_index;
    if ( v7 >= 0 && v7 < game->runtime_row_count )
    {
      v8 = 21 * (lane_offset + v6 + 8 * v7);
      tile_id = game->runtime_cells[0][v8 / 0x15].tile_id;
      v10 = (char *)game + 4 * v8;
      v11 = tile_id;
      if ( (unsigned __int8)is_sub_loc_empty((cRSubLoc *)(v10 + 3930824)) == 0
        && v11 != 0
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
