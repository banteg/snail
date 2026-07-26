/*
 * mangled: _ZN15cRSpriteManager4LoadEPcii
 * demangled: cRSpriteManager::Load(char*, int, int)
 * address: 00010ba0
 * size: 420
 */

/* cRSpriteManager::Load(char*, int, int) */

void __thiscall cRSpriteManager::Load(cRSpriteManager *this,char *param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;

  cVar1 = *param_1;
  pcVar4 = param_1;
  while (cVar1 != '.') {
    pcVar4 = pcVar4 + 1;
    cVar1 = *pcVar4;
  }
  if (this[0x2af94] == (cRSpriteManager)0x0) {
    iVar6 = 0;
  }
  else {
    if (0 < *(int *)(this + 0x2af98)) {
      iVar5 = 0;
      iVar6 = 0;
      do {
        iVar2 = Rstrcmp((char *)(iVar6 + *(int *)(this + 0x2afa0)),param_1);
        if (iVar2 != 0) {
          iVar6 = iVar6 + *(int *)(this + 0x2afa0);
          goto joined_r0x00010c44;
        }
        iVar5 = iVar5 + 1;
        iVar6 = iVar6 + 0x58;
      } while (iVar5 < *(int *)(this + 0x2af98));
    }
    iVar6 = 0;
  }
joined_r0x00010c44:
  if (199 < param_2) {
    RShellError("Too many Sprite References - Increase RSPRITE_REFERENCE_MAX(%i) in RSprite.h",200);
  }
  if (iVar6 == 0) {
    (&_gSpriteReference)[param_2 * 0x20] = 0;
    uVar3 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,param_1,(cTgaHeader *)0x0,
                            param_3);
    iVar6 = param_2 * 0x20;
    *(undefined4 *)(&DAT_002ac60c + iVar6) = 0;
    *(undefined4 *)(&DAT_002ac610 + iVar6) = 0;
    *(undefined4 *)(&DAT_002ac604 + iVar6) = 0;
    *(undefined4 *)(&DAT_002ac608 + iVar6) = 0;
    *(undefined4 *)(&DAT_002ac614 + iVar6) = 0x3f800000;
    *(undefined4 *)(&DAT_002ac618 + iVar6) = 0x3f800000;
    *(undefined4 *)(&DAT_002ac600 + iVar6) = uVar3;
  }
  else {
    iVar5 = param_2 * 0x20;
    (&_gSpriteReference)[param_2 * 0x20] = 1;
    *(undefined4 *)(&DAT_002ac600 + iVar5) =
         *(undefined4 *)(&DAT_002ac600 + (char)this[0x2af9c] * 0x20);
    *(undefined4 *)(&DAT_002ac604 + iVar5) = *(undefined4 *)(iVar6 + 0x40);
    *(undefined4 *)(&DAT_002ac608 + iVar5) = *(undefined4 *)(iVar6 + 0x44);
    *(undefined4 *)(&DAT_002ac60c + iVar5) = *(undefined4 *)(iVar6 + 0x48);
    *(undefined4 *)(&DAT_002ac610 + iVar5) = *(undefined4 *)(iVar6 + 0x4c);
    *(undefined4 *)(&DAT_002ac614 + iVar5) = *(undefined4 *)(iVar6 + 0x50);
    *(undefined4 *)(&DAT_002ac618 + iVar5) = *(undefined4 *)(iVar6 + 0x54);
  }
  **(uint **)(&DAT_002ac600 + param_2 * 0x20) =
       **(uint **)(&DAT_002ac600 + param_2 * 0x20) | param_3;
  *(undefined4 *)(*(int *)(&DAT_002ac600 + param_2 * 0x20) + 0x90) = 0;
  return;
}
