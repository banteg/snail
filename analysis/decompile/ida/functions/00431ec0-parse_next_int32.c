/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: parse_next_int32 @ 0x431ec0 */
/* selector: parse_next_int32 */

// Parses the next signed decimal integer from the caller-owned text cursor, skipping leading spaces and advancing the cursor past the consumed digits.
int __cdecl sub_431EC0(char **a1)
{
  char *v1; // eax
  int v2; // edi
  int v3; // eax
  char *v4; // esi
  char v5; // dl

  if ( **a1 == 32 )
  {
    do
    {
      v1 = *a1 + 1;
      *a1 = v1;
    }
    while ( *v1 == 32 );
  }
  if ( **a1 == 45 )
  {
    v2 = -1;
    ++*a1;
  }
  else
  {
    v2 = 1;
  }
  v3 = 0;
  if ( **a1 >= 48 )
  {
    do
    {
      v4 = *a1;
      v5 = **a1;
      if ( v5 > 57 )
        break;
      v3 = v5 + 10 * v3 - 48;
      *a1 = v4 + 1;
    }
    while ( v4[1] >= 48 );
  }
  return v2 * v3;
}

