/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: append_c_string @ 0x431e50 */
/* selector: append_c_string */

// Void Windows `RTextAppend(char*, char*)`: advances to the destination string's trailing NUL and appends the source string in place.
void __cdecl append_c_string(char *destination, char *source)
{
  char *v2; // eax
  char v3; // cl
  char *v4; // edx
  char i; // cl

  v2 = destination;
  if ( *destination != 0 )
  {
    do
      v3 = *++v2;
    while ( v3 != 0 );
  }
  v4 = source;
  for ( i = *source; i != 0; ++v4 )
  {
    *v2 = i;
    i = v4[1];
    ++v2;
  }
  *v2 = 0;
}
