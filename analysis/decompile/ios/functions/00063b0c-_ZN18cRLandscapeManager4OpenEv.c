/*
 * mangled: _ZN18cRLandscapeManager4OpenEv
 * demangled: cRLandscapeManager::Open()
 * address: 00063b0c
 * size: 80
 */

/* cRLandscapeManager::Open() */

void __thiscall cRLandscapeManager::Open(cRLandscapeManager *this)

{
  undefined4 uVar1;

  *(undefined4 *)this = 0;
  uVar1 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,"Backgrounds/SpaceRed.pvr",
                          (cTgaHeader *)0x0,0x20400);
  *(undefined4 *)(this + 0x3584) = uVar1;
  cRSpriteManager::Load
            ((cRSpriteManager *)PTR__gRSpriteManager_001b61e4,"Backgrounds/SpaceRed.pvr",7,0x20400);
  return;
}
