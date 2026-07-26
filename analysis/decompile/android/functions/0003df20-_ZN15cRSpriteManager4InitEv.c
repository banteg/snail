/*
 * mangled: _ZN15cRSpriteManager4InitEv
 * demangled: cRSpriteManager::Init()
 * address: 0003df20
 * size: 236
 */

/* cRSpriteManager::Init() */

void __thiscall cRSpriteManager::Init(cRSpriteManager *this)

{
  int iVar1;
  int iVar2;
  cRSpriteManager *pcVar3;

  *(undefined4 *)(this + 0x2af84) = 0;
  iVar1 = 0;
  *(undefined4 *)(this + 0x2af88) = 0;
  this[0x2af94] = (cRSpriteManager)0x0;
  *(cRSpriteManager **)(this + 0x2af90) = this + 4;
  iVar2 = 1;
  *(undefined4 *)(this + 0x2af8c) = 0;
  *this = (cRSpriteManager)0x0;
  pcVar3 = this;
  do {
    cRSprite::Init((cRSprite *)(this + iVar1 * 0xb0 + 4));
    if (iVar1 == 0) {
      *(undefined4 *)(this + 0x14) = 0;
      *(cRSpriteManager **)(this + 0x10) = this + 0xb4;
    }
    else {
      if (iVar1 == 999) {
        *(undefined4 *)(this + 0x2aee0) = 0;
        *(cRSpriteManager **)(this + 0x2aee4) = this + 0x2ae24;
        return;
      }
      *(cRSpriteManager **)(pcVar3 + 0x14) = this + iVar1 * 0xb0 + -0xac;
      *(cRSpriteManager **)(pcVar3 + 0x10) = this + iVar2 * 0xb0 + 4;
      if (999 < iVar2) {
        return;
      }
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0xb0;
  } while( true );
}
