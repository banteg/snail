/*
 * mangled: _ZN10cRViewportC2Ev
 * demangled: cRViewport::cRViewport()
 * address: 00086e30
 * size: 60
 */

/* cRViewport::cRViewport() */

void __thiscall cRViewport::cRViewport(cRViewport *this)

{
  undefined4 uVar1;

  uVar1 = DAT_00086e6c;
  *(undefined4 *)(this + 0x2c) = DAT_00086e6c;
  *(undefined4 *)(this + 0xc) = uVar1;
  *(undefined4 *)(this + 0x10) = uVar1;
  *(undefined4 *)(this + 0x28) = uVar1;
  this[0x24] = (cRViewport)0x1;
  uVar1 = DAT_00086e70;
  *(undefined4 *)(this + 0x18) = DAT_00086e70;
  *(undefined4 *)(this + 0x14) = uVar1;
  *(undefined4 *)(this + 8) = 0;
  *(undefined4 *)(this + 0x1c) = DAT_00086e74;
  return;
}
