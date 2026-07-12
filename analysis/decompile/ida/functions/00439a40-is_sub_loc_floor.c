/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_sub_loc_floor @ 0x439a40 */
/* selector: is_sub_loc_floor */

int32_t __fastcall is_sub_loc_floor(TrackRowCell *cell)
{
  uint8_t tile_id; // al
  int32_t result; // eax

  tile_id = cell->tile_id;
  LOBYTE(result) = tile_id == 1 || tile_id == 20 || tile_id == 21 || tile_id == 33 || tile_id == 34 || tile_id == 27;
  return result;
}

