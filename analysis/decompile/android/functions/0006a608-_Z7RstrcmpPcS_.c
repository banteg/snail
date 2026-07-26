/*
 * mangled: _Z7RstrcmpPcS_
 * demangled: Rstrcmp(char*, char*)
 * address: 0006a608
 * size: 104
 */

/* Rstrcmp(char*, char*) */

bool Rstrcmp(char *param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;

  iVar3 = 0;
  do {
    cVar2 = param_1[iVar3];
    cVar1 = param_2[iVar3];
    iVar3 = iVar3 + 1;
    if ((byte)(cVar2 + 0x9fU) < 0x1a) {
      cVar2 = cVar2 + -0x20;
    }
    if ((byte)(cVar1 + 0x9fU) < 0x1a) {
      cVar1 = cVar1 + -0x20;
    }
  } while ((cVar1 != '\0' && cVar2 != '\0') && (cVar2 == cVar1));
  return cVar1 == '\0' && cVar2 == '\0';
}
