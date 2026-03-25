/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: find_case_insensitive_substring @ 0x44e600 */
/* selector: find_case_insensitive_substring */

// Parser-side metadata matcher used for case-insensitive, prefix-friendly tag probes.
char *__cdecl sub_44E600(char *a1, char *a2)
{
  char *v2; // ebp
  char *v3; // esi
  char v4; // bl
  int v5; // edi
  char v7; // bl

  v2 = a2;
  if ( *a2 )
  {
    while ( 1 )
    {
      v3 = a1;
      v4 = ascii_upper_if_lowercase(*v2);
      if ( ascii_upper_if_lowercase(*a1) == v4 )
        break;
LABEL_8:
      if ( !*v3 )
        return v2;
      if ( !*++v2 )
        return nullptr;
    }
    v5 = v2 - a1;
    while ( (v3++)[v5 + 1] )
    {
      v7 = ascii_upper_if_lowercase(*v3);
      if ( v7 != ascii_upper_if_lowercase(v3[v5]) )
        goto LABEL_8;
    }
    if ( !*v3 )
      return v2;
  }
  return nullptr;
}

