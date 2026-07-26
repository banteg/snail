/*
 * mangled: _ZN15cRSpriteManager3NewEiiii
 * demangled: cRSpriteManager::New(int, int, int, int)
 * address: 0001123c
 * size: 356
 */

/* cRSpriteManager::New(int, int, int, int) */

undefined4 * cRSpriteManager::New(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;

  puVar4 = *(undefined4 **)(param_1 + 0x2af90);
  if (puVar4 == (undefined4 *)0x0) {
    puVar4 = &_gSpriteDummy;
  }
  else {
    *(undefined4 *)(param_1 + 0x2af90) = puVar4[3];
    iVar1 = param_2 * 4 + param_1;
    puVar4[2] = param_2;
    if (*(int *)(iVar1 + 0x2af84) != 0) {
      *(undefined4 **)(*(int *)(iVar1 + 0x2af84) + 0x10) = puVar4;
    }
    puVar4[4] = 0;
    puVar4[3] = *(undefined4 *)(iVar1 + 0x2af84);
    *(undefined4 **)(iVar1 + 0x2af84) = puVar4;
    puVar4[1] = 0x49;
    tColour::White((tColour *)(puVar4 + 0xb));
    puVar4[0x1e] = 0xbc54fdf4;
    puVar4[0x21] = 0x3f800000;
    puVar4[10] = 1;
    puVar4[0x29] = 1;
    puVar4[0x24] = 0xc3fa0000;
    *puVar4 = 0xffffffff;
    puVar4[0x26] = 0;
    uVar2 = puVar4[1] | 1 << (param_2 + 0x18U & 0xff);
    iVar1 = param_3 * 0x20;
    puVar4[0x27] = 0;
    puVar4[0x1a] = 0;
    puVar4[0x1c] = 0;
    puVar4[0x1d] = 0;
    puVar4[0x1f] = 0;
    puVar4[0x20] = 0;
    puVar4[0x22] = 0;
    puVar4[0x23] = 0;
    puVar4[8] = 0;
    puVar4[9] = 0;
    puVar4[0x17] = 0;
    puVar4[0x16] = 0;
    puVar4[0x15] = 0;
    puVar4[0x25] = 0;
    puVar4[0x28] = 0;
    puVar4[0x2a] = 0;
    puVar4[0x2b] = 0;
    puVar4[1] = uVar2;
    uVar3 = *(undefined4 *)(&DAT_002ac600 + iVar1);
    puVar4[0x19] = 0;
    puVar4[0x26] = param_3;
    puVar4[7] = uVar3;
    puVar4[0x27] = *(undefined4 *)(*(int *)(&DAT_002ac600 + iVar1) + 0x90);
    if ((**(uint **)(&DAT_002ac600 + iVar1) & 0x2000) != 0) {
      puVar4[1] = uVar2 | 0x2000;
      puVar4[0x2b] = *(undefined4 *)(*(int *)(&DAT_002ac600 + iVar1) + 0x94);
      if ((**(uint **)(&DAT_002ac600 + iVar1) & 0x4000) != 0) {
        puVar4[1] = uVar2 | 0x6000;
      }
    }
  }
  return puVar4;
}
