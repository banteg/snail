/*
 * mangled: _ZN5cRBodC1Ev
 * demangled: cRBod::cRBod()
 * address: 00030744
 * size: 124
 */

/* cRBod::cRBod() */

cRBod * __thiscall cRBod::cRBod(cRBod *this)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;

  iVar4 = DAT_000307c4 + 0x3075c;
  *(int *)this = *(int *)(iVar4 + DAT_000307c8) + 8;
  tColourSmall::tColourSmall((tColourSmall *)(this + 0x28));
  *(undefined4 *)(this + 4) = 0x2000020;
  tColourSmall::White((tColourSmall *)(this + 0x28));
  iVar2 = DAT_000307cc;
  *(undefined4 *)(this + 0x24) = 0;
  uVar1 = DAT_000307c0;
  piVar3 = *(int **)(iVar4 + iVar2);
  *(undefined4 *)(this + 0x20) = DAT_000307c0;
  *(undefined4 *)(this + 0x18) = uVar1;
  *(undefined4 *)(this + 0x14) = uVar1;
  *(undefined4 *)(this + 0x10) = uVar1;
  *(undefined4 *)(this + 0x1c) = uVar1;
  *piVar3 = *piVar3 + 1;
  return this;
}
