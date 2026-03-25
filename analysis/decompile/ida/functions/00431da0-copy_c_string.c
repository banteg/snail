/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_c_string @ 0x431da0 */
/* selector: copy_c_string */

// Copies one NUL-terminated C string into the destination buffer and returns the advanced source pointer.
_BYTE *__cdecl sub_431DA0(_BYTE *a1, _BYTE *a2)
{
  _BYTE *result; // eax
  char v4; // dl

  result = a2;
  do
  {
    *a1 = *result;
    v4 = *result;
    ++a1;
    ++result;
  }
  while ( v4 );
  return result;
}

