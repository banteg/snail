/*
 * mangled: _ZN15cRSpriteManager3NewEiiii
 * demangled: cRSpriteManager::New(int, int, int, int)
 * address: 0003de1c
 * size: 244
 */

/* cRSpriteManager::New(int, int, int, int) */

cRSprite * cRSpriteManager::New(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  cRSprite *this;
  int iVar7;

  this = *(cRSprite **)(param_1 + 0x2af90);
  iVar5 = DAT_0003df14 + 0x3de48;
  if (this == (cRSprite *)0x0) {
    return *(cRSprite **)(iVar5 + DAT_0003df1c);
  }
  *(int *)(this + 8) = param_2;
  *(undefined4 *)(param_1 + 0x2af90) = *(undefined4 *)(this + 0xc);
  iVar7 = param_1 + (param_2 + 44000) * 4;
  iVar3 = *(int *)(param_1 + (param_2 + 44000) * 4 + 4);
  if (iVar3 != 0) {
    *(cRSprite **)(iVar3 + 0x10) = this;
  }
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar7 + 4);
  *(cRSprite **)(iVar7 + 4) = this;
  cRSprite::Init(this);
  iVar3 = DAT_0003df18;
  *(int *)(this + 0x98) = param_3;
  uVar1 = DAT_0003df10;
  iVar5 = *(int *)(iVar5 + iVar3);
  *(undefined4 *)(this + 0xac) = DAT_0003df10;
  uVar6 = *(uint *)(this + 4) | 1 << (param_2 + 0x18U & 0xff);
  *(uint *)(this + 4) = uVar6;
  *(undefined4 *)(this + 100) = uVar1;
  *(undefined4 *)(this + 0xa8) = uVar1;
  puVar4 = *(uint **)(iVar5 + param_3 * 0x20 + 4);
  uVar2 = puVar4[0x24];
  *(uint **)(this + 0x1c) = puVar4;
  *(uint *)(this + 0x9c) = uVar2;
  uVar2 = *puVar4;
  if ((uVar2 & 0x2000) != 0) {
    *(uint *)(this + 0xac) = puVar4[0x25];
    *(uint *)(this + 4) = uVar6 | 0x2000;
    if ((uVar2 & 0x4000) != 0) {
      *(uint *)(this + 4) = uVar6 | 0x6000;
    }
  }
  return this;
}
