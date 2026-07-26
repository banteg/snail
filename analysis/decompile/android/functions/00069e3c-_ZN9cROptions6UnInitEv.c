/*
 * mangled: _ZN9cROptions6UnInitEv
 * demangled: cROptions::UnInit()
 * address: 00069e3c
 * size: 152
 */

/* cROptions::UnInit() */

void __thiscall cROptions::UnInit(cROptions *this)

{
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x10));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x1c));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x18));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x14));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x20));
  gRegisterSaveFile("asm.cfg",gConfig,0x130);
  return;
}
