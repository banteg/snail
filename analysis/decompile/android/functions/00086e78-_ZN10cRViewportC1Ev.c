/*
 * mangled: _ZN10cRViewportC1Ev
 * demangled: cRViewport::cRViewport()
 * address: 00086e78
 * size: 60
 */

/* cRViewport::cRViewport() */

void __thiscall cRViewport::cRViewport(cRViewport *this)

{
  undefined4 uVar1;

  uVar1 = DAT_00086eb4;
  *(undefined4 *)(this + 0x2c) = DAT_00086eb4;
  *(undefined4 *)(this + 0xc) = uVar1;
  *(undefined4 *)(this + 0x10) = uVar1;
  *(undefined4 *)(this + 0x28) = uVar1;
  this[0x24] = (cRViewport)0x1;
  uVar1 = DAT_00086eb8;
  *(undefined4 *)(this + 0x18) = DAT_00086eb8;
  *(undefined4 *)(this + 0x14) = uVar1;
  *(undefined4 *)(this + 8) = 0;
  *(undefined4 *)(this + 0x1c) = DAT_00086ebc;
  return;
}
