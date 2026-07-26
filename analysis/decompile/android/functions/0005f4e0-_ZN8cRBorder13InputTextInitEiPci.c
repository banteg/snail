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
  int iVar2;
  int iVar3;

  *(int *)(this + 0x704) = param_3;
  Rstrcpy((char *)(this + 0x6c4),param_2);
  iVar3 = 0;
  *(undefined4 *)(this + 0x6f4) = 0;
  *(undefined4 *)(this + 0x708) = 0;
  if (this[0x2c4] == (cRBorder)0x0) {
    iVar3 = 0;
  }
  else {
    iVar2 = 1;
    do {
      *(int *)(this + 0x708) = iVar2;
      iVar3 = iVar3 + 1;
      *(int *)(this + 0x6f4) = iVar3;
      iVar1 = iVar2 + 0x2c4;
      iVar2 = iVar2 + 1;
    } while (this[iVar1] != (cRBorder)0x0);
  }
  this[iVar3 + 0x2c4] = (cRBorder)0x7c;
  *(int *)(this + 0x70c) = param_1;
  this[iVar3 + 0x2c5] = (cRBorder)0x0;
  *(undefined4 *)(this + 0x6f8) = 1;
  *(undefined4 *)(this + 0x6fc) = 0;
  *(undefined4 *)(this + 0x700) = 0x3daaaaab;
  RePosition(this);
  if ((param_3 & 0xcU) != 0) {
    cRInputOK::Init((cRInputOK *)(this + 0x2a0));
    return;
  }
  return;
}
