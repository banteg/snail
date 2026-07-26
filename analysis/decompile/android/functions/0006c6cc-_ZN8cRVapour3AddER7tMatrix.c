/*
 * mangled: _ZN8cRVapour3AddER7tMatrix
 * demangled: cRVapour::Add(tMatrix&)
 * address: 0006c6cc
 * size: 208
 */

/* cRVapour::Add(tMatrix&) */

void __thiscall cRVapour::Add(cRVapour *this,tMatrix *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;

  iVar7 = *(int *)(this + 0x74);
  iVar6 = *(int *)(this + 0x78);
  if (iVar7 < iVar6) {
    uVar1 = *(undefined4 *)(param_1 + 4);
    uVar2 = *(undefined4 *)(param_1 + 8);
    uVar3 = *(undefined4 *)(param_1 + 0xc);
    puVar8 = (undefined4 *)(*(int *)(this + 0x84) + iVar7 * 0x40);
    *puVar8 = *(undefined4 *)param_1;
    puVar8[1] = uVar1;
    puVar8[2] = uVar2;
    puVar8[3] = uVar3;
    uVar1 = *(undefined4 *)(param_1 + 0x14);
    uVar2 = *(undefined4 *)(param_1 + 0x18);
    uVar3 = *(undefined4 *)(param_1 + 0x1c);
    puVar8[4] = *(undefined4 *)(param_1 + 0x10);
    puVar8[5] = uVar1;
    puVar8[6] = uVar2;
    puVar8[7] = uVar3;
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    uVar2 = *(undefined4 *)(param_1 + 0x28);
    uVar3 = *(undefined4 *)(param_1 + 0x2c);
    puVar8[8] = *(undefined4 *)(param_1 + 0x20);
    puVar8[9] = uVar1;
    puVar8[10] = uVar2;
    puVar8[0xb] = uVar3;
    uVar1 = *(undefined4 *)(param_1 + 0x34);
    uVar2 = *(undefined4 *)(param_1 + 0x38);
    uVar3 = *(undefined4 *)(param_1 + 0x3c);
    puVar8[0xc] = *(undefined4 *)(param_1 + 0x30);
    puVar8[0xd] = uVar1;
    puVar8[0xe] = uVar2;
    puVar8[0xf] = uVar3;
    *(int *)(this + 0x74) = iVar7 + 1;
  }
  else {
    if (iVar6 < 2) {
      puVar8 = *(undefined4 **)(this + 0x84);
    }
    else {
      puVar8 = *(undefined4 **)(this + 0x84);
      iVar5 = 1;
      puVar4 = puVar8;
      do {
        iVar5 = iVar5 + 1;
        *puVar4 = puVar4[0x10];
        puVar4[1] = puVar4[0x11];
        puVar4[2] = puVar4[0x12];
        puVar4[3] = puVar4[0x13];
        puVar4[4] = puVar4[0x14];
        puVar4[5] = puVar4[0x15];
        puVar4[6] = puVar4[0x16];
        puVar4[7] = puVar4[0x17];
        puVar4[8] = puVar4[0x18];
        puVar4[9] = puVar4[0x19];
        puVar4[10] = puVar4[0x1a];
        puVar4[0xb] = puVar4[0x1b];
        puVar4[0xc] = puVar4[0x1c];
        puVar4[0xd] = puVar4[0x1d];
        puVar4[0xe] = puVar4[0x1e];
        puVar4[0xf] = puVar4[0x1f];
        puVar4 = puVar4 + 0x10;
      } while (iVar5 != iVar6);
    }
    uVar1 = *(undefined4 *)(param_1 + 4);
    uVar2 = *(undefined4 *)(param_1 + 8);
    uVar3 = *(undefined4 *)(param_1 + 0xc);
    puVar8 = puVar8 + (iVar7 + -1) * 0x10;
    *puVar8 = *(undefined4 *)param_1;
    puVar8[1] = uVar1;
    puVar8[2] = uVar2;
    puVar8[3] = uVar3;
    uVar1 = *(undefined4 *)(param_1 + 0x14);
    uVar2 = *(undefined4 *)(param_1 + 0x18);
    uVar3 = *(undefined4 *)(param_1 + 0x1c);
    puVar8[4] = *(undefined4 *)(param_1 + 0x10);
    puVar8[5] = uVar1;
    puVar8[6] = uVar2;
    puVar8[7] = uVar3;
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    uVar2 = *(undefined4 *)(param_1 + 0x28);
    uVar3 = *(undefined4 *)(param_1 + 0x2c);
    puVar8[8] = *(undefined4 *)(param_1 + 0x20);
    puVar8[9] = uVar1;
    puVar8[10] = uVar2;
    puVar8[0xb] = uVar3;
    uVar1 = *(undefined4 *)(param_1 + 0x34);
    uVar2 = *(undefined4 *)(param_1 + 0x38);
    uVar3 = *(undefined4 *)(param_1 + 0x3c);
    puVar8[0xc] = *(undefined4 *)(param_1 + 0x30);
    puVar8[0xd] = uVar1;
    puVar8[0xe] = uVar2;
    puVar8[0xf] = uVar3;
  }
  return;
}
