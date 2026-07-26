/*
 * mangled: _ZN6cRPath6MirrorEPS_
 * demangled: cRPath::Mirror(cRPath*)
 * address: 00056e74
 * size: 820
 */

/* cRPath::Mirror(cRPath*) */

void __thiscall cRPath::Mirror(cRPath *this,cRPath *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;

  uVar2 = *(undefined4 *)(param_1 + 0x40);
  this[0x30] = (cRPath)0x1;
  *(undefined4 *)(this + 0x40) = uVar2;
  iVar4 = *(int *)(param_1 + 0x38);
  *(undefined4 *)(this + 0x44) = *(undefined4 *)(param_1 + 0x44);
  uVar2 = *(undefined4 *)(param_1 + 0x48);
  *(int *)(this + 0x38) = iVar4;
  *(undefined4 *)(this + 0x48) = uVar2;
  uVar2 = RShellMemoryMalloc(iVar4 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)(this + 0x4c) = uVar2;
  uVar2 = RShellMemoryMalloc(*(int *)(this + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(this + 0x50) = uVar2;
  if (0 < *(int *)(this + 0x38)) {
    iVar4 = 0;
    iVar1 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar1 + 0xa0) = 0;
      iVar5 = *(int *)(this + 0x4c) + iVar1;
      iVar1 = iVar1 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)(this + 0x38));
  }
  this[0x84] = param_1[0x84];
  **(undefined4 **)(this + 0x24) = **(undefined4 **)(param_1 + 0x24);
  *(undefined4 *)(this + 0x2c) = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(this + 0x34) = *(undefined4 *)(param_1 + 0x34);
  if (0 < *(int *)(this + 0x38)) {
    iVar4 = 0;
    iVar1 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(float *)(*(int *)(this + 0x4c) + iVar1 + 0x90) =
           -*(float *)(*(int *)(param_1 + 0x4c) + iVar1 + 0x90);
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar1 + 0x9c) =
           *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar1 + 0x9c);
      *(float *)(*(int *)(this + 0x4c) + iVar1 + 0x98) =
           -*(float *)(*(int *)(param_1 + 0x4c) + iVar1 + 0x98);
      *(float *)(*(int *)(this + 0x4c) + iVar1 + 0x94) =
           -*(float *)(*(int *)(param_1 + 0x4c) + iVar1 + 0x94);
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar1 + 0xa0) =
           *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar1 + 0xa0);
      puVar8 = (undefined4 *)(*(int *)(param_1 + 0x4c) + iVar1);
      puVar9 = (undefined4 *)(*(int *)(this + 0x4c) + iVar1);
      uVar2 = puVar8[1];
      uVar3 = puVar8[2];
      uVar6 = puVar8[3];
      *puVar9 = *puVar8;
      puVar9[1] = uVar2;
      puVar9[2] = uVar3;
      puVar9[3] = uVar6;
      uVar2 = puVar8[5];
      uVar3 = puVar8[6];
      uVar6 = puVar8[7];
      puVar9[4] = puVar8[4];
      puVar9[5] = uVar2;
      puVar9[6] = uVar3;
      puVar9[7] = uVar6;
      uVar2 = puVar8[9];
      uVar3 = puVar8[10];
      uVar6 = puVar8[0xb];
      puVar9[8] = puVar8[8];
      puVar9[9] = uVar2;
      puVar9[10] = uVar3;
      puVar9[0xb] = uVar6;
      uVar2 = puVar8[0xd];
      uVar3 = puVar8[0xe];
      uVar6 = puVar8[0xf];
      puVar9[0xc] = puVar8[0xc];
      puVar9[0xd] = uVar2;
      puVar9[0xe] = uVar3;
      puVar9[0xf] = uVar6;
      *(float *)(iVar1 + *(int *)(this + 0x4c)) = -*(float *)(iVar1 + *(int *)(this + 0x4c));
      *(float *)(iVar1 + *(int *)(this + 0x4c) + 0x10) =
           -*(float *)(iVar1 + *(int *)(this + 0x4c) + 0x10);
      *(float *)(iVar1 + *(int *)(this + 0x4c) + 0x20) =
           -*(float *)(iVar1 + *(int *)(this + 0x4c) + 0x20);
      *(float *)(iVar1 + *(int *)(this + 0x4c) + 0x30) =
           -*(float *)(iVar1 + *(int *)(this + 0x4c) + 0x30);
      iVar5 = *(int *)(param_1 + 0x4c) + iVar1;
      iVar7 = *(int *)(this + 0x4c) + iVar1;
      uVar2 = *(undefined4 *)(iVar5 + 0x84);
      uVar3 = *(undefined4 *)(iVar5 + 0x88);
      *(undefined4 *)(iVar7 + 0x80) = *(undefined4 *)(iVar5 + 0x80);
      *(undefined4 *)(iVar7 + 0x84) = uVar2;
      *(undefined4 *)(iVar7 + 0x88) = uVar3;
      *(float *)(iVar1 + *(int *)(this + 0x4c) + 0x80) =
           -*(float *)(iVar1 + *(int *)(this + 0x4c) + 0x80);
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar1 + 0x8c) =
           *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar1 + 0x8c);
      puVar8 = (undefined4 *)(*(int *)(param_1 + 0x50) + iVar1);
      puVar9 = (undefined4 *)(*(int *)(this + 0x50) + iVar1);
      uVar2 = puVar8[1];
      uVar3 = puVar8[2];
      uVar6 = puVar8[3];
      *puVar9 = *puVar8;
      puVar9[1] = uVar2;
      puVar9[2] = uVar3;
      puVar9[3] = uVar6;
      uVar2 = puVar8[5];
      uVar3 = puVar8[6];
      uVar6 = puVar8[7];
      puVar9[4] = puVar8[4];
      puVar9[5] = uVar2;
      puVar9[6] = uVar3;
      puVar9[7] = uVar6;
      uVar2 = puVar8[9];
      uVar3 = puVar8[10];
      uVar6 = puVar8[0xb];
      puVar9[8] = puVar8[8];
      puVar9[9] = uVar2;
      puVar9[10] = uVar3;
      puVar9[0xb] = uVar6;
      uVar2 = puVar8[0xd];
      uVar3 = puVar8[0xe];
      uVar6 = puVar8[0xf];
      puVar9[0xc] = puVar8[0xc];
      puVar9[0xd] = uVar2;
      puVar9[0xe] = uVar3;
      puVar9[0xf] = uVar6;
      *(float *)(iVar1 + *(int *)(this + 0x50)) = -*(float *)(iVar1 + *(int *)(this + 0x50));
      *(float *)(iVar1 + *(int *)(this + 0x50) + 0x10) =
           -*(float *)(iVar1 + *(int *)(this + 0x50) + 0x10);
      *(float *)(iVar1 + *(int *)(this + 0x50) + 0x20) =
           -*(float *)(iVar1 + *(int *)(this + 0x50) + 0x20);
      *(float *)(iVar1 + *(int *)(this + 0x50) + 0x30) =
           -*(float *)(iVar1 + *(int *)(this + 0x50) + 0x30);
      iVar5 = *(int *)(param_1 + 0x50) + iVar1;
      iVar7 = *(int *)(this + 0x50) + iVar1;
      uVar2 = *(undefined4 *)(iVar5 + 0x84);
      uVar3 = *(undefined4 *)(iVar5 + 0x88);
      *(undefined4 *)(iVar7 + 0x80) = *(undefined4 *)(iVar5 + 0x80);
      *(undefined4 *)(iVar7 + 0x84) = uVar2;
      *(undefined4 *)(iVar7 + 0x88) = uVar3;
      *(float *)(iVar1 + *(int *)(this + 0x50) + 0x80) =
           -*(float *)(iVar1 + *(int *)(this + 0x50) + 0x80);
      iVar5 = *(int *)(this + 0x50) + iVar1;
      iVar7 = *(int *)(param_1 + 0x50) + iVar1;
      iVar1 = iVar1 + 0xa8;
      *(undefined4 *)(iVar5 + 0x8c) = *(undefined4 *)(iVar7 + 0x8c);
    } while (iVar4 < *(int *)(this + 0x38));
  }
  CalcLengthZ(this);
  return;
}
