/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_sub_loc_ramp @ 0x439a70 */
/* selector: is_sub_loc_ramp */

// Exact SubLoc predicate matching cross-port `cRSubLoc::IsRamp()`: accepts the authored ramp tile family 2 through 13.
int32_t __fastcall is_sub_loc_ramp(TrackRowCell *cell)
{
  SubLocTileId tile_id; // al
  int32_t result; // eax

  tile_id = cell->tile_id;
  LOBYTE(result) = tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE
                || tile_id == SUBLOC_TILE_RAMP_GREATER
                || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE
                || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
                || tile_id == SUBLOC_TILE_RAMP_GREATER_RAISED
                || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED
                || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH
                || tile_id == SUBLOC_TILE_RAMP_GREATER_BACKPATCH
                || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH
                || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACKET
                || tile_id == SUBLOC_TILE_RAMP_LESS
                || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACKET;
  return result;
}
