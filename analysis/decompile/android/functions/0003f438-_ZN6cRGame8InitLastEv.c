/*
 * mangled: _ZN6cRGame8InitLastEv
 * demangled: cRGame::InitLast()
 * address: 0003f438
 * size: 164
 */

/* cRGame::InitLast() */

void __thiscall cRGame::InitLast(cRGame *this)

{
  OFInit();
  if (gOFORef == -1) {
    OFONewUser(gConfig + 0xf0);
  }
  wprintf("GameInitLast\n");
  cKeyPad::Open((cKeyPad *)(this + 0xbf0));
  cRBackdrop::Init((cRBackdrop *)(this + 0x4d2e0),1);
  G0GameInitFlag = 1;
  cROptions::Apply((bool)((char)Game + -0x80));
  *(undefined4 *)(Game + 0x718b4) = 0;
  return;
}
