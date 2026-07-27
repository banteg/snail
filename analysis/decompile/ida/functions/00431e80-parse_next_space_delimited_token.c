/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: parse_next_space_delimited_token @ 0x431e80 */
/* selector: parse_next_space_delimited_token */

// Void Windows `RTextExtractString(char**, char*)`: skips leading spaces, copies the next space- or CR-delimited token from the caller-owned text cursor into the destination buffer, and advances the cursor.
void __cdecl parse_next_space_delimited_token(char **cursor, char *out)
{
  char *v2; // ecx
  char v4; // cl
  char *v5; // ecx

  if ( **cursor == 32 )
  {
    do
    {
      v2 = *cursor + 1;
      *cursor = v2;
    }
    while ( *v2 == 32 );
  }
  if ( **cursor != 32 )
  {
    do
    {
      v4 = **cursor;
      if ( v4 == 13 )
        break;
      *out++ = v4;
      v5 = *cursor + 1;
      *cursor = v5;
    }
    while ( *v5 != 32 );
  }
  *out = 0;
}
