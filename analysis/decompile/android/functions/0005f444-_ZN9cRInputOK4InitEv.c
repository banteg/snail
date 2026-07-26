/*
 * mangled: _ZN9cRInputOK4InitEv
 * demangled: cRInputOK::Init()
 * address: 0005f444
 * size: 140
 */

/* cRInputOK::Init() */

void __thiscall cRInputOK::Init(cRInputOK *this)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;

  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  iVar2 = *(int *)(this + 0x1c);
  uVar3 = *(undefined4 *)(iVar2 + 0x70);
  *(undefined4 *)(this + 0x20) = uVar1;
  cRBorder::Init(uVar1,0x14,&DAT_00093290,uVar3,0,0,*(undefined4 *)(iVar2 + 0x1b0),
                 *(undefined4 *)(iVar2 + 0x1b4),*(undefined4 *)(iVar2 + 0x1b8),
                 *(undefined4 *)(iVar2 + 0x1bc),0,0);
  AI(this);
  return;
}
