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
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;

  iVar4 = DAT_0005f4d4 + 0x5f45c;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(**(int **)(iVar4 + DAT_0005f4d8) + 0xd14));
  uVar1 = DAT_0005f4d0;
  iVar3 = *(int *)(this + 0x1c);
  uVar5 = *(undefined4 *)(iVar3 + 0x70);
  *(undefined4 *)(this + 0x20) = uVar2;
  cRBorder::Init(uVar2,0x14,iVar4 + DAT_0005f4dc,uVar5,uVar1,uVar1,*(undefined4 *)(iVar3 + 0x1b0),
                 *(undefined4 *)(iVar3 + 0x1b4),*(undefined4 *)(iVar3 + 0x1b8),
                 *(undefined4 *)(iVar3 + 0x1bc),0,uVar1);
  AI(this);
  return;
}
