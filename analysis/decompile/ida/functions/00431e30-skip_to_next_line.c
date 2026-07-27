/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: skip_to_next_line @ 0x431e30 */
/* selector: skip_to_next_line */

// Void Windows `RTextNewLine(char**)`: advances the caller-owned text cursor to the next line break or NUL and then steps once more so the cursor starts on the following line.
void __cdecl skip_to_next_line(char **cursor)
{
  char *v1; // eax

  if ( **cursor != 0 )
  {
    do
    {
      if ( **cursor == 10 )
        break;
      v1 = *cursor + 1;
      *cursor = v1;
    }
    while ( *v1 != 0 );
  }
  ++*cursor;
}
