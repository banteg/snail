/*
 * mangled: _ZN6cRGame5Init5Ev
 * demangled: cRGame::Init5()
 * address: 0003f4f4
 * size: 220
 */

/* cRGame::Init5() */

void __thiscall cRGame::Init5(cRGame *this)

{
  undefined8 uVar1;

  wprintf("GameInit5\n");
  cRObjects::BuildObjects((cRObjects *)gObjectList);
  if (gG0DeviceScreenWidth == 320.0) {
    uVar1 = cRBackdrop::Open((cRBackdrop *)(this + 0x4d2e0),8);
  }
  else {
    uVar1 = cRBackdrop::Open((cRBackdrop *)(this + 0x4d2e0),0x14);
  }
  *(undefined4 *)(this + 0x4d360) = 0;
  *(undefined4 *)(this + 0x4d3d4) = 0;
  *(undefined4 *)(this + 0x4d3d0) = 0;
  uVar1 = RShellSetMouse(0,(float)uVar1,(float)((ulonglong)uVar1 >> 0x20));
  RShellSetMouse(1,(float)uVar1,(float)((ulonglong)uVar1 >> 0x20));
  *(undefined4 *)(this + 0x3a463c) = 2;
  return;
}
