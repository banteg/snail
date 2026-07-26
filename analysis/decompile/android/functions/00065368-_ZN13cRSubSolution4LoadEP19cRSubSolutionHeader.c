/*
 * mangled: _ZN13cRSubSolution4LoadEP19cRSubSolutionHeader
 * demangled: cRSubSolution::Load(cRSubSolutionHeader*)
 * address: 00065368
 * size: 440
 */

/* cRSubSolution::Load(cRSubSolutionHeader*) */

void __thiscall cRSubSolution::Load(cRSubSolution *this,cRSubSolutionHeader *param_1)

{
  int iVar1;
  cRSubSolution *pcVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  cRSubSolutionHeader *pcVar7;
  undefined4 uVar8;

  if (*(uint *)(param_1 + 0x28) == (*(int *)(param_1 + 4) * *(int *)(param_1 + 4) ^ 0xdeadbabeU)) {
    uVar4 = *(undefined4 *)(param_1 + 0x74);
    *(undefined4 *)(this + 0x48) = *(undefined4 *)(param_1 + 0x48);
    uVar8 = *(undefined4 *)(param_1 + 0x54);
    *(undefined4 *)(this + 0x6c) = uVar4;
    *(undefined4 *)(this + 0x34) = uVar8;
    *(undefined4 *)(this + 0x28) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(this + 0x2c) = *(undefined4 *)(param_1 + 0x30);
    Rstrcpy((char *)(this + 0x54),(char *)(param_1 + 0x5c));
    *(undefined4 *)(this + 4) = *(undefined4 *)(param_1 + 4);
    uVar4 = *(undefined4 *)(param_1 + 0xc);
    uVar8 = *(undefined4 *)(param_1 + 0x10);
    uVar5 = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)(this + 8) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(this + 0xc) = uVar4;
    *(undefined4 *)(this + 0x10) = uVar8;
    *(undefined4 *)(this + 0x14) = uVar5;
    uVar4 = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(this + 0x18) = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 *)(this + 0x1c) = uVar4;
    uVar4 = *(undefined4 *)(param_1 + 0x4c);
    *(undefined4 *)(this + 0x20) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(this + 0x1fab0) = *(undefined4 *)(param_1 + 0x78);
    uVar8 = *(undefined4 *)(param_1 + 0x7c);
    *(undefined4 *)(this + 0x4c) = uVar4;
    uVar4 = *(undefined4 *)(param_1 + 0x50);
    *(undefined4 *)(this + 0x1fab4) = uVar8;
    *(undefined4 *)(this + 0x1fab8) = *(undefined4 *)(param_1 + 0x80);
    *(undefined4 *)(this + 0x50) = uVar4;
    uVar4 = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(this + 0x1fabc) = *(undefined4 *)(param_1 + 0x84);
    *(undefined4 *)(this + 0x24) = uVar4;
    *(undefined4 *)(this + 0x68) = *(undefined4 *)(param_1 + 0x70);
    *(undefined4 *)(this + 0x38) = *(undefined4 *)(param_1 + 0x38);
    iVar3 = *(int *)(this + 0x6c);
    *(undefined4 *)(this + 0x3c) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(this + 0x44) = *(undefined4 *)(param_1 + 0x44);
    if (0 < iVar3) {
      iVar6 = 0;
      pcVar2 = this;
      pcVar7 = param_1 + 0x88;
      do {
        iVar6 = iVar6 + 1;
        *(undefined2 *)(pcVar2 + 0x70) = *(undefined2 *)pcVar7;
        pcVar2 = pcVar2 + 6;
        pcVar7 = pcVar7 + 2;
      } while (iVar6 < iVar3);
      iVar6 = 0;
      pcVar2 = this;
      do {
        iVar1 = iVar6 * 2;
        iVar6 = iVar6 + 1;
        *(undefined2 *)(pcVar2 + 0x72) = *(undefined2 *)(param_1 + iVar1 + (iVar3 + 0x44) * 2);
        pcVar2 = pcVar2 + 6;
      } while (iVar6 < iVar3);
      if (0 < iVar3) {
        iVar6 = 0;
        pcVar2 = this;
        do {
          iVar1 = iVar6 + (iVar3 + 0x22) * 4;
          iVar6 = iVar6 + 1;
          *(ushort *)(pcVar2 + 0x74) = (ushort)(byte)param_1[iVar1];
          pcVar2 = pcVar2 + 6;
        } while (iVar6 < iVar3);
      }
    }
    *(undefined4 *)this = 1;
    return;
  }
  *(undefined4 *)this = 0;
  return;
}
