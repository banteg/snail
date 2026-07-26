/*
 * mangled: _ZN12cRTipManager6TipNewEP9cRTipDatab
 * demangled: cRTipManager::TipNew(cRTipData*, bool)
 * address: 00086a84
 * size: 104
 */

/* cRTipManager::TipNew(cRTipData*, bool) */

cRTip * __thiscall cRTipManager::TipNew(cRTipManager *this,cRTipData *param_1,bool param_2)

{
  int iVar1;

  iVar1 = 0;
  if (*(int *)(this + 0x2c) != 0) {
    if (*(int *)(this + 0x4c) == 0) {
      iVar1 = 1;
    }
    else {
      if (*(int *)(this + 0x6c) != 0) {
        RShellError("Run out of Tips");
        return (cRTip *)0x0;
      }
      iVar1 = 2;
    }
  }
  cRTip::Init((cRTip *)(this + iVar1 * 0x20 + 0x2c),param_1,param_2);
  return (cRTip *)(this + iVar1 * 0x20 + 0x2c);
}
