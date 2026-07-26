/*
 * mangled: _ZN8cRGalaxy6UnInitEv
 * demangled: cRGalaxy::UnInit()
 * address: 0005a4c8
 * size: 348
 */

/* cRGalaxy::UnInit() */

void __thiscall cRGalaxy::UnInit(cRGalaxy *this)

{
  *(undefined4 *)this = 0;
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e2c));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e30));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e28));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e40));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e44));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e4c));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e48));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e50));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e54));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e68));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e5c));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e64));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8e60));
  return;
}
