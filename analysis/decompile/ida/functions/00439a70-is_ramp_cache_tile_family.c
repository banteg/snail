/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_ramp_cache_tile_family @ 0x439a70 */
/* selector: is_ramp_cache_tile_family */

int32_t __fastcall is_ramp_cache_tile_family(TrackRowCell *cell)
{
  uint8_t tile_id; // al
  int32_t result; // eax

  tile_id = cell->tile_id;
  LOBYTE(result) = tile_id == 2
                || tile_id == 3
                || tile_id == 4
                || tile_id == 8
                || tile_id == 9
                || tile_id == 10
                || tile_id == 11
                || tile_id == 12
                || tile_id == 13
                || tile_id == 5
                || tile_id == 6
                || tile_id == 7;
  return result;
}

