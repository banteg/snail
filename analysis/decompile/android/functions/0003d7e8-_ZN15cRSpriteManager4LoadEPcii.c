/*
 * mangled: _ZN15cRSpriteManager4LoadEPcii
 * demangled: cRSpriteManager::Load(char*, int, int)
 * address: 0003d7e8
 * size: 412
 */

/* cRSpriteManager::Load(char*, int, int) */

void __thiscall cRSpriteManager::Load(cRSpriteManager *this,char *param_1,int param_2,int param_3)

{
  char cVar1;
  cRSpriteManager cVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  uint uVar9;
  undefined4 uVar10;
  undefined4 uVar11;

  cVar1 = *param_1;
  pcVar8 = param_1;
  while (cVar1 != '.') {
    pcVar8 = pcVar8 + 1;
    cVar1 = *pcVar8;
  }
  if (this[0x2af94] == (cRSpriteManager)0x0) {
    iVar5 = 0;
  }
  else {
    iVar5 = SearchSet(this,param_1);
  }
  if (199 < param_2) {
    RShellError("Too many Sprite References - Increase RSPRITE_REFERENCE_MAX(%i) in RSprite.h",200);
  }
  if (iVar5 != 0) {
    uVar10 = *(undefined4 *)(iVar5 + 0x40);
    iVar3 = param_2 * 4 + 1;
    iVar6 = param_2 * 2 + 1;
    uVar11 = *(undefined4 *)(iVar5 + 0x48);
    gSpriteReference[param_2 * 0x20] = 1;
    cVar2 = this[0x2af9c];
    iVar7 = param_2 * 0x20;
    *(undefined4 *)(gSpriteReference + iVar3 * 8) = uVar10;
    uVar10 = *(undefined4 *)(iVar5 + 0x44);
    *(undefined4 *)(gSpriteReference + iVar6 * 0x10) = uVar11;
    *(undefined4 *)(gSpriteReference + iVar6 * 0x10 + 4) = *(undefined4 *)(iVar5 + 0x4c);
    puVar4 = *(uint **)(gSpriteReference + (uint)(byte)cVar2 * 0x20 + 4);
    uVar11 = *(undefined4 *)(iVar5 + 0x50);
    *(undefined4 *)(gSpriteReference + iVar3 * 8 + 4) = uVar10;
    *(undefined4 *)(gSpriteReference + iVar7 + 0x18) = uVar11;
    uVar9 = *puVar4;
    *(undefined4 *)(gSpriteReference + iVar7 + 0x1c) = *(undefined4 *)(iVar5 + 0x54);
    *(uint **)(gSpriteReference + iVar7 + 4) = puVar4;
    puVar4[0x24] = 0;
    *puVar4 = uVar9 | param_3;
    return;
  }
  gSpriteReference[param_2 * 0x20] = 0;
  puVar4 = (uint *)cRTextures::Add((cRTextures *)gTextureList,param_1,(cTgaHeader *)0x0,param_3);
  iVar7 = param_2 * 4 + 1;
  iVar3 = param_2 * 2 + 1;
  iVar5 = param_2 * 0x20;
  *(undefined4 *)(gSpriteReference + iVar7 * 8) = 0;
  *(undefined4 *)(gSpriteReference + iVar7 * 8 + 4) = 0;
  *(undefined4 *)(gSpriteReference + iVar3 * 0x10 + 4) = 0;
  *(undefined4 *)(gSpriteReference + iVar3 * 0x10) = 0;
  *(undefined4 *)(gSpriteReference + iVar5 + 0x1c) = 0x3f800000;
  *(undefined4 *)(gSpriteReference + iVar5 + 0x18) = 0x3f800000;
  uVar9 = *puVar4;
  *(uint **)(gSpriteReference + iVar5 + 4) = puVar4;
  puVar4[0x24] = 0;
  *puVar4 = uVar9 | param_3;
  return;
}
