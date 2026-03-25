/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: xor_decode_buffer_with_index @ 0x433010 */
/* selector: xor_decode_buffer_with_index */

_BYTE *__cdecl sub_433010(_BYTE *a1, int a2)
{
  _BYTE *result; // eax
  int i; // ecx

  result = a1;
  for ( i = 0; i < a2; ++i )
    *result++ ^= i;
  return result;
}

