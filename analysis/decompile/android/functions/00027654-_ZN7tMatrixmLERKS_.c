/*
 * mangled: _ZN7tMatrixmLERKS_
 * demangled: tMatrix::operator*=(tMatrix const&)
 * address: 00027654
 * size: 80
 */

/* tMatrix::TEMPNAMEPLACEHOLDERVALUE(tMatrix const&) */

void __thiscall tMatrix::operator*=(tMatrix *this,tMatrix *param_1)

{
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;

  local_50 = *(undefined4 *)this;
  uStack_4c = *(undefined4 *)(this + 4);
  uStack_48 = *(undefined4 *)(this + 8);
  uStack_44 = *(undefined4 *)(this + 0xc);
  local_40 = *(undefined4 *)(this + 0x10);
  uStack_3c = *(undefined4 *)(this + 0x14);
  uStack_38 = *(undefined4 *)(this + 0x18);
  uStack_34 = *(undefined4 *)(this + 0x1c);
  local_30 = *(undefined4 *)(this + 0x20);
  uStack_2c = *(undefined4 *)(this + 0x24);
  uStack_28 = *(undefined4 *)(this + 0x28);
  uStack_24 = *(undefined4 *)(this + 0x2c);
  local_20 = *(undefined4 *)(this + 0x30);
  uStack_1c = *(undefined4 *)(this + 0x34);
  uStack_18 = *(undefined4 *)(this + 0x38);
  uStack_14 = *(undefined4 *)(this + 0x3c);
  Multiply(this,(tMatrix *)&local_50,param_1);
  return;
}
