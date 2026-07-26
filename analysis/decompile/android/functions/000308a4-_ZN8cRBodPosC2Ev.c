/*
 * mangled: _ZN8cRBodPosC2Ev
 * demangled: cRBodPos::cRBodPos()
 * address: 000308a4
 * size: 64
 */

/* cRBodPos::cRBodPos() */

cRBodPos * __thiscall cRBodPos::cRBodPos(cRBodPos *this)

{
  int iVar1;
  int iVar2;

  iVar1 = DAT_000308e4;
  cRBod::cRBod((cRBod *)this);
  iVar2 = DAT_000308e8;
  *(undefined4 *)(this + 4) = 0x2000420;
  *(int *)this = *(int *)(iVar1 + 0x308c0 + iVar2) + 8;
  tMatrix::Identity((tMatrix *)(this + 0x2c));
  return this;
}
