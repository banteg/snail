/*
 * mangled: _ZN8cRBorder10UnHideInitEv
 * demangled: cRBorder::UnHideInit()
 * address: 0005be94
 * size: 24
 */

/* cRBorder::UnHideInit() */

void __thiscall cRBorder::UnHideInit(cRBorder *this)

{
  *(undefined4 *)(this + 0x38) = 0x3f800000;
  *(uint *)(this + 0x194) = *(uint *)(this + 0x194) & 0xffffefff;
  return;
}
