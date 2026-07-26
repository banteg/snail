/*
 * mangled: _ZN6cRExit6UnInitEv
 * demangled: cRExit::UnInit()
 * address: 000624ec
 * size: 116
 */

/* cRExit::UnInit() */

void __thiscall cRExit::UnInit(cRExit *this)

{
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x10));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x14));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x18));
  cRBorderManager::UnHideBorders((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(Game + 0x15c) = *(undefined4 *)(this + 8);
  return;
}
