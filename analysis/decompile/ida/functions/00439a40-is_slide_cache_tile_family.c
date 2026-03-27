/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_slide_cache_tile_family @ 0x439a40 */
/* selector: is_slide_cache_tile_family */

int32_t __fastcall is_slide_cache_tile_family(TrackRowCell *cell)
{
  uint8_t tile_id; // al
  int32_t result; // eax

  tile_id = cell->tile_id;
  LOBYTE(result) = tile_id == 1 || tile_id == 20 || tile_id == 21 || tile_id == 33 || tile_id == 34 || tile_id == 27;
  return result;
}

