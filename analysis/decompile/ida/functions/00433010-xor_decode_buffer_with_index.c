/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: xor_decode_buffer_with_index @ 0x433010 */
/* selector: xor_decode_buffer_with_index */

char *__cdecl xor_decode_buffer_with_index(char *bytes, int byte_count)
{
  char *result; // eax
  int i; // ecx

  result = bytes;
  for ( i = 0; i < byte_count; ++i )
    *result++ ^= i;
  return result;
}
