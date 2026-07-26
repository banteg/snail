/*
 * mangled: _ZN5cRBodC1Ev
 * demangled: cRBod::cRBod()
 * address: 00030744
 * size: 124
 */

/* cRBod::cRBod() */

cRBod * __thiscall cRBod::cRBod(cRBod *this)

{
  *(undefined ***)this = &PTR_AI_0009abd0;
  tColourSmall::tColourSmall((tColourSmall *)(this + 0x28));
  *(undefined4 *)(this + 4) = 0x2000020;
  tColourSmall::White((tColourSmall *)(this + 0x28));
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  gBodCount = gBodCount + 1;
  return this;
}
