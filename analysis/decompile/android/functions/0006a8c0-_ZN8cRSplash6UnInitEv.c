/*
 * mangled: _ZN8cRSplash6UnInitEv
 * demangled: cRSplash::UnInit()
 * address: 0006a8c0
 * size: 56
 */

/* cRSplash::UnInit() */

void __thiscall cRSplash::UnInit(cRSplash *this)

{
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 8));
  *(undefined4 *)(Game + 0x15c) = 0xe;
  return;
}
