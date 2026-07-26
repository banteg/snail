/*
 * mangled: _ZN12cRLoadingBar2AIEv
 * demangled: cRLoadingBar::AI()
 * address: 0008a5b0
 * size: 168
 */

/* cRLoadingBar::AI() */

void __thiscall cRLoadingBar::AI(cRLoadingBar *this)

{
  float fVar1;

  if (this[0x34] != (cRLoadingBar)0x0) {
    this[0x34] = (cRLoadingBar)0x0;
    if (this[0x35] != (cRLoadingBar)0x0) {
      if (this[0x36] != (cRLoadingBar)0x0) {
        cRSplashManager::SetSplash((cRSplashManager *)G0SplashManager,(char *)(this + 0x37));
        G0SplashManager[0x45] = 0;
      }
      if (this[0x77] != (cRLoadingBar)0x0) {
        cRSplashManager::SetBar((cRSplashManager *)G0SplashManager,(char *)(this + 0x78));
      }
      this[0x35] = (cRLoadingBar)0x0;
    }
    fVar1 = (float)ScriptAI(this);
    cRSplashManager::Render(fVar1);
    this[0x34] = (cRLoadingBar)0x1;
    return;
  }
  return;
}
