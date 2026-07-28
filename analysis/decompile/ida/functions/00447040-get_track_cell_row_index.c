/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_cell_row_index @ 0x447040 */
/* selector: get_track_cell_row_index */

// Exact Windows implementation of `cRSubLoc::Yi()`: masks the cell's low three lane bits, backs up to lane zero, subtracts the runtime-cell slab base, and divides by eight cells per row. The iOS implementation independently preserves the same algorithm with its port-specific 0x44-byte cell stride; Windows uses 0x54.
int32_t __thiscall get_track_cell_row_index(cRSubLoc *cell)
{
  return ((char *)(cell - (cell->lane_and_flags & 7)) - (char *)g_game_base - 4407520) / 84 / 8;
}
