/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: xor_archive_bytes_in_place @ 0x431980 */
/* selector: xor_archive_bytes_in_place */

// Applies the archive byte XOR mask in place over the requested byte span; the same transform is used to decode archive reads and to encode rebuilt archive payloads.
__int16 __cdecl sub_431980(int a1, int a2, int a3)
{
  int v3; // ecx
  __int16 result; // ax

  v3 = a1;
  for ( result = a3; v3 < a1 + a3; ++v3 )
  {
    result = 3 * (char)v3;
    *(_BYTE *)(a2 - a1 + v3) ^= (unsigned __int8)result ^ (unsigned __int8)(v3 * v3);
  }
  return result;
}

