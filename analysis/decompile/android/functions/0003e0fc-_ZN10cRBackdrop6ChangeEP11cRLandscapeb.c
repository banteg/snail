/*
 * mangled: _ZN10cRBackdrop6ChangeEP11cRLandscapeb
 * demangled: cRBackdrop::Change(cRLandscape*, bool)
 * address: 0003e0fc
 * size: 76
 */

/* cRBackdrop::Change(cRLandscape*, bool) */

void __thiscall cRBackdrop::Change(cRBackdrop *this,cRLandscape *param_1,bool param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;

  if (*(int *)(param_1 + 0x84) != 0) {
    uVar1 = *(undefined4 *)param_1;
    *(undefined4 *)(this + 0x68) = *(undefined4 *)(param_1 + 0x19c);
    *(undefined4 *)(this + 0x80) = 1;
    uVar2 = *(undefined4 *)(param_1 + 0x1a0);
    this[100] = (cRBackdrop)0x1;
    *(undefined4 *)(this + 0x6c) = uVar2;
    uVar2 = *(undefined4 *)(param_1 + 0x1a4);
    this[0x74] = (cRBackdrop)param_2;
    *(undefined4 *)(this + 0x70) = uVar2;
    *(undefined4 *)(this + 0x60) = uVar1;
    this[0x59] = (cRBackdrop)0x0;
    return;
  }
  *(undefined4 *)(this + 0x80) = 0;
  return;
}
