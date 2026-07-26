/*
 * mangled: _ZN15cRSpriteManager4InitEv
 * demangled: cRSpriteManager::Init()
 * address: 000110d4
 * size: 348
 */

/* cRSpriteManager::Init() */

void __thiscall cRSpriteManager::Init(cRSpriteManager *this)

{
  cRSpriteManager *pcVar1;
  cRSpriteManager *pcVar2;
  int iVar3;
  int iVar4;

  iVar3 = 0;
  this[0x2af94] = (cRSpriteManager)0x0;
  iVar4 = 1;
  *this = (cRSpriteManager)0x0;
  *(undefined4 *)(this + 0x2af84) = 0;
  *(undefined4 *)(this + 0x2af88) = 0;
  *(undefined4 *)(this + 0x2af8c) = 0;
  *(cRSpriteManager **)(this + 0x2af90) = this + 4;
  pcVar2 = this;
  do {
    *(undefined4 *)(pcVar2 + 8) = 0x49;
    tColour::White((tColour *)(this + iVar3 * 0xb0 + 0x30));
    pcVar1 = (cRSpriteManager *)0x0;
    *(undefined4 *)(pcVar2 + 0x7c) = 0xbc54fdf4;
    *(undefined4 *)(pcVar2 + 0x88) = 0x3f800000;
    *(undefined4 *)(pcVar2 + 0x6c) = 0;
    *(undefined4 *)(pcVar2 + 0x74) = 0;
    *(undefined4 *)(pcVar2 + 0x78) = 0;
    *(undefined4 *)(pcVar2 + 0x80) = 0;
    *(undefined4 *)(pcVar2 + 0x84) = 0;
    *(undefined4 *)(pcVar2 + 0x8c) = 0;
    *(undefined4 *)(pcVar2 + 0x90) = 0;
    *(undefined4 *)(pcVar2 + 0x94) = 0xc3fa0000;
    *(undefined4 *)(pcVar2 + 0x60) = 0;
    *(undefined4 *)(pcVar2 + 0x5c) = 0;
    *(undefined4 *)(pcVar2 + 0x58) = 0;
    *(undefined4 *)(pcVar2 + 0x98) = 0;
    *(undefined4 *)(pcVar2 + 0xac) = 0;
    *(undefined4 *)(pcVar2 + 0xb0) = 0;
    if (iVar3 == 0) {
      pcVar1 = this + 0xb4;
    }
    *(undefined4 *)(pcVar2 + 0x2c) = 1;
    *(undefined4 *)(pcVar2 + 0x24) = 0;
    *(undefined4 *)(pcVar2 + 0x28) = 0;
    *(undefined4 *)(pcVar2 + 4) = 0xffffffff;
    *(undefined4 *)(pcVar2 + 0x9c) = 0;
    *(undefined4 *)(pcVar2 + 0xa0) = 0;
    *(undefined4 *)(pcVar2 + 0xa4) = 0;
    *(undefined4 *)(pcVar2 + 0xa8) = 1;
    if (iVar3 == 0) {
      *(undefined4 *)(this + 0x14) = 0;
      *(cRSpriteManager **)(this + 0x10) = pcVar1;
    }
    else {
      if (iVar3 == 999) {
        *(cRSpriteManager **)(this + 0x2aee4) = this + 0x2ae24;
        *(undefined4 *)(this + 0x2aee0) = 0;
        return;
      }
      *(cRSpriteManager **)(pcVar2 + 0x14) = this + iVar3 * 0xb0 + -0xac;
      *(cRSpriteManager **)(pcVar2 + 0x10) = this + iVar4 * 0xb0 + 4;
      if (999 < iVar4) {
        return;
      }
    }
    iVar3 = iVar3 + 1;
    pcVar2 = pcVar2 + 0xb0;
    iVar4 = iVar4 + 1;
  } while( true );
}
