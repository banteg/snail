/*
 * mangled: _ZN14cAccelerometer4InitEv
 * demangled: cAccelerometer::Init()
 * address: 0005b390
 * size: 84
 */

/* cAccelerometer::Init() */

void __thiscall cAccelerometer::Init(cAccelerometer *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;

  iVar3 = DAT_0005b3f8;
  iVar5 = DAT_0005b3f4;
  uVar1 = DAT_0005b3e4;
  *(undefined4 *)(this + 8) = DAT_0005b3e4;
  *(undefined4 *)this = uVar1;
  *(undefined4 *)(this + 0xc) = uVar1;
  *(undefined4 *)(this + 0x10) = uVar1;
  piVar4 = *(int **)(iVar5 + 0x5b3a8 + iVar3);
  *(undefined4 *)(this + 0x14) = uVar1;
  uVar2 = DAT_0005b3e8;
  *(undefined4 *)(this + 4) = DAT_0005b3ec;
  iVar5 = *piVar4;
  *(undefined4 *)(iVar5 + 0x4c) = uVar1;
  *(undefined4 *)(iVar5 + 0x48) = uVar1;
  *(undefined4 *)(iVar5 + 0x40) = uVar2;
  *(undefined4 *)(iVar5 + 0x3c) = uVar2;
  *(undefined4 *)(this + 0x18) = DAT_0005b3f0;
  return;
}
