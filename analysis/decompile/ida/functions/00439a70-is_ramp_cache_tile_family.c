/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_ramp_cache_tile_family @ 0x439a70 */
/* selector: is_ramp_cache_tile_family */

bool __thiscall sub_439A70(_BYTE *this)
{
  char v1; // al

  v1 = *(this + 60);
  return v1 == 2
      || v1 == 3
      || v1 == 4
      || v1 == 8
      || v1 == 9
      || v1 == 10
      || v1 == 11
      || v1 == 12
      || v1 == 13
      || v1 == 5
      || v1 == 6
      || v1 == 7;
}

