/*
 * mangled: _ZN5cRBodC2Ev
 * demangled: cRBod::cRBod()
 * address: 000307d0
 * size: 124
 */

/* cRBod::cRBod() */

cRBod * __thiscall cRBod::cRBod(cRBod *this)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;

  iVar4 = DAT_00030850 + 0x307e8;
  *(int *)this = *(int *)(iVar4 + DAT_00030854) + 8;
  tColourSmall::tColourSmall((tColourSmall *)(this + 0x28));
  *(undefined4 *)(this + 4) = 0x2000020;
  tColourSmall::White((tColourSmall *)(this + 0x28));
  iVar2 = DAT_00030858;
  *(undefined4 *)(this + 0x24) = 0;
  uVar1 = DAT_0003084c;
  piVar3 = *(int **)(iVar4 + iVar2);
  *(undefined4 *)(this + 0x20) = DAT_0003084c;
  *(undefined4 *)(this + 0x18) = uVar1;
  *(undefined4 *)(this + 0x14) = uVar1;
  *(undefined4 *)(this + 0x10) = uVar1;
  *(undefined4 *)(this + 0x1c) = uVar1;
  *piVar3 = *piVar3 + 1;
  return this;
}
