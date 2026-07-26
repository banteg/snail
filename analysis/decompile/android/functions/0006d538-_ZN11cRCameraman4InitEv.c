/*
 * mangled: _ZN11cRCameraman4InitEv
 * demangled: cRCameraman::Init()
 * address: 0006d538
 * size: 108
 */

/* cRCameraman::Init() */

void __thiscall cRCameraman::Init(cRCameraman *this)

{
  undefined4 uVar1;
  int iVar2;

  iVar2 = DAT_0006d5ac;
  this[0xcc] = (cRCameraman)0x0;
  iVar2 = **(int **)(iVar2 + 0x6d55c + DAT_0006d5b0);
  *(int *)(this + 0xc0) = iVar2 + 0x81364;
  *(int *)(this + 0xc4) = iVar2 + 0x718a0;
  tMatrix::Identity((tMatrix *)(this + 0x80));
  tMatrix::Identity((tMatrix *)(this + 0x40));
  tMatrix::Identity((tMatrix *)this);
  uVar1 = DAT_0006d5a4;
  *(undefined4 *)(this + 0xd4) = DAT_0006d5a4;
  *(undefined4 *)(this + 0xd0) = uVar1;
  *(undefined4 *)(this + 200) = DAT_0006d5a8;
  return;
}
