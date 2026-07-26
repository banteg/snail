/*
 * mangled: _ZN15cRBorderManager11HideBordersEv
 * demangled: cRBorderManager::HideBorders()
 * address: 0005c874
 * size: 12
 */

/* cRBorderManager::HideBorders() */

void __thiscall cRBorderManager::HideBorders(cRBorderManager *this)

{
  cRBorderStack::Perform((cRBorderStack *)(this + 0x2c),0);
  return;
}
