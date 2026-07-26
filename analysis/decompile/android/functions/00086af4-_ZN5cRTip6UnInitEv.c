/*
 * mangled: _ZN5cRTip6UnInitEv
 * demangled: cRTip::UnInit()
 * address: 00086af4
 * size: 116
 */

/* cRTip::UnInit() */

void __thiscall cRTip::UnInit(cRTip *this)

{
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0xc));
  if (*(cRBorder **)(this + 0x10) != (cRBorder *)0x0) {
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x10));
  }
  if (*(cRBorder **)(this + 0x14) != (cRBorder *)0x0) {
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x14));
  }
  *(undefined4 *)this = 0;
  return;
}
