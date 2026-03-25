/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_snail_skin @ 0x445f60 */
/* selector: initialize_snail_skin */

char *__thiscall sub_445F60(_DWORD *this)
{
  char *v1; // eax
  char *result; // eax

  v1 = (char *)MEMORY[0x4DF904];
  *this = 0;
  result = v1 + 4400896;
  *(this + 5) = 0;
  *(this + 4) = result;
  return result;
}

