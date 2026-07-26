/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: find_case_insensitive_substring @ 0x44e600 */
/* selector: find_case_insensitive_substring */

// Windows `Rstrfind(char*, char*)`: scans the second argument for the first ASCII-case-insensitive match of the first argument and returns that searched-string cursor. Used for prefix-friendly parser metadata and tag probes.
char *__cdecl find_case_insensitive_substring(char *pattern, char *searched)
{
  char *v2; // ebp
  char *v3; // esi
  char v4; // bl
  int v5; // edi
  char v6; // al
  char v7; // bl
  char v8; // al

  v2 = searched;
  if ( *searched != 0 )
  {
    while ( 1 )
    {
      v3 = pattern;
      v4 = ascii_upper_if_lowercase(*v2);
      if ( ascii_upper_if_lowercase(*pattern) == v4 )
        break;
LABEL_8:
      if ( *v3 == 0 )
        return v2;
      v8 = *++v2;
      if ( v8 == 0 )
        return nullptr;
    }
    v5 = v2 - pattern;
    while ( 1 )
    {
      v6 = (v3++)[v5 + 1];
      if ( v6 == 0 )
        break;
      v7 = ascii_upper_if_lowercase(*v3);
      if ( v7 != ascii_upper_if_lowercase(v3[v5]) )
        goto LABEL_8;
    }
    if ( *v3 == 0 )
      return v2;
  }
  return nullptr;
}
