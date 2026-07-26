/*
 * mangled: _Z14RShellBlankTgaP10cTgaHeaderii
 * demangled: RShellBlankTga(cTgaHeader*, int, int)
 * address: 0002a350
 * size: 216
 */

/* RShellBlankTga(cTgaHeader*, int, int) */

void RShellBlankTga(cTgaHeader *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar3 = 0;
  iVar4 = 2;
  param_1[0x11] = (cTgaHeader)0x8;
  *(short *)(param_1 + 0xc) = (short)param_2;
  *(short *)(param_1 + 0xe) = (short)param_3;
  param_1[7] = (cTgaHeader)0x0;
  param_1[0x10] = (cTgaHeader)0x20;
  param_1[2] = (cTgaHeader)0x2;
  param_1[6] = (cTgaHeader)0x0;
  param_1[5] = (cTgaHeader)0x0;
  param_1[4] = (cTgaHeader)0x0;
  param_1[3] = (cTgaHeader)0x0;
  param_1[1] = (cTgaHeader)0x0;
  *param_1 = (cTgaHeader)0x0;
  *(undefined2 *)(param_1 + 8) = 0;
  *(undefined2 *)(param_1 + 10) = 0;
  if (0 < param_2) {
    do {
      if (0 < param_3) {
        iVar5 = 0;
        iVar1 = iVar4;
        iVar2 = iVar3 << 2;
        do {
          iVar5 = iVar5 + 1;
          param_1[iVar2 + 0x12] = (cTgaHeader)0x0;
          param_1[iVar2 + 0x13] = (cTgaHeader)0x0;
          param_1[iVar1 + 0x12] = (cTgaHeader)0x0;
          param_1[iVar2 + 0x15] = (cTgaHeader)0x0;
          iVar1 = iVar1 + param_2 * 4;
          iVar2 = iVar2 + param_2 * 4;
        } while (iVar5 != param_3);
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar3 != param_2);
  }
  return;
}
