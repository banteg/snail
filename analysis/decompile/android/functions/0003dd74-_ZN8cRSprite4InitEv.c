/*
 * mangled: _ZN8cRSprite4InitEv
 * demangled: cRSprite::Init()
 * address: 0003dd74
 * size: 152
 */

/* cRSprite::Init() */

void __thiscall cRSprite::Init(cRSprite *this)

{
  undefined4 uVar1;

  *(undefined4 *)(this + 4) = 0x49;
  tColour::White();
  uVar1 = DAT_0003de0c;
  *(undefined4 *)(this + 0xac) = DAT_0003de0c;
  *(undefined4 *)(this + 0x68) = uVar1;
  *(undefined4 *)(this + 0x70) = uVar1;
  *(undefined4 *)(this + 0x74) = uVar1;
  *(undefined4 *)(this + 0x7c) = uVar1;
  *(undefined4 *)(this + 0x80) = uVar1;
  *(undefined4 *)(this + 0x88) = uVar1;
  *(undefined4 *)(this + 0x8c) = uVar1;
  *(undefined4 *)(this + 0x5c) = uVar1;
  *(undefined4 *)(this + 0x58) = uVar1;
  *(undefined4 *)(this + 0x54) = uVar1;
  *(undefined4 *)(this + 0x94) = uVar1;
  *(undefined4 *)(this + 0xa8) = uVar1;
  *(undefined4 *)(this + 0xa0) = 0;
  uVar1 = DAT_0003de10;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x78) = uVar1;
  *(undefined4 *)(this + 0x24) = 0;
  uVar1 = DAT_0003de14;
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x84) = uVar1;
  *(undefined4 *)(this + 0x9c) = 0;
  uVar1 = DAT_0003de18;
  *(undefined4 *)(this + 0xa4) = 1;
  *(undefined4 *)(this + 0x90) = uVar1;
  *(undefined4 *)(this + 0x28) = 1;
  *(undefined4 *)this = 0xffffffff;
  return;
}
