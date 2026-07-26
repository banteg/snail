/*
 * mangled: _ZN10cRBackdrop6ChangeEP11cRLandscapeb
 * demangled: cRBackdrop::Change(cRLandscape*, bool)
 * address: 000412f8
 * size: 88
 */

/* cRBackdrop::Change(cRLandscape*, bool) */

void __thiscall cRBackdrop::Change(cRBackdrop *this,cRLandscape *param_1,bool param_2)

{
  undefined4 uVar1;

  if (*(int *)(param_1 + 0x84) != 0) {
    this[0x4d] = (cRBackdrop)0x0;
    this[0x58] = (cRBackdrop)0x1;
    *(undefined4 *)(this + 0x54) = *(undefined4 *)param_1;
    *(undefined4 *)(this + 0x5c) = *(undefined4 *)(param_1 + 0x19c);
    *(undefined4 *)(this + 0x60) = *(undefined4 *)(param_1 + 0x1a0);
    uVar1 = *(undefined4 *)(param_1 + 0x1a4);
    this[0x68] = (cRBackdrop)param_2;
    *(undefined4 *)(this + 100) = uVar1;
    *(undefined4 *)(this + 0x1358) = 1;
    return;
  }
  *(undefined4 *)(this + 0x1358) = 0;
  return;
}
