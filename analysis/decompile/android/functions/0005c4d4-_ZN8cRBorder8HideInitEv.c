/*
 * mangled: _ZN8cRBorder8HideInitEv
 * demangled: cRBorder::HideInit()
 * address: 0005c4d4
 * size: 40
 */

/* cRBorder::HideInit() */

void __thiscall cRBorder::HideInit(cRBorder *this)

{
  undefined4 uVar1;

  uVar1 = DAT_0005c4fc;
  if ((*(uint *)(this + 0x194) & 0x1000) != 0) {
    return;
  }
  *(uint *)(this + 0x194) = *(uint *)(this + 0x194) | 0x1000;
  *(undefined4 *)(this + 0x38) = uVar1;
  cRToolTip::ReSet((cRToolTip *)(this + 0x284));
  return;
}
