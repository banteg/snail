/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: strings_equal_case_insensitive_path @ 0x44e6c0 */
/* selector: strings_equal_case_insensitive_path */

// Exact Windows `Rstrcmp(char*, char*)` from RString.o: performs strict ASCII-case-insensitive equality, requiring both strings to terminate after the folded match. Windows returns a full int and every caller consumes EAX; importing the mobile decompilers' inferred bool ABI changes the exact VC6 return sequence.
int __cdecl strings_equal_case_insensitive_path(char *left, char *right)
{
  char v4; // al
  char v5; // cl

  while ( 1 )
  {
    v4 = *left;
    v5 = *right;
    ++left;
    ++right;
    if ( v4 >= 97 && v4 <= 122 )
      v4 -= 32;
    if ( v5 >= 97 && v5 <= 122 )
      v5 -= 32;
    if ( v4 == 0 )
      break;
    if ( v5 == 0 || v4 != v5 )
      return 0;
  }
  return v5 == 0;
}
