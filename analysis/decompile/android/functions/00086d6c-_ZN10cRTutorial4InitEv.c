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
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;

  iVar1 = DAT_00086dd4;
  iVar4 = DAT_00086dcc + 0x86d84;
  piVar2 = *(int **)(iVar4 + DAT_00086dd0);
  *(undefined4 *)this = 0;
  iVar3 = *piVar2;
  **(undefined4 **)(iVar4 + iVar1) = 0;
  uVar5 = *(uint *)(iVar3 + 0x7190c);
  *(int *)(this + 0xc) = iVar3 + 0x718a0;
  *(uint *)(iVar3 + 0x7190c) = uVar5 | 0x600000;
  *(uint *)(iVar3 + 0x7190c) = *(uint *)(iVar3 + 0x7190c) & 0xfffffffd;
  return;
}
