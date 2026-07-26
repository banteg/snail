/*
 * mangled: _ZN15cRSpriteManager3NewEiiii
 * demangled: cRSpriteManager::New(int, int, int, int)
 * address: 0003de1c
 * size: 244
 */

/* cRSpriteManager::New(int, int, int, int) */

cRSprite * cRSpriteManager::New(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  cRSprite *this;
  int iVar5;

  this = *(cRSprite **)(param_1 + 0x2af90);
  if (this == (cRSprite *)0x0) {
    return (cRSprite *)gSpriteDummy;
  }
  *(int *)(this + 8) = param_2;
  *(undefined4 *)(param_1 + 0x2af90) = *(undefined4 *)(this + 0xc);
  iVar5 = param_1 + (param_2 + 44000) * 4;
  iVar2 = *(int *)(param_1 + (param_2 + 44000) * 4 + 4);
  if (iVar2 != 0) {
    *(cRSprite **)(iVar2 + 0x10) = this;
  }
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar5 + 4);
  *(cRSprite **)(iVar5 + 4) = this;
  cRSprite::Init(this);
  *(int *)(this + 0x98) = param_3;
  *(undefined4 *)(this + 0xac) = 0;
  uVar4 = *(uint *)(this + 4) | 1 << (param_2 + 0x18U & 0xff);
  *(uint *)(this + 4) = uVar4;
  *(undefined4 *)(this + 100) = 0;
  *(undefined4 *)(this + 0xa8) = 0;
  puVar3 = *(uint **)(gSpriteReference + param_3 * 0x20 + 4);
  uVar1 = puVar3[0x24];
  *(uint **)(this + 0x1c) = puVar3;
  *(uint *)(this + 0x9c) = uVar1;
  uVar1 = *puVar3;
  if ((uVar1 & 0x2000) != 0) {
    *(uint *)(this + 0xac) = puVar3[0x25];
    *(uint *)(this + 4) = uVar4 | 0x2000;
    if ((uVar1 & 0x4000) != 0) {
      *(uint *)(this + 4) = uVar4 | 0x6000;
    }
  }
  return this;
}
