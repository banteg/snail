/*
 * mangled: _ZN10cRBackdrop8SetWorldEi
 * demangled: cRBackdrop::SetWorld(int)
 * address: 0003e154
 * size: 56
 */

/* cRBackdrop::SetWorld(int) */

void __thiscall cRBackdrop::SetWorld(cRBackdrop *this,int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;

  uVar1 = *(undefined4 *)(this + 0xc0);
  uVar2 = *(undefined4 *)(this + 0xe0);
  *(int *)(this + 0xc0) = param_1;
  *(int *)(this + 0xe0) = param_1;
  *(undefined4 *)(this + 0xbc) = uVar1;
  *(undefined4 *)(this + 0xdc) = uVar2;
  *(float *)(this + 0xb4) = 1.0 - *(float *)(this + 0xb4);
  *(float *)(this + 0xd4) = 1.0 - *(float *)(this + 0xd4);
  return;
}
