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

  *(undefined4 *)this = 0;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,"Backgrounds/SpaceRed.jpg",(cTgaHeader *)0x0,
                          0x20400);
  *(undefined4 *)(this + 0x3584) = uVar1;
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Backgrounds/SpaceRed.jpg",7,0x20400);
  return;
}
