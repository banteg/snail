/*
 * mangled: _ZN7tMatrixmlERKS_
 * demangled: tMatrix::operator*(tMatrix const&)
 * address: 000275ec
 * size: 104
 */

/* tMatrix::TEMPNAMEPLACEHOLDERVALUE(tMatrix const&) */

tMatrix * __thiscall tMatrix::operator*(tMatrix *this,tMatrix *param_1)

{
  tMatrix *in_r2;
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

  local_50 = *(undefined4 *)param_1;
  uStack_4c = *(undefined4 *)(param_1 + 4);
  uStack_48 = *(undefined4 *)(param_1 + 8);
  uStack_44 = *(undefined4 *)(param_1 + 0xc);
  local_40 = *(undefined4 *)(param_1 + 0x10);
  uStack_3c = *(undefined4 *)(param_1 + 0x14);
  uStack_38 = *(undefined4 *)(param_1 + 0x18);
  uStack_34 = *(undefined4 *)(param_1 + 0x1c);
  local_30 = *(undefined4 *)(param_1 + 0x20);
  uStack_2c = *(undefined4 *)(param_1 + 0x24);
  uStack_28 = *(undefined4 *)(param_1 + 0x28);
  uStack_24 = *(undefined4 *)(param_1 + 0x2c);
  local_20 = *(undefined4 *)(param_1 + 0x30);
  uStack_1c = *(undefined4 *)(param_1 + 0x34);
  uStack_18 = *(undefined4 *)(param_1 + 0x38);
  uStack_14 = *(undefined4 *)(param_1 + 0x3c);
  Multiply(param_1,(tMatrix *)&local_50,in_r2);
  memmove(this,param_1,0x40);
  return this;
}
