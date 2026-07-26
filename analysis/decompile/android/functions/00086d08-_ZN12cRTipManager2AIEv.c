/*
 * mangled: _ZN12cRTipManager2AIEv
 * demangled: cRTipManager::AI()
 * address: 00086d08
 * size: 100
 */

/* cRTipManager::AI() */

void __thiscall cRTipManager::AI(cRTipManager *this)

{
  int iVar1;

  if (*(int *)(this + 0x2c) == 1) {
    cRTip::AI((cRTip *)(this + 0x2c));
    iVar1 = *(int *)(this + 0x4c);
  }
  else {
    iVar1 = *(int *)(this + 0x4c);
  }
  if (iVar1 == 1) {
    cRTip::AI((cRTip *)(this + 0x4c));
    if (*(int *)(this + 0x6c) != 1) {
      return;
    }
  }
  else if (*(int *)(this + 0x6c) != 1) {
    return;
  }
  cRTip::AI((cRTip *)(this + 0x6c));
  return;
}
