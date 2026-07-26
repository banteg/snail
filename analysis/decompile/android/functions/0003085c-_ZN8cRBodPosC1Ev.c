/*
 * mangled: _ZN8cRBodPosC1Ev
 * demangled: cRBodPos::cRBodPos()
 * address: 0003085c
 * size: 64
 */

/* cRBodPos::cRBodPos() */

cRBodPos * __thiscall cRBodPos::cRBodPos(cRBodPos *this)

{
  int iVar1;
  int iVar2;

  iVar1 = DAT_0003089c;
  cRBod::cRBod((cRBod *)this);
  iVar2 = DAT_000308a0;
  *(undefined4 *)(this + 4) = 0x2000420;
  *(int *)this = *(int *)(iVar1 + 0x30878 + iVar2) + 8;
  tMatrix::Identity((tMatrix *)(this + 0x2c));
  return this;
}
