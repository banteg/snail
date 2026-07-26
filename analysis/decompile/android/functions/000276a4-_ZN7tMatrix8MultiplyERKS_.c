/*
 * mangled: _ZN7tMatrix8MultiplyERKS_
 * demangled: tMatrix::Multiply(tMatrix const&)
 * address: 000276a4
 * size: 4
 */

/* tMatrix::Multiply(tMatrix const&) */

void __thiscall tMatrix::Multiply(tMatrix *this,tMatrix *param_1)

{
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;

  uStack_50 = *(undefined4 *)this;
  uStack_4c = *(undefined4 *)(this + 4);
  uStack_48 = *(undefined4 *)(this + 8);
  uStack_44 = *(undefined4 *)(this + 0xc);
  uStack_40 = *(undefined4 *)(this + 0x10);
  uStack_3c = *(undefined4 *)(this + 0x14);
  uStack_38 = *(undefined4 *)(this + 0x18);
  uStack_34 = *(undefined4 *)(this + 0x1c);
  uStack_30 = *(undefined4 *)(this + 0x20);
  uStack_2c = *(undefined4 *)(this + 0x24);
  uStack_28 = *(undefined4 *)(this + 0x28);
  uStack_24 = *(undefined4 *)(this + 0x2c);
  uStack_20 = *(undefined4 *)(this + 0x30);
  uStack_1c = *(undefined4 *)(this + 0x34);
  uStack_18 = *(undefined4 *)(this + 0x38);
  uStack_14 = *(undefined4 *)(this + 0x3c);
  Multiply(this,(tMatrix *)&uStack_50,param_1);
  return;
}
