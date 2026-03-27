/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: parse_next_space_delimited_token @ 0x431e80 */
/* selector: parse_next_space_delimited_token */

// Skips leading spaces, copies the next space-delimited token from the caller-owned text cursor into the destination buffer, and advances the cursor.
char **__cdecl parse_next_space_delimited_token(char **cursor, char *out)
{
  char **result; // eax
  char *v3; // ecx
  char v5; // cl
  char *v6; // ecx

  result = cursor;
  if ( **cursor == 32 )
  {
    do
    {
      v3 = *cursor + 1;
      *cursor = v3;
    }
    while ( *v3 == 32 );
  }
  if ( **cursor != 32 )
  {
    do
    {
      v5 = **cursor;
      if ( v5 == 13 )
        break;
      *out++ = v5;
      v6 = *cursor + 1;
      *cursor = v6;
    }
    while ( *v6 != 32 );
  }
  *out = 0;
  return result;
}

