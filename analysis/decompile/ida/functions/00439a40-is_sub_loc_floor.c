/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_sub_loc_floor @ 0x439a40 */
/* selector: is_sub_loc_floor */

// Exact Windows counterpart of cross-port `cRSubLoc::IsFloor()`: accepts tile ids 1, 20, 21, 33, 34, and 27.
int32_t __fastcall is_sub_loc_floor(TrackRowCell *cell)
{
  SubLocTileId tile_id; // al
  int32_t result; // eax

  tile_id = cell->tile_id;
  LOBYTE(result) = tile_id == SUBLOC_TILE_FLOOR_DOT
                || tile_id == SUBLOC_TILE_FLOOR_VARIANT_14
                || tile_id == SUBLOC_TILE_FLOOR_DASH
                || tile_id == SUBLOC_TILE_GARBAGE_HAZARD
                || tile_id == SUBLOC_TILE_SALT_HAZARD
                || tile_id == SUBLOC_TILE_FLOOR_VARIANT_1B;
  return result;
}
