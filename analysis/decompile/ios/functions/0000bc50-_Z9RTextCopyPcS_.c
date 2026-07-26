/*
 * mangled: _Z9RTextCopyPcS_
 * demangled: RTextCopy(char*, char*)
 * address: 0000bc50
 * size: 24
 */

/* RTextCopy(char*, char*) */

void RTextCopy(char *param_1,char *param_2)

{
  char cVar1;

  do {
    *param_1 = *param_2;
    cVar1 = *param_2;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  return;
}
