/*
 * mangled: _ZN7cRMouse11ClickiPhoneEbff
 * demangled: cRMouse::ClickiPhone(bool, float, float)
 * address: 00031004
 * size: 148
 */

/* cRMouse::ClickiPhone(bool, float, float) */

void cRMouse::ClickiPhone(bool param_1,float param_2,float param_3)

{
  int iVar1;
  cRMouse *this;
  cRMouse in_r1;
  float *in_r2;
  float *in_r3;
  undefined8 uVar2;
  undefined4 local_18;
  undefined4 local_14;

  this = (cRMouse *)(uint)param_1;
  *(undefined4 *)(this + 0x30) = 0;
  uVar2 = ConvertScreenXY(this,param_2,param_3,in_r2,in_r3);
  this[0x19] = in_r1;
  *(undefined4 *)(this + 0x1c) = local_14;
  iVar1 = Game;
  *(undefined4 *)(this + 0x20) = local_18;
  if ((*(int *)(iVar1 + 0x718fc) != 2) || (gConfig._8_4_ != 0)) {
    RShellSetMouse(0,(float)uVar2,(float)((ulonglong)uVar2 >> 0x20));
  }
  return;
}
