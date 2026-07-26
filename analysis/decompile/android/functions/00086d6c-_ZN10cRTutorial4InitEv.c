/*
 * mangled: _ZN10cRTutorial4InitEv
 * demangled: cRTutorial::Init()
 * address: 00086d6c
 * size: 96
 */

/* cRTutorial::Init() */

void __thiscall cRTutorial::Init(cRTutorial *this)

{
  int iVar1;
  uint uVar2;

  *(undefined4 *)this = 0;
  iVar1 = Game;
  RFontTypeSet = 0;
  uVar2 = *(uint *)(Game + 0x7190c);
  *(int *)(this + 0xc) = Game + 0x718a0;
  *(uint *)(iVar1 + 0x7190c) = uVar2 | 0x600000;
  *(uint *)(iVar1 + 0x7190c) = *(uint *)(iVar1 + 0x7190c) & 0xfffffffd;
  return;
}
