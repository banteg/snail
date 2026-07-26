/*
 * mangled: _ZN6cRGame5Init5Ev
 * demangled: cRGame::Init5()
 * address: 0003f4f4
 * size: 220
 */

/* cRGame::Init5() */

void __thiscall cRGame::Init5(cRGame *this)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;

  iVar2 = DAT_0003f5d8 + 0x3f50c;
  wprintf((char *)(iVar2 + DAT_0003f5dc));
  cRObjects::BuildObjects(*(cRObjects **)(iVar2 + DAT_0003f5e0));
  if (**(float **)(iVar2 + DAT_0003f5e4) == DAT_0003f5d0) {
    uVar3 = cRBackdrop::Open((cRBackdrop *)(this + 0x4d2e0),8);
  }
  else {
    uVar3 = cRBackdrop::Open((cRBackdrop *)(this + 0x4d2e0),0x14);
  }
  uVar1 = DAT_0003f5d4;
  *(undefined4 *)(this + 0x4d360) = 0;
  *(undefined4 *)(this + 0x4d3d4) = uVar1;
  *(undefined4 *)(this + 0x4d3d0) = uVar1;
  uVar3 = RShellSetMouse(0,(float)uVar3,(float)((ulonglong)uVar3 >> 0x20));
  RShellSetMouse(1,(float)uVar3,(float)((ulonglong)uVar3 >> 0x20));
  *(undefined4 *)(this + 0x3a463c) = 2;
  return;
}
