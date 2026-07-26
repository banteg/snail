/*
 * mangled: _ZN8cRVapour3AddER7tMatrix
 * demangled: cRVapour::Add(tMatrix&)
 * address: 00017bec
 * size: 244
 */

/* cRVapour::Add(tMatrix&) */

void __thiscall cRVapour::Add(cRVapour *this,tMatrix *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  int unaff_r5;
  undefined4 *puVar6;

  iVar2 = *(int *)(this + 0x74);
  iVar4 = *(int *)(this + 0x78);
  if (iVar4 <= iVar2) {
    if (iVar4 != 1 && -1 < iVar4 + -1) {
      unaff_r5 = 0;
    }
    if (0 < iVar4 + -1) {
      do {
        iVar2 = unaff_r5 * 0x40;
        unaff_r5 = unaff_r5 + 1;
        puVar6 = (undefined4 *)(*(int *)(this + 0x84) + iVar2);
        *puVar6 = puVar6[0x10];
        puVar6[1] = puVar6[0x11];
        puVar6[2] = puVar6[0x12];
        puVar6[3] = puVar6[0x13];
        puVar6[4] = puVar6[0x14];
        puVar6[5] = puVar6[0x15];
        puVar6[6] = puVar6[0x16];
        puVar6[7] = puVar6[0x17];
        puVar6[8] = puVar6[0x18];
        puVar6[9] = puVar6[0x19];
        puVar6[10] = puVar6[0x1a];
        puVar6[0xb] = puVar6[0x1b];
        puVar6[0xc] = puVar6[0x1c];
        puVar6[0xd] = puVar6[0x1d];
        puVar6[0xe] = puVar6[0x1e];
        puVar6[0xf] = puVar6[0x1f];
      } while (unaff_r5 < *(int *)(this + 0x78) + -1);
      iVar2 = *(int *)(this + 0x74);
    }
    iVar2 = iVar2 * 0x40 + *(int *)(this + 0x84);
    uVar1 = *(undefined4 *)(param_1 + 4);
    uVar3 = *(undefined4 *)(param_1 + 8);
    uVar5 = *(undefined4 *)(param_1 + 0xc);
    *(undefined4 *)(iVar2 + -0x40) = *(undefined4 *)param_1;
    *(undefined4 *)(iVar2 + -0x3c) = uVar1;
    *(undefined4 *)(iVar2 + -0x38) = uVar3;
    *(undefined4 *)(iVar2 + -0x34) = uVar5;
    uVar1 = *(undefined4 *)(param_1 + 0x14);
    uVar3 = *(undefined4 *)(param_1 + 0x18);
    uVar5 = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(iVar2 + -0x30) = *(undefined4 *)(param_1 + 0x10);
    *(undefined4 *)(iVar2 + -0x2c) = uVar1;
    *(undefined4 *)(iVar2 + -0x28) = uVar3;
    *(undefined4 *)(iVar2 + -0x24) = uVar5;
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    uVar3 = *(undefined4 *)(param_1 + 0x28);
    uVar5 = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(iVar2 + -0x20) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(iVar2 + -0x1c) = uVar1;
    *(undefined4 *)(iVar2 + -0x18) = uVar3;
    *(undefined4 *)(iVar2 + -0x14) = uVar5;
    uVar1 = *(undefined4 *)(param_1 + 0x34);
    uVar3 = *(undefined4 *)(param_1 + 0x38);
    uVar5 = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(iVar2 + -0x10) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(iVar2 + -0xc) = uVar1;
    *(undefined4 *)(iVar2 + -8) = uVar3;
    *(undefined4 *)(iVar2 + -4) = uVar5;
    return;
  }
  puVar6 = (undefined4 *)(iVar2 * 0x40 + *(int *)(this + 0x84));
  uVar1 = *(undefined4 *)(param_1 + 4);
  uVar3 = *(undefined4 *)(param_1 + 8);
  uVar5 = *(undefined4 *)(param_1 + 0xc);
  *puVar6 = *(undefined4 *)param_1;
  puVar6[1] = uVar1;
  puVar6[2] = uVar3;
  puVar6[3] = uVar5;
  uVar1 = *(undefined4 *)(param_1 + 0x14);
  uVar3 = *(undefined4 *)(param_1 + 0x18);
  uVar5 = *(undefined4 *)(param_1 + 0x1c);
  puVar6[4] = *(undefined4 *)(param_1 + 0x10);
  puVar6[5] = uVar1;
  puVar6[6] = uVar3;
  puVar6[7] = uVar5;
  uVar1 = *(undefined4 *)(param_1 + 0x24);
  uVar3 = *(undefined4 *)(param_1 + 0x28);
  uVar5 = *(undefined4 *)(param_1 + 0x2c);
  puVar6[8] = *(undefined4 *)(param_1 + 0x20);
  puVar6[9] = uVar1;
  puVar6[10] = uVar3;
  puVar6[0xb] = uVar5;
  uVar1 = *(undefined4 *)(param_1 + 0x34);
  uVar3 = *(undefined4 *)(param_1 + 0x38);
  uVar5 = *(undefined4 *)(param_1 + 0x3c);
  puVar6[0xc] = *(undefined4 *)(param_1 + 0x30);
  puVar6[0xd] = uVar1;
  puVar6[0xe] = uVar3;
  puVar6[0xf] = uVar5;
  *(int *)(this + 0x74) = *(int *)(this + 0x74) + 1;
  return;
}
