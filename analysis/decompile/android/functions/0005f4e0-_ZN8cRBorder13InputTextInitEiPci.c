/*
 * mangled: _ZN8cRBorder13InputTextInitEiPci
 * demangled: cRBorder::InputTextInit(int, char*, int)
 * address: 0005f4e0
 * size: 200
 */

/* cRBorder::InputTextInit(int, char*, int) */

void __thiscall cRBorder::InputTextInit(cRBorder *this,int param_1,char *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;

  *(int *)(this + 0x704) = param_3;
  Rstrcpy((char *)(this + 0x6c4),param_2);
  iVar5 = 0;
  *(undefined4 *)(this + 0x6f4) = 0;
  *(undefined4 *)(this + 0x708) = 0;
  if (this[0x2c4] == (cRBorder)0x0) {
    iVar5 = 0;
  }
  else {
    iVar4 = 1;
    do {
      *(int *)(this + 0x708) = iVar4;
      iVar5 = iVar5 + 1;
      *(int *)(this + 0x6f4) = iVar5;
      iVar1 = iVar4 + 0x2c4;
      iVar4 = iVar4 + 1;
    } while (this[iVar1] != (cRBorder)0x0);
  }
  this[iVar5 + 0x2c4] = (cRBorder)0x7c;
  uVar2 = DAT_0005f5a8;
  *(int *)(this + 0x70c) = param_1;
  this[iVar5 + 0x2c5] = (cRBorder)0x0;
  *(undefined4 *)(this + 0x6f8) = 1;
  uVar3 = DAT_0005f5ac;
  *(undefined4 *)(this + 0x6fc) = uVar2;
  *(undefined4 *)(this + 0x700) = uVar3;
  RePosition(this);
  if ((param_3 & 0xcU) != 0) {
    cRInputOK::Init((cRInputOK *)(this + 0x2a0));
    return;
  }
  return;
}
