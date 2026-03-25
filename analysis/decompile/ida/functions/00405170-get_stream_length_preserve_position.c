/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_stream_length_preserve_position @ 0x405170 */
/* selector: get_stream_length_preserve_position */

// Seeks one open file stream to the end, reads its byte length, and restores the original stream position before returning.
int __cdecl sub_405170(#91 *Stream)
{
  int v1; // edi
  int v2; // ebx

  v1 = ftell(Stream);
  fseek(Stream, 0, 2);
  v2 = ftell(Stream);
  fseek(Stream, v1, 0);
  return v2;
}

