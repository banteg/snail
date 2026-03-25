/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: file_exists @ 0x405140 */
/* selector: file_exists */

char __cdecl sub_405140(char *FileName)
{
  #91 *v1; // eax

  v1 = fopen(FileName, Mode);
  if ( !v1 )
    return 0;
  fclose(v1);
  return 1;
}

