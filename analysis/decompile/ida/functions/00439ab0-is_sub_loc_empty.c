/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_sub_loc_empty @ 0x439ab0 */
/* selector: is_sub_loc_empty */

// Exact Windows counterpart of cross-port `cRSubLoc::IsEmpty()`: accepts tile ids 0, 28, 35, 14, and 29.
int32_t __fastcall is_sub_loc_empty(TrackRowCell *cell)
{
  SubLocTileId tile_id; // al
  int32_t result; // eax

  tile_id = cell->tile_id;
  LOBYTE(result) = tile_id == SUBLOC_TILE_EMPTY
                || tile_id == SUBLOC_TILE_UNIVERSE_HOLE
                || tile_id == SUBLOC_TILE_RING_MARKER
                || tile_id == SUBLOC_TILE_WALL2
                || tile_id == SUBLOC_TILE_PATH_ENTRY_LOWERCASE;
  return result;
}
