/*
 * mangled: _Z15RTextExtractIntPPc
 * demangled: RTextExtractInt(char**)
 * address: 0000be00
 * size: 156
 */

/* RTextExtractInt(char**) */

int RTextExtractInt(char **param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  char cVar5;

  pcVar3 = *param_1;
  cVar5 = *pcVar3;
  while (cVar5 == ' ') {
    pcVar3 = pcVar3 + 1;
    *param_1 = pcVar3;
    cVar5 = *pcVar3;
  }
  if (cVar5 == '-') {
    pcVar3 = pcVar3 + 1;
    *param_1 = pcVar3;
    iVar4 = -1;
  }
  else {
    pcVar3 = *param_1;
    iVar4 = 1;
  }
  cVar5 = *pcVar3;
  if (9 < (byte)(cVar5 - 0x30U)) {
    return 0;
  }
  iVar2 = 0;
  do {
    pcVar3 = pcVar3 + 1;
    iVar1 = (int)cVar5;
    *param_1 = pcVar3;
    cVar5 = *pcVar3;
    iVar2 = iVar2 * 10 + iVar1 + -0x30;
  } while ((byte)(cVar5 - 0x30U) < 10);
  return iVar4 * iVar2;
}
