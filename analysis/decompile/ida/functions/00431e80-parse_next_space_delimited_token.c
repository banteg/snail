/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: parse_next_space_delimited_token @ 0x431e80 */
/* selector: parse_next_space_delimited_token */

// Skips leading spaces, copies the next space-delimited token from the caller-owned text cursor into the destination buffer, and advances the cursor.
char **__cdecl sub_431E80(char **a1, _BYTE *a2)
{
  char **result; // eax
  char *v3; // ecx
  char v5; // cl
  char *v6; // ecx

  result = a1;
  if ( **a1 == 32 )
  {
    do
    {
      v3 = *a1 + 1;
      *a1 = v3;
    }
    while ( *v3 == 32 );
  }
  if ( **a1 != 32 )
  {
    do
    {
      v5 = **a1;
      if ( v5 == 13 )
        break;
      *a2++ = v5;
      v6 = *a1 + 1;
      *a1 = v6;
    }
    while ( *v6 != 32 );
  }
  *a2 = 0;
  return result;
}

