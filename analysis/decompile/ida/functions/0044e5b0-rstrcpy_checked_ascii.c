/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rstrcpy_checked_ascii @ 0x44e5b0 */
/* selector: rstrcpy_checked_ascii */

// Copies a null-terminated resource string to a destination buffer while reporting high-bit bytes through the engine's `Dodgy Rstrcpy` diagnostic. This helper is hot across path, text, and script setup code.
char __cdecl sub_44E5B0(char *a1, char *ArgList)
{
  char *v2; // esi
  char result; // al
  char *v4; // edi

  v2 = ArgList;
  result = *ArgList;
  if ( *ArgList )
  {
    v4 = a1;
    do
    {
      *v4 = result;
      if ( *v2 < 0 )
        report_errorf("Dodgy Rstrcpy %s", v2);
      result = v2[1];
      ++v4;
      ++v2;
    }
    while ( result );
    *v4 = 0;
  }
  else
  {
    *a1 = 0;
  }
  return result;
}

