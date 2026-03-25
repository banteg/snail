/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: toggle_archive_high_bit_in_place @ 0x405350 */
/* selector: toggle_archive_high_bit_in_place */

// Toggles bit 7 on each byte in place; used to decode the legacy `.dam` archive payload before rebuild.
_BYTE *__cdecl sub_405350(_BYTE *a1, int a2)
{
  int v2; // ecx
  _BYTE *result; // eax

  v2 = a2;
  result = a1;
  if ( a2 > 0 )
  {
    do
    {
      *result++ ^= 0x80u;
      --v2;
    }
    while ( v2 );
  }
  return result;
}

