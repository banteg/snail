/*
 * mangled: _ZN13cRSubSolution4SaveEPh
 * demangled: cRSubSolution::Save(unsigned char*)
 * address: 00065638
 * size: 452
 */

/* cRSubSolution::Save(unsigned char*) */

void __thiscall cRSubSolution::Save(cRSubSolution *this,uchar *param_1)

{
  cRSubSolution *pcVar1;
  int iVar2;
  int iVar3;
  cRSubSolution *pcVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  uchar *puVar9;

  uVar6 = *(undefined4 *)(this + 0x6c);
  *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(this + 0x48);
  *(undefined4 *)this = 1;
  *(undefined4 *)(param_1 + 0x74) = uVar6;
  uVar6 = *(undefined4 *)(this + 0x28);
  *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(this + 0x34);
  *(undefined4 *)(param_1 + 0x2c) = uVar6;
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(this + 0x2c);
  Rstrcpy((char *)(param_1 + 0x5c),(char *)(this + 0x54));
  uVar6 = *(undefined4 *)(this + 0xc);
  uVar5 = *(undefined4 *)(this + 0x10);
  uVar7 = *(undefined4 *)(this + 0x14);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(this + 8);
  *(undefined4 *)(param_1 + 0xc) = uVar6;
  *(undefined4 *)(param_1 + 0x10) = uVar5;
  *(undefined4 *)(param_1 + 0x14) = uVar7;
  uVar6 = *(undefined4 *)(this + 0x1c);
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(this + 0x18);
  *(undefined4 *)(param_1 + 0x1c) = uVar6;
  uVar6 = *(undefined4 *)(this + 0x4c);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(this + 0x20);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(this + 0x1fab0);
  *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(this + 0x1fab4);
  *(undefined4 *)(param_1 + 0x4c) = uVar6;
  uVar6 = *(undefined4 *)(this + 0x50);
  *(undefined4 *)(param_1 + 0x80) = *(undefined4 *)(this + 0x1fab8);
  uVar5 = *(undefined4 *)(this + 0x1fabc);
  *(undefined4 *)(param_1 + 0x50) = uVar6;
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(this + 0x24);
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(this + 4);
  *(uint *)(param_1 + 0x28) = *(int *)(this + 4) * *(int *)(this + 4) ^ 0xdeadbabe;
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(this + 0x68);
  *(undefined4 *)(param_1 + 0x84) = uVar5;
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(this + 0x38);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(this + 0x3c);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(this + 0x40);
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(this + 0x44);
  iVar2 = *(int *)(this + 0x6c);
  if (iVar2 < 1) {
    iVar3 = iVar2 + 0x22;
  }
  else {
    iVar3 = 0;
    pcVar4 = this;
    puVar9 = param_1 + 0x88;
    do {
      pcVar1 = pcVar4 + 0x70;
      iVar3 = iVar3 + 1;
      pcVar4 = pcVar4 + 6;
      *(undefined2 *)puVar9 = *(undefined2 *)pcVar1;
      puVar9 = puVar9 + 2;
    } while (iVar3 < iVar2);
    iVar3 = 0;
    pcVar4 = this;
    do {
      iVar8 = iVar3 * 2;
      pcVar1 = pcVar4 + 0x72;
      iVar3 = iVar3 + 1;
      pcVar4 = pcVar4 + 6;
      *(undefined2 *)(param_1 + iVar8 + (iVar2 + 0x44) * 2) = *(undefined2 *)pcVar1;
    } while (iVar3 < iVar2);
    iVar3 = iVar2 + 0x22;
    if (0 < iVar2) {
      iVar8 = 0;
      pcVar4 = this;
      do {
        pcVar1 = pcVar4 + 0x74;
        pcVar4 = pcVar4 + 6;
        param_1[iVar8 + iVar3 * 4] = (uchar)*(undefined2 *)pcVar1;
        iVar8 = iVar8 + 1;
        iVar2 = *(int *)(this + 0x6c);
      } while (iVar8 < iVar2);
      iVar3 = iVar2 + 0x22;
    }
  }
  *(int *)param_1 = iVar2 + iVar3 * 4;
  return;
}
