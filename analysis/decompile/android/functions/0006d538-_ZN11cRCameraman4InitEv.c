/*
 * mangled: _ZN11cRCameraman4InitEv
 * demangled: cRCameraman::Init()
 * address: 0006d538
 * size: 108
 */

/* cRCameraman::Init() */

void __thiscall cRCameraman::Init(cRCameraman *this)

{
  int iVar1;

  this[0xcc] = (cRCameraman)0x0;
  iVar1 = Game + 0x718a0;
  *(int *)(this + 0xc0) = Game + 0x81364;
  *(int *)(this + 0xc4) = iVar1;
  tMatrix::Identity((tMatrix *)(this + 0x80));
  tMatrix::Identity((tMatrix *)(this + 0x40));
  tMatrix::Identity((tMatrix *)this);
  *(undefined4 *)(this + 0xd4) = 0;
  *(undefined4 *)(this + 0xd0) = 0;
  *(undefined4 *)(this + 200) = 0x42f00000;
  return;
}
