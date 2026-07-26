/*
 * mangled: _ZN8cRBodPosC1Ev
 * demangled: cRBodPos::cRBodPos()
 * address: 0003085c
 * size: 64
 */

/* cRBodPos::cRBodPos() */

cRBodPos * __thiscall cRBodPos::cRBodPos(cRBodPos *this)

{
  cRBod::cRBod((cRBod *)this);
  *(undefined4 *)(this + 4) = 0x2000420;
  *(undefined ***)this = &PTR_AI_0009abc0;
  tMatrix::Identity((tMatrix *)(this + 0x2c));
  return this;
}
