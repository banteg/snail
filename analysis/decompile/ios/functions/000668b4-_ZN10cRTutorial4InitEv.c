/*
 * mangled: _ZN10cRTutorial4InitEv
 * demangled: cRTutorial::Init()
 * address: 000668b4
 * size: 80
 */

/* cRTutorial::Init() */

void __thiscall cRTutorial::Init(cRTutorial *this)

{
  int iVar1;

  *(undefined4 *)this = 0;
  iVar1 = *(int *)PTR__Game_001b60b8;
  *(int *)(this + 0xc) = iVar1 + 0x72b78;
  *(undefined4 *)PTR__RFontTypeSet_001b61f8 = 0;
  *(uint *)(iVar1 + 0x72bdc) = *(uint *)(iVar1 + 0x72bdc) | 0x600000;
  *(uint *)(*(int *)(this + 0xc) + 100) = *(uint *)(*(int *)(this + 0xc) + 100) & 0xfffffffd;
  return;
}
