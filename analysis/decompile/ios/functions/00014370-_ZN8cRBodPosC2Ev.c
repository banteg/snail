/*
 * mangled: _ZN8cRBodPosC2Ev
 * demangled: cRBodPos::cRBodPos()
 * address: 00014370
 * size: 124
 */

/* cRBodPos::cRBodPos() */

void __thiscall cRBodPos::cRBodPos(cRBodPos *this)

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
  *(undefined ***)this = &PTR_AI_001b6b20;
  *(undefined4 *)(this + 4) = 0x2000420;
  tMatrix::Identity((tMatrix *)(this + 0x2c));
  return;
}
