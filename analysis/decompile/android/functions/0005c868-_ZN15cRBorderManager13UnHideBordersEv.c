/*
 * mangled: _ZN15cRBorderManager13UnHideBordersEv
 * demangled: cRBorderManager::UnHideBorders()
 * address: 0005c868
 * size: 12
 */

/* cRBorderManager::UnHideBorders() */

void __thiscall cRBorderManager::UnHideBorders(cRBorderManager *this)

{
  cRBorderStack::Perform((cRBorderStack *)(this + 0x2c),1);
  return;
}
