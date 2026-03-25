/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_slide_cache_tile_family @ 0x439a40 */
/* selector: is_slide_cache_tile_family */

bool __thiscall sub_439A40(_BYTE *this)
{
  char v1; // al

  v1 = *(this + 60);
  return v1 == 1 || v1 == 20 || v1 == 21 || v1 == 33 || v1 == 34 || v1 == 27;
}

