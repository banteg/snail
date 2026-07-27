/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rstrcpy_checked_ascii @ 0x44e5b0 */
/* selector: rstrcpy_checked_ascii */

// Exact void Windows `Rstrcpy(char*, char const*)`: copies a null-terminated resource string while the Windows build additionally reports high-bit bytes through its `Dodgy Rstrcpy` diagnostic. Both mobile ports preserve the authored RString.o owner and const source contract; Windows callers discard the final copied byte left incidentally in EAX.
void __cdecl rstrcpy_checked_ascii(char *destination, const char *source)
{
  const char *v2; // esi
  char v3; // al
  char *v4; // edi

  v2 = source;
  v3 = *source;
  if ( *source != 0 )
  {
    v4 = destination;
    do
    {
      *v4 = v3;
      if ( *v2 < 0 )
        report_errorf("Dodgy Rstrcpy %s", v2);
      v3 = v2[1];
      ++v4;
      ++v2;
    }
    while ( v3 != 0 );
    *v4 = 0;
  }
  else
  {
    *destination = 0;
  }
}
