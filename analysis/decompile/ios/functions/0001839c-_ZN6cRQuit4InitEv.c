/*
 * mangled: _ZN6cRQuit4InitEv
 * demangled: cRQuit::Init()
 * address: 0001839c
 * size: 184
 */

/* cRQuit::Init() */

void __thiscall cRQuit::Init(cRQuit *this)

{
  undefined4 uVar1;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;

  *(undefined4 *)this = 1;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 4) = uVar1;
  tColour::tColour((tColour *)&local_28,1.0,1.0,1.0,0.999);
  cRBorder::Init(uVar1,0x2040081c,0x52,0x41000000,0x41400000,local_28,uStack_24,uStack_20,uStack_1c,
                 0,1);
  cRBorder::Scale(*(cRBorder **)(this + 4),1.3333334);
  *(undefined4 *)(*(int *)(this + 4) + 0x16c) = 0;
  cRBorder::HideInit(*(cRBorder **)(this + 4));
  return;
}
