/*
 * mangled: _Z21RShellConvertFileNamePcS_
 * demangled: RShellConvertFileName(char*, char*)
 * address: 0000bbb0
 * size: 100
 */

/* RShellConvertFileName(char*, char*) */

void RShellConvertFileName(char *param_1,char *param_2)

{
  char cVar1;

  cVar1 = *param_2;
  while (cVar1 != '\0') {
    if (cVar1 == '/') {
      *param_1 = '_';
    }
    else {
      *param_1 = cVar1;
      if ((byte)(cVar1 + 0xbfU) < 0x1a) {
        *param_1 = cVar1 + ' ';
      }
    }
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
    cVar1 = *param_2;
  }
  *param_1 = '\0';
  return;
}
