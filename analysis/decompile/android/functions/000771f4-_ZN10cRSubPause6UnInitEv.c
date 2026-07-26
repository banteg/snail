/*
 * mangled: _ZN10cRSubPause6UnInitEv
 * demangled: cRSubPause::UnInit()
 * address: 000771f4
 * size: 100
 */

/* cRSubPause::UnInit() */

void __thiscall cRSubPause::UnInit(cRSubPause *this)

{
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)this);
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 4));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 8));
  cRMouse::SetInActive((cRMouse *)(Game + 0x228));
  return;
}
