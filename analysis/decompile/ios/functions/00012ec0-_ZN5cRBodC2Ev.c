/*
 * mangled: _ZN5cRBodC2Ev
 * demangled: cRBod::cRBod()
 * address: 00012ec0
 * size: 100
 */

/* cRBod::cRBod() */

void __thiscall cRBod::cRBod(cRBod *this)

{
  *(undefined ***)this = &PTR_AI_001b6b0c;
  tColourSmall::tColourSmall((tColourSmall *)(this + 0x28));
  *(undefined4 *)(this + 4) = 0x2000020;
  tColourSmall::White((tColourSmall *)(this + 0x28));
  _gBodCount = _gBodCount + 1;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  return;
}
