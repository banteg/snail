/*
 * mangled: _ZN10cRFaceQuad11RotateUVCCWEv
 * demangled: cRFaceQuad::RotateUVCCW()
 * address: 00011a70
 * size: 68
 */

/* cRFaceQuad::RotateUVCCW() */

void __thiscall cRFaceQuad::RotateUVCCW(cRFaceQuad *this)

{
  undefined4 uVar1;
  undefined4 uVar2;

  uVar1 = *(undefined4 *)(this + 0x10);
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(this + 0x18);
  *(undefined4 *)(this + 0x18) = *(undefined4 *)(this + 0x20);
  uVar2 = *(undefined4 *)(this + 0x28);
  *(undefined4 *)(this + 0x28) = uVar1;
  uVar1 = *(undefined4 *)(this + 0x14);
  *(undefined4 *)(this + 0x20) = uVar2;
  *(undefined4 *)(this + 0x14) = *(undefined4 *)(this + 0x1c);
  *(undefined4 *)(this + 0x1c) = *(undefined4 *)(this + 0x24);
  uVar2 = *(undefined4 *)(this + 0x2c);
  *(undefined4 *)(this + 0x2c) = uVar1;
  *(undefined4 *)(this + 0x24) = uVar2;
  return;
}
