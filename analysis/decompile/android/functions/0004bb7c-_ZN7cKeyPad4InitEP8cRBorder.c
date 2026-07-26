/*
 * mangled: _ZN7cKeyPad4InitEP8cRBorder
 * demangled: cKeyPad::Init(cRBorder*)
 * address: 0004bb7c
 * size: 88
 */

/* cKeyPad::Init(cRBorder*) */

void __thiscall cKeyPad::Init(cKeyPad *this,cRBorder *param_1)

{
  *(undefined4 *)this = 1;
  *(undefined4 *)(this + 0x18) = 0x43f00000;
  *(cRBorder **)(this + 0x1c) = param_1;
  *(undefined4 *)(this + 0xc) = 0;
  this[0x120] = (cKeyPad)0x0;
  *(undefined4 *)(this + 0x10) = 0x3cbda12f;
  cRSound::Play((int)&gRSound);
  cGlowManager::Init((cGlowManager *)(this + 0x20));
  return;
}
