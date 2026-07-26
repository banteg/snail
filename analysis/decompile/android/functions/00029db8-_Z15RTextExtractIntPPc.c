/*
 * mangled: _Z15RTextExtractIntPPc
 * demangled: RTextExtractInt(char**)
 * address: 00029db8
 * size: 144
 */

/* RTextExtractInt(char**) */

int RTextExtractInt(char **param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  byte *pbVar5;
  int iVar6;

  pcVar4 = *param_1;
  cVar1 = *pcVar4;
  while (cVar1 == ' ') {
    pcVar4 = pcVar4 + 1;
    *param_1 = pcVar4;
    cVar1 = *pcVar4;
  }
  if (cVar1 == '-') {
    pbVar5 = (byte *)(pcVar4 + 1);
    *param_1 = (char *)pbVar5;
    iVar6 = -1;
  }
  else {
    pbVar5 = (byte *)*param_1;
    iVar6 = 1;
  }
  uVar3 = (uint)*pbVar5;
  if ((uVar3 - 0x30 & 0xff) < 10) {
    iVar2 = 0;
    do {
      pbVar5 = pbVar5 + 1;
      *param_1 = (char *)pbVar5;
      iVar2 = uVar3 + iVar2 * 10;
      uVar3 = (uint)*pbVar5;
      iVar2 = iVar2 + -0x30;
    } while ((uVar3 - 0x30 & 0xff) < 10);
    iVar6 = iVar6 * iVar2;
  }
  else {
    iVar6 = 0;
  }
  return iVar6;
}
