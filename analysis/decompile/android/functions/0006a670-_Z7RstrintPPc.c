/*
 * mangled: _Z7RstrintPPc
 * demangled: Rstrint(char**)
 * address: 0006a670
 * size: 228
 */

/* Rstrint(char**) */

int Rstrint(char **param_1)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;

  pbVar4 = (byte *)*param_1;
  bVar2 = *pbVar4;
  pbVar5 = pbVar4;
  if (bVar2 != 0x2b && bVar2 != 0x2d) {
    do {
      if (bVar2 == 0x2e) goto LAB_0006a740;
      if ((byte)(bVar2 - 0x30) < 10) goto LAB_0006a734;
      pbVar4 = pbVar5 + 1;
      *param_1 = (char *)pbVar4;
      bVar2 = *pbVar4;
      pbVar5 = pbVar4;
    } while (bVar2 != 0x2b && bVar2 != 0x2d);
  }
  if (bVar2 == 0x2d) {
    pbVar5 = pbVar4 + 1;
    *param_1 = (char *)pbVar5;
    bVar2 = pbVar4[1];
    iVar6 = -1;
  }
  else {
    pbVar5 = (byte *)*param_1;
LAB_0006a734:
    iVar6 = 1;
    bVar2 = *pbVar5;
  }
  uVar1 = (uint)bVar2;
  if ((uVar1 - 0x30 & 0xff) < 10) {
    iVar3 = 0;
    do {
      pbVar5 = pbVar5 + 1;
      *param_1 = (char *)pbVar5;
      iVar3 = uVar1 + iVar3 * 10;
      uVar1 = (uint)*pbVar5;
      iVar3 = iVar3 + -0x30;
    } while ((uVar1 - 0x30 & 0xff) < 10);
    iVar6 = iVar6 * iVar3;
  }
  else {
LAB_0006a740:
    iVar6 = 0;
  }
  return iVar6;
}
