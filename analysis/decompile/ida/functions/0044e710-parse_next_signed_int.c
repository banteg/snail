/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: parse_next_signed_int @ 0x44e710 */
/* selector: parse_next_signed_int */

// Advances a text cursor to the next numeric token, parses an optional sign and decimal digits, and leaves the cursor after the consumed integer. Shared by shipped asset and level-script parsers.
int __cdecl sub_44E710(char **a1)
{
  char *v1; // edx
  char v2; // al
  int v3; // edi
  int v4; // eax
  char *v5; // esi
  char v6; // dl

  if ( **a1 != 45 )
  {
    do
    {
      v1 = *a1;
      v2 = **a1;
      if ( v2 == 43 || v2 == 46 || v2 >= 48 && v2 <= 57 )
        break;
      *a1 = v1 + 1;
    }
    while ( v1[1] != 45 );
  }
  if ( **a1 == 45 )
  {
    v3 = -1;
    ++*a1;
  }
  else
  {
    v3 = 1;
  }
  v4 = 0;
  if ( **a1 >= 48 )
  {
    do
    {
      v5 = *a1;
      v6 = **a1;
      if ( v6 > 57 )
        break;
      v4 = v6 + 10 * v4 - 48;
      *a1 = v5 + 1;
    }
    while ( v5[1] >= 48 );
  }
  return v3 * v4;
}

