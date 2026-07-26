/*
 * mangled: _ZN12cRTipManager10UnInitTipsEv
 * demangled: cRTipManager::UnInitTips()
 * address: 00086b70
 * size: 100
 */

/* cRTipManager::UnInitTips() */

void __thiscall cRTipManager::UnInitTips(cRTipManager *this)

{
  int iVar1;

  if (*(int *)(this + 0x2c) == 1) {
    cRTip::UnInit((cRTip *)(this + 0x2c));
    iVar1 = *(int *)(this + 0x4c);
  }
  else {
    iVar1 = *(int *)(this + 0x4c);
  }
  if (iVar1 == 1) {
    cRTip::UnInit((cRTip *)(this + 0x4c));
    if (*(int *)(this + 0x6c) != 1) {
      return;
    }
  }
  else if (*(int *)(this + 0x6c) != 1) {
    return;
  }
  cRTip::UnInit((cRTip *)(this + 0x6c));
  return;
}
