/*
 * mangled: _ZN10cRBackdrop8SetWorldEi
 * demangled: cRBackdrop::SetWorld(int)
 * address: 0003e154
 * size: 56
 */

/* cRBackdrop::SetWorld(int) */

void __thiscall cRBackdrop::SetWorld(cRBackdrop *this,int param_1)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;

  fVar1 = DAT_0003e18c;
  fVar4 = DAT_0003e18c - *(float *)(this + 0xb4);
  uVar2 = *(undefined4 *)(this + 0xc0);
  uVar3 = *(undefined4 *)(this + 0xe0);
  *(int *)(this + 0xc0) = param_1;
  *(int *)(this + 0xe0) = param_1;
  *(undefined4 *)(this + 0xbc) = uVar2;
  *(undefined4 *)(this + 0xdc) = uVar3;
  *(float *)(this + 0xb4) = fVar4;
  *(float *)(this + 0xd4) = fVar1 - *(float *)(this + 0xd4);
  return;
}
