/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: parse_next_float32 @ 0x431f20 */
/* selector: parse_next_float32 */

// Parses the next signed decimal float from the caller-owned text cursor, consuming digits and one decimal point before returning the float32 value.
double __cdecl sub_431F20(char **a1)
{
  char *v1; // edx
  char v2; // al
  double v3; // st7
  double v4; // st6
  double v5; // st5
  char *v6; // edx
  char v7; // al

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
    v3 = -1.0;
    ++*a1;
  }
  else
  {
    v3 = 1.0;
  }
  v4 = 0.0;
  v5 = 0.0;
  while ( 1 )
  {
    v6 = *a1;
    v7 = **a1;
    if ( (v7 < 48 || v7 > 57) && v7 != 46 )
      break;
    if ( v7 == 46 )
    {
      v5 = 1.0;
      *a1 = v6 + 1;
    }
    else
    {
      *a1 = v6 + 1;
      v4 = (double)(v7 - 48) + v4 * 10.0;
      v5 = v5 * 0.1;
    }
  }
  if ( v5 == 0.0 )
    v5 = 1.0;
  return v3 * (v5 * v4);
}

