/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: strings_equal_case_insensitive @ 0x431dc0 */
/* selector: strings_equal_case_insensitive */

// Windows `RTextCompStart(char*, char*)`: compares ASCII case-insensitively and returns true when the prefix argument terminates after matching. Mobile `Rstrcmp` is strict equality instead; the contiguous RShell.o RText sequence and ObjectTextLoad call graph resolve the owner.
bool __cdecl strings_equal_case_insensitive(char *left, char *prefix)
{
  char *v2; // esi
  char *v3; // edi
  char v4; // dl
  char v5; // cl
  char v6; // al
  char v7; // bl

  v2 = prefix;
  v3 = left;
  v4 = *prefix;
  v5 = *prefix;
  v6 = *left;
  if ( *left >= 97 && v6 <= 122 )
    v6 -= 32;
  if ( v5 >= 97 && v5 <= 122 )
    v5 -= 32;
  if ( *left != 0 )
  {
    do
    {
      if ( v4 == 0 || v6 != v5 )
        break;
      v7 = v3[1];
      v4 = v2[1];
      ++v3;
      ++v2;
      v6 = v7;
      v5 = v4;
      if ( v7 >= 97 && v7 <= 122 )
        v6 = v7 - 32;
      if ( v4 >= 97 && v4 <= 122 )
        v5 = v4 - 32;
    }
    while ( v7 != 0 );
  }
  return *v2 == 0;
}
