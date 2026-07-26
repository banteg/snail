/*
 * mangled: _ZN6cRGame5Init5Ev
 * demangled: cRGame::Init5()
 * address: 0004276c
 * size: 112
 */

/* cRGame::Init5() */

void __thiscall cRGame::Init5(cRGame *this)

{
  wprintf("GameInit5\n");
  cRObjects::BuildObjects((cRObjects *)PTR__gObjectList_001b61cc);
  cRBackdrop::Open((cRBackdrop *)(this + 0x4d2e0));
  *(undefined4 *)(this + 0x4e638) = 0;
  RShellSetMouse(0,320.0,240.0);
  RShellSetMouse(1,320.0,240.0);
  *(undefined4 *)(this + 0x376620) = 2;
  return;
}
