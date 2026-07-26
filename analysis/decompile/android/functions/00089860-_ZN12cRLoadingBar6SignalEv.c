/*
 * mangled: _ZN12cRLoadingBar6SignalEv
 * demangled: cRLoadingBar::Signal()
 * address: 00089860
 * size: 176
 */

/* cRLoadingBar::Signal() */

void __thiscall cRLoadingBar::Signal(cRLoadingBar *this)

{
  int iVar1;
  uint in_fpscr;

  if (this[0x34] == (cRLoadingBar)0x0) {
    return;
  }
  if (this[0xbd] == (cRLoadingBar)0x0) {
    iVar1 = *(int *)(this + 4);
    *(int *)(this + 4) = iVar1 + 1;
    if (gConfig._172_4_ == 0) {
      gConfig._172_4_ = 1;
    }
    iVar1 = __divsi3(((iVar1 + 1) - *(int *)(this + 8)) * 100,0x4c8 - *(int *)(this + 8));
    if (99 < iVar1) {
      iVar1 = 100;
    }
    if (G0SplashManager[0x45] != '\0') {
      if (0 < iVar1 - *(int *)this) {
        G0SplashManager._160_4_ = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
        *(int *)this = iVar1;
        this[0xd3] = (cRLoadingBar)0x1;
        return;
      }
      return;
    }
    return;
  }
  return;
}
