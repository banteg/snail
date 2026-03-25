/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sound_bank @ 0x44dcb0 */
/* selector: initialize_sound_bank */

// Registers one null-terminated table of shipped SFX paths into the shared runtime sound table by repeatedly calling `register_sound_sample` with each path and its normalization class.
char *__stdcall sub_44DCB0(char **a1)
{
  char **v1; // esi
  char *result; // eax
  char **v3; // edi

  v1 = a1;
  result = *a1;
  if ( **a1 )
  {
    v3 = a1;
    do
    {
      v1 += 3;
      v3[1] = (char *)register_sound_sample(result, (int)v3[2]);
      v3 = v1;
      result = *v1;
    }
    while ( **v1 );
  }
  return result;
}

