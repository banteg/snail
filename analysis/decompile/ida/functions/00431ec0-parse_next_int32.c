/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: parse_next_int32 @ 0x431ec0 */
/* selector: parse_next_int32 */

// Parses the next signed decimal integer from the caller-owned text cursor, skipping leading spaces and advancing the cursor past the consumed digits.
int32_t __cdecl parse_next_int32(char **cursor)
{
  char *v1; // eax
  int v2; // edi
  int v3; // eax
  char *v4; // esi
  char v5; // dl

  if ( **cursor == 32 )
  {
    do
    {
      v1 = *cursor + 1;
      *cursor = v1;
    }
    while ( *v1 == 32 );
  }
  if ( **cursor == 45 )
  {
    v2 = -1;
    ++*cursor;
  }
  else
  {
    v2 = 1;
  }
  v3 = 0;
  if ( **cursor >= 48 )
  {
    do
    {
      v4 = *cursor;
      v5 = **cursor;
      if ( v5 > 57 )
        break;
      v3 = v5 + 10 * v3 - 48;
      *cursor = v4 + 1;
    }
    while ( v4[1] >= 48 );
  }
  return v2 * v3;
}

