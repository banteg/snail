/*
 * mangled: _ZN6cRGame8InitLastEv
 * demangled: cRGame::InitLast()
 * address: 00049ac8
 * size: 448
 */

/* cRGame::InitLast() */

void __thiscall cRGame::InitLast(cRGame *this)

{
  undefined4 uVar1;

  wprintf("GameInitLast\n");
  cKeyPad::Open((cKeyPad *)(this + 0xbf0));
  this[0x4e640] = (cRGame)0x0;
  *(undefined4 *)(this + 0x4d330) = 0xffffffff;
  this[0x4d338] = (cRGame)0x0;
  *(undefined4 *)(this + 0x4e6a8) = 0;
  *(undefined4 *)(this + 0x4e63c) = 1;
  *(undefined4 *)(this + 0x4e69c) = 0;
  *(undefined4 *)(this + 0x4e6a4) = 5;
  *(undefined4 *)(this + 0x4e6a0) = 0x3b5a740e;
  *(float *)(this + 0x4e66c) = 1.0 - *(float *)(this + 0x4e66c);
  uVar1 = *(undefined4 *)(this + 0x4e678);
  *(undefined4 *)(this + 0x4e678) = 5;
  *(undefined4 *)(this + 0x4e674) = uVar1;
  *(float *)(this + 0x4e68c) = 1.0 - *(float *)(this + 0x4e68c);
  uVar1 = *(undefined4 *)(this + 0x4e698);
  *(undefined4 *)(this + 0x4e698) = 5;
  *(undefined4 *)(this + 0x4e694) = uVar1;
  if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 1) == 0) {
    *(undefined4 *)(this + 0x4e638) = 0;
    *(undefined4 *)(this + 0x4e644) = 0;
    *(undefined4 *)(this + 0x4e648) = 0x3caaaaab;
  }
  else {
    *(undefined4 *)(this + 0x4e638) = 1;
    *(undefined4 *)(this + 0x4e644) = 0x3f800000;
    *(undefined4 *)(this + 0x4e648) = 0x3caaaaab;
  }
  *(undefined4 *)(this + 0x4e64c) = 0;
  *(undefined4 *)(this + 0x4e650) = 0xbb2b92a7;
  *(undefined4 *)(this + 0x4e654) = 0;
  *(undefined4 *)(this + 0x4e658) = 0xbb64c389;
  *(undefined4 *)(this + 0x4e670) = 0x3bb60b61;
  *(undefined4 *)(this + 0x4e66c) = 0;
  *(undefined4 *)(this + 0x4e674) = 0;
  *(undefined4 *)(this + 0x4e678) = 0;
  *(undefined4 *)(this + 0x4e68c) = 0;
  *(undefined4 *)(this + 0x4e694) = 0;
  *(undefined4 *)(this + 0x4e698) = 0;
  *(undefined4 *)(this + 0x4e690) = 0x3b888889;
  cRBackdrop::SetDistort((cRBackdrop *)(this + 0x4d2e0),0.0);
  *(undefined4 *)(this + 0x4d30c) = 0x44000000;
  *(undefined4 *)(this + 0x4d310) = 0x44000000;
  *PTR__G0GameInitFlag_001b6104 = 1;
  return;
}
