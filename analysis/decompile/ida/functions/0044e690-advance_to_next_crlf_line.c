/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: advance_to_next_crlf_line @ 0x44e690 */
/* selector: advance_to_next_crlf_line */

// Exact Windows `Rstrnewline(char*)`: returns the first byte after the next CRLF pair, or null when there is no following non-empty line.
char *__cdecl advance_to_next_crlf_line(char *cursor)
{
  char *v1; // ecx
  char v2; // al

  v1 = cursor;
  v2 = *cursor;
  if ( *cursor == 0 )
    return nullptr;
  while ( v2 != 13 || v1[1] != 10 )
  {
    v2 = *++v1;
    if ( v2 == 0 )
      return nullptr;
  }
  return v1[2] != 0 ? v1 + 2 : nullptr;
}
