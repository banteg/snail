/*
 * mangled: _ZN18cRLandscapeManager4OpenEv
 * demangled: cRLandscapeManager::Open()
 * address: 000689e0
 * size: 92
 */

/* cRLandscapeManager::Open() */

void __thiscall cRLandscapeManager::Open(cRLandscapeManager *this)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;

  iVar2 = DAT_00068a3c;
  *(undefined4 *)this = 0;
  iVar2 = iVar2 + 0x68a04;
  pcVar3 = (char *)(iVar2 + DAT_00068a44);
  uVar1 = cRTextures::Add(*(cRTextures **)(iVar2 + DAT_00068a40),pcVar3,(cTgaHeader *)0x0,0x20400);
  *(undefined4 *)(this + 0x3584) = uVar1;
  cRSpriteManager::Load(*(cRSpriteManager **)(iVar2 + DAT_00068a48),pcVar3,7,0x20400);
  return;
}
