/*
 * mangled: _Z14RTextCompStartPcS_
 * demangled: RTextCompStart(char*, char*)
 * address: 0000bc68
 * size: 184
 */

/* RTextCompStart(char*, char*) */

int RTextCompStart(char *param_1,char *param_2)

{
  int iVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;

  cVar3 = *param_1;
  cVar2 = *param_2;
  cVar5 = cVar3;
  if ((byte)(cVar3 + 0x9fU) < 0x1a) {
    cVar5 = cVar3 + -0x20;
  }
  cVar4 = cVar2;
  if ((byte)(cVar2 + 0x9fU) < 0x1a) {
    cVar4 = cVar2 + -0x20;
  }
  while ((cVar3 != '\0' && (cVar4 == cVar5 && cVar2 != '\0'))) {
    cVar3 = param_1[1];
    cVar2 = param_2[1];
    param_1 = param_1 + 1;
    cVar5 = cVar3;
    if ((byte)(cVar3 + 0x9fU) < 0x1a) {
      cVar5 = cVar3 + -0x20;
    }
    param_2 = param_2 + 1;
    cVar4 = cVar2;
    if ((byte)(cVar2 + 0x9fU) < 0x1a) {
      cVar4 = cVar2 + -0x20;
    }
  }
  iVar1 = 1 - cVar2;
  if (1 < (uint)(int)cVar2) {
    iVar1 = 0;
  }
  return iVar1;
}
