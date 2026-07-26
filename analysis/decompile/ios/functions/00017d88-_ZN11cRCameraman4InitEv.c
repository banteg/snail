/*
 * mangled: _ZN11cRCameraman4InitEv
 * demangled: cRCameraman::Init()
 * address: 00017d88
 * size: 108
 */

/* cRCameraman::Init() */

void __thiscall cRCameraman::Init(cRCameraman *this)

{
  undefined *puVar1;

  puVar1 = PTR__Game_001b60b8;
  *(int *)(this + 0xc0) = *(int *)PTR__Game_001b60b8 + 0x81fc0;
  *(int *)(this + 0xc4) = *(int *)puVar1 + 0x72b78;
  this[0xcc] = (cRCameraman)0x0;
  tMatrix::Identity((tMatrix *)(this + 0x80));
  tMatrix::Identity((tMatrix *)(this + 0x40));
  tMatrix::Identity((tMatrix *)this);
  *(undefined4 *)(this + 0xd0) = 0;
  *(undefined4 *)(this + 0xd4) = 0;
  *(undefined4 *)(this + 200) = 0x42f00000;
  return;
}
