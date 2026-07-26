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
  uint *puVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;

  iVar10 = DAT_0003d98c + 0x3d810;
  cVar1 = *param_1;
  pcVar5 = param_1;
  while (cVar1 != '.') {
    pcVar5 = pcVar5 + 1;
    cVar1 = *pcVar5;
  }
  if (this[0x2af94] == (cRSpriteManager)0x0) {
    iVar8 = 0;
  }
  else {
    iVar8 = SearchSet(this,param_1);
  }
  iVar4 = DAT_0003d998;
  if (199 < param_2) {
    RShellError((char *)(iVar10 + DAT_0003d994),200);
    iVar4 = DAT_0003d998;
  }
  DAT_0003d998 = iVar4;
  if (iVar8 != 0) {
    uVar11 = *(undefined4 *)(iVar8 + 0x40);
    iVar6 = *(int *)(iVar10 + DAT_0003d990);
    iVar10 = param_2 * 4 + 1;
    iVar4 = param_2 * 2 + 1;
    uVar12 = *(undefined4 *)(iVar8 + 0x48);
    *(undefined1 *)(iVar6 + param_2 * 0x20) = 1;
    cVar2 = this[0x2af9c];
    iVar9 = iVar6 + param_2 * 0x20;
    *(undefined4 *)(iVar6 + iVar10 * 8) = uVar11;
    uVar11 = *(undefined4 *)(iVar8 + 0x44);
    *(undefined4 *)(iVar6 + iVar4 * 0x10) = uVar12;
    *(undefined4 *)(iVar6 + iVar4 * 0x10 + 4) = *(undefined4 *)(iVar8 + 0x4c);
    puVar3 = *(uint **)(iVar6 + (uint)(byte)cVar2 * 0x20 + 4);
    uVar12 = *(undefined4 *)(iVar8 + 0x50);
    *(undefined4 *)(iVar6 + iVar10 * 8 + 4) = uVar11;
    *(undefined4 *)(iVar9 + 0x18) = uVar12;
    uVar7 = *puVar3;
    *(undefined4 *)(iVar9 + 0x1c) = *(undefined4 *)(iVar8 + 0x54);
    *(uint **)(iVar9 + 4) = puVar3;
    puVar3[0x24] = 0;
    *puVar3 = uVar7 | param_3;
    return;
  }
  iVar6 = *(int *)(iVar10 + DAT_0003d990);
  *(undefined1 *)(iVar6 + param_2 * 0x20) = 0;
  puVar3 = (uint *)cRTextures::Add(*(cRTextures **)(iVar10 + iVar4),param_1,(cTgaHeader *)0x0,
                                   param_3);
  iVar10 = param_2 * 4 + 1;
  iVar8 = param_2 * 2 + 1;
  iVar4 = iVar6 + param_2 * 0x20;
  *(undefined4 *)(iVar6 + iVar10 * 8) = 0;
  uVar11 = DAT_0003d984;
  *(undefined4 *)(iVar6 + iVar10 * 8 + 4) = 0;
  *(undefined4 *)(iVar6 + iVar8 * 0x10 + 4) = uVar11;
  *(undefined4 *)(iVar6 + iVar8 * 0x10) = uVar11;
  uVar11 = DAT_0003d988;
  *(undefined4 *)(iVar4 + 0x1c) = DAT_0003d988;
  *(undefined4 *)(iVar4 + 0x18) = uVar11;
  uVar7 = *puVar3;
  *(uint **)(iVar4 + 4) = puVar3;
  puVar3[0x24] = 0;
  *puVar3 = uVar7 | param_3;
  return;
}
