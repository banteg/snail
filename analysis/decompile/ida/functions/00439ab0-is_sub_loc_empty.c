/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_sub_loc_empty @ 0x439ab0 */
/* selector: is_sub_loc_empty */

bool __thiscall sub_439AB0(_BYTE *this)
{
  char v1; // al

  v1 = *(this + 60);
  return !v1 || v1 == 28 || v1 == 35 || v1 == 14 || v1 == 29;
}

