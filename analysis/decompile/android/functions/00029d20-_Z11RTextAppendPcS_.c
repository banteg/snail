/*
 * mangled: _Z11RTextAppendPcS_
 * demangled: RTextAppend(char*, char*)
 * address: 00029d20
 * size: 64
 */

/* RTextAppend(char*, char*) */

void RTextAppend(char *param_1,char *param_2)

{
  char cVar1;

  cVar1 = *param_1;
  while (cVar1 != '\0') {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  cVar1 = *param_2;
  while (cVar1 != '\0') {
    *param_1 = cVar1;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
    cVar1 = *param_2;
  }
  *param_1 = '\0';
  return;
}
