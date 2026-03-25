/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: strings_equal_case_insensitive @ 0x431dc0 */
/* selector: strings_equal_case_insensitive */

// Compares two NUL-terminated strings case-insensitively and returns true only when both terminate together after matching.
bool __cdecl sub_431DC0(char *a1, _BYTE *a2)
{
  _BYTE *v2; // esi
  char *v3; // edi
  char v4; // dl
  char v5; // cl
  char v6; // al
  char v7; // bl

  v2 = a2;
  v3 = a1;
  v4 = *a2;
  v5 = *a2;
  v6 = *a1;
  if ( *a1 >= 97 && v6 <= 122 )
    v6 -= 32;
  if ( v5 >= 97 && v5 <= 122 )
    v5 -= 32;
  if ( *a1 )
  {
    do
    {
      if ( !v4 || v6 != v5 )
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
    while ( v7 );
  }
  return *v2 == 0;
}

