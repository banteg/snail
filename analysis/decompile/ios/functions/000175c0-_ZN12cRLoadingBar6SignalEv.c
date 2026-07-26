/*
 * mangled: _ZN12cRLoadingBar6SignalEv
 * demangled: cRLoadingBar::Signal()
 * address: 000175c0
 * size: 212
 */

/* cRLoadingBar::Signal() */

void __thiscall cRLoadingBar::Signal(cRLoadingBar *this)

{
  undefined *this_00;
  int iVar1;
  int iVar2;
  uint in_fpscr;
  undefined4 uVar3;

  iVar1 = *(int *)(this + 0x1c);
  if (iVar1 == 8) {
    return;
  }
  iVar2 = *(int *)(this + 4);
  *(int *)(this + 4) = iVar2 + 1;
  if (*(int *)(PTR__gConfig_001b60d4 + 0xac) == 0) {
    *(undefined4 *)(PTR__gConfig_001b60d4 + 0xac) = 1;
    iVar1 = *(int *)(this + 0x1c);
  }
  this_00 = PTR__G0SplashManager_001b61d4;
  if (iVar1 != 3) {
    iVar2 = ((iVar2 + 1) * 100) / 0x422;
    if (0x5f < iVar2) {
      iVar2 = 100;
    }
    if (iVar1 == 6) {
      if (1 < iVar2 - *(int *)this) {
        uVar3 = VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
        *(undefined4 *)(PTR__G0SplashManager_001b61d4 + 0x20) = uVar3;
        *(int *)this = iVar2;
        wprintf("Signal %i (%i%%)\n",*(undefined4 *)(this + 4));
        cRSplashWindowManager::Render((cRSplashWindowManager *)this_00,*(float *)(this + 0x28));
        MacSwapBuffers();
        return;
      }
      return;
    }
    return;
  }
  *(undefined4 *)(this + 0x1c) = 4;
  this[0x24] = (cRLoadingBar)0x1;
  return;
}
