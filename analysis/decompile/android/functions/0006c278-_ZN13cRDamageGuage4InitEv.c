/*
 * mangled: _ZN13cRDamageGuage4InitEv
 * demangled: cRDamageGuage::Init()
 * address: 0006c278
 * size: 60
 */

/* cRDamageGuage::Init() */

void __thiscall cRDamageGuage::Init(cRDamageGuage *this)

{
  undefined4 uVar1;

  uVar1 = DAT_0006c2b4;
  *(undefined4 *)(this + 0x24) = DAT_0006c2b4;
  *(undefined4 *)(this + 0x1c) = uVar1;
  *(undefined4 *)(this + 0x20) = uVar1;
  *(undefined4 *)(this + 0x10) = uVar1;
  *(undefined4 *)(this + 4) = uVar1;
  this[0xc] = (cRDamageGuage)0x0;
  uVar1 = DAT_0006c2b8;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 8) = uVar1;
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 0x28) = DAT_0006c2bc;
  return;
}
