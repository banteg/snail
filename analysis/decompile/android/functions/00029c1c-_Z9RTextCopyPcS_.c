/*
 * mangled: _Z9RTextCopyPcS_
 * demangled: RTextCopy(char*, char*)
 * address: 00029c1c
 * size: 32
 */

/* RTextCopy(char*, char*) */

void RTextCopy(char *param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;

  iVar2 = 0;
  do {
    param_1[iVar2] = param_2[iVar2];
    pcVar1 = param_2 + iVar2;
    iVar2 = iVar2 + 1;
  } while (*pcVar1 != '\0');
  return;
}
