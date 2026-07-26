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
  int *piVar2;
  int iVar3;
  cRMouse in_r1;
  float *in_r2;
  float *in_r3;
  undefined8 uVar4;
  undefined4 local_18;
  undefined4 local_14;

  iVar1 = DAT_00031098;
  this = (cRMouse *)(uint)param_1;
  *(undefined4 *)(this + 0x30) = 0;
  uVar4 = ConvertScreenXY(this,param_2,param_3,in_r2,in_r3);
  iVar3 = DAT_0003109c;
  this[0x19] = in_r1;
  piVar2 = *(int **)(iVar1 + 0x31044 + iVar3);
  *(undefined4 *)(this + 0x1c) = local_14;
  iVar3 = *piVar2;
  *(undefined4 *)(this + 0x20) = local_18;
  if ((*(int *)(iVar3 + 0x718fc) != 2) ||
     (*(int *)(*(int *)(iVar1 + 0x31044 + DAT_000310a0) + 8) != 0)) {
    RShellSetMouse(0,(float)uVar4,(float)((ulonglong)uVar4 >> 0x20));
  }
  return;
}
