/*
 * mangled: _ZN7cKeyPad4InitEP8cRBorder
 * demangled: cKeyPad::Init(cRBorder*)
 * address: 0007685c
 * size: 108
 */

/* cKeyPad::Init(cRBorder*) */

void __thiscall cKeyPad::Init(cKeyPad *this,cRBorder *param_1)

{
  *(undefined4 *)this = 1;
  *(undefined4 *)(this + 0x18) = 0x43f00000;
  *(undefined4 *)(this + 0xc) = 0;
  *(cRBorder **)(this + 0x1c) = param_1;
  this[0x120] = (cKeyPad)0x0;
  *(undefined4 *)(this + 0x10) = 0x3cbda12f;
  cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x19);
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0xa0) = 0;
  *(undefined4 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 0xe0) = 0;
  *(undefined4 *)(this + 0x100) = 0;
  return;
}
