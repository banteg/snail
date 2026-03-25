/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: scramble_archive_bytes_in_place @ 0x405270 */
/* selector: scramble_archive_bytes_in_place */

// Applies the archive rebuild byte-scramble in place by XORing each byte with its index-derived polynomial mask.
__int16 __cdecl sub_405270(int a1, int a2)
{
  int i; // ecx
  __int16 result; // ax

  for ( i = 0; i < a2; ++i )
  {
    result = 3 * (char)i;
    *(_BYTE *)(i + a1) ^= (unsigned __int8)result ^ (unsigned __int8)(i * i);
  }
  return result;
}

