/*
 * mangled: _ZN9cRWarning6UnInitEv
 * demangled: cRWarning::UnInit()
 * address: 0006f6bc
 * size: 36
 */

/* cRWarning::UnInit() */

void __thiscall cRWarning::UnInit(cRWarning *this)

{
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x14));
  return;
}
