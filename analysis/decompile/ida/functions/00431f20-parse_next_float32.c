/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: parse_next_float32 @ 0x431f20 */
/* selector: parse_next_float32 */

// Exact Windows `RTextExtractFloat(char**)`: advances the caller-owned cursor to a signed decimal token, consumes digits and one decimal point, and returns the parsed float32 value. Mobile also retains a later code-equivalent RString.o `Rstrfloat` sibling, but the complete adjacent RText sequence resolves the canonical Windows owner.
float __cdecl parse_next_float32(char **cursor)
{
  char *v1; // edx
  char v2; // al
  double v3; // st7
  double v4; // st6
  double v5; // st5
  char *v6; // edx
  char v7; // al

  if ( **cursor != 45 )
  {
    do
    {
      v1 = *cursor;
      v2 = **cursor;
      if ( v2 == 43 || v2 == 46 || v2 >= 48 && v2 <= 57 )
        break;
      *cursor = v1 + 1;
    }
    while ( v1[1] != 45 );
  }
  if ( **cursor == 45 )
  {
    v3 = -1.0;
    ++*cursor;
  }
  else
  {
    v3 = 1.0;
  }
  v4 = 0.0;
  v5 = 0.0;
  while ( 1 )
  {
    v6 = *cursor;
    v7 = **cursor;
    if ( (v7 < 48 || v7 > 57) && v7 != 46 )
      break;
    if ( v7 == 46 )
    {
      v5 = 1.0;
      *cursor = v6 + 1;
    }
    else
    {
      *cursor = v6 + 1;
      v4 = (double)(v7 - 48) + v4 * 10.0;
      v5 = v5 * 0.1;
    }
  }
  if ( v5 == 0.0 )
    v5 = 1.0;
  return v3 * (v5 * v4);
}
