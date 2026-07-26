/*
 * mangled: _ZN6cRTime4ZeroEv
 * demangled: cRTime::Zero()
 * address: 0006c300
 * size: 36
 */

/* cRTime::Zero() */

void __thiscall cRTime::Zero(cRTime *this)

{
  undefined4 uVar1;

  uVar1 = DAT_0006c324;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x14) = uVar1;
  *(undefined4 *)this = uVar1;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0;
  *(undefined4 *)(this + 0xc) = 0;
  return;
}
