/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: append_c_string @ 0x431e50 */
/* selector: append_c_string */

// Advances to the destination string's trailing NUL and appends the source string in place.
_BYTE *__cdecl sub_431E50(_BYTE *a1, _BYTE *a2)
{
  _BYTE *result; // eax
  _BYTE *v4; // edx
  char i; // cl

  result = a1;
  if ( *a1 )
  {
    while ( *++result )
      ;
  }
  v4 = a2;
  for ( i = *a2; i; ++v4 )
  {
    *result = i;
    i = v4[1];
    ++result;
  }
  *result = 0;
  return result;
}

