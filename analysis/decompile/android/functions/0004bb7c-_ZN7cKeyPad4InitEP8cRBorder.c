/*
 * mangled: _ZN7cKeyPad4InitEP8cRBorder
 * demangled: cKeyPad::Init(cRBorder*)
 * address: 0004bb7c
 * size: 88
 */

/* cKeyPad::Init(cRBorder*) */

void __thiscall cKeyPad::Init(cKeyPad *this,cRBorder *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;

  iVar3 = DAT_0004bbe0;
  *(undefined4 *)this = 1;
  iVar2 = DAT_0004bbe4;
  *(undefined4 *)(this + 0x18) = DAT_0004bbd4;
  *(cRBorder **)(this + 0x1c) = param_1;
  iVar3 = *(int *)(iVar3 + 0x4bb98 + iVar2);
  *(undefined4 *)(this + 0xc) = DAT_0004bbd8;
  uVar1 = DAT_0004bbdc;
  this[0x120] = (cKeyPad)0x0;
  *(undefined4 *)(this + 0x10) = uVar1;
  cRSound::Play(iVar3);
  cGlowManager::Init((cGlowManager *)(this + 0x20));
  return;
}
