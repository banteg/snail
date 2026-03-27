/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_floor_cache_tile_family @ 0x439ad0 */
/* selector: is_floor_cache_tile_family */

int32_t __fastcall is_floor_cache_tile_family(TrackRowCell *cell)
{
  uint8_t tile_id; // al
  int32_t result; // eax

  tile_id = cell->tile_id;
  LOBYTE(result) = tile_id == 15
                || tile_id == 23
                || tile_id == 24
                || tile_id == 25
                || tile_id == 26
                || tile_id == 16
                || tile_id == 18
                || tile_id == 19;
  return result;
}

